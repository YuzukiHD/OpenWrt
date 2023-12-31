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

#ifndef __DE_CDC_TYPE_H__
#define __DE_CDC_TYPE_H__

union __cdc_ctrl_reg {
	unsigned int dwval;
	struct {
		unsigned int en:1;
		unsigned int res:31;
	} bits;
};

union __cdc_update_reg {
	unsigned int dwval;
	struct {
		unsigned int update:1;
		unsigned int res:31;
	} bits;
};

union __cdc_csc_const_reg_t {
	unsigned int dwval;
	struct {
		unsigned int constant:10;
		unsigned int r0:22;
	} bits;
};

union __cdc_csc_coef_reg_t {
	unsigned int dwval;
	struct {
		unsigned int coef:20;
		unsigned int r0:12;
	} bits;
};

union __cdc_lut_coef_reg_t {
	unsigned int dwval;
	struct {
		unsigned int coef:30;
		unsigned int r0:2;
	} bits;
};

struct __cdc_reg_t {
	union __cdc_ctrl_reg ctrl;
	union __cdc_update_reg update;
	unsigned int res0[3];

	union __cdc_csc_const_reg_t in_d[3];
	union __cdc_csc_coef_reg_t in_c0[3];
	union __cdc_csc_const_reg_t in_c03;
	union __cdc_csc_coef_reg_t in_c1[3];
	union __cdc_csc_const_reg_t in_c13;
	union __cdc_csc_coef_reg_t in_c2[3];
	union __cdc_csc_const_reg_t in_c23;

	unsigned int res1;
	union __cdc_csc_const_reg_t out_d[3];
	union __cdc_csc_coef_reg_t out_c0[3];
	union __cdc_csc_const_reg_t out_c03;
	union __cdc_csc_coef_reg_t out_c1[3];
	union __cdc_csc_const_reg_t out_c13;
	union __cdc_csc_coef_reg_t out_c2[3];
	union __cdc_csc_const_reg_t out_c23;
};

struct __cdc_status {
	unsigned int convert_type;
	unsigned int in_fmt;
};

#endif
