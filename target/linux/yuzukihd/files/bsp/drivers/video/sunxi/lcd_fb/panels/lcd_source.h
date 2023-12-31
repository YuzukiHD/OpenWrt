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

#include "panels.h"

extern struct sunxi_lcd_drv g_lcd_drv;

/**
 * sunxi_lcd_delay_ms.
 * @ms: Delay time, unit: millisecond.
 */
s32 sunxi_lcd_delay_ms(u32 ms);

/**
 * sunxi_lcd_delay_us.
 * @us: Delay time, unit: microsecond.
 */
s32 sunxi_lcd_delay_us(u32 us);


/**
 * sunxi_lcd_backlight_enable - enable the backlight of panel.
 * @screen_id: The index of screen.
 */
void sunxi_lcd_backlight_enable(u32 screen_id);

/**
 * sunxi_lcd_backlight_disable - disable the backlight of panel.
 * @screen_id: The index of screen.
 */
void sunxi_lcd_backlight_disable(u32 screen_id);

/**
 * sunxi_lcd_power_enable - enable the power of panel.
 * @screen_id: The index of screen.
 * @pwr_id:     The index of power
 */
void sunxi_lcd_power_enable(u32 screen_id, u32 pwr_id);

/**
 * sunxi_lcd_power_disable - disable the power of panel.
 * @screen_id: The index of screen.
 * @pwr_id:     The index of power
 */
void sunxi_lcd_power_disable(u32 screen_id, u32 pwr_id);

/**
 * sunxi_pwm_enable - enable pwm modules, start output pwm wave.
 * @pwm_channel: The index of pwm channel.
 *
 * need to conifg gpio for pwm function
 */
s32 sunxi_lcd_pwm_enable(u32 pwm_channel);

/**
 * sunxi_pwm_disable - disable pwm modules, stop output pwm wave.
 * @pwm_channel: The index of pwm channel.
 */
s32 sunxi_lcd_pwm_disable(u32 pwm_channel);



/**
 * sunxi_lcd_pin_cfg - config pin panel used
 * @screen_id: The index of screen.
 * @bon:     1: config pin according to sys_config, 0: set disable state
 */
s32 sunxi_lcd_pin_cfg(u32 screen_id, u32 bon);

/**
 * sunxi_lcd_set_panel_funs -  set panel functions.
 * @name: The panel driver name.
 * @lcd_cfg: The functions.
 */
s32 sunxi_lcd_set_panel_funs(char *name, struct disp_lcd_panel_fun *lcd_cfg);

/**
 * sunxi_lcd_gpio_set_value
 * @screen_id: The index of screen.
 * @io_index:  the index of gpio
 * @value: value of gpio to be set
 */
s32 sunxi_lcd_gpio_set_value(u32 screen_id, u32 io_index, u32 value);

/**
 * sunxi_lcd_gpio_set_direction
 * @screen_id: The index of screen.
 * @io_index:  the index of gpio
 * @direction: value of gpio to be set
 */
s32 sunxi_lcd_gpio_set_direction(u32 screen_id, u32 io_index, u32 direction);

/**
 * sunxi_lcd_cmd_write
 * @screen_id: The index of screen.
 * @cmd:  command to be send
 */
s32 sunxi_lcd_cmd_write(u32 screen_id, u8 cmd);

/**
 * sunxi_lcd_para_write
 * @screen_id: The index of screen.
 * @cmd:  command to be send
 */
s32 sunxi_lcd_para_write(u32 screen_id, u8 para);

/**
 * sunxi_lcd_para_write
 * @screen_id: The index of screen.
 * @cmd:  command to be send
 */
s32 sunxi_lcd_cmd_read(u32 screen_id, u8 cmd, u8 *rx_buf, u8 len);

extern struct sunxi_lcd_drv g_lcd_drv;
