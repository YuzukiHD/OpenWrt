/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * (C) Copyright 2015-2020
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Wim Hwang <huangwei@allwinnertech.com>
 *
 * sunxi gpio utils
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#ifndef __SW_GPIO_H
#define __SW_GPIO_H

#define SUNXI_PINCTRL	"pio"
#define SUNXI_R_PINCTRL	"r_pio"
#include <linux/pinctrl/pinconf-generic.h>

/* pin group base number name space,
 * the max pin number : 26*32=832.
 */
#define SUNXI_BANK_SIZE 32
#define SUNXI_PA_BASE	0
#define SUNXI_PB_BASE	32
#define SUNXI_PC_BASE	64
#define SUNXI_PD_BASE	96
#define SUNXI_PE_BASE	128
#define SUNXI_PF_BASE	160
#define SUNXI_PG_BASE	192
#define SUNXI_PH_BASE	224
#define SUNXI_PI_BASE	256
#define SUNXI_PJ_BASE	288
#define SUNXI_PK_BASE	320
#define SUNXI_PL_BASE	352
#define SUNXI_PM_BASE	384
#define SUNXI_PN_BASE	416
#define SUNXI_PO_BASE	448
#define AXP_PIN_BASE	1024

#define SUNXI_PIN_NAME_MAX_LEN	8

/* sunxi gpio name space */
#define GPIOA(n)	(SUNXI_PA_BASE + (n))
#define GPIOB(n)	(SUNXI_PB_BASE + (n))
#define GPIOC(n)	(SUNXI_PC_BASE + (n))
#define GPIOD(n)	(SUNXI_PD_BASE + (n))
#define GPIOE(n)	(SUNXI_PE_BASE + (n))
#define GPIOF(n)	(SUNXI_PF_BASE + (n))
#define GPIOG(n)	(SUNXI_PG_BASE + (n))
#define GPIOH(n)	(SUNXI_PH_BASE + (n))
#define GPIOI(n)	(SUNXI_PI_BASE + (n))
#define GPIOJ(n)	(SUNXI_PJ_BASE + (n))
#define GPIOK(n)	(SUNXI_PK_BASE + (n))
#define GPIOL(n)	(SUNXI_PL_BASE + (n))
#define GPIOM(n)	(SUNXI_PM_BASE + (n))
#define GPION(n)	(SUNXI_PN_BASE + (n))
#define GPIOO(n)	(SUNXI_PO_BASE + (n))
#define GPIO_AXP(n)	(AXP_PIN_BASE  + (n))

/* sunxi specific input/output/eint functions */
#define SUNXI_PIN_INPUT_FUNC	(0)
#define SUNXI_PIN_OUTPUT_FUNC	(1)
#define SUNXI_PIN_EINT_FUNC	(6)
#define SUNXI_PIN_IO_DISABLE	(7)

/* axp group base number name space,
 * axp pinctrl number space coherent to sunxi-pinctrl.
 */
#define AXP_PINCTRL	        "axp-pinctrl"
#define AXP_CFG_GRP		(0xFFFF)
#define AXP_PIN_INPUT_FUNC	(0)
#define AXP_PIN_OUTPUT_FUNC	(1)
#define IS_AXP_PIN(pin)		(pin >= AXP_PIN_BASE)

/* sunxi specific pull up/down */
enum sunxi_pull_up_down {
	SUNXI_PULL_DISABLE = 0,
	SUNXI_PULL_UP,
	SUNXI_PULL_DOWN,
};

/* sunxi specific data types */
enum sunxi_data_type {
	SUNXI_DATA_LOW = 0,
	SUNXI_DATA_HIGH = 0,
};

/* sunxi specific pull status */
enum sunxi_pin_pull {
	SUNXI_PIN_PULL_DISABLE	= 0x00,
	SUNXI_PIN_PULL_UP	= 0x01,
	SUNXI_PIN_PULL_DOWN	= 0x02,
	SUNXI_PIN_PULL_RESERVED	= 0x03,
};

