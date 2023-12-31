/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * Copyright (C) 2015 Allwinnertech, z.q <zengqi@allwinnertech.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef __DISP_EINK__H__
#define __DISP_EINK__H__

#include "disp_private.h"
#include "include.h"
#include <video/sunxi_display2.h>

#define EINK_POWER_NUM 4
#define IMAGE_BUF_NUM 13
#define WAVE_DATA_BUF_NUM  16
#define INDEX_BUFFER_NUM 2
#define EINK_RECT_MODE 0x400

/* #define __EINK_DEBUG__ */

struct st_argb {
	u8 blue;
	u8 green;
	u8 red;
	u8 alpha;
};

struct eink_buffer_manager {
	unsigned int in_index;
	unsigned int out_index;
	struct mutex mlock;
	struct eink_8bpp_image image_slot[IMAGE_BUF_NUM];
	unsigned int buf_size;
	unsigned int width;
	unsigned int height;

	bool (*is_full)(struct eink_buffer_manager *buffer_mgr);
	bool (*is_empty)(struct eink_buffer_manager *buffer_mgr);
	struct eink_8bpp_image *(*get_last_image)(struct eink_buffer_manager *
						   buffer_mgr);
	struct eink_8bpp_image *(*get_current_image)(struct eink_buffer_manager
						      *buffer_mgr);
	s32 (*queue_image)(struct eink_buffer_manager *buffer_mgr,
			   struct disp_layer_config_inner *config,
			   unsigned int layer_num, unsigned int mode,
			   struct area_info update_area);
	s32 (*dequeue_image)(struct eink_buffer_manager *buffer_mgr);
	s32 (*clear_image)(struct eink_buffer_manager *buffer_mgr);
};

struct pipeline_list {
	struct list_head free_list;
	struct list_head used_list;
	struct mutex mlock;
};

struct pipeline_info {
	struct area_info area;
	unsigned int frame_index;
	unsigned int total_frames;
	unsigned int pipeline_no;
	enum eink_update_mode mode;
	enum eink_bit_num bit_num;
	unsigned int wave_file_addr;
	bool enable_flag;
	int overlap_flag;
	struct list_head node;
};
struct pipeline_manager {
	unsigned int disp;
	int overlap_num;
	struct pipeline_list list;
	struct mutex mlock;

	int (*check_overlap)(struct pipeline_manager *, struct area_info);
	int (*op_skip)(struct pipeline_manager *, unsigned int);
	int (*config_one_pipeline)(struct pipeline_manager *, struct area_info,
				    enum eink_update_mode);
	int (*config_and_enable_one_pipeline)(struct pipeline_manager *,
					       struct area_info,
					       enum eink_update_mode,
					       unsigned int,
					       unsigned int *tframes);
	int (*update_pipeline_list)(struct pipeline_manager *, unsigned int,
				     unsigned int *);
	int (*used_list_status)(struct pipeline_manager *manager);
	int (*free_list_status)(struct pipeline_manager *manager);
	int (*check_overlap_num)(struct pipeline_manager *manager);
	int (*clear_pipeline_list)(struct pipeline_manager *manager);
};

struct wavedata_queue {
	unsigned int head;
	unsigned int tail;
	void *wavedata_vaddr[WAVE_DATA_BUF_NUM];
	void *wavedata_paddr[WAVE_DATA_BUF_NUM];
	bool wavedata_used[WAVE_DATA_BUF_NUM];
	struct rect_size size;
	spinlock_t slock;
};

struct eink_private {
	void *index_vaddr[INDEX_BUFFER_NUM];
	bool enable_flag;
	void *index_paddr[INDEX_BUFFER_NUM];
	unsigned char new_index;
	unsigned char old_index;

	bool index_fresh;
	char *wave_file_path;
	unsigned int fresh_frame_index;
	unsigned int decode_frame_index;
	unsigned int total_frame;
	unsigned int irq_no;
	struct wavedata_queue wavedata_ring_buffer;
	struct work_struct decode_frame_work;
	struct eink_init_param param;
	struct clk *eink_clk;
	struct clk *edma_clk;
	unsigned long eink_base_addr;
	spinlock_t slock;

};

int ring_buffer_manager_init(struct disp_eink_manager *eink_manager);
int ring_buffer_manager_exit(struct disp_eink_manager *eink_manager);
int pipeline_manager_init(struct disp_eink_manager *eink_manager);
int pipeline_manager_exit(struct disp_eink_manager *eink_manager);
int write_edma(struct disp_eink_manager *manager);
int disp_init_eink(struct disp_bsp_init_para *para);
int eink_display_one_frame(struct disp_eink_manager *manager);
extern int eink_irq_query_index(void);

extern s32 tcon0_simple_close(u32 sel);
extern s32 tcon0_simple_open(u32 sel);
extern void *disp_malloc(u32 num_bytes, void *phy_addr);
extern void disp_free(void *virt_addr, void *phy_addr, u32 num_bytes);
extern struct format_manager *disp_get_format_manager(unsigned int id);

#endif
