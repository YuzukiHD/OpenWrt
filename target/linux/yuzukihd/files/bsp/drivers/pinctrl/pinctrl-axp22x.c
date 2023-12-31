// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * AXP22x pinctrl and GPIO driver
 *
 * Copyright (C) 2016 Maxime Ripard <maxime.ripard@free-electrons.com>
 * Copyright (C) 2017 Quentin Schulz <quentin.schulz@free-electrons.com>
 */

#include <linux/bitops.h>
#include <linux/device.h>
#include <linux/gpio/driver.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/pinctrl/pinconf-generic.h>
#include <linux/pinctrl/pinctrl.h>
#include <linux/pinctrl/pinmux.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/slab.h>

#include <linux/power_supply.h>
#include <linux/mutex.h>
#include <linux/param.h>
#include <linux/jiffies.h>
#include <linux/fs.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>
#include <linux/types.h>
#include <linux/string.h>
#include <asm/irq.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/pm_runtime.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/err.h>
#include "power/axp2101.h"

#define AXP22X_GPIO_FUNCTIONS		0x7
#define AXP22X_GPIO_FUNCTION_OUT_LOW	0
#define AXP22X_GPIO_FUNCTION_OUT_HIGH	1
#define AXP22X_GPIO_FUNCTION_INPUT	2

#define AXP22X_FUNC_GPIO_OUT	0
#define AXP22X_FUNC_GPIO_IN		1
#define AXP22X_FUNC_LDO			2
#define AXP22X_FUNC_ADC			3
#define AXP22X_FUNCS_NB			4

#define AXP22X_MUX_GPIO_OUT		0
#define AXP22X_MUX_GPIO_IN		BIT(1)
#define AXP22X_MUX_ADC			BIT(2)

struct axp22x_pctrl_desc {
	const struct pinctrl_pin_desc	*pins;
	unsigned int			npins;
	/* Stores the pins supporting LDO function. Bit offset is pin number. */
	u8				ldo_mask;
	/* Stores the pins supporting ADC function. Bit offset is pin number. */
	u8				adc_mask;
	u8				gpio_status_offset;
	u8				adc_mux;
};

struct axp22x_pinctrl_function {
	const char	*name;
	unsigned int	muxval;
	const char	**groups;
	unsigned int	ngroups;
};

struct axp22x_pctl {
	struct gpio_chip	chip;
	struct regmap		*regmap;
	struct pinctrl_dev			*pctl_dev;
	struct device				*dev;
	const struct axp22x_pctrl_desc		*desc;
	struct axp22x_pinctrl_function		funcs[AXP22X_FUNCS_NB];
};


static const struct pinctrl_pin_desc axp22x_pins[] = {
	PINCTRL_PIN(0, "GPIO0"),
	PINCTRL_PIN(1, "GPIO1"),
};

static const struct axp22x_pctrl_desc axp22x_data = {
	.pins	= axp22x_pins,
	.npins	= ARRAY_SIZE(axp22x_pins),
	.ldo_mask = BIT(0) | BIT(1),
	.adc_mask = BIT(0) | BIT(1),
	.gpio_status_offset = 0,
	.adc_mux = AXP22X_MUX_ADC,
};

static int axp22x_gpio_get_reg(unsigned int offset)
{
	switch (offset) {
	case 0:
		return AXP22X_GPIO0_CTL;
	case 1:
		return AXP22X_GPIO1_CTL;
	}

	return -EINVAL;
}

static int axp22x_gpio_input(struct gpio_chip *chip, unsigned int offset)
{
	return pinctrl_gpio_direction_input(chip->base + offset);
}

static int axp22x_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct axp22x_pctl *pctl = gpiochip_get_data(chip);
	unsigned int val;
	int ret;

	ret = regmap_read(pctl->regmap, AXP22X_GPIO01_SIGNAL, &val);
	if (ret)
		return ret;

	return !!(val & BIT(offset + pctl->desc->gpio_status_offset));
}

