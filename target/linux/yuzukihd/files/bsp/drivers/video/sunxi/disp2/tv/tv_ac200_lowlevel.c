/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * Allwinner SoCs tv driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "tv_ac200.h"
#include "tv_ac200_lowlevel.h"

static s32 aw1683_wr_reg(u16 addr, u16 val)
{
	return acx00_reg_write(tv_priv.acx00, addr, val);
}

static s32 aw1683_rd_reg(u16 addr, u16 *val)
{
	*val = acx00_reg_read(tv_priv.acx00, addr);
	return 0;
}


s32 aw1683_tve_init(const u16 *p_dac_cali)
{
	u16 data;

	if (p_dac_cali == NULL)
		return -1;

	/* clk for tve */
	aw1683_wr_reg(0x001a, 0x0003);
	aw1683_wr_reg(0x0040, 0x0702);
	aw1683_wr_reg(0x000c, 0x4e01);
	aw1683_wr_reg(0x000c, 0xce01);
	aw1683_wr_reg(0x0018, 0x0001);
	aw1683_wr_reg(0x0018, 0x000f);

	/* sid for tve */
	if (*p_dac_cali == 0)
		aw1683_rd_reg(0x8002, &data);
	else
		data = *p_dac_cali;
	if (data == 0)
		aw1683_wr_reg(0x4306, 0x28f);
	else if (data < 0x3f5 && data > 0)
		aw1683_wr_reg(0x4306, data + 10);
	else
		aw1683_wr_reg(0x4306, data);

	/* tve anto check */
	aw1683_wr_reg(0x4008, 0x12a0);
	aw1683_wr_reg(0x400a, 0x4300);
	aw1683_wr_reg(0x40f4, 0x0230);
	aw1683_wr_reg(0x40f8, 0x0064);
	aw1683_wr_reg(0x40fa, 0x0c80);
	aw1683_wr_reg(0x4040, 0x0002);
	aw1683_wr_reg(0x4030, 0x0001);

	return 0;
}

s32 aw1683_tve_plug_status(void)
{
	u16 data;

	aw1683_rd_reg(0x4038, &data);
	return (data & 0x3);
}

