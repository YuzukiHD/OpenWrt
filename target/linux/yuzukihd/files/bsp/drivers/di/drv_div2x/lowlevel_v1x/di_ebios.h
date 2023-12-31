/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * Allwinner SoCs de-interlace driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __DI_EBIOS_H__
#define __DI_EBIOS_H__
#include <linux/types.h>

typedef struct __SCAL_SRC_TYPE {
	/* 0:plannar; 1: interleaved; 2: plannar uv combined;
	 * 4: plannar mb; 6: uv combined mb
	 */
	__u8    mod;
	/* 0:yuv444; 1: yuv422; 2: yuv420; 3:yuv411; 4: csi rgb; 5:rgb888 */
	__u8    fmt;
	__u8    ps;        /*  */
} __di_src_type_t;

typedef struct __SCAL_OUT_TYPE {
	/* 0:plannar rgb; 1: argb(byte0,byte1, byte2, byte3); 2:bgra;
	 * 4:yuv444; 5:yuv420; 6:yuv422; 7:yuv411
	 */
	__u8    fmt;
	__u8    ps;        /*  */
	/* output alpha channel enable, valid when rgb888fmt */
	__u8    alpha_en;
} __di_out_type_t;

typedef struct __SCAL_SRC_SIZE {
	__u32   src_width;
	__u32   src_height;
	__u32   scal_width;
	__u32   scal_height;
} __di_src_size_t;

typedef struct __SCAL_OUT_SIZE {
	__u32   width;
	__u32   height;
	__u32   fb_width;
	__u32   fb_height;
} __di_out_size_t;

typedef struct _SCAL_BUF_ADDR {
	__u32   ch0_addr;
	__u32   ch1_addr;
	__u32   ch2_addr;
} __di_buf_addr_t;


typedef enum {
	DI_BGRA = 0,
	DI_ARGB = 1,
	DI_AYUV = 0,
	DI_VUYA = 1,
	DI_UVUV = 0,
	DI_VUVU = 1,
	DI_UYVY = 0,
	DI_YUYV = 1,
	DI_VYUY = 2,
	DI_YVYU = 3,
	DI_RGB565 = 0,
	DI_BGR565 = 1,
	DI_ARGB4444 = 0,
	DI_BGRA4444 = 1,
	DI_ARGB1555 = 0,
	DI_BGRA5551 = 1
} __di_ps_t;

typedef enum {
	DI_PLANNAR = 0,
	DI_INTERLEAVED,
	DI_UVCOMBINED,
	DI_PLANNARMB = 4,
	DI_UVCOMBINEDMB = 6
} __di_inmode_t;


typedef enum {
	DI_INYUV444 = 0,
	DI_INYUV422,
	DI_INYUV420,
	DI_INYUV411,
	DI_INRGB565,
	DI_INRGB888,
	DI_INRGB4444,
	DI_INRGB1555
} __di_infmt_t;

typedef enum {
	DI_OUTPRGB888 = 0,
	DI_OUTI0RGB888,
	DI_OUTI1RGB888,
	DI_OUTPYUV444 = 4,
	DI_OUTPYUV420,
	DI_OUTPYUV422,
	DI_OUTPYUV411,
	DI_OUTUVCYUV420 = 13
} __di_outfmt_t;