static int axp22x_gpio_get_direction(struct gpio_chip *chip,
				     unsigned int offset)
{
	struct axp22x_pctl *pctl = gpiochip_get_data(chip);
	unsigned int val;
	int reg, ret;

	reg = axp22x_gpio_get_reg(offset);
	if (reg < 0)
		return reg;

	ret = regmap_read(pctl->regmap, reg, &val);
	if (ret)
		return ret;

	/*
	 * This shouldn't really happen if the pin is in use already,
	 * or if it's not in use yet, it doesn't matter since we're
	 * going to change the value soon anyway. Default to output.
	 */
	if ((val & AXP22X_GPIO_FUNCTIONS) > 2)
		return 0;

	/*
	 * The GPIO directions are the three lowest values.
	 * 2 is input, 0 and 1 are output
	 */
	return val & 2;
}

static int axp22x_gpio_output(struct gpio_chip *chip, unsigned int offset,
			      int value)
{
	chip->set(chip, offset, value);

	return 0;
}

static void axp22x_gpio_set(struct gpio_chip *chip, unsigned int offset,
			    int value)
{
	struct axp22x_pctl *pctl = gpiochip_get_data(chip);
	int reg;

	reg = axp22x_gpio_get_reg(offset);
	if (reg < 0)
		return;

	regmap_update_bits(pctl->regmap, reg,
			   AXP22X_GPIO_FUNCTIONS,
			   value ? AXP22X_GPIO_FUNCTION_OUT_HIGH :
			   AXP22X_GPIO_FUNCTION_OUT_LOW);
}

static int axp22x_pmx_set(struct pinctrl_dev *pctldev, unsigned int offset,
			  u8 config)
{
	struct axp22x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);
	int reg;

	reg = axp22x_gpio_get_reg(offset);
	if (reg < 0)
		return reg;

	return regmap_update_bits(pctl->regmap, reg, AXP22X_GPIO_FUNCTIONS,
				  config);
}

static int axp22x_pmx_func_cnt(struct pinctrl_dev *pctldev)
{
	struct axp22x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	return ARRAY_SIZE(pctl->funcs);
}

static const char *axp22x_pmx_func_name(struct pinctrl_dev *pctldev,
					unsigned int selector)
{
	struct axp22x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	return pctl->funcs[selector].name;
}

static int axp22x_pmx_func_groups(struct pinctrl_dev *pctldev,
				  unsigned int selector,
				  const char * const **groups,
				  unsigned int *num_groups)
{
	struct axp22x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctl->funcs[selector].groups;
	*num_groups = pctl->funcs[selector].ngroups;

	return 0;
}

static int axp22x_pmx_set_mux(struct pinctrl_dev *pctldev,
			      unsigned int function, unsigned int group)
{
	struct axp22x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);
	unsigned int mask;

	/* Every pin supports GPIO_OUT and GPIO_IN functions */
	if (function <= AXP22X_FUNC_GPIO_IN)
		return axp22x_pmx_set(pctldev, group,
				      pctl->funcs[function].muxval);

	if (function == AXP22X_FUNC_LDO)
		mask = pctl->desc->ldo_mask;
	else
		mask = pctl->desc->adc_mask;

	if (!(BIT(group) & mask))
		return -EINVAL;

	/*
	 * We let the regulator framework handle the LDO muxing as muxing bits
	 * are basically also regulators on/off bits. It's better not to enforce
	 * any state of the regulator when selecting LDO mux so that we don't
	 * interfere with the regulator driver.
	 */
	if (function == AXP22X_FUNC_LDO)
		return 0;

	return axp22x_pmx_set(pctldev, group, pctl->funcs[function].muxval);
}

static int axp22x_pmx_gpio_set_direction(struct pinctrl_dev *pctldev,
					 struct pinctrl_gpio_range *range,
					 unsigned int offset, bool input)
{
	struct axp22x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	if (input)
		return axp22x_pmx_set(pctldev, offset,
				      pctl->funcs[AXP22X_FUNC_GPIO_IN].muxval);

	return axp22x_pmx_set(pctldev, offset,
			      pctl->funcs[AXP22X_FUNC_GPIO_OUT].muxval);
}

