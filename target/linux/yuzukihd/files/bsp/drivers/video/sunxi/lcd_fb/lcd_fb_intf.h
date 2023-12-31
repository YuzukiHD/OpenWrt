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
#include "include.h"

#ifndef _LCD_FB_INTF_
#define _LCD_FB_INTF_

struct disp_gpio_info {
	unsigned gpio;
	char name[32];
	int value;
};

#define DISP_IRQ_RETURN IRQ_HANDLED
#define DISP_PIN_STATE_ACTIVE "active"
#define DISP_PIN_STATE_SLEEP "sleep"

int lcd_fb_register_irq(u32 IrqNo, u32 Flags, void *Handler, void *pArg,
			  u32 DataSize, u32 Prio);
void lcd_fb_unregister_irq(u32 IrqNo, void *Handler, void *pArg);
void lcd_fb_disable_irq(u32 IrqNo);
void lcd_fb_enable_irq(u32 IrqNo);

/* returns: 0:invalid, 1: int; 2:str, 3: gpio */
int lcd_fb_script_get_item(char *main_name, char *sub_name, int value[],
			     int count);

int lcd_fb_get_ic_ver(void);

int lcd_fb_gpio_request(struct disp_gpio_info *gpio_info);
int lcd_fb_gpio_request_simple(struct disp_gpio_info *gpio_list,
				 u32 group_count_max);
int lcd_fb_gpio_release(struct disp_gpio_info *gpio_info);

/* direction: 0:input, 1:output */
int lcd_fb_gpio_set_direction(u32 p_handler, u32 direction,
				const char *gpio_name);
int lcd_fb_gpio_get_value(u32 p_handler, const char *gpio_name);
int lcd_fb_gpio_set_value(u32 p_handler, u32 value_to_gpio,
			    const char *gpio_name);
int lcd_fb_pin_set_state(char *dev_name, char *name);

int lcd_fb_power_enable(char *name);
int lcd_fb_power_disable(char *name);
void *lcd_fb_malloc(u32 size);

uintptr_t lcd_fb_pwm_request(u32 pwm_id);
int lcd_fb_pwm_free(uintptr_t p_handler);
int lcd_fb_pwm_enable(uintptr_t p_handler);
int lcd_fb_pwm_disable(uintptr_t p_handler);
int lcd_fb_pwm_config(uintptr_t p_handler, int duty_ns, int period_ns);
int lcd_fb_pwm_set_polarity(uintptr_t p_handler, int polarity);
s32 disp_delay_ms(u32 ms);
s32 disp_delay_us(u32 us);

#endif
