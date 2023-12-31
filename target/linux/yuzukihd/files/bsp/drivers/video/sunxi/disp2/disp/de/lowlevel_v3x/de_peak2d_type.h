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
 *  File name   :   de_peak2d_type.h
 *
 *  Description :   display engine 3.0 2D-peak struct declaration
 *
 *  History     :   2016/03/30  vito cheng  v0.1  Initial version
 *
 ******************************************************************************/

#ifndef __DE_PEAK2D_TYPE_H__
#define __DE_PEAK2D_TYPE_H__

#include "de_rtmx.h"

union PEAK2D_EN_REG {
	unsigned int dwval;
	struct {
		unsigned int en:1;
		unsigned int res0:31;
	} bits;
};

union PEAK2D_CORING_REG {
	unsigned int dwval;
	struct {
		unsigned int corth:10;
		unsigned int res0:22;
	} bits;
};

union PEAK2D_GAIN0_REG {
	unsigned int dwval;
	struct {
		unsigned int dipthr0:10;
		unsigned int res0:6;
		unsigned int dipthr1:10;
		unsigned int res1:6;
	} bits;
};

union PEAK2D_GAIN1_REG {
	unsigned int dwval;
	struct {
		unsigned int gain:8;
		unsigned int res0:8;
		unsigned int neggain:5;
		unsigned int res1:3;
		unsigned int beta:5;
		unsigned int res2:3;
	} bits;
};

struct __peak2d_reg_t {
	union PEAK2D_EN_REG en; /* 0x0000 */
	union PEAK2D_CORING_REG coring; /* 0x0004 */
	union PEAK2D_GAIN0_REG gain0; /* 0x0008 */
	union PEAK2D_GAIN1_REG gain1; /* 0x000c */
};

struct __peak2d_config_data {
	/* peak2d */
	unsigned int level; /* detail level */

	/* size */
	int inw; /* overlay width */
	int inh; /* overlay height */
	int outw; /* overlay scale width */
	int outh; /* overlay scale height */

};

#endif
