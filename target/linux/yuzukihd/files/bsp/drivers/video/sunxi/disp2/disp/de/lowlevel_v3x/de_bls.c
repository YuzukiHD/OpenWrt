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

/*******************************************************************************
 *  All Winner Tech, All Right Reserved. 2014-2016 Copyright (c)
 *
 *  File name   :   de_bls.c
 *
 *  Description :   display engine 3.0 bls basic function definition
 *
 *  History     :   2016-3-3 zzz  v0.1  Initial version
 *
 ******************************************************************************/

#include "de_bls_type.h"
#include "de_enhance.h"

static struct __bls_reg_t *bls_dev[DE_NUM][CHN_NUM];
static struct de_reg_blocks bls_ctrl_block[DE_NUM][CHN_NUM];
static struct de_reg_blocks bls_para_block[DE_NUM][CHN_NUM];

unsigned int uatten_lut[32] = {
	6, 7, 8, 8, 9, 10, 10, 11,
	12, 12, 13, 14, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15,
	15, 10, 9, 9, 8, 8, 7, 7
};

unsigned int gain_lut[16] = {
	1, 1, 1, 2,
	2, 3, 3, 4,
	6, 8, 10, 15,
	20, 25, 25, 25
};

/*******************************************************************************
 * function       : de_bls_set_reg_base(unsigned int sel, unsigned int chno,
 *                  unsigned int base)
 * description    : set bls reg base
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  base        <reg base>
 * return         :
 *                  success
 ******************************************************************************/
int de_bls_set_reg_base(unsigned int sel, unsigned int chno, void *base)
{
	DE_INFO("sel=%d, chno=%d, base=0x%p\n", sel, chno, base);
	bls_dev[sel][chno] = (struct __bls_reg_t *) base;

	return 0;
}

int de_bls_update_regs(unsigned int sel, unsigned int chno)
{
	if (bls_ctrl_block[sel][chno].dirty == 0x1) {
		memcpy((void *)bls_ctrl_block[sel][chno].off,
			     bls_ctrl_block[sel][chno].val,
			     bls_ctrl_block[sel][chno].size);
		bls_ctrl_block[sel][chno].dirty = 0x0;
	}

	if (bls_para_block[sel][chno].dirty == 0x1) {
		memcpy((void *)bls_para_block[sel][chno].off,
			     bls_para_block[sel][chno].val,
			     bls_para_block[sel][chno].size);
		bls_para_block[sel][chno].dirty = 0x0;
	}
	return 0;
}

int de_bls_init(unsigned int sel, unsigned int chno, uintptr_t reg_base)
{
	uintptr_t base;
	void *memory;

	/* FIXME: chno is not considered */
	base = reg_base + (sel + 1) * 0x00100000 + BLS_OFST;
	DE_INFO("sel %d, bls_base[%d]=0x%p\n", sel, chno, (void *)base);

	memory = kmalloc(sizeof(struct __bls_reg_t), GFP_KERNEL | __GFP_ZERO);
	if (memory == NULL) {
		DE_WARN("malloc bls[%d][%d] memory fail! size=0x%x\n", sel, chno,
			    (unsigned int)sizeof(struct __bls_reg_t));
		return -1;
	}

	bls_ctrl_block[sel][chno].off = base;
	bls_ctrl_block[sel][chno].val = memory;
	bls_ctrl_block[sel][chno].size = 0x10;
	bls_ctrl_block[sel][chno].dirty = 0;

	bls_para_block[sel][chno].off = base + 0x10;
	bls_para_block[sel][chno].val = memory + 0x10;
	bls_para_block[sel][chno].size = 0x30;
	bls_para_block[sel][chno].dirty = 0;

	de_bls_set_reg_base(sel, chno, memory);

	return 0;
}

int de_bls_double_init(unsigned int sel, unsigned int chno, uintptr_t reg_base)
{
	uintptr_t base;

	/* FIXME: chno is not considered */
	base = reg_base + (sel + 1) * 0x00100000 + BLS_OFST;
	DE_INFO("sel %d, bls_base[%d]=0x%p\n", sel, chno, (void *)base);

	de_bls_set_reg_base(sel, chno, (void *)base);

	return 0;
}

int de_bls_exit(unsigned int sel, unsigned int chno)
{
	kfree(bls_ctrl_block[sel][chno].val);
	return 0;
}

int de_bls_double_exit(unsigned int sel, unsigned int chno)
{
	return 0;
}

