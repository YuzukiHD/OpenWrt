/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * Allwinner SoCs eink200 driver.
 *
 * Copyright (C) 2019 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "panel_ctrl.h"

struct __eink_panel *eink_panel_array[] = {
	&default_eink,
	/* add new panel below */
	NULL,
};

void EINK_OPEN_FUNC(EINK_PANEL_FUNC func, u32 delay)
{
	struct timing_ctrl_manager *mgr = get_timing_ctrl_mgr();

	if (mgr == NULL) {
		sunxi_err(NULL, "%s:input para wrong!\n", __func__);
		return;
	}

	if (func == NULL) {
		sunxi_err(NULL, "%s:func is NULL\n", __func__);
	}
	if (mgr->set_open_func)
		mgr->set_open_func(mgr, func, delay);
}

void EINK_CLOSE_FUNC(EINK_PANEL_FUNC func, u32 delay)
{
	struct timing_ctrl_manager *mgr = get_timing_ctrl_mgr();

	if (mgr == NULL) {
		sunxi_err(NULL, "%s:input para wrong!\n", __func__);
		return;
	}

	if (mgr->set_close_func)
		mgr->set_close_func(mgr, func, delay);
}

static void set_panel_funcs(void)
{
	int i = 0;

	for (i = 0; eink_panel_array[i] != NULL; i++) {
		eink_set_panel_funcs(eink_panel_array[i]->name,
					 &eink_panel_array[i]->func);
	}
}

int eink_panel_init(void)
{
	EINK_DEBUG_MSG("eink_panel_init!\n");
	set_panel_funcs();

	return 0;
}
/**
 * panel_pin_cfg - config pin panel used
 * @en:     1: config pin according to sys_config, 0: set disable state
 */
s32 panel_pin_cfg(u32 en)
{
	int ret = 0;

	ret = eink_panel_pin_cfg(en);
	return ret;
}

/**
 * panel_gpio_set_value
 * @io_index:  the index of gpio
 * @value: value of gpio to be set
 */
s32 panel_gpio_set_value(u32 io_index, u32 value)
{
	int ret = 0;
	char gpio_name[20];
	struct timing_ctrl_manager *mgr = get_timing_ctrl_mgr();

	if (mgr == NULL) {
		sunxi_err(NULL, "%s:something is err\n", __func__);
		return -1;
	}

	if (io_index >= EINK_GPIO_NUM) {
		sunxi_err(NULL, "%s:gpio num out of range\n", __func__);
		return -1;
	}
	sprintf(gpio_name, "eink_gpio_%d", io_index);

	EINK_DEBUG_MSG("io_index = %d\n", io_index);
	ret = eink_sys_gpio_set_value(mgr->gpio_hdl[io_index], value, gpio_name);
	return ret;
}