static const struct pinmux_ops axp22x_pmx_ops = {
	.get_functions_count	= axp22x_pmx_func_cnt,
	.get_function_name	= axp22x_pmx_func_name,
	.get_function_groups	= axp22x_pmx_func_groups,
	.set_mux		= axp22x_pmx_set_mux,
	.gpio_set_direction	= axp22x_pmx_gpio_set_direction,
	.strict			= true,
};

static int axp22x_groups_cnt(struct pinctrl_dev *pctldev)
{
	struct axp22x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	return pctl->desc->npins;
}

static int axp22x_group_pins(struct pinctrl_dev *pctldev, unsigned int selector,
			     const unsigned int **pins, unsigned int *num_pins)
{
	struct axp22x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*pins = (unsigned int *)&pctl->desc->pins[selector];
	*num_pins = 1;

	return 0;
}

static const char *axp22x_group_name(struct pinctrl_dev *pctldev,
				     unsigned int selector)
{
	struct axp22x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	return pctl->desc->pins[selector].name;
}

static const struct pinctrl_ops axp22x_pctrl_ops = {
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_group,
	.dt_free_map		= pinconf_generic_dt_free_map,
	.get_groups_count	= axp22x_groups_cnt,
	.get_group_name		= axp22x_group_name,
	.get_group_pins		= axp22x_group_pins,
};

static int axp22x_funcs_groups_from_mask(struct device *dev, unsigned int mask,
					  unsigned int mask_len,
					  struct axp22x_pinctrl_function *func,
					  const struct pinctrl_pin_desc *pins)
{
	unsigned long int mask_cpy = mask;
	const char **group;
	unsigned int ngroups = hweight8(mask);
	int bit;

	func->ngroups = ngroups;
	if (func->ngroups > 0) {
		func->groups = devm_kcalloc(dev,
					    ngroups, sizeof(const char *),
					    GFP_KERNEL);
		if (!func->groups)
			return -ENOMEM;
		group = func->groups;
		for_each_set_bit(bit, &mask_cpy, mask_len) {
			*group = pins[bit].name;
			group++;
		}
	}

	return 0;
}

static int axp22x_build_funcs_groups(struct platform_device *pdev)
{
	struct axp22x_pctl *pctl = platform_get_drvdata(pdev);
	int i, ret, pin, npins = pctl->desc->npins;

	pctl->funcs[AXP22X_FUNC_GPIO_OUT].name = "gpio_out";
	pctl->funcs[AXP22X_FUNC_GPIO_OUT].muxval = AXP22X_MUX_GPIO_OUT;
	pctl->funcs[AXP22X_FUNC_GPIO_IN].name = "gpio_in";
	pctl->funcs[AXP22X_FUNC_GPIO_IN].muxval = AXP22X_MUX_GPIO_IN;
	pctl->funcs[AXP22X_FUNC_LDO].name = "ldo";
	/*
	 * Muxval for LDO is useless as we won't use it.
	 * See comment in axp22x_pmx_set_mux.
	 */
	pctl->funcs[AXP22X_FUNC_ADC].name = "adc";
	pctl->funcs[AXP22X_FUNC_ADC].muxval = pctl->desc->adc_mux;

	/* Every pin supports GPIO_OUT and GPIO_IN functions */
	for (i = 0; i <= AXP22X_FUNC_GPIO_IN; i++) {
		pctl->funcs[i].ngroups = npins;
		pctl->funcs[i].groups = devm_kcalloc(&pdev->dev,
						     npins, sizeof(char *),
						     GFP_KERNEL);
		if (!pctl->funcs[i].groups)
			return -ENOMEM;
		for (pin = 0; pin < npins; pin++)
			pctl->funcs[i].groups[pin] = pctl->desc->pins[pin].name;
	}

	ret = axp22x_funcs_groups_from_mask(&pdev->dev, pctl->desc->ldo_mask,
				      npins, &pctl->funcs[AXP22X_FUNC_LDO],
				      pctl->desc->pins);
	if (ret)
		return ret;

	ret = axp22x_funcs_groups_from_mask(&pdev->dev, pctl->desc->adc_mask,
				      npins, &pctl->funcs[AXP22X_FUNC_ADC],
				      pctl->desc->pins);
	if (ret)
		return ret;

	return 0;
}