/*******************************************************************************
 * function       : de_bls_enable(unsigned int sel, unsigned int chno,
 *                  unsigned int en)
 * description    : enable/disable bls
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  en          <enable: 0-diable; 1-enable>
 * return         :
 *                  success
 ******************************************************************************/
int de_bls_enable(unsigned int sel, unsigned int chno, unsigned int en)
{
	DE_INFO("sel=%d, chno=%d, en=%d\n", sel, chno, en);
	de_set_bits(&bls_dev[sel][chno]->ctrl.dwval, en, 0, 1);
	bls_ctrl_block[sel][chno].dirty = 1;
	return 0;
}

/*******************************************************************************
 * function       : de_bls_set_size(unsigned int sel, unsigned int chno,
 *                   unsigned int width, unsigned int height)
 * description    : set bls size
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  width       <input width>
 *                                      height  <input height>
 * return         :
 *                  success
 ******************************************************************************/
int de_bls_set_size(unsigned int sel, unsigned int chno, unsigned int width,
			   unsigned int height)
{
	bls_dev[sel][chno]->size.dwval = (height - 1) << 16 | (width - 1);
	bls_ctrl_block[sel][chno].dirty = 1;
	return 0;
}

/*******************************************************************************
 * function       : de_bls_set_window(unsigned int sel, unsigned int chno,
 *                  unsigned int win_enable, de_rect window)
 * description    : set bls window
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 *                  win_enable  <enable: 0-window mode diable;
 *                                       1-window mode enable>
 *                                      window  <window rectangle>
 * return         :
 *                  success
 ******************************************************************************/
int de_bls_set_window(unsigned int sel, unsigned int chno,
			     unsigned int win_enable, struct de_rect window)
{
	de_set_bits(&bls_dev[sel][chno]->ctrl.dwval, win_enable, 1, 1);

	if (win_enable) {
		bls_dev[sel][chno]->win0.dwval = window.y << 16 | window.x;
		bls_dev[sel][chno]->win1.dwval =
			(window.y + window.h - 1) << 16 |
			(window.x + window.w - 1);
	}

	bls_ctrl_block[sel][chno].dirty = 1;
	return 0;
}

/*******************************************************************************
 * function       : de_bls_init_para(unsigned int sel, unsigned int chno,
 *                  unsigned int gain)
 * description    : set bls para
 * parameters     :
 *                  sel         <rtmx select>
 *                  chno        <overlay select>
 * return         :
 *                  success
 ******************************************************************************/
int de_bls_init_para(unsigned int sel, unsigned int chno)
{
	unsigned int i, j, tmpval, gain;

	memset(bls_dev[sel][chno], 0, sizeof(struct __bls_reg_t));
	bls_dev[sel][chno]->bls_pos.dwval = 86 << 16 | 118;
	for (i = 0; i < 4; i++) {
		tmpval = 0;

		for (j = 0; j < 8; j++)
			tmpval = (tmpval << 4) +
			(uatten_lut[i * 8 + 7 - j] & 0xF);

		bls_dev[sel][chno]->bls_attlut[i].dwval = tmpval;
	}

	gain = 1; /* 5 */
	for (i = 0; i < 4; i++) {
		tmpval = 0;

		for (j = 0; j < 4; j++)
			tmpval = (tmpval << 8) +
			((gain_lut[i * 4 + 3 - j] * gain) & 0xFF);

		bls_dev[sel][chno]->bls_gainlut[i].dwval = tmpval;
	}

	bls_para_block[sel][chno].dirty = 1;
	return 0;
}

/*******************************************************************************
 * function       : de_bls_info2para(unsigned int sel, unsigned int chno,
 *                  unsigned int fmt, unsigned int dev_type,
 *                  __dns_config_data *para)
 * description    : info->para conversion
 * parameters     :
 *                  sel               <rtmx select>
 *                  chno              <overlay select>
 *                  fmt               <rgb/yuv>
 *                  dev_type          <output dev>
 *                  para              <bsp para>
 * return         :
 *                  success
 ******************************************************************************/
int de_bls_info2para(unsigned int sel, unsigned int chno,
			   unsigned int fmt, unsigned int dev_type,
			   struct __bls_config_data *para,
			   unsigned int bypass)
{
	if ((fmt == 1) || (bypass == 1))
		para->mod_en = 0;
	else
		para->mod_en = (para->level > 4) ? 1 : 0;
						/* return enable info */

	de_bls_enable(sel, chno, para->mod_en);
	bls_ctrl_block[sel][chno].dirty = 1;
	return 0;
}