s32 aw1683_tve_set_mode(u32 mode)
{
	u32 inter = 0;
	u32 ccir =  1;
	u32 m    =  (mode == 11) ? 1:0;
	u32 c    =  ccir ? 2:3;
	u32 i	 =  inter;
	u32 x    =  tv_video_timing[m].x_res;
	u32 y    =  tv_video_timing[m].y_res/(i+1);
	u32 hbp  = (tv_video_timing[m].hor_back_porch
			   +tv_video_timing[m].hor_sync_time) * c;
	u32 vbp  = (tv_video_timing[m].ver_back_porch
			   +tv_video_timing[m].ver_sync_time);
	u32 syuv = ccir ? 0:1;
	/* u32 resync_pixels	= 0x7b*c; */

	aw1683_wr_reg(0x5000, syuv);
	aw1683_wr_reg(0x5008, hbp-1);
	aw1683_wr_reg(0x500a, x*c-1);
	aw1683_wr_reg(0x500c, vbp-1);
	aw1683_wr_reg(0x500e, y-1);
	aw1683_wr_reg(0x5016, vbp-1+i);
	aw1683_wr_reg(0x5010, 0x0000);
	aw1683_wr_reg(0x5012, 0x0004);

	if (mode == 14) {
		aw1683_wr_reg(0x4002, 0x8000);
		aw1683_wr_reg(0x4004, 0x0000);
		aw1683_wr_reg(0x4006, 0x0707);
/* aw1683_wr_reg(0x4008, 0x0001); */
		aw1683_wr_reg(0x400a, 0x4300);
		aw1683_wr_reg(0x400c, 0x1400);
		aw1683_wr_reg(0x400e, 0x3000);
		aw1683_wr_reg(0x4010, 0x7c1f);
		aw1683_wr_reg(0x4012, 0x21f0);
		aw1683_wr_reg(0x4014, 0x0020);
		aw1683_wr_reg(0x4016, 0x0076);
		aw1683_wr_reg(0x4018, 0x0016);
		aw1683_wr_reg(0x401a, 0x0000);
		aw1683_wr_reg(0x401c, 0x020d);
		aw1683_wr_reg(0x401e, 0x0016);
		aw1683_wr_reg(0x4020, 0x011a);
		aw1683_wr_reg(0x4022, 0x00f0);
		aw1683_wr_reg(0x4100, 0x0001);
		aw1683_wr_reg(0x4102, 0x0000);
		aw1683_wr_reg(0x4104, 0x0000);
		aw1683_wr_reg(0x4106, 0x0000);
		aw1683_wr_reg(0x4108, 0x0002);
		aw1683_wr_reg(0x410a, 0x0000);
		aw1683_wr_reg(0x410c, 0x004f);
		aw1683_wr_reg(0x410e, 0x0000);
		aw1683_wr_reg(0x4110, 0x0000);
		aw1683_wr_reg(0x4112, 0x0000);
		aw1683_wr_reg(0x4114, 0x447e);
		aw1683_wr_reg(0x4116, 0x0016);
		aw1683_wr_reg(0x4118, 0xa0a0);
		aw1683_wr_reg(0x411a, 0x0000);
		aw1683_wr_reg(0x411c, 0x00f0);
		aw1683_wr_reg(0x411e, 0x0010);
		aw1683_wr_reg(0x4120, 0x0320);
		aw1683_wr_reg(0x4122, 0x01e8);
		aw1683_wr_reg(0x4124, 0x05a0);
		aw1683_wr_reg(0x4126, 0x0000);
		aw1683_wr_reg(0x4128, 0x0000);
		aw1683_wr_reg(0x412a, 0x0001);
		aw1683_wr_reg(0x412c, 0x0101);
		aw1683_wr_reg(0x412e, 0x0000);
/* aw1683_wr_reg(0x4130, 0x0000); */
/* aw1683_wr_reg(0x4132, 0x3016); */
		aw1683_wr_reg(0x4134, 0x0000);
		aw1683_wr_reg(0x4136, 0x0000);
		aw1683_wr_reg(0x4138, 0x0000);
		aw1683_wr_reg(0x413a, 0x0000);
		aw1683_wr_reg(0x413c, 0x0000);
		aw1683_wr_reg(0x413e, 0x0000);
		aw1683_wr_reg(0x5014, 0x0100);
		aw1683_wr_reg(0x4130, 0x0000);
		aw1683_wr_reg(0x4132, 0x2004);	/* 2004 */
		aw1683_wr_reg(0x4000, 0x0300);
	} else {
		aw1683_wr_reg(0x4002, 0x8000);
		aw1683_wr_reg(0x4004, 0x0001);
		aw1683_wr_reg(0x4006, 0x0707);
/* aw1683_wr_reg(0x4008, 0x0001); */
		aw1683_wr_reg(0x400a, 0x4300);
		aw1683_wr_reg(0x400c, 0x1400);
		aw1683_wr_reg(0x400e, 0x3000);
		aw1683_wr_reg(0x4010, 0x8acb);
		aw1683_wr_reg(0x4012, 0x2a09);
		aw1683_wr_reg(0x4014, 0x0018);
		aw1683_wr_reg(0x4016, 0x008a);
		aw1683_wr_reg(0x4018, 0x0016);
		aw1683_wr_reg(0x401a, 0x0000);
		aw1683_wr_reg(0x401c, 0x0271);
		aw1683_wr_reg(0x401e, 0x0016);
		aw1683_wr_reg(0x4020, 0x00fc);
		aw1683_wr_reg(0x4022, 0x00fc);
		aw1683_wr_reg(0x4100, 0x0000);
		aw1683_wr_reg(0x4102, 0x0000);
		aw1683_wr_reg(0x4104, 0x0001);
		aw1683_wr_reg(0x4106, 0x0000);
		aw1683_wr_reg(0x4108, 0x0005);
		aw1683_wr_reg(0x410a, 0x0000);
		aw1683_wr_reg(0x410c, 0x2929);
		aw1683_wr_reg(0x410e, 0x0000);
		aw1683_wr_reg(0x4110, 0x0000);
		aw1683_wr_reg(0x4112, 0x0000);
		aw1683_wr_reg(0x4114, 0x447e);
		aw1683_wr_reg(0x4116, 0x0016);
		aw1683_wr_reg(0x4118, 0xabab);
		aw1683_wr_reg(0x411a, 0x0000);
		aw1683_wr_reg(0x411c, 0x00fc);
		aw1683_wr_reg(0x411e, 0x0010);
		aw1683_wr_reg(0x4120, 0x0320);
		aw1683_wr_reg(0x4122, 0x01e8);
		aw1683_wr_reg(0x4124, 0x05a0);
		aw1683_wr_reg(0x4126, 0x0000);
		aw1683_wr_reg(0x4128, 0x0000);
		aw1683_wr_reg(0x412a, 0x0001);
		aw1683_wr_reg(0x412c, 0x0101);
		aw1683_wr_reg(0x412e, 0x0000);
/* aw1683_wr_reg(0x4130, 0x0380); */
/* aw1683_wr_reg(0x4132, 0x3009); */
		aw1683_wr_reg(0x4134, 0x0000);
		aw1683_wr_reg(0x4136, 0x0000);
		aw1683_wr_reg(0x4138, 0x0000);
		aw1683_wr_reg(0x413a, 0x0000);
		aw1683_wr_reg(0x413c, 0x0000);
		aw1683_wr_reg(0x413e, 0x0000);
		aw1683_wr_reg(0x43a0, 0x0001);
		aw1683_wr_reg(0x43a2, 0x0003);
		aw1683_wr_reg(0x5014, 0x2149);
		aw1683_wr_reg(0x4130, 0x0380);
		aw1683_wr_reg(0x4132, 0x2009);	/* 2004 */
		aw1683_wr_reg(0x4000, 0x0300);
	}

	/* aw1683_wr_bits(0x4000,0x0,0x1); */
	/* aw1683_wr_reg(0x4000,0x0301); */

	return 0;
}