typedef union {
	u32 dwval;
	struct {
		u32 en                 :  1;    /* Default: 0x0; */
		u32 res0               : 31;    /* Default:; */
	} bits;
} DI_EN_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 reg_rdy_en         :  1;    /* Default: 0x0; */
		u32 coef_rdy_en        :  1;    /* Default: 0x0; */
		u32 wb_en              :  1;    /* Default: 0x0; */
		u32 res0               :  5;    /* Default:; */
		u32 out_port_sel       :  2;    /* Default: 0x0; */
		u32 res1               :  1;    /* Default:; */
		u32 out_ctrl           :  1;    /* Default: 0x0; */
		u32 in_ctrl            :  3;    /* Default: 0x0; */
		u32 res2               :  1;    /* Default:; */
		u32 frm_start          :  1;    /* Default: 0x0; */
		u32 res3               :  6;    /* Default:; */
		/* fir coef ram access control, for  single buffer */
		u32 coef_access_ctrl   :  1;
		u32 res4               :  8;    /* Default:; */
	} bits;
} DI_FRM_CTRL_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 res0               :  1;    /* Default:; */
		u32 csc_bypass_en      :  1;    /* Default: 0x0; */
		u32 res1               : 28;    /* Default:; */
		u32 sram_map_sel       :  2;    /* Default: 0x0; */
	} bits;
} DI_BYPASS_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 res0               :  8;    /* Default:; */
		u32 linebuf_agth       :  1;    /* Default: 0x0; */
		u32 res1               : 23;    /* Default:; */
	} bits;
} DI_AGTH_SEL_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 trig_line          : 13;    /* Default: 0x0; */
		u32 res0               :  2;    /* Default:; */
		u32 field_sel          :  1;    /* Default: 0x0; */
		u32 current_line       : 12;    /* Default: 0x0; */
		u32 res1               :  4;    /* Default:; */
	} bits;
} DI_LINT_CTRL_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 prefrm_addr;    /* Default: 0x0; */
	} bits;
} DI_3D_PRELUMA_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 buf_addr;    /* Default: 0x0; */
	} bits;
} DI_BUF_ADDR0_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 buf_addr;    /* Default: 0x0; */
	} bits;
} DI_BUF_ADDR1_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 buf_addr;    /* Default: 0x0; */
	} bits;
} DI_BUF_ADDR2_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 field_cnt          :  8;    /* Default: 0x0; */
		u32 valid_field_cnt    :  3;    /* Default: 0x0; */
		u32 res0               :  1;    /* Default:; */
		u32 field_loop_mod     :  1;    /* Default: 0x0; */
		u32 res1               : 11;    /* Default:; */
		u32 fir_offset         :  6;    /* Default: 0x20; */
		u32 res2               :  2;    /* Default:; */
	} bits;
} DI_FIELD_CTRL_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 x_offset0          :  5;    /* Default: 0x0; */
		u32 res0               :  3;    /* Default:; */
		u32 y_offset0          :  5;    /* Default: 0x0; */
		u32 res1               :  3;    /* Default:; */
		u32 x_offset1          :  5;    /* Default: 0x0; */
		u32 res2               : 11;    /* Default:; */
	} bits;
} DI_TB_OFF0_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 x_offset0          :  5;    /* Default: 0x0; */
		u32 res0               :  3;    /* Default:; */
		u32 y_offset0          :  5;    /* Default: 0x0; */
		u32 res1               :  3;    /* Default:; */
		u32 x_offset1          :  5;    /* Default: 0x0; */
		u32 res2               : 11;    /* Default:; */
	} bits;
} DI_TB_OFF1_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 x_offset0          :  5;    /* Default: 0x0; */
		u32 res0               :  3;    /* Default:; */
		u32 y_offset0          :  5;    /* Default: 0x0; */
		u32 res1               :  3;    /* Default:; */
		u32 x_offset1          :  5;    /* Default: 0x0; */
		u32 res2               : 11;    /* Default:; */
	} bits;
} DI_TB_OFF2_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 prefrm_addr;    /* Default: 0x0; */
	} bits;
} DI_3D_PRECHROMA_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 line_stride;    /* Default: 0x0; */
	} bits;
} DI_LINESTRD0_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 line_stride;    /* Default: 0x0; */
	} bits;
} DI_LINESTRD1_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 line_stride;    /* Default: 0x0; */
	} bits;
} DI_LINESTRD2_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 data_ps            :  2;    /* Default: 0x0; */
		u32 res0               :  2;    /* Default:; */
		u32 data_fmt           :  3;    /* Default: 0x0; */
		u32 res1               :  1;    /* Default:; */
		u32 data_mod           :  3;    /* Default: 0x0; */
		u32 res2               :  1;    /* Default:; */
		u32 scan_mod           :  1;    /* Default: 0x0; */
		u32 res3               :  1;    /* Default:; */
		u32 a_coef_sel         :  1;    /* Default: 0x0; */
		u32 res4               :  1;    /* Default:; */
		u32 byte_seq           :  1;    /* Default: 0x0; */
		u32 res5               : 15;    /* Default:; */
	} bits;
} DI_INPUT_FMT_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 wb_addr;    /* Default: 0x0; */
	} bits;
} DI_WB_ADDR0_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 wb_addr;    /* Default: 0x0; */
	} bits;
} DI_WB_ADDR1_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 wb_addr;    /* Default: 0x0; */
	} bits;
} DI_WB_ADDR2_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 data_fmt           :  4;    /* Default: 0x0; */
		u32 scan_mod           :  1;    /* Default: 0x0; */
		u32 data_ps            :  2;    /* Default:; */
		u32 alpha_en           :  1;    /* Default: 0x0; */
		u32 byte_seq           :  1;    /* Default: 0x0; */
		u32 res2               : 23;    /* Default:; */
	} bits;
} DI_OUTPUT_FMT_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 res0               :  7;    /* Default:; */
		u32 wb_en              :  1;    /* Default: 0x0; */
		u32 res1               :  1;    /* Default:; */
		u32 line_en            :  1;    /* Default: 0x0; */
		u32 reg_load_en        :  1;    /* Default: 0x0; */
		u32 res2               : 21;    /* Default:; */
	} bits;
} DI_INT_EN_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 res0               :  7;    /* Default:; */
		u32 wb_status          :  1;    /* Default: 0x0; */
		u32 res1               :  1;    /* Default:; */
		u32 line_status        :  1;    /* Default: 0x0; */
		u32 reg_load_status    :  1;    /* Default: 0x0; */
		u32 res2               : 21;    /* Default:; */
	} bits;
} DI_INT_STATUS_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 frm_busy           :  1;    /* Default: 0x0; */
		u32 wb_status          :  1;    /* Default: 0x0; */
		u32 cfg_pending        :  1;    /* Default: 0x0; */
		u32 res0               :  1;    /* Default:; */
		u32 dram_status        :  1;    /* Default: 0x0; */
		u32 lcd_field          :  1;    /* Default: 0x0; */
		u32 res1               :  5;    /* Default:; */
		/* fir coef access status, for single buffer */
		u32 coef_access_status :  1;
		u32 wb_err_status      :  1;    /* Default: 0x0; */
		u32 res2               :  1;    /* Default:; */
		u32 wb_err_losedata    :  1;    /* Default: 0x0; */
		u32 wb_err_sync        :  1;    /* Default: 0x0; */
		u32 line_on_sync       : 13;    /* Default: 0x0; */
		u32 res3               :  3;    /* Default:; */
	} bits;
} DI_STATUS_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 coef               : 13;    /* Default: 0x0; */
		u32 res0               : 19;    /* Default:; */
	} bits;
} DI_CSC_COEF00_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 coef               : 13;    /* Default: 0x0; */
		u32 res0               : 19;    /* Default:; */
	} bits;
} DI_CSC_COEF01_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 coef               : 13;    /* Default: 0x0; */
		u32 res0               : 19;    /* Default:; */
	} bits;
} DI_CSC_COEF02_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 cont               : 14;    /* Default: 0x0; */
		u32 res0               : 18;    /* Default:; */
	} bits;
} DI_CSC_COEF03_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 coef               : 13;    /* Default: 0x0; */
		u32 res0               : 19;    /* Default:; */
	} bits;
} DI_CSC_COEF10_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 coef               : 13;    /* Default: 0x0; */
		u32 res0               : 19;    /* Default:; */
	} bits;
} DI_CSC_COEF11_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 coef               : 13;    /* Default: 0x0; */
		u32 res0               : 19;    /* Default:; */
	} bits;
} DI_CSC_COEF12_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 cont               : 14;    /* Default: 0x0; */
		u32 res0               : 18;    /* Default:; */
	} bits;
} DI_CSC_COEF13_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 coef               : 13;    /* Default: 0x0; */
		u32 res0               : 19;    /* Default:; */
	} bits;
} DI_CSC_COEF20_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 coef               : 13;    /* Default: 0x0; */
		u32 res0               : 19;    /* Default:; */
	} bits;
} DI_CSC_COEF21_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 coef               : 13;    /* Default: 0x0; */
		u32 res0               : 19;    /* Default:; */
	} bits;
} DI_CSC_COEF22_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 cont               : 14;    /* Default: 0x0; */
		u32 res0               : 18;    /* Default:; */
	} bits;
} DI_CSC_COEF23_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 en                 :  1;    /* Default: 0x0; */
		u32 res0               :  7;    /* Default:; */
		u32 flag_out_en        :  1;    /* Default: 0x0; */
		u32 res1               :  7;    /* Default:; */
		u32 mod                :  2;    /* Default: 0x0; */
		u32 res2               :  6;    /* Default:; */
		u32 diagintp_en        :  1;    /* Default: 0x0; */
		u32 tempdiff_en        :  1;    /* Default: 0x0; */
		u32 res3               :  6;    /* Default:; */
	} bits;
} DI_DI_CTRL_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 th0                :  7;    /* Default: 0x28; */
		u32 res0               :  1;    /* Default:; */
		u32 th1                :  7;    /* Default: 0x5; */
		u32 res1               :  9;    /* Default:; */
		u32 th3                :  8;    /* Default: 0x8; */
	} bits;
} DI_DI_DIAGINTP_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 sad_central_th     :  7;    /* Default: 0xA; */
		u32 res0               :  1;    /* Default:; */
		u32 ambiguity_th       :  7;    /* Default: 0xA; */
		u32 res1               :  1;    /* Default:; */
		u32 direct_dither_th   : 11;    /* Default: 0xF; */
		u32 res2               :  5;    /* Default:; */
	} bits;
} DI_DI_TEMPDIFF_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 minlumath          :  8;    /* Default: 0x9; */
		u32 maxlumath          :  8;    /* Default: 0x10; */
		u32 avglumashifter     :  8;    /* Default: 0x6; */
		u32 pixel_static_th    :  2;    /* Default: 0x3; */
		u32 res0               :  6;    /* Default:; */
	} bits;
} DI_DI_LUMA_TH_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 th2                :  8;    /* Default: 0xA; */
		u32 res0               :  8;    /* Default:; */
		u32 th3                :  8;    /* Default: 0x14; */
		u32 res1               :  8;    /* Default:; */
	} bits;
} DI_DI_SPATCOMP_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 chroma_diff_th     :  8;    /* Default: 0x5; */
		u32 res0               :  8;    /* Default:; */
		u32 luma               :  6;    /* Default: 0x1F; */
		u32 res1               :  2;    /* Default:; */
		u32 chroma             :  6;    /* Default: 0x1F; */
		u32 res2               :  2;    /* Default:; */
	} bits;
} DI_DI_CHROMADIFF_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 prefrm_addr;    /* Default: 0x0; */
	} bits;
} DI_DI_PRELUMA_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 prefrm_addr;    /* Default: 0x0; */
	} bits;
} DI_DI_PRECHROMA_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 tile_flag_addr0;    /* Default: 0x0; */
	} bits;
} DI_DI_TILEFLAG0_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 tile_flag_addr1;    /* Default: 0x0; */
	} bits;
} DI_DI_TILEFLAG1_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 tile_flag_linestrd;    /* Default: 0x200; */
	} bits;
} DI_DI_FLAGLINESTRD_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 field_cnt          :  8;    /* Default: 0x0; */
		u32 valid_field_cnt    :  3;    /* Default: 0x0; */
		u32 res0               :  1;
		u32 field_loop_mod     :  1;    /* Default: 0x0; */
		u32 res1               :  19;
	} bits;
} DI_DI_FLAG_SEQ_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 en                 :  1;    /* Default: 0x0; */
		u32 res0               : 31;    /* Default:; */
	} bits;
} DI_WB_LINESTRD_EN_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 line_strd;    /* Default: 0x0; */
	} bits;
} DI_WB_LINESTRD0_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 line_strd;    /* Default: 0x0; */
	} bits;
} DI_WB_LINESTRD1_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 line_strd;    /* Default: 0x0; */
	} bits;
} DI_WB_LINESTRD2_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 mod_sel            :  2;    /* Default: 0x0; */
		u32 res0               :  6;    /* Default:; */
		u32 ci_out_en          :  1;    /* Default: 0x0; */
		u32 res1               :  1;    /* Default:; */
		u32 ss_out_en          :  1;    /* Default: 0x0; */
		u32 li_in_en           :  1;    /* Default: 0x0; */
		u32 tb_out_scan_mod    :  1;    /* Default: 0x0; */
		u32 res2               :  3;    /* Default:; */
		u32 ci_out_mod         :  3;    /* Default: 0x0; */
		u32 res3               :  5;    /* Default:; */
		u32 tb_out_mod_field   :  2;    /* Default: 0x0; */
		u32 res4               :  6;    /* Default:; */
	} bits;
} DI_3D_CTRL_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 right_ch0_addr;    /* Default: 0x0; */
	} bits;
} DI_3D_BUF_ADDR0_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 right_ch1_addr;    /* Default: 0x0; */
	} bits;
} DI_3D_BUF_ADDR1_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 right_ch2_addr;    /* Default: 0x0; */
	} bits;
} DI_3D_BUF_ADDR2_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 x_offset0          :  5;    /* Default: 0x0; */
		u32 res0               :  3;    /* Default:; */
		u32 y_offset0          :  5;    /* Default: 0x0; */
		u32 res1               :  3;    /* Default:; */
		u32 x_offset1          :  5;    /* Default: 0x0; */
		u32 res2               : 11;    /* Default:; */
	} bits;
} DI_3D_TB_OFF0_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 x_offset0          :  5;    /* Default: 0x0; */
		u32 res0               :  3;    /* Default:; */
		u32 y_offset0          :  5;    /* Default: 0x0; */
		u32 res1               :  3;    /* Default:; */
		u32 x_offset1          :  5;    /* Default: 0x0; */
		u32 res2               : 11;    /* Default:; */
	} bits;
} DI_3D_TB_OFF1_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 x_offset0          :  5;    /* Default: 0x0; */
		u32 res0               :  3;    /* Default:; */
		u32 y_offset0          :  5;    /* Default: 0x0; */
		u32 res1               :  3;    /* Default:; */
		u32 x_offset1          :  5;    /* Default: 0x0; */
		u32 res2               : 11;    /* Default:; */
	} bits;
} DI_3D_TB_OFF2_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 wb_stride          :  5;    /* Default: 0x0; */
	} bits;
} DI_3D_WB_STRD_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 in_width           : 13;    /* Default: 0x0; */
		u32 res0               :  3;    /* Default:; */
		u32 in_height          : 13;    /* Default: 0x0; */
		u32 res1               :  3;    /* Default:; */
	} bits;
} DI_CH0_INSIZE_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 out_width          : 13;    /* Default: 0x0; */
		u32 res0               :  3;    /* Default:; */
		u32 out_height         : 13;    /* Default: 0x0; */
		u32 res1               :  3;    /* Default:; */
	} bits;
} DI_CH0_OUTSIZE_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 factor_frac        : 16;    /* Default: 0x0; */
		u32 factor_int         :  8;    /* Default: 0x0; */
		u32 res0               :  8;    /* Default:; */
	} bits;
} DI_CH0_HORZFACT_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 factor_frac        : 16;    /* Default: 0x0; */
		u32 factor_int         :  8;    /* Default: 0x0; */
		u32 res0               :  8;    /* Default:; */
	} bits;
} DI_CH0_VERTFACT_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 phase              : 20;    /* Default: 0x0; */
		u32 res0               : 12;    /* Default:; */
	} bits;
} DI_CH0_HORZPHASE_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 phase              : 20;    /* Default: 0x0; */
		u32 res0               : 12;    /* Default:; */
	} bits;
} DI_CH0_VERTPHASE0_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 phase              : 20;    /* Default: 0x0; */
		u32 res0               : 12;    /* Default:; */
	} bits;
} DI_CH0_VERTPHASE1_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 tap0               :  7;    /* Default: 0x7D; */
		u32 res0               :  1;    /* Default:; */
		u32 tap1               :  7;    /* Default: 0x1; */
		u32 res1               :  1;    /* Default:; */
		u32 tap2               :  7;    /* Default: 0x1; */
		u32 res2               :  1;    /* Default:; */
		u32 tap3               :  7;    /* Default: 0x1; */
		u32 res3               :  1;    /* Default:; */
	} bits;
} DI_CH0_HORZTAP0_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 tap4               :  7;    /* Default: 0x1; */
		u32 res0               :  1;    /* Default:; */
		u32 tap5               :  7;    /* Default: 0x1; */
		u32 res1               :  1;    /* Default:; */
		u32 tap6               :  7;    /* Default: 0x1; */
		u32 res2               :  1;    /* Default:; */
		u32 tap7               :  7;    /* Default: 0x1; */
		u32 res3               :  1;    /* Default:; */
	} bits;
} DI_CH0_HORZTAP1_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 tap0               :  7;    /* Default: 0x7F; */
		u32 res0               :  1;    /* Default:; */
		u32 tap1               :  7;    /* Default: 0x1; */
		u32 res1               :  1;    /* Default:; */
		u32 tap2               :  7;    /* Default: 0x1; */
		u32 res2               :  1;    /* Default:; */
		u32 tap3               :  7;    /* Default: 0x1; */
		u32 res3               :  1;    /* Default:; */
	} bits;
} DI_CH0_VERTTAP_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 in_width           : 13;    /* Default: 0x0; */
		u32 res0               :  3;    /* Default:; */
		u32 in_height          : 13;    /* Default: 0x0; */
		u32 res1               :  3;    /* Default:; */
	} bits;
} DI_CH1_INSIZE_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 out_width          : 13;    /* Default: 0x0; */
		u32 res0               :  3;    /* Default:; */
		u32 out_height         : 13;    /* Default: 0x0; */
		u32 res1               :  3;    /* Default:; */
	} bits;
} DI_CH1_OUTSIZE_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 factor_frac        : 16;    /* Default: 0x0; */
		u32 factor_int         :  8;    /* Default: 0x0; */
		u32 res0               :  8;    /* Default:; */
	} bits;
} DI_CH1_HORZFACT_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 factor_frac        : 16;    /* Default: 0x0; */
		u32 factor_int         :  8;    /* Default: 0x0; */
		u32 res0               :  8;    /* Default:; */
	} bits;
} DI_CH1_VERTFACT_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 phase              : 20;    /* Default: 0x0; */
		u32 res0               : 12;    /* Default:; */
	} bits;
} DI_CH1_HORZPHASE_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 phase              : 20;    /* Default: 0x0; */
		u32 res0               : 12;    /* Default:; */
	} bits;
} DI_CH1_VERTPHASE0_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 phase              : 20;    /* Default: 0x0; */
		u32 res0               : 12;    /* Default:; */
	} bits;
} DI_CH1_VERTPHASE1_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 tap0               :  7;    /* Default: 0x7D; */
		u32 res0               :  1;    /* Default:; */
		u32 tap1               :  7;    /* Default: 0x1; */
		u32 res1               :  1;    /* Default:; */
		u32 tap2               :  7;    /* Default: 0x1; */
		u32 res2               :  1;    /* Default:; */
		u32 tap3               :  7;    /* Default: 0x1; */
		u32 res3               :  1;    /* Default:; */
	} bits;
} DI_CH1_HORZTAP0_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 tap4               :  7;    /* Default: 0x1; */
		u32 res0               :  1;    /* Default:; */
		u32 tap5               :  7;    /* Default: 0x1; */
		u32 res1               :  1;    /* Default:; */
		u32 tap6               :  7;    /* Default: 0x1; */
		u32 res2               :  1;    /* Default:; */
		u32 tap7               :  7;    /* Default: 0x1; */
		u32 res3               :  1;    /* Default:; */
	} bits;
} DI_CH1_HORZTAP1_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 tap0               :  7;    /* Default: 0x7F; */
		u32 res0               :  1;    /* Default:; */
		u32 tap1               :  7;    /* Default: 0x1; */
		u32 res1               :  1;    /* Default:; */
		u32 tap2               :  7;    /* Default: 0x1; */
		u32 res2               :  1;    /* Default:; */
		u32 tap3               :  7;    /* Default: 0x1; */
		u32 res3               :  1;    /* Default:; */
	} bits;
} DI_CH1_VERTTAP_REG_t;

