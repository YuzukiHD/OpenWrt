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

#include "de_feat.h"

#if defined(SUPPORT_ATW)
#include "de_atw_type.h"
#include "de_rtmx.h"

#define ATW_OFST 0x5000
static struct __atw_reg_t *atw_dev[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks atw_attr_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks atw_buf_block[DE_NUM][VI_CHN_NUM];
static struct de_reg_blocks atw_coeff_block[DE_NUM][VI_CHN_NUM];

int de_atw_set_reg_base(unsigned int sel, unsigned int chno, void *base)
{
	DE_INFO("sel=%d, chno=%d, base=0x%p\n", sel, chno, base);
	atw_dev[sel][chno] = (struct __atw_reg_t *) base;

	return 0;
}

int de_atw_init(unsigned int sel, unsigned int chno, uintptr_t reg_base)
{
	uintptr_t atw_base;
	void *memory;

	atw_base = reg_base + (sel + 1) * 0x00100000 + ATW_OFST;
	memory = kmalloc(sizeof(struct __atw_reg_t), GFP_KERNEL | __GFP_ZERO);
	if (memory == NULL) {
		DE_WARN("malloc uscaler[%d][%d] memory fail! size=0x%x\n", sel,
		chno, (unsigned int)sizeof(struct __atw_reg_t));
		return -1;
	}

	atw_attr_block[sel][chno].off = atw_base;
	atw_attr_block[sel][chno].val = memory;
	atw_attr_block[sel][chno].size = 0x14;
	atw_attr_block[sel][chno].dirty = 0;

	atw_buf_block[sel][chno].off = atw_base + 0x20;
	atw_buf_block[sel][chno].val = memory + 0x20;
	atw_buf_block[sel][chno].size = 0x10;
	atw_buf_block[sel][chno].dirty = 0;

	atw_coeff_block[sel][chno].off = atw_base + 0x30;
	atw_coeff_block[sel][chno].val = memory + 0x30;
	atw_coeff_block[sel][chno].size = 0x10;
	atw_coeff_block[sel][chno].dirty = 0;

	de_atw_set_reg_base(sel, chno, memory);

	return 0;
}

int de_atw_exit(unsigned int sel, unsigned int chno)
{
	kfree(atw_attr_block[sel][chno].val);
	kfree(atw_buf_block[sel][chno].val);
	kfree(atw_coeff_block[sel][chno].val);

	return 0;
}

int de_atw_double_init(unsigned int sel, unsigned int chno, uintptr_t reg_base)
{
	uintptr_t atw_base;

	atw_base = reg_base + (sel + 1) * 0x00100000 + ATW_OFST;
	de_atw_set_reg_base(sel, chno, (void *)atw_base);

	return 0;
}

int de_atw_double_exit(unsigned int sel)
{
	return 0;
}

int de_atw_update_regs(unsigned int sel, unsigned int chno)
{

	if (atw_attr_block[sel][chno].dirty == 0x1) {
		memcpy((void *)atw_attr_block[sel][chno].off,
		atw_attr_block[sel][chno].val,
		atw_attr_block[sel][chno].size);
		atw_attr_block[sel][chno].dirty = 0x0;
	}
	if (atw_buf_block[sel][chno].dirty == 0x1) {
		memcpy((void *)atw_buf_block[sel][chno].off,
		atw_buf_block[sel][chno].val,
		atw_buf_block[sel][chno].size);
		atw_buf_block[sel][chno].dirty = 0x0;
	}
	if (atw_coeff_block[sel][chno].dirty == 0x1) {
		memcpy((void *)atw_coeff_block[sel][chno].off,
		atw_coeff_block[sel][chno].val,
		atw_coeff_block[sel][chno].size);
		atw_coeff_block[sel][chno].dirty = 0x0;
	}

	return 0;
}

int de_atw_disable(unsigned int sel, unsigned int chno)
{
	atw_dev[sel][chno]->attr.dwval = 0x0;
	atw_attr_block[sel][chno].dirty = 0x1;

	return 0;
}

int de_atw_set_lay_cfg(unsigned int sel, unsigned int chno, unsigned int mode,
		       unsigned int m, unsigned int n, struct __lay_para_t *cfg)
{
	unsigned int tmp, bm, bn, bits;

	tmp = cfg->en;
	tmp |= (0x1 << 1);
	tmp |= (mode << 4);
	tmp |= (cfg->fmt << 8);
	atw_dev[sel][chno]->attr.dwval = tmp;

	tmp = cfg->layer.w == 0 ? 0 : cfg->layer.w - 1;
	tmp |= ((cfg->layer.h == 0 ? 0 : cfg->layer.h - 1) << 16);
	atw_dev[sel][chno]->size.dwval = tmp;
	atw_dev[sel][chno]->out_size.dwval = tmp;

	tmp = cfg->layer.x;
	tmp |= (cfg->layer.y << 16);
	atw_dev[sel][chno]->coor.dwval = tmp;

	if (cfg->layer.w >= 0x800)
		bits = 2;
	else if (cfg->layer.w >= 0x400)
		bits = 3;
	else if (cfg->layer.w >= 0x200)
		bits = 4;
	else
		bits = 8;

	tmp = bits;
	if (cfg->layer.h >= 0x800)
		bits = 2;
	else if (cfg->layer.h >= 0x400)
		bits = 3;
	else if (cfg->layer.h >= 0x200)
		bits = 4;
	else
		bits = 8;

	tmp = tmp < bits ? tmp : bits;
	atw_dev[sel][chno]->shift.dwval = tmp;

	bm = (mode == 1) ? (m << 1) : m;
	bn = (mode == 2) ? (n << 1) : n;
	tmp = (cfg->layer.w << 8) / bm;
	tmp |= (((cfg->layer.h << 8) / bn) << 16);
	atw_dev[sel][chno]->step.dwval = tmp;

	tmp = m;
	tmp |= (n << 8);
	atw_dev[sel][chno]->block.dwval = tmp;


	atw_attr_block[sel][chno].dirty = 0x1;
	atw_buf_block[sel][chno].dirty = 0x1;
	atw_coeff_block[sel][chno].dirty = 0x1;

	return 0;
}

int de_atw_set_overlay_size(unsigned int sel, unsigned int chno,
			    unsigned int w, unsigned int h)
{
	unsigned int tmp;

	tmp = w == 0 ? 0 : w - 1;
	tmp |= ((h == 0 ? 0 : h - 1) << 16);
	atw_dev[sel][chno]->ovl_size.dwval = tmp;
	atw_buf_block[sel][chno].dirty = 0x1;

	return 0;
}

int de_atw_set_lay_laddr(unsigned int sel, unsigned int chno, unsigned char fmt,
			 struct de_rect crop, unsigned int *size,
			 unsigned int *align, unsigned long long *addr,
			 unsigned char *haddr)
{
	long long addr_off[3];
	unsigned int pitch[3];
	unsigned int x0, y0, ycnt;

	x0 = crop.x;
	y0 = crop.y;
	ycnt = 0;

	if (fmt <= DE_FORMAT_BGRX_8888)
		ycnt = 4;
	else if (fmt <= DE_FORMAT_BGR_888)
		ycnt = 3;
	else
		ycnt = 4;

	pitch[0] = DISPALIGN(size[0] * ycnt, align[0]);
	addr_off[0] = addr[0] + pitch[0] * y0 + x0 * ycnt;

	haddr[0] = (addr_off[0] >> 32) & 0xff;
	atw_dev[sel][chno]->pitch.dwval = pitch[0];
	atw_dev[sel][chno]->laddr.dwval = (addr_off[0] & 0xffffffff);

	atw_buf_block[sel][chno].dirty = 0x1;
	atw_coeff_block[sel][chno].dirty = 0x1;

	return 0;
}

int de_atw_set_coeff_laddr(unsigned int sel, unsigned int chno,
			   unsigned int addr)
{
	atw_dev[sel][chno]->lcaddr.dwval = addr;
	atw_coeff_block[sel][chno].dirty = 0x1;

	return 0;
}
#endif
