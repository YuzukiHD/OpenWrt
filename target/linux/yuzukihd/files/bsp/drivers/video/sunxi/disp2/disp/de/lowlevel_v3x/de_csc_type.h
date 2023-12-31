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

/*****************************************************************************
 *  All Winner Tech, All Right Reserved. 2015-2016 Copyright (c)
 *
 *  File name   :       de_csc_type.h
 *
 *  Description :       display engine csc struct declaration
 *
 *  History     :       2016/03/16  iptang  v0.1  Initial version
****************************************************************************/

#ifndef __DE_CSC_TYPE_H__
#define __DE_CSC_TYPE_H__

union __csc_coeff_reg_t {
	unsigned int dwval;
	struct {
		unsigned int c:20;
		unsigned int r0:12;
	} bits;
};

union __csc_const_reg_t {
	unsigned int dwval;
	struct {
		unsigned int c:11;
		unsigned int r0:5;
		unsigned int d:11;
		unsigned int r1:5;
	} bits;
};

/* Channel CSC */
struct __ccsc_reg_t {
	union __csc_coeff_reg_t c0[3];
	union __csc_const_reg_t d0;
	union __csc_coeff_reg_t c1[3];
	union __csc_const_reg_t d1;
	union __csc_coeff_reg_t c2[3];
	union __csc_const_reg_t d2;
};

/* FCE CSC */
union __vep_csc_en_reg_t {
	unsigned int dwval;
	struct {
		unsigned int en:1;
		unsigned int r0:31;
	} bits;
};

union __vep_csc_const_reg_t {
	unsigned int dwval;
	struct {
		unsigned int constant:10;
		unsigned int r0:22;
	} bits;
};

union __vep_csc_coef_reg_t {
	unsigned int dwval;
	struct {
		unsigned int coef:20;
		unsigned int r0:12;
	} bits;
};

struct __icsc_reg_t {
	union __vep_csc_en_reg_t en;
	union __vep_csc_const_reg_t d[3];
	union __vep_csc_coef_reg_t c0[3];
	union __vep_csc_const_reg_t c03;
	union __vep_csc_coef_reg_t c1[3];
	union __vep_csc_const_reg_t c13;
	union __vep_csc_coef_reg_t c2[3];
	union __vep_csc_const_reg_t c23;
};

struct __fcc_csc_reg_t {
	/* FCC input CSC */
	union __vep_csc_coef_reg_t in_c0[3];
	union __vep_csc_const_reg_t in_c03;
	union __vep_csc_coef_reg_t in_c1[3];
	union __vep_csc_const_reg_t in_c13;
	union __vep_csc_coef_reg_t in_c2[3];
	union __vep_csc_const_reg_t in_c23;
	union __vep_csc_const_reg_t in_d[3];
	unsigned int res;

	/* FCC output CSC */
	union __vep_csc_coef_reg_t out_c0[3];
	union __vep_csc_const_reg_t out_c03;
	union __vep_csc_coef_reg_t out_c1[3];
	union __vep_csc_const_reg_t out_c13;
	union __vep_csc_coef_reg_t out_c2[3];
	union __vep_csc_const_reg_t out_c23;
	union __vep_csc_const_reg_t out_d[3];
};

#endif
