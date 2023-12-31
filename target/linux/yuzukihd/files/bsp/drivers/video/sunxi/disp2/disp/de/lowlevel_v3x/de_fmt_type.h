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

#ifndef __DE_FMT_TYPE_H__
#define __DE_FMT_TYPE_H__

#include "de_rtmx.h"

#define FMT_OFST 0xA8000

union FMT_CTRL_REG {
	unsigned int dwval;
	struct {
		unsigned int en:1;
		unsigned int res:31;
	} bits;
};

union FMT_SIZE_REG {
	unsigned int dwval;
	struct {
		unsigned int width:13;
		unsigned int res0:3;
		unsigned int height:13;
		unsigned int res1:3;
	} bits;
};

union FMT_SWAP_REG {
	unsigned int dwval;
	struct {
		unsigned int swap_en:1;
		unsigned int res:31;
	} bits;
};

union FMT_BITDEPTH_REG {
	unsigned int dwval;
	struct {
		unsigned int outbitdepth:1;
		unsigned int res:31;
	} bits;
};

union FMT_FORMAT_REG {
	unsigned int dwval;
	struct {
		unsigned int colorspace:2;
		unsigned int res0:14;
		unsigned int pixel_format:2;
		unsigned int res1:14;
	} bits;
};

union FMT_COEF_REG {
	unsigned int dwval;
	struct {
		unsigned int c0_hcoef_sel:3;
		unsigned int res0:5;
		unsigned int c0_vcoef_sel:2;
		unsigned int res1:6;
		unsigned int c1_hcoef_sel:3;
		unsigned int res2:5;
		unsigned int c1_vcoef_sel:2;
		unsigned int res3:6;
	} bits;
};

union FMT_LIMIT_REG {
	unsigned int dwval;
	struct {
		unsigned int low:10;
		unsigned int res0:6;
		unsigned int high:10;
		unsigned int res1:6;
	} bits;
};

struct __fmt_reg_t {
	union FMT_CTRL_REG ctrl; /* 0x00 */
	union FMT_SIZE_REG size; /* 0x04 */
	union FMT_SWAP_REG swap; /* 0x08 */
	union FMT_BITDEPTH_REG bitdepth; /* 0x0c */
	union FMT_FORMAT_REG format; /* 0x10 */
	union FMT_COEF_REG coef; /* 0x14 */
	unsigned int reg[2]; /* 0x18/0x1c */
	union FMT_LIMIT_REG lmt_y; /* 0x20 */
	union FMT_LIMIT_REG lmt_c0; /* 0x24 */
	union FMT_LIMIT_REG lmt_c1; /* 0x28 */
};

#endif