typedef union {
	u32 dwval;
	struct {
		u32 tap0                         :  8;
		u32 tap1                         :  8;
		u32 tap2                         :  8;
		u32 tap3                         :  8;
	} bits;
} DI_CH0_HORZCOEF0_REGN_t;

typedef union {
	u32 dwval;
	struct {
		u32 tap4                         :  8;
		u32 tap5                         :  8;
		u32 tap6                         :  8;
		u32 tap7                         :  8;
	} bits;
} DI_CH0_HORZCOEF1_REGN_t;

typedef union {
	u32 dwval;
	struct {
		u32 tap0                         :  8;
		u32 tap1                         :  8;
		u32 tap2                         :  8;
		u32 tap3                         :  8;
	} bits;
} DI_CH0_VERTCOEF_REGN_t;

typedef union {
	u32 dwval;
	struct {
		u32 res0               :  32;    /*  */
	} bits;
} DI_RESEVED_REG_t;


/* device define */
typedef struct {
	DI_EN_REG_t                     modl_en;/* 0x00 */
	DI_FRM_CTRL_REG_t               frm_ctrl;/* 0x04 */
	DI_BYPASS_REG_t                 bypass;/* 0x08 */
	DI_AGTH_SEL_REG_t               agth_sel;/* 0x0c */
	DI_LINT_CTRL_REG_t              lint_ctrl;/* 0x10 */
	DI_RESEVED_REG_t		res0x14[2];/* 0x14~0x1b */
	DI_3D_PRELUMA_REG_t		trd_preluma;/* 0x1c */
	DI_BUF_ADDR0_REG_t              buf_addr0;/* 0x20 */
	DI_BUF_ADDR1_REG_t              buf_addr1;/* 0x24 */
	DI_BUF_ADDR2_REG_t              buf_addr2;/* 0x28 */
	DI_FIELD_CTRL_REG_t             field_ctrl;/* 0x2c */
	DI_TB_OFF0_REG_t                tb_off0;/* 0x30 */
	DI_TB_OFF1_REG_t                tb_off1;/* 0x34 */
	DI_TB_OFF2_REG_t                tb_off2;/* 0x38 */
	DI_3D_PRECHROMA_REG_t		trd_prechroma;/* 0x3c */
	DI_LINESTRD0_REG_t              linestrd0;/* 0x40 */
	DI_LINESTRD1_REG_t              linestrd1;/* 0x44 */
	DI_LINESTRD2_REG_t              linestrd2;/* 0x48 */
	DI_INPUT_FMT_REG_t              input_fmt;/* 0x4c */
	DI_WB_ADDR0_REG_t               wb_addr0;/* 0x50 */
	DI_WB_ADDR1_REG_t               wb_addr1;/* 0x54 */
	DI_WB_ADDR2_REG_t               wb_addr2;/* 0x58 */
	DI_OUTPUT_FMT_REG_t             output_fmt;/* 0x5c */
	DI_INT_EN_REG_t                 int_en;/* 0x60 */
	DI_INT_STATUS_REG_t             int_status;/* 0x64 */
	DI_STATUS_REG_t                 status;/* 0x68 */
	DI_RESEVED_REG_t                res0x6c;/* 0x6c */
	DI_CSC_COEF03_REG_t             csc_coef[12];/* 0x70~0x9f */
	DI_DI_CTRL_REG_t                di_ctrl;/* 0xa0 */
	DI_DI_DIAGINTP_REG_t            di_diagintp;/* 0xa4 */
	DI_DI_TEMPDIFF_REG_t            di_tempdiff;/* 0xa8 */
	DI_DI_LUMA_TH_REG_t             di_lumath;/* 0xac */
	DI_DI_SPATCOMP_REG_t            di_spatcomp;/* 0xb0 */
	DI_DI_CHROMADIFF_REG_t          di_chromadiff;/* 0xb4 */
	DI_DI_PRELUMA_REG_t             di_preluma;/* 0xb8 */
	DI_DI_PRECHROMA_REG_t           di_prechroma;/* 0xbc */
	DI_DI_TILEFLAG0_REG_t	        di_tileflag0;/* 0xc0 */
	DI_DI_TILEFLAG1_REG_t           di_tileflag1;/* 0xc4 */
	DI_DI_FLAGLINESTRD_REG_t	di_flaglinestrd;/* 0xc8 */
	DI_DI_FLAG_SEQ_REG_t		di_flagseq;/* 0xcc */
	DI_WB_LINESTRD_EN_REG_t         wb_linestrd_en;/* 0xd0 */
	DI_WB_LINESTRD0_REG_t           wb_linestrd0;/* 0xd4 */
	DI_WB_LINESTRD1_REG_t           wb_linestrd1;/* 0xd8 */
	DI_WB_LINESTRD2_REG_t           wb_linestrd2;/* 0xdc */
	DI_3D_CTRL_REG_t                trd_ctrl;/* 0xe0 */
	DI_3D_BUF_ADDR0_REG_t           trd_buf_addr0;/* 0xe4 */
	DI_3D_BUF_ADDR1_REG_t           trd_buf_addr1;/* 0xe8 */
	DI_3D_BUF_ADDR2_REG_t           trd_buf_addr2;/* 0xec */
	DI_3D_TB_OFF0_REG_t             trd_tb_off0;/* 0xf0 */
	DI_3D_TB_OFF1_REG_t             trd_tb_off1;/* 0xf4 */
	DI_3D_TB_OFF2_REG_t             trd_tb_off2;/* 0xf8 */
	DI_3D_WB_STRD_REG_t		trd_wb_strd;/* 0xfc */
	DI_CH0_INSIZE_REG_t             ch0_insize;/* 0x100 */
	DI_CH0_OUTSIZE_REG_t            ch0_outsize;/* 0x104 */
	DI_CH0_HORZFACT_REG_t           ch0_horzfact;/* 0x108 */
	DI_CH0_VERTFACT_REG_t           ch0_vertfact;/* 0x10c */
	DI_CH0_HORZPHASE_REG_t          ch0_horzphase;/* 0x110 */
	DI_CH0_VERTPHASE0_REG_t         ch0_vertphase0;/* 0x114 */
	DI_CH0_VERTPHASE1_REG_t         ch0_vertphase1;/* 0x118 */
	DI_RESEVED_REG_t		res0x11c;/* 0x11c */
	DI_CH0_HORZTAP0_REG_t           ch0_horztap0;/* 0x120 */
	DI_CH0_HORZTAP1_REG_t           ch0_horztap1;/* 0x124 */
	DI_CH0_VERTTAP_REG_t            ch0_verttap;/* 0x128 */
	DI_RESEVED_REG_t		res0x12c[53];/* 0x12c~0x1FF */
	DI_CH1_INSIZE_REG_t             ch1_insize;/* 0x200 */
	DI_CH1_OUTSIZE_REG_t            ch1_outsize;/* 0x204 */
	DI_CH1_HORZFACT_REG_t           ch1_horzfact;/* 0x208 */
	DI_CH1_VERTFACT_REG_t           ch1_vertfact;/* 0x20c */
	DI_CH1_HORZPHASE_REG_t          ch1_horzphase;/* 0x210 */
	DI_CH1_VERTPHASE0_REG_t         ch1_vertphase0;/* 0x214 */
	DI_CH1_VERTPHASE1_REG_t         ch1_vertphase1;/* 0x218 */
	DI_RESEVED_REG_t		res0x21c;/* 0x21c */
	DI_CH1_HORZTAP0_REG_t           ch1_horztap0;/* 0x220 */
	DI_CH1_HORZTAP1_REG_t           ch1_horztap1;/* 0x224 */
	DI_CH1_VERTTAP_REG_t            ch1_verttap;/* 0x228 */
	DI_RESEVED_REG_t		res0x22c[117];/* 0x22c~0x3FF */
	DI_CH0_HORZCOEF0_REGN_t         ch0_horzcoef0[32];/* 0x400~0x47f */
	DI_CH0_HORZCOEF1_REGN_t         ch0_horzcoef1[32];/* 0x480~0x4ff */
	DI_CH0_VERTCOEF_REGN_t          ch0_vertcoef[32];/* 0x500~0x5ff */
	DI_RESEVED_REG_t		res0x580[32];/* 0x580~0x57f */
	DI_CH0_HORZCOEF0_REGN_t         ch1_horzcoef0[32];/* 0x600~0x67f */
	DI_CH0_HORZCOEF1_REGN_t         ch1_horzcoef1[32];/* 0x680~6ff */
	DI_CH0_VERTCOEF_REGN_t          ch1_vertcoef[32];/* 0x700~0x77f */
	DI_RESEVED_REG_t		res0x780[32];/* 0x780~0x7ff */
	DI_CH0_HORZCOEF0_REGN_t         ch3_horzcoef0[32];/* 0x800~0x87f */
	DI_CH0_HORZCOEF1_REGN_t         ch3_horzcoef1[32];/* 0x880~8ff */
	DI_CH0_VERTCOEF_REGN_t          ch3_vertcoef[32];/* 0x900~0x97f */
	DI_RESEVED_REG_t		res0xA80[32];/* 0xa80~0xaff */
} __di_dev_t;