s32 aw1683_tve_open(void)
{
	u16 data;

	aw1683_wr_reg(0x4008, 0x02a1);
	aw1683_wr_reg(0x4000, 0x0301);
	aw1683_rd_reg(0x4008, &data);
	if (data != 0x02a1)
		return -1;
	aw1683_rd_reg(0x4000, &data);
	if (data != 0x0301)
		return -1;

	return 0;
}

s32 aw1683_tve_close(void)
{
	aw1683_wr_reg(0x4000, 0x0300);
	aw1683_wr_reg(0x4008, 0x02a0);

	return 0;
}

#if defined(__DISP_TEMP_CODE__)
s32 aw1683_tve(void)
{
	s32 mode	= 1;
	s32 inter   = 0;
	s32 ccir	= 1;

	aw1673_video_rgb(mode, inter, ccir);
	aw1683_tve_init();
	aw1683_tve_set_mode(mode);
	aw1683_tve_open();

	while (1) {
		aw1683_tve_close();
		mode = 0;
		aw1673_video_rgb(mode, inter, ccir);
		aw1683_tve_set_mode(mode);
		aw1683_tve_open();

		aw1683_tve_close();
		mode = 1;
		aw1673_video_rgb(mode, inter, ccir);
		aw1683_tve_set_mode(mode);
		aw1683_tve_open();
	}

	return RET_OK;
}
#endif

s32 aw1683_enable_chip(void)
{
	aw1683_wr_reg(0x0002, 0x0001);
	return 0;
}
