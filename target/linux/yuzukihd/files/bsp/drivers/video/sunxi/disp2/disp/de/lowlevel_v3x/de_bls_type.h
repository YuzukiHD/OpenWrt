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


/*******************************************************************************
 *  All Winner Tech, All Right Reserved. 2014-2016 Copyright (c)
 *
 *  File name   :   de_bls_type.h
 *
 *  Description :   display engine 3.0 bls struct declaration
 *
 *  History     :   2016-3-3 zzz  v0.1  Initial version
 *
 ******************************************************************************/

#ifndef __DE_BLS_TYPE_H__
#define __DE_BLS_TYPE_H__

#include "de_rtmx.h"

union BLS_CTRL_REG {
	unsigned int dwval;
	struct {
		unsigned int en:1;
		unsigned int win_en:1;
		unsigned int res0:2;
		unsigned int input_csc_en:1;
		unsigned int output_csc_en:1;
		unsigned int res1:2;
		unsigned int res2:24;
	} bits;
};

union BLS_SIZE_REG {
	unsigned int dwval;
	struct {
		unsigned int width:13;
		unsigned int res0:3;
		unsigned int height:13;
		unsigned int res1:3;
	} bits;
};

union BLS_POS_REG {
	unsigned int dwval;
	struct {
		unsigned int u_offset:8;
		unsigned int res0:8;
		unsigned int v_offset:8;
		unsigned int res1:8;
	} bits;
};

union BLS_WIN0_REG {
	unsigned int dwval;
	struct {
		unsigned int win_left:13;
		unsigned int res0:3;
		unsigned int win_top:13;
		unsigned int res1:3;
	} bits;
};

union BLS_WIN1_REG {
	unsigned int dwval;
	struct {
		unsigned int win_right:13;
		unsigned int res0:3;
		unsigned int win_bot:13;
		unsigned int res1:3;
	} bits;
};

union BLS_ATTLUT_REG {
	unsigned int dwval;
	struct {
		unsigned int k0:4;
		unsigned int k1:4;
		unsigned int k2:4;
		unsigned int k3:4;
		unsigned int k4:4;
		unsigned int k5:4;
		unsigned int k6:4;
		unsigned int k7:4;
	} bits;
};

union BLS_LUTCTRL_REG {
	unsigned int dwval;
	struct {
		unsigned int zone_lut_row_sel:5;
		unsigned int res0:11;
		unsigned int res1:15;
		unsigned int zone_lut_access:1;
	} bits;
};

union BLS_GAINLUT_REG {
	unsigned int dwval;
	struct {
		unsigned int gain0:8;
		unsigned int gain1:8;
		unsigned int gain2:8;
		unsigned int gain3:8;
	} bits;
};

struct __bls_reg_t {
	union BLS_CTRL_REG ctrl;           /* 0x00 */
	union BLS_SIZE_REG size;           /* 0x04 */
	union BLS_WIN0_REG win0;           /* 0x08 */
	union BLS_WIN1_REG win1;           /* 0x0c */
	union BLS_ATTLUT_REG bls_attlut[4];    /* 0x10 */
	union BLS_POS_REG bls_pos;             /* 0x20 */
	unsigned int res0[3];                  /* 0x24-0x2c */
	union BLS_GAINLUT_REG bls_gainlut[4];  /* 0x30 */
};

struct __bls_config_data {
	/* return info */
	unsigned int mod_en; /* return mod en info */

	/* parameter */
	unsigned int level; /* user level */
};

#endif
