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

/* ********************************************************************************************************************* */
/* All Winner Tech, All Right Reserved. 2014-2015 Copyright (c) */
/*  */
/* File name   :	de_scaler.h */
/*  */
/* Description :	display engine 2.0 gsu/vsu basic function declaration */
/*  */
/* History     :	2014/03/20  vito cheng  v0.1  Initial version */
/*  */
/* ********************************************************************************************************************* */

#ifndef __DE_SCALER_H__
#define __DE_SCALER_H__

#include "de_rtmx.h"

/* GSU configuration */
#define GSU_PHASE_NUM            16
#define GSU_PHASE_FRAC_BITWIDTH  18 /* bit19 to bit2 is fraction part */
#define GSU_PHASE_FRAC_REG_SHIFT 2  /* bit19 to bit2 is fraction part, and bit1 to bit0 is void */
#define GSU_FB_FRAC_BITWIDTH     32 /* frame buffer information fraction part bit width */

/* VSU configuration */
#define VSU_PHASE_NUM            32
#define VSU_PHASE_FRAC_BITWIDTH  19 /* bit19 to bit1 is fraction part */
#define VSU_PHASE_FRAC_REG_SHIFT 1  /* bit19 to bit1 is fraction part, and bit0 is void */
#define VSU_FB_FRAC_BITWIDTH     32 /* frame buffer information fraction part bit width */

/* GSU/VSU size limitation */
#define VSU_OFST       0x20000      /* VSU0 offset based on RTMX */
#define SC_MIN_WIDTH   32
#define SC_MIN_HEIGHT  8

enum vsu_pixel_format {
	VSU_FORMAT_YUV422					= 0x00,
	VSU_FORMAT_YUV420					= 0x01,
	VSU_FORMAT_YUV411					= 0x02,
	VSU_FORMAT_RGB						= 0x03
};

/* VSU FUNCTION */
int de_vsu_init(unsigned int sel, uintptr_t reg_base);
int de_vsu_update_regs(unsigned int sel);
int de_vsu_set_reg_base(unsigned int sel, unsigned int chno, void *base);
int de_vsu_enable(unsigned int sel, unsigned int chno, unsigned int en);
int de_vsu_set_para(unsigned int sel, unsigned int chno, unsigned int enable, unsigned char fmt,
					unsigned int in_w, unsigned int in_h, unsigned int out_w, unsigned int out_h,
					scaler_para *ypara, scaler_para *cpara, unsigned char yv12_d1_en);
int de_vsu_calc_scaler_para(unsigned char fmt, de_rect64 crop, de_rect frame, de_rect *crop_fix,
							scaler_para *ypara, scaler_para *cpara);
int de_vsu_sel_ovl_scaler_para(unsigned char *en, scaler_para *layer_luma_scale_para, scaler_para *layer_chroma_scale_para,
							   scaler_para *ovl_luma_scale_para, scaler_para *ovl_chroma_scale_para);
int de_vsu_recalc_scale_para(int coarse_status, unsigned int vsu_outw, unsigned int vsu_outh,
							 unsigned int vsu_inw, unsigned int vsu_inh, unsigned int vsu_inw_c, unsigned int vsu_inh_c,
							 scaler_para *fix_y_para, scaler_para *fix_c_para);
int de_recalc_ovl_bld_for_scale(unsigned int scaler_en, unsigned char *lay_en, int laynum, scaler_para *step,
						 de_rect *layer, de_rect *bld_rect, unsigned int *ovlw, unsigned int *ovlh,
						 unsigned int gsu_sel, unsigned int scn_w, unsigned scn_h);

int de_get_d1_flag(unsigned int layer_en, unsigned char fmt, de_rect64 crop, de_rect frame,
		   unsigned int lcd_width, unsigned int lcd_height);
void de_d1_p2p_recalc(unsigned char yv12_d1_en, unsigned int lcd_width, unsigned int lcd_height,
		      de_rect64 *crop64, de_rect *frame, scaler_para *p2p_para);

/* GSU FUNCTION */
int de_gsu_init(unsigned int sel, uintptr_t reg_base);
int de_gsu_update_regs(unsigned int sel);
int de_gsu_set_reg_base(unsigned int sel, unsigned int chno, void *base);
int de_gsu_enable(unsigned int sel, unsigned int chno, unsigned int en);
int de_gsu_set_para(unsigned int sel, unsigned int chno, unsigned int enable,
					unsigned int in_w, unsigned int in_h, unsigned int out_w, unsigned int out_h, scaler_para *para);
int de_gsu_calc_scaler_para(de_rect64 crop, de_rect frame, de_rect *crop_fix, scaler_para *para);
int de_calc_ovl_coord(unsigned int frame_coord, unsigned int scale_step, int gsu_sel);
int de_gsu_sel_ovl_scaler_para(unsigned char *en, scaler_para *layer_scale_para, scaler_para *ovl_scale_para);

#endif