/* sunxi specific driver levels */
enum sunxi_pin_drv_level {
	SUNXI_DRV_LEVEL0 = 10,
	SUNXI_DRV_LEVEL1 = 20,
	SUNXI_DRV_LEVEL2 = 30,
	SUNXI_DRV_LEVEL3 = 40,
};

/* sunxi specific data bit status */
enum sunxi_pin_data_status {
	SUNXI_PIN_DATA_LOW  = 0x00,
	SUNXI_PIN_DATA_HIGH = 0x01,
};

/* sunxi pin interrupt trigger mode */
enum sunxi_pin_int_trigger_mode {
	SUNXI_PIN_EINT_POSITIVE_EDGE   =   0x0,
	SUNXI_PIN_EINT_NEGATIVE_EDGE   =   0x1,
	SUNXI_PIN_EINT_HIGN_LEVEL      =   0x2,
	SUNXI_PIN_EINT_LOW_LEVEL       =   0x3,
	SUNXI_PIN_EINT_DOUBLE_EDGE     =   0x4
};

/* the source clock of pin int */
enum sunxi_pin_int_source_clk {
	SUNXI_PIN_INT_SRC_CLK_32K = 0x0,
	SUNXI_PIN_INT_SRC_CLK_24M = 0x1
};

/*
 * pin configuration (pull up/down and drive strength) type and its value are
 * packed together into a 32-bits. The lower 8-bits represent the configuration
 * type and the upper 24-bits hold the value of the configuration type.
 */
#define SUNXI_PINCFG_PACK(type, value)	(((value) << 8) | (type & 0xFF))
#define SUNXI_PINCFG_UNPACK_TYPE(cfg)	((cfg) & 0xFF)
#define SUNXI_PINCFG_UNPACK_VALUE(cfg)	(((cfg) & 0xFFFFFF00) >> 8)

static inline int sunxi_gpio_to_name(int gpio, char *name)
{
	int bank, index;

	if (!name)
		return -EINVAL;

	if (IS_AXP_PIN(gpio)) {
		/* axp gpio name like this : GPIO0/GPIO1/.. */
		index = gpio - AXP_PIN_BASE;
		sprintf(name, "GPIO%d", index);
	} else {
		/* sunxi gpio name like this : PA0/PA1/PB0 */
		bank = gpio / SUNXI_BANK_SIZE;
		index = gpio % SUNXI_BANK_SIZE;
		sprintf(name, "P%c%d", ('A' + bank), index);
	}

	return 0;
}

/* pio end, invalid macro */
#define GPIO_INDEX_INVALID	(0xFFFFFFF0)
#define GPIO_CFG_INVALID	(0xEEEEEEEE)
#define GPIO_PULL_INVALID	(0xDDDDDDDD)
#define GPIO_DRVLVL_INVALID	(0xCCCCCCCC)
#define IRQ_NUM_INVALID		(0xFFFFFFFF)
#define AXP_PORT_VAL		(0x0000FFFF)

/* pio default macro */
#define GPIO_PULL_DEFAULT	((u32)-1)
#define GPIO_DRVLVL_DEFAULT	((u32)-1)
#define GPIO_DATA_DEFAULT	((u32)-1)

/*
 * struct gpio_config - gpio config info
 * @gpio:      gpio global index, must be unique
 * @mul_sel:   multi sel val: 0 - input, 1 - output.
 * @pull:      pull val: 0 - pull up/down disable, 1 - pull up
 * @drv_level: driver level val: 0 - level 0, 1 - level 1
 * @data:      data val: 0 - low, 1 - high, only valid when mul_sel is input/output
 */
struct gpio_config {
	u32	data;
	u32	gpio;
	u32	mul_sel;
	u32	pull;
	u32	drv_level;
};

#endif
