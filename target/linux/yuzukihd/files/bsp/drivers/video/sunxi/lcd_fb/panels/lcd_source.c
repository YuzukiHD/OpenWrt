/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "lcd_source.h"

/**
 * sunxi_lcd_delay_ms.
 * @ms: Delay time, unit: millisecond.
 */
s32 sunxi_lcd_delay_ms(u32 ms)
{
	return g_lcd_drv.src_ops.sunxi_lcd_delay_ms(ms);

	return -1;
}

/**
 * sunxi_lcd_delay_us.
 * @us: Delay time, unit: microsecond.
 */
s32 sunxi_lcd_delay_us(u32 us)
{
	return g_lcd_drv.src_ops.sunxi_lcd_delay_us(us);

	return -1;
}


/**
 * sunxi_lcd_backlight_enable - enable the backlight of panel.
 * @screen_id: The index of screen.
 */
void sunxi_lcd_backlight_enable(u32 screen_id)
{
	if (g_lcd_drv.src_ops.sunxi_lcd_backlight_enable)
		g_lcd_drv.src_ops.sunxi_lcd_backlight_enable(screen_id);
}

/**
 * sunxi_lcd_backlight_disable - disable the backlight of panel.
 * @screen_id: The index of screen.
 */
void sunxi_lcd_backlight_disable(u32 screen_id)
{
	if (g_lcd_drv.src_ops.sunxi_lcd_backlight_disable)
		g_lcd_drv.src_ops.sunxi_lcd_backlight_disable(screen_id);
}

/**
 * sunxi_lcd_power_enable - enable the power of panel.
 * @screen_id: The index of screen.
 * @pwr_id:     The index of power
 */
void sunxi_lcd_power_enable(u32 screen_id, u32 pwr_id)
{
	if (g_lcd_drv.src_ops.sunxi_lcd_power_enable)
		g_lcd_drv.src_ops.sunxi_lcd_power_enable(screen_id, pwr_id);
}

/**
 * sunxi_lcd_power_disable - disable the power of panel.
 * @screen_id: The index of screen.
 * @pwr_id:     The index of power
 */
void sunxi_lcd_power_disable(u32 screen_id, u32 pwr_id)
{
	if (g_lcd_drv.src_ops.sunxi_lcd_power_disable)
		g_lcd_drv.src_ops.sunxi_lcd_power_disable(screen_id, pwr_id);
}

/**
 * sunxi_lcd_pwm_enable - enable pwm modules, start output pwm wave.
 * @screen_id: The index of screen.
 *
 * need to conifg gpio for pwm function
 */
s32 sunxi_lcd_pwm_enable(u32 screen_id)
{
	if (g_lcd_drv.src_ops.sunxi_lcd_pwm_enable)
		return g_lcd_drv.src_ops.sunxi_lcd_pwm_enable(screen_id);

	return -1;
}

/**
 * sunxi_lcd_pwm_disable - disable pwm modules, stop output pwm wave.
 * @screen_id: The index of screen.
 */
s32 sunxi_lcd_pwm_disable(u32 screen_id)
{
	if (g_lcd_drv.src_ops.sunxi_lcd_pwm_disable)
		return g_lcd_drv.src_ops.sunxi_lcd_pwm_disable(screen_id);

	return -1;
}


/**
 * sunxi_lcd_set_panel_funs -  set panel functions.
 * @name: The panel driver name.
 * @lcd_cfg: The functions.
 */
s32 sunxi_lcd_set_panel_funs(char *name, struct disp_lcd_panel_fun *lcd_cfg)
{
	if (g_lcd_drv.src_ops.sunxi_lcd_set_panel_funs)
		return g_lcd_drv.src_ops.sunxi_lcd_set_panel_funs(name,
								  lcd_cfg);

	return -1;
}

/**
 * sunxi_lcd_pin_cfg - config pin panel used
 * @screen_id: The index of screen.
 * @bon:     1: config pin according to sys_config, 0: set disable state
 */
s32 sunxi_lcd_pin_cfg(u32 screen_id, u32 bon)
{
	if (g_lcd_drv.src_ops.sunxi_lcd_pin_cfg)
		return g_lcd_drv.src_ops.sunxi_lcd_pin_cfg(screen_id, bon);

	return -1;
}

/**
 * sunxi_lcd_gpio_set_value
 * @screen_id: The index of screen.
 * @io_index:  the index of gpio
 * @value: value of gpio to be set
 */
s32 sunxi_lcd_gpio_set_value(u32 screen_id, u32 io_index, u32 value)
{
	if (g_lcd_drv.src_ops.sunxi_lcd_gpio_set_value)
		return g_lcd_drv.src_ops.sunxi_lcd_gpio_set_value(screen_id,
								  io_index,
								  value);

	return -1;
}

/**
 * sunxi_lcd_gpio_set_direction
 * @screen_id: The index of screen.
 * @io_index:  the index of gpio
 * @direct: value of gpio to be set
 */
s32 sunxi_lcd_gpio_set_direction(u32 screen_id, u32 io_index, u32 direct)
{
	if (g_lcd_drv.src_ops.sunxi_lcd_gpio_set_direction)
		return g_lcd_drv.src_ops.sunxi_lcd_gpio_set_direction(screen_id,
								      io_index,
								      direct);

	return -1;
}

/**
 * sunxi_lcd_cmd_write
 * @screen_id: The index of screen.
 * @cmd:  command to be send
 */
s32 sunxi_lcd_cmd_write(u32 screen_id, u8 cmd)
{
	if (g_lcd_drv.src_ops.sunxi_lcd_cmd_write)
		return g_lcd_drv.src_ops.sunxi_lcd_cmd_write(screen_id, cmd);

	return -1;
}

/**
 * sunxi_lcd_para_write
 * @screen_id: The index of screen.
 * @para:  para to be writed
 */
s32 sunxi_lcd_para_write(u32 screen_id, u8 para)
{
	if (g_lcd_drv.src_ops.sunxi_lcd_para_write)
		return g_lcd_drv.src_ops.sunxi_lcd_para_write(screen_id, para);

	return -1;
}

/**
 * sunxi_lcd_para_write
 * @screen_id: The index of screen.
 * @cmd:  command to be read
 * @len:  length of bytes to be read
 */
s32 sunxi_lcd_cmd_read(u32 screen_id, u8 cmd, u8 *rx_buf, u8 len)
{
	if (g_lcd_drv.src_ops.sunxi_lcd_cmd_read)
		return g_lcd_drv.src_ops.sunxi_lcd_cmd_read(screen_id, cmd, rx_buf, len);

	return -1;
}