static const struct of_device_id axp22x_pctl_match[] = {
	{ .compatible = "x-powers,axp221-gpio", .data = &axp22x_data, },
	{ .compatible = "x-powers,axp223-gpio", .data = &axp22x_data, },
	{ .compatible = "x-powers,axp22x-gpio", .data = &axp22x_data, },
	{ }
};
MODULE_DEVICE_TABLE(of, axp22x_pctl_match);

static int axp22x_pctl_probe(struct platform_device *pdev)
{
	struct axp20x_dev *axp22x = dev_get_drvdata(pdev->dev.parent);
	struct axp22x_pctl *pctl;
	struct device *dev = &pdev->dev;
	struct pinctrl_desc *pctrl_desc;
	int ret;

	if (!of_device_is_available(pdev->dev.of_node))
		return -ENODEV;

	if (!axp22x) {
		dev_err(&pdev->dev, "Parent drvdata not set\n");
		return -EINVAL;
	}

	pctl = devm_kzalloc(&pdev->dev, sizeof(*pctl), GFP_KERNEL);
	if (!pctl)
		return -ENOMEM;

	pctl->chip.base			= -1;
	pctl->chip.can_sleep		= true;
	pctl->chip.request		= gpiochip_generic_request;
	pctl->chip.free			= gpiochip_generic_free;
	pctl->chip.parent		= &pdev->dev;
	pctl->chip.label		= dev_name(&pdev->dev);
	pctl->chip.owner		= THIS_MODULE;
	pctl->chip.get			= axp22x_gpio_get;
	pctl->chip.get_direction	= axp22x_gpio_get_direction;
	pctl->chip.set			= axp22x_gpio_set;
	pctl->chip.direction_input	= axp22x_gpio_input;
	pctl->chip.direction_output	= axp22x_gpio_output;

	pctl->desc = of_device_get_match_data(dev);

	pctl->chip.ngpio		= pctl->desc->npins;

	pctl->regmap = axp22x->regmap;
	pctl->dev = &pdev->dev;

	platform_set_drvdata(pdev, pctl);

	ret = axp22x_build_funcs_groups(pdev);
	if (ret) {
		dev_err(&pdev->dev, "failed to build groups\n");
		return ret;
	}

	pctrl_desc = devm_kzalloc(&pdev->dev, sizeof(*pctrl_desc), GFP_KERNEL);
	if (!pctrl_desc)
		return -ENOMEM;

	pctrl_desc->name = dev_name(&pdev->dev);
	pctrl_desc->owner = THIS_MODULE;
	pctrl_desc->pins = pctl->desc->pins;
	pctrl_desc->npins = pctl->desc->npins;
	pctrl_desc->pctlops = &axp22x_pctrl_ops;
	pctrl_desc->pmxops = &axp22x_pmx_ops;

	pctl->pctl_dev = devm_pinctrl_register(&pdev->dev, pctrl_desc, pctl);
	if (IS_ERR(pctl->pctl_dev)) {
		dev_err(&pdev->dev, "couldn't register pinctrl driver\n");
		return PTR_ERR(pctl->pctl_dev);
	}

	ret = devm_gpiochip_add_data(&pdev->dev, &pctl->chip, pctl);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register GPIO chip\n");
		return ret;
	}

	ret = gpiochip_add_pin_range(&pctl->chip, dev_name(&pdev->dev),
				     pctl->desc->pins->number,
				     pctl->desc->pins->number,
				     pctl->desc->npins);
	if (ret) {
		dev_err(&pdev->dev, "failed to add pin range\n");
		return ret;
	}

	dev_info(&pdev->dev, "AXP22X pinctrl and GPIO driver loaded\n");

	return 0;
}

static struct platform_driver axp22x_pctl_driver = {
	.probe		= axp22x_pctl_probe,
	.driver = {
		.name		= "axp22x-gpio",
		.of_match_table	= axp22x_pctl_match,
	},
};

module_platform_driver(axp22x_pctl_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_AUTHOR("Quentin Schulz <quentin.schulz@free-electrons.com>");
MODULE_DESCRIPTION("AXP22x PMIC pinctrl and GPIO driver");
MODULE_LICENSE("GPL");
