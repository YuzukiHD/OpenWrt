/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * sunxi_timer_alarm.c
 * (C) Copyright 2018-2024
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Frank <frank@allwinnertech.com>
 * Martin <wuyan.martin@allwinnertech.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/bitops.h>
#include <linux/clk.h>
#include <linux/export.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/pwm.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/time.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/pm_wakeirq.h>
#include <linux/pm_domain.h>

/*
static const unsigned long long prescale[] = {
	1, 2, 4, 8, 16, 32, 64, 128
};
*/
static const unsigned long long clkrate[] = {
	32768,         //32.768KHz  max time: 2^32 / 32768 * 128 seconds = 194 days
	24*1000*1000,  //24MHz      max time: 2^32 / 24M * 128 seconds = 6.36 hours
};

#define PRESCALE_INDEX		(7)
#define CLKRATE_INDEX		(0)
#define TIMER_IRQ_EN_REG	0x00
#define TIMER_IRQ_EN(val)		BIT(val)
#define TIMER_IRQ_ST_REG	0x04
#define TIMER_CTL_REG(val)	(0x10 * val + 0x10)
#define TIMER_CTL_ENABLE		BIT(0)
#define TIMER_CTL_RELOAD		BIT(1)
#define TIMER_CTL_CLK_SRC(val)		(((val) & 0x3) << 2)
#define TIMER_CTL_CLK_SRC_OSC24M		(1)
#define TIMER_CTL_CLK_PRES(val)		(((val) & 0x7) << 4)
#define TIMER_CTL_ONESHOT		BIT(7)
#define TIMER_INTVAL_REG(val)	(0x10 * (val) + 0x14)
#define TIMER_CNTVAL_REG(val)	(0x10 * (val) + 0x18)

//#define REG_TO_SEC(reg, prescale_index, clkrate_index)		((unsigned long long)(((unsigned long long)reg << prescale_index) / clkrate[clkrate_index]))  //unit: seconds
#define SEC_TO_REG(sec, prescale_index, clkrate_index)		((unsigned int)(((unsigned long long)sec * clkrate[clkrate_index]) >> prescale_index))

struct _alarm_res {
	void __iomem *timer_base;
	unsigned long jiffies_start;  //for printing
	unsigned long long interval;  //timer's interrupt interval (unit: seconds)
	void *store_mem;
	unsigned int size;
	int irq;
	spinlock_t lock;
};

static struct _alarm_res alarm_res;

static void set_alarm_regs(u8 timer)
{
	u32 val = 0;
	unsigned long flags;

	spin_lock_irqsave(&alarm_res.lock, flags);

	/* set Timer1's interval value */
	val = SEC_TO_REG(alarm_res.interval, PRESCALE_INDEX, CLKRATE_INDEX);

	writel(val, alarm_res.timer_base + TIMER_INTVAL_REG(timer));

	/*
	 *	set timer mode (0:continuous, 1:single-shot)
	 *	set clock pre-scale (0x0:1, 0x1:2, 0x2:4, 0x3:8, 0x4:16, 0x5:32, 0x6:64, 0x7:128)
	 *	set clock source (0x0:LOSC, 0x1:OSC24M)
	 *	enable reload value
	 */
	val = (0x1 << 7) | (PRESCALE_INDEX << 4) | (CLKRATE_INDEX << 2) | (TIMER_CTL_RELOAD);

	writel(val, alarm_res.timer_base + TIMER_CTL_REG(timer));

	while (!(readl(alarm_res.timer_base + TIMER_CTL_REG(timer)) & 0x2))
		;

	/* enable interrupt */
	writel(TIMER_IRQ_EN(timer), alarm_res.timer_base);

	val = readl(alarm_res.timer_base + TIMER_CTL_REG(timer));
	writel(val | TIMER_CTL_ENABLE | TIMER_CTL_RELOAD,
	       alarm_res.timer_base + TIMER_CTL_REG(timer));
	pr_debug("%s(): expect interval = %llus\n", __func__, alarm_res.interval);
	alarm_res.jiffies_start = jiffies;

	spin_unlock_irqrestore(&alarm_res.lock, flags);
}

static void clear_alarm_regs(u8 timer)
{
	unsigned long flags;
	u32 val = readl(alarm_res.timer_base + TIMER_CTL_REG(timer));

	pr_debug("%s()\n", __func__);

	spin_lock_irqsave(&alarm_res.lock, flags);

	writel(val & ~TIMER_CTL_ENABLE, alarm_res.timer_base + TIMER_CTL_REG(timer));
	writel(0, alarm_res.timer_base + TIMER_INTVAL_REG(timer));	//clear interval value
	writel(0, alarm_res.timer_base + TIMER_CNTVAL_REG(timer));	//clear current  value

	writel((1 << timer), alarm_res.timer_base + TIMER_IRQ_ST_REG);  //clear Timer1's IRQ pending status
	spin_unlock_irqrestore(&alarm_res.lock, flags);
}

static ssize_t
interval_show(struct class *class, struct class_attribute *attr, char *buf)
{
	unsigned long long value = 0;

	value = alarm_res.interval;
	return sprintf(buf, "%llu\n", value);
}

static ssize_t
interval_store(struct class *class, struct class_attribute *attr,
	   const char *buf, size_t count)
{
	int err = 0;
	unsigned long long value = 0;

	err = kstrtoull(buf, 10, &value);
	if (err) {
		pr_err("%s(): ERROR: invalid value\n", __func__);
		return -EINVAL;
	}

	alarm_res.interval = value;
	return count;
}

