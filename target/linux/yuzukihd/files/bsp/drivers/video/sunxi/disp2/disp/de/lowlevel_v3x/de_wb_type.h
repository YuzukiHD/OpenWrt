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

/**
 *	All Winner Tech, All Right Reserved. 2014-2015 Copyright (c)
 *
 *	File name   :       de_wb_type.h
 *
 *	Description :       display engine 2.0 wbc struct declaration
 *
 *	History     :       2014/03/03   wangxuan   initial version
 *
 */
#ifndef __DE_WB_TYPE_H__
#define __DE_WB_TYPE_H__

#define ____SEPARATOR_DEFEINE____
#define WB_END_IE	0x1
#define WB_FINISH_IE	(0x1<<4)
#define WB_FIFO_OVERFLOW_ERROR_IE	(0x1<<5)
#define WB_TIMEOUT_ERROR_IE	(0x1<<6)

#define MININWIDTH 8
#define MININHEIGHT 4
/* support 8192,limit by LCD */
#define MAXINWIDTH 4096
/* support 8192,limit by LCD */
#define MAXINHEIGHT 4096
#define LINE_BUF_LEN 2048
#define LOCFRACBIT 18
#define SCALERPHASE 16

#define ____SEPARATOR_REGISTERS____
union __wb_gctrl_reg_t {
	unsigned int dwval;
	struct {
		unsigned int wb_start:1;
		unsigned int r0:3;
		unsigned int soft_reset:1;
		unsigned int r1:11;
		unsigned int in_port_sel:2;
		unsigned int r2:10;
		unsigned int auto_gate_en:1;
		unsigned int clk_gate:1;
		unsigned int r3:1;
		unsigned int bist_en:1;
	} bits;
};

union __wb_size_reg_t {
	unsigned int dwval;
	struct {
		unsigned int width:13;
		unsigned int r0:3;
		unsigned int height:13;
		unsigned int r1:3;
	} bits;
};

union __wb_crop_coord_reg_t {
	unsigned int dwval;
	struct {
		unsigned int crop_left:13;
		unsigned int r0:3;
		unsigned int crop_top:13;
		unsigned int r1:3;
	} bits;
};

union __wb_crop_size_reg_t {
	unsigned int dwval;
	struct {
		unsigned int crop_width:13;
		unsigned int r0:3;
		unsigned int crop_height:13;
		unsigned int r1:3;
	} bits;
};

union __wb_addr_reg_t {
	unsigned int dwval;
	struct {
		unsigned int addr:32;
	} bits;
};

union __wb_high_addr_reg_t {
	unsigned int dwval;
	struct {
		unsigned int ch0_h_addr:8;
		unsigned int ch1_h_addr:8;
		unsigned int ch2_h_addr:8;
		unsigned int r0:8;
	} bits;
};

union __wb_pitch_reg_t {
	unsigned int dwval;
	struct {
		unsigned int pitch:32;
	} bits;
};

union __wb_addr_switch_reg_t {
	unsigned int dwval;
	struct {
		unsigned int cur_group:1;
		unsigned int r0:15;
		unsigned int auto_switch:1;
		unsigned int r1:3;
		unsigned int manual_group:1;
		unsigned int r2:11;
	} bits;
};

union __wb_format_reg_t {
	unsigned int dwval;
	struct {
		unsigned int format:4;
		unsigned int r0:28;
	} bits;
};

union __wb_int_reg_t {
	unsigned int dwval;
	struct {
		unsigned int int_en:1;
		unsigned int r0:31;
	} bits;
};

union __wb_status_reg_t {
	unsigned int dwval;
	struct {
		unsigned int irq:1;
		unsigned int r0:3;
		unsigned int finish:1;
		unsigned int overflow:1;
		unsigned int timeout:1;
		unsigned int r1:1;
		unsigned int busy:1;
		unsigned int r2:23;
	} bits;
};

union __wb_bypass_reg_t {
	unsigned int dwval;
	struct {
		unsigned int csc_en:1;
		unsigned int cs_en:1;
		unsigned int fs_en:1;
		unsigned int r0:29;
	} bits;
};

