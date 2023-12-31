/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * Allwinner SoCs timing table
 *
 * Copyright (C) 2017 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#include "drv_vdpo_timing.h"

static struct disp_video_timings video_timing[] = {
	{
		.vic = 0,
		.tv_mode = DISP_TV_MOD_NTSC,
		.pixel_clk = 13500000,
		.pixel_repeat = 0,
		.x_res = 720,
		.y_res = 480,
		.hor_total_time = 858,
		.hor_back_porch = 60,
		.hor_front_porch = 16,
		.hor_sync_time = 62,
		.ver_total_time = 525,
		.ver_back_porch = 30,
		.ver_front_porch = 9,
		.ver_sync_time = 6,
		.hor_sync_polarity = 0,/* 0: negative, 1: positive */
		.ver_sync_polarity = 0,/* 0: negative, 1: positive */
		.b_interlace = 0,
		.vactive_space = 0,
		.trd_mode = 0,

	},
	{
		.vic = 0,
		.tv_mode = DISP_TV_MOD_PAL,
		.pixel_clk = 13500000,
		.pixel_repeat = 0,
		.x_res = 720,
		.y_res = 576,
		.hor_total_time = 864,
		.hor_back_porch = 68,
		.hor_front_porch = 12,
		.hor_sync_time = 64,
		.ver_total_time = 625,
		.ver_back_porch = 39,
		.ver_front_porch = 5,
		.ver_sync_time = 5,
		.hor_sync_polarity = 0,/* 0: negative, 1: positive */
		.ver_sync_polarity = 0,/* 0: negative, 1: positive */
		.b_interlace = 0,
		.vactive_space = 0,
		.trd_mode = 0,
	},
	{
		.vic = 0,
		.tv_mode = DISP_TV_MOD_480I,
		.pixel_clk = 13500000,
		.pixel_repeat = 0,
		.x_res = 720,
		.y_res = 480,
		.hor_total_time = 858,
		.hor_back_porch = 57,
		.hor_front_porch = 62,
		.hor_sync_time = 19,
		.ver_total_time = 525,
		.ver_back_porch = 4,
		.ver_front_porch = 1,
		.ver_sync_time = 3,
		.hor_sync_polarity = 1,/* 0: negative, 1: positive */
		.ver_sync_polarity = 1,/* 0: negative, 1: positive */
		.b_interlace = 1,
		.vactive_space = 0,
		.trd_mode = 0,
	},
	{
		.vic = 0,
		.tv_mode = DISP_TV_MOD_576I,
		.pixel_clk = 13500000,
		.pixel_repeat = 0,
		.x_res = 720,
		.y_res = 576,
		.hor_total_time = 864,
		.hor_back_porch = 69,
		.hor_front_porch = 63,
		.hor_sync_time = 12,
		.ver_total_time = 625,
		.ver_back_porch = 2,
		.ver_front_porch = 44,
		.ver_sync_time = 3,
		.hor_sync_polarity = 1,/* 0: negative, 1: positive */
		.ver_sync_polarity = 1,/* 0: negative, 1: positive */
		.b_interlace = 1,
		.vactive_space = 0,
		.trd_mode = 0,
	},
	{
		.vic = 0,
		.tv_mode = DISP_TV_MOD_480P,
		.pixel_clk = 27000000,
		.pixel_repeat = 0,
		.x_res = 720,
		.y_res = 480,
		.hor_total_time = 858,
		.hor_back_porch = 60,
		.hor_front_porch = 62,
		.hor_sync_time = 16,
		.ver_total_time = 525,
		.ver_back_porch = 9,
		.ver_front_porch = 30,
		.ver_sync_time = 6,
		.hor_sync_polarity = 1,/* 0: negative, 1: positive */
		.ver_sync_polarity = 1,/* 0: negative, 1: positive */
		.b_interlace = 0,
		.vactive_space = 0,
		.trd_mode = 0,
	},
	{
		.vic = 0,
		.tv_mode = DISP_TV_MOD_576P,
		.pixel_clk = 27000000,
		.pixel_repeat = 0,
		.x_res = 720,
		.y_res = 576,
		.hor_total_time = 864,
		.hor_back_porch = 68,
		.hor_front_porch = 64,
		.hor_sync_time = 12,
		.ver_total_time = 625,
		.ver_back_porch = 5,
		.ver_front_porch = 39,
		.ver_sync_time = 5,
		.hor_sync_polarity = 1,/* 0: negative, 1: positive */
		.ver_sync_polarity = 1,/* 0: negative, 1: positive */
		.b_interlace = 0,
		.vactive_space = 0,
		.trd_mode = 0,
	},
	{
		.vic = 0,
		.tv_mode = DISP_TV_MOD_720P_60HZ,
		.pixel_clk = 74250000,
		.pixel_repeat = 0,
		.x_res = 1280,
		.y_res = 720,
		.hor_total_time = 1650,
		.hor_back_porch = 220,
		.hor_front_porch = 40,
		.hor_sync_time = 110,
		.ver_total_time = 750,
		.ver_back_porch = 5,
		.ver_front_porch = 20,
		.ver_sync_time = 5,
		.hor_sync_polarity = 1,/* 0: negative, 1: positive */
		.ver_sync_polarity = 1,/* 0: negative, 1: positive */
		.b_interlace = 0,
		.vactive_space = 0,
		.trd_mode = 0,
	},
	{
		.vic = 0,
		.tv_mode = DISP_TV_MOD_720P_50HZ,
		.pixel_clk = 74250000,
		.pixel_repeat = 0,
		.x_res = 1280,
		.y_res = 720,
		.hor_total_time = 1980,
		.hor_back_porch = 220,
		.hor_front_porch = 40,
		.hor_sync_time = 440,
		.ver_total_time = 750,
		.ver_back_porch = 5,
		.ver_front_porch = 20,
		.ver_sync_time = 5,
		.hor_sync_polarity = 1,/* 0: negative, 1: positive */
		.ver_sync_polarity = 1,/* 0: negative, 1: positive */
		.b_interlace = 0,
		.vactive_space = 0,
		.trd_mode = 0,
	},
	{
		.vic = 0,
		.tv_mode = DISP_TV_MOD_1080I_60HZ,
		.pixel_clk = 74250000,
		.pixel_repeat = 0,
		.x_res = 1920,
		.y_res = 1080,
		.hor_total_time = 2200,
		.hor_back_porch = 148,
		.hor_front_porch = 44,
		.hor_sync_time = 88,
		.ver_total_time = 1125,
		.ver_back_porch = 2,
		.ver_front_porch = 38,
		.ver_sync_time = 5,
		.hor_sync_polarity = 1,/* 0: negative, 1: positive */
		.ver_sync_polarity = 1,/* 0: negative, 1: positive */
		.b_interlace = 1,
		.vactive_space = 0,
		.trd_mode = 0,
	},
	{
		.vic = 0,
		.tv_mode = DISP_TV_MOD_1080I_50HZ,
		.pixel_clk = 74250000,
		.pixel_repeat = 0,
		.x_res = 1920,
		.y_res = 1080,
		.hor_total_time = 2640,
		.hor_back_porch = 148,
		.hor_front_porch = 44,
		.hor_sync_time = 528,
		.ver_total_time = 1125,
		.ver_back_porch = 2,
		.ver_front_porch = 38,
		.ver_sync_time = 5,
		.hor_sync_polarity = 1,/* 0: negative, 1: positive */
		.ver_sync_polarity = 1,/* 0: negative, 1: positive */
		.b_interlace = 1,
		.vactive_space = 0,
		.trd_mode = 0,
	},
	{
		.vic = 0,
		.tv_mode = DISP_TV_MOD_1080P_60HZ,
		.pixel_clk = 148500000,
		.pixel_repeat = 0,
		.x_res = 1920,
		.y_res = 1080,
		.hor_total_time = 2200,
		.hor_back_porch = 148,
		.hor_front_porch = 44,
		.hor_sync_time = 88,
		.ver_total_time = 1125,
		.ver_back_porch = 4,
		.ver_front_porch = 36,
		.ver_sync_time = 5,
		.hor_sync_polarity = 1,/* 0: negative, 1: positive */
		.ver_sync_polarity = 1,/* 0: negative, 1: positive */
		.b_interlace = 0,
		.vactive_space = 0,
		.trd_mode = 0,
	},
	{
		.vic = 0,
		.tv_mode = DISP_TV_MOD_3840_1080P_30,
		.pixel_clk = 148500000,
		.pixel_repeat = 0,
		.x_res = 3840,
		.y_res = 1080,
		.hor_total_time = 4400,
		.hor_back_porch = 296,
		.hor_front_porch = 88,
		.hor_sync_time = 176,
		.ver_total_time = 1125,
		.ver_back_porch = 4,
		.ver_front_porch = 36,
		.ver_sync_time = 5,
		.hor_sync_polarity = 1,/* 0: negative, 1: positive */
		.ver_sync_polarity = 1,/* 0: negative, 1: positive */
		.b_interlace = 0,
		.vactive_space = 0,
		.trd_mode = 0,
	},
	{
		.vic = 0,
		.tv_mode = DISP_TV_MOD_1080P_50HZ,
		.pixel_clk = 148500000,
		.pixel_repeat = 0,
		.x_res = 1920,
		.y_res = 1080,
		.hor_total_time = 2640,
		.hor_back_porch = 148,
		.hor_front_porch = 44,
		.hor_sync_time = 528,
		.ver_total_time = 1125,
		.ver_back_porch = 4,
		.ver_front_porch = 36,
		.ver_sync_time = 5,
		.hor_sync_polarity = 1,/* 0: negative, 1: positive */
		.ver_sync_polarity = 1,/* 0: negative, 1: positive */
		.b_interlace = 0,
		.vactive_space = 0,
		.trd_mode = 0,
	},
	{
		.vic = 0,
		.tv_mode = DISP_VGA_MOD_800_600P_60,
		.pixel_clk = 40000000,
		.pixel_repeat = 0,
		.x_res = 800,
		.y_res = 600,
		.hor_total_time = 1056,
		.hor_back_porch = 88,
		.hor_front_porch = 40,
		.hor_sync_time = 128,
		.ver_total_time = 628,
		.ver_back_porch = 23,
		.ver_front_porch = 1,
		.ver_sync_time = 4,
		.hor_sync_polarity = 1,/* 0: negative, 1: positive */
		.ver_sync_polarity = 1,/* 0: negative, 1: positive */
		.b_interlace = 0,
		.vactive_space = 0,
		.trd_mode = 0,
	},
	{
		.vic = 0,
		.tv_mode = DISP_VGA_MOD_1920_1080P_60,
		.pixel_clk = 14850000,
		.pixel_repeat = 0,
		.x_res = 1920,
		.y_res = 1080,
		.hor_total_time = 2200,
		.hor_back_porch = 88,
		.hor_front_porch = 40,
		.hor_sync_time = 128,
		.ver_total_time = 628,
		.ver_back_porch = 23,
		.ver_front_porch = 1,
		.ver_sync_time = 4,
		.hor_sync_polarity = 1,/* 0: negative, 1: positive */
		.ver_sync_polarity = 1,/* 0: negative, 1: positive */
		.b_interlace = 0,
		.vactive_space = 0,
		.trd_mode = 0,
	},
};