static struct class_attribute timer_alarm_attrs[] = {
	__ATTR(interval, S_IWUSR | S_IRUGO, interval_show, interval_store),
};

static struct class timer_alarm_class = {
	.name = "timer_alarm",
	.owner = THIS_MODULE,
};

static irqreturn_t alarm_interrupt(int irq, void *dev_id)
{

	writel((1 << 1), alarm_res.timer_base + TIMER_IRQ_ST_REG);
	pr_debug("%s(): actual interval = %lus\n",
			__func__, (jiffies - alarm_res.jiffies_start) / HZ);  //note: jiffies does not update when CPU is sleeping
	alarm_res.jiffies_start = jiffies;  //for continuous mode

	return IRQ_HANDLED;
}

static int alarm_probe(struct platform_device *pdev)
{

	struct device *dev = &pdev->dev;
	struct resource res;
	struct device_node *np = pdev->dev.of_node;
	int i, err = 0;

	dev_dbg(dev, "%s()\n", __func__);

	alarm_res.timer_base = of_iomap(np, 0);
	if (!alarm_res.timer_base) {
		pr_crit("Can't map registers");
		return -ENXIO;
	}
	if (of_address_to_resource(np, 0, &res))
		return -EINVAL;
	alarm_res.jiffies_start = 0;
	alarm_res.interval = 0;
	alarm_res.size = resource_size(&res);
	alarm_res.store_mem = devm_kmalloc(dev, alarm_res.size, GFP_KERNEL);
	if (!alarm_res.store_mem) {
		printk("alloc memory failed!\n");
		return -ENOMEM;
	}
	spin_lock_init(&alarm_res.lock);

	alarm_res.irq = irq_of_parse_and_map(np, 0);
	if (!alarm_res.irq) {
		dev_err(dev, "parse IRQ failed\n");
		return -EINVAL;
	}

	if (of_property_read_bool(np, "wakeup-source")) {
		err = device_init_wakeup(dev, true);
		if (unlikely(err)) {
			dev_err(dev, "device_init_wakeup() failed\n");
			return err;
		}
		if (!device_can_wakeup(dev)) {
			dev_err(dev, "not a wakup device\n");
			return -EINVAL;
		}
		err = dev_pm_set_wake_irq(dev, alarm_res.irq);
		if (unlikely(err)) {
			dev_err(dev, "dev_pm_set_wake_irq() failed\n");
			return err;
		}
	} else {
		dev_err(dev, "cannot find wakeup-source\n");
		return -EINVAL;
	}

	err = devm_request_irq(dev, alarm_res.irq, alarm_interrupt, __IRQF_TIMER | IRQF_NO_THREAD, "alarm", dev);
	if (unlikely(err)) {
		dev_err(dev, "devm_request_irq() failed\n");
		return err;
	}

	//use sysfs for user space interaction
	err = class_register(&timer_alarm_class);
	if (unlikely(err)) {
		dev_err(dev, "class_register() failed\n");
		return err;
	}

	for (i = 0; i < ARRAY_SIZE(timer_alarm_attrs); i++) {
		err = class_create_file(&timer_alarm_class, &timer_alarm_attrs[i]);
		if (err) {
			dev_err(dev, "class_create_file() failed\n");
			while (i--)
				class_remove_file(&timer_alarm_class, &timer_alarm_attrs[i]);
			class_unregister(&timer_alarm_class);
			return err;
		}
	}

	dev_dbg(dev, "sunxi timer alarm probed success\n");
	return 0;
}

static int alarm_remove (struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int i;

	dev_dbg(dev, "%s()\n", __func__);

	clear_alarm_regs(1);
	dev_pm_clear_wake_irq(dev);
	device_init_wakeup(dev, false);

	for (i = 0; i < ARRAY_SIZE(timer_alarm_attrs); i++)
		class_remove_file(&timer_alarm_class, &timer_alarm_attrs[i]);
	class_unregister(&timer_alarm_class);

	return 0;
}

int sunxi_alarm_suspend(struct device *dev)
{
	memcpy(alarm_res.store_mem, alarm_res.timer_base, alarm_res.size);
	clear_alarm_regs(1);
	if (alarm_res.interval)
		set_alarm_regs(1);
	return 0;
}

int sunxi_alarm_resume(struct device *dev)
{
	clear_alarm_regs(1);
	memcpy(alarm_res.timer_base, alarm_res.store_mem, alarm_res.size);
	return 0;
}

static const struct of_device_id dt_ids[] = {
	{ .compatible = "allwinner,timer_alarm"},
	{},
};

MODULE_DEVICE_TABLE(of, dt_ids);

const struct dev_pm_ops sunxi_alarm_pm_ops = {
	.suspend = sunxi_alarm_suspend,
	.resume = sunxi_alarm_resume,
};

static struct platform_driver alarm_driver = {
	.driver = {
		.name = "timer_alarm",
		.pm = &sunxi_alarm_pm_ops,
		.of_match_table = of_match_ptr(dt_ids),
	},
	.probe  = alarm_probe,
	.remove = alarm_remove,
};

static int sunxi_alarm_init(void)
{
	int ret;

	ret = platform_driver_register(&alarm_driver);
	if (ret)
		pr_err("platform_driver_register() failed: %d\n", ret);

	return ret;
}

static void sunxi_alarm_exit(void)
{
	platform_driver_unregister(&alarm_driver);
}

module_init(sunxi_alarm_init);
module_exit(sunxi_alarm_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Frank & Martin");
MODULE_DESCRIPTION("Allwinner timer alarm");
MODULE_VERSION("1.0.1");
