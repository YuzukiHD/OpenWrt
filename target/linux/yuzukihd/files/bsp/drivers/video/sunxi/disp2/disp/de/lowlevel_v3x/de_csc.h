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

#ifndef __DE_CSC_H__
#define __DE_CSC_H__

#include "de_rtmx.h"

enum de_hdr_type {
	DE_SDR = 0,
	DE_WCG = 1,
	DE_HDR10 = 2,
	DE_HLG = 3,
};

int de_ccsc_apply(unsigned int sel, unsigned int ch_id,
		  struct disp_csc_config *config);
int de_ccsc_update_regs(unsigned int sel);
int de_ccsc_init(struct disp_bsp_init_para *para);
int de_ccsc_double_init(struct disp_bsp_init_para *para);
int de_ccsc_exit(void);
int de_ccsc_double_exit(void);
int de_csc_coeff_calc(unsigned int infmt, unsigned int incscmod,
		      unsigned int inrange, unsigned int outfmt,
		      unsigned int outcscmod, unsigned int outrange,
		      int *csc_coeff);
int de_cdc_coeff_set(unsigned int sel, unsigned int ch_id,
			    struct disp_csc_config *config, unsigned int fmt,
			    unsigned int mode, unsigned int color_range,
			    unsigned int eotf);
int de_cdc_enable(unsigned int screen_id, unsigned int enable);

#endif