__s32 DI_Init(void);
__s32 DI_Config_Src(__di_buf_addr_t *addr, __di_src_size_t *size,
			__di_src_type_t *type);
__s32 DI_Set_Scaling_Factor(__di_src_size_t *in_size,
			__di_out_size_t *out_size);
__s32 DI_Set_Scaling_Coef(__di_src_size_t *in_size, __di_out_size_t *out_size,
			__di_src_type_t *in_type,  __di_out_type_t *out_type);
__s32 DI_Set_Out_Format(__di_out_type_t *out_type);
__s32 DI_Set_Out_Size(__di_out_size_t *out_size);
__s32 DI_Set_Writeback_Addr(__di_buf_addr_t *addr);
__s32 DI_Set_Writeback_Addr_ex(__di_buf_addr_t *addr, __di_out_size_t *size,
			__di_out_type_t *type);
__s32 DI_Set_Di_Ctrl(__u8 en, __u8 mode, __u8 diagintp_en, __u8 tempdiff_en);
__s32 DI_Set_Di_PreFrame_Addr(__u32 luma_addr, __u32 chroma_addr);
__s32 DI_Set_Di_MafFlag_Src(__u32 cur_addr, __u32 pre_addr, __u32 stride);
__s32 DI_Set_Di_Field(u32 field);
__s32 DI_Set_Reg_Rdy(void);
__s32 DI_Enable(void);
__s32 DI_Module_Enable(void);
__s32 DI_Set_Reset(void);
__s32 DI_Set_Irq_Enable(__u32 enable);
__s32 DI_Clear_irq(void);
__s32 DI_Get_Irq_Status(void);
__s32 DI_Set_Writeback_Start(void);
__s32 DI_Internal_Set_Clk(__u32 enable);
__u32 DI_VAtoPA(__u32 va);

#endif