/**
 * @name       :vdpo_get_timing_num
 * @brief      :get the number of timing that is support
 * @param[IN]  :none
 * @param[OUT] :none
 * @return     :the number of timing that is support
 */
u32 vdpo_get_timing_num(void)
{
	return sizeof(video_timing) / sizeof(struct disp_video_timings);
}

/**
 * @name       :vdpo_get_timing_info
 * @brief      :get timing info of specified mode
 * @param[IN]  :mode:output resolution
 * @param[OUT] :info:pointer that store the timing info
 * @return     :0 if success
 */
s32 vdpo_get_timing_info(enum disp_tv_mode mode,
			 struct disp_video_timings **info)
{
	s32 ret = -1;
	u32 i, list_num;
	struct disp_video_timings *tmp_info;

	list_num = vdpo_get_timing_num();
	tmp_info = video_timing;
	for (i = 0; i < list_num; ++i) {
		if (mode == tmp_info->tv_mode) {
			*info = tmp_info;
			ret = 0;
			break;
		}
		++tmp_info;
	}
	return ret;
}

/**
 * @name       vdpo_is_mode_support
 * @brief      if a specified mode is support
 * @param[IN]  mode:resolution output mode
 * @param[OUT] none
 * @return     1 if support, 0 if not support
 */
s32 vdpo_is_mode_support(enum disp_tv_mode mode)
{
	s32 ret = 0;
	u32 i, list_num;
	struct disp_video_timings *tmp_info;

	list_num = vdpo_get_timing_num();
	tmp_info = video_timing;
	for (i = 0; i < list_num; ++i) {
		if (mode == tmp_info[i].tv_mode) {
			ret = 1;
			break;
		}
	}

	return ret;
}