union __wb_cs_reg_t {
	unsigned int dwval;
	struct {
		unsigned int m:13;
		unsigned int r1:3;
		unsigned int n:13;
		unsigned int r0:3;
	} bits;
};

union __wb_fs_size_reg_t {
	unsigned int dwval;
	struct {
		unsigned int width:13;
		unsigned int r1:3;
		unsigned int height:13;
		unsigned int r0:3;
	} bits;
};

union __wb_fs_step_reg_t {
	unsigned int dwval;
	struct {
		unsigned int r1:2;
		unsigned int frac:18;
		unsigned int intg:2;
		unsigned int r0:10;
	} bits;
};

union __wb_coeff_reg_t {
	unsigned int dwval;
	struct {
		unsigned int coef0:8;
		unsigned int coef1:8;
		unsigned int coef2:8;
		unsigned int coef3:8;
	} bits;
};

struct __wb_reg_t {
	union __wb_gctrl_reg_t gctrl;			/* 0x0000 */
	union __wb_size_reg_t size;			/* 0x0004 */
	union __wb_crop_coord_reg_t crop_coord;	/* 0x0008 */
	union __wb_crop_size_reg_t crop_size;		/* 0x000c */
	union __wb_addr_reg_t wb_addr_a0;		/* 0x0010 */
	union __wb_addr_reg_t wb_addr_a1;		/* 0x0014 */
	union __wb_addr_reg_t wb_addr_a2;		/* 0x0018 */
	union __wb_high_addr_reg_t wb_addr_ah;	/* 0x001c */
	union __wb_addr_reg_t wb_addr_b0;		/* 0x0020 */
	union __wb_addr_reg_t wb_addr_b1;		/* 0x0024 */
	union __wb_addr_reg_t wb_addr_b2;		/* 0x0028 */
	union __wb_high_addr_reg_t wb_addr_bh;	/* 0x002c */
	union __wb_pitch_reg_t wb_pitch0;		/* 0x0030 */
	union __wb_pitch_reg_t wb_pitch1;		/* 0x0034 */
	unsigned int res0[2];			/* 0x0038-0x003c */
	union __wb_addr_switch_reg_t addr_switch;	/* 0x0040 */
	union __wb_format_reg_t fmt;			/* 0x0044 */
	union __wb_int_reg_t intr;			/* 0x0048 */
	union __wb_status_reg_t status;		/* 0x004c */
	unsigned int res1;			/* 0x0050 */
	union __wb_bypass_reg_t bypass;		/* 0x0054 */
	unsigned int res2[6];			/* 0x0058-0x006c */
	union __wb_cs_reg_t cs_horz;			/* 0x0070 */
	union __wb_cs_reg_t cs_vert;			/* 0x0074 */
	unsigned int res3[2];			/* 0x0078-0x007c */
	union __wb_fs_size_reg_t fs_insize;		/* 0x0080 */
	union __wb_fs_size_reg_t fs_outsize;		/* 0x0084 */
	union __wb_fs_step_reg_t fs_hstep;		/* 0x0088 */
	union __wb_fs_step_reg_t fs_vstep;		/* 0x008c */
	unsigned int res4[92];			/* 0x0090-0x01fc */
	union __wb_coeff_reg_t yhcoeff[16];		/* 0X0200-0x23c */
	unsigned int res5[16];			/* 0X0240-0x27c */
	union __wb_coeff_reg_t chcoeff[16];		/* 0X0280-0x2bc */
	unsigned int res6[16];			/* 0x02c0-0x02fc */
};

enum wb_output_fmt {
	WB_FORMAT_RGB_888 = 0x0,
	WB_FORMAT_BGR_888 = 0x1,
	WB_FORMAT_ARGB_8888 = 0x4,
	WB_FORMAT_ABGR_8888 = 0x5,
	WB_FORMAT_BGRA_8888 = 0x6,
	WB_FORMAT_RGBA_8888 = 0x7,
	WB_FORMAT_YUV420_P = 0x8,
	WB_FORMAT_YUV420_SP_VUVU = 0xc,
	WB_FORMAT_YUV420_SP_UVUV = 0xd,
};

extern unsigned int wb_lan2coefftab16[16];
extern unsigned int wb_lan2coefftab16_down[16];

#endif
