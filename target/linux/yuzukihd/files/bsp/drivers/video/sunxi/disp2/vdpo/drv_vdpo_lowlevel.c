/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * Allwinner SoCs vdpo lowlevel driver.
 *
 * Copyright (C) 2017 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#include "drv_vdpo_lowlevel.h"

volatile struct __vdpo_dev *vdpo_dev[VDPO_NUM];

void __vdpo_module_en(u32 dev_sel, u32 module_en, u32 sepa_sync_en)
{
	vdpo_dev[dev_sel]->module_ctrl.bits.separate_sync_en = sepa_sync_en;
	vdpo_dev[dev_sel]->module_ctrl.bits.vdpo_mudule_en = module_en;
}

void __vdpo_fmt_set(u32 dev_sel, u32 data_seq_sel, u32 sync_fmt, u32 data_width,
		    u32 interlace)
{
	vdpo_dev[dev_sel]->fmt_ctrl.bits.data_seq_sel = data_seq_sel;
	vdpo_dev[dev_sel]->fmt_ctrl.bits.embedded_sync_fmt = sync_fmt;
	vdpo_dev[dev_sel]->fmt_ctrl.bits.output_data_width = data_width;
	vdpo_dev[dev_sel]->fmt_ctrl.bits.interlace_mode = interlace;
}

void __vdpo_chroma_spl_set(u32 dev_sel, u8 cr_type, u8 cb_type)
{
	vdpo_dev[dev_sel]->hor_spl_ctrl.bits.cb_hori_spl_type = cb_type;
	vdpo_dev[dev_sel]->hor_spl_ctrl.bits.cr_hori_spl_type = cr_type;
}

void __vdpo_clamp_set(u32 dev_sel, u16 y_min, u16 y_max, u16 cb_min, u16 cb_max,
		      u16 cr_min, u16 cr_max)
{
	vdpo_dev[dev_sel]->clamp0.bits.y_val_range_min = y_min;
	vdpo_dev[dev_sel]->clamp0.bits.y_val_range_max = y_max;
	vdpo_dev[dev_sel]->clamp1.bits.cb_val_range_min = cb_min;
	vdpo_dev[dev_sel]->clamp1.bits.cb_val_range_max = cb_max;
	vdpo_dev[dev_sel]->clamp2.bits.cr_val_range_min = cr_min;
	vdpo_dev[dev_sel]->clamp2.bits.cr_val_range_max = cr_max;
}

void __vdpo_sync_pol_set(u32 dev_sel, u8 hb_pol, u8 vb_pol, u8 field_pol)
{
	vdpo_dev[dev_sel]->sync_ctrl.bits.h_blank_pol = hb_pol;
	vdpo_dev[dev_sel]->sync_ctrl.bits.v_blank_pol = vb_pol;
	vdpo_dev[dev_sel]->sync_ctrl.bits.field_pol = field_pol;
}

void __vdpo_dclk_adjust(u32 dev_sel, u8 dclk_invt, u8 dly_en, u8 dly_num)
{
	vdpo_dev[dev_sel]->sync_ctrl.bits.dclk_invert = dclk_invt;
	vdpo_dev[dev_sel]->sync_ctrl.bits.dclk_dly_num = dly_num;
	vdpo_dev[dev_sel]->sync_ctrl.bits.dclk_dly_en = dly_en;
}

u32 __vdpo_get_curline(u32 sel)
{
	u32 line = vdpo_dev[sel]->status.bits.current_line;

	return line;
}

u32 __vdpo_get_field(u32 sel)
{
	u32 field = vdpo_dev[sel]->status.bits.field_pol_sta;

	return field;
}

s32 __vdpo_irq_en(u32 sel, u32 int_type, u32 line)
{
	s32 ret = 0;

	if (int_type == V_INT) {
		vdpo_dev[sel]->int_ctrl.bits.vb_int_en = 1;
	} else if (int_type == L_INT) {
		vdpo_dev[sel]->line_int_num.bits.int_line_num = line;
		vdpo_dev[sel]->int_ctrl.bits.line_match_int_en = 1;
	} else
		ret = -1;
	return ret;
}

s32 __vdpo_irq_disable(u32 sel, u32 int_type)
{
	s32 ret = 0;

	if (int_type == V_INT)
		vdpo_dev[sel]->int_ctrl.bits.vb_int_en = 0;
	else if (int_type == L_INT)
		vdpo_dev[sel]->int_ctrl.bits.line_match_int_en = 0;
	else
		ret = -1;
	return ret;
}

u32 __vdpo_irq_process(u32 sel)
{
	if ((vdpo_dev[sel]->int_ctrl.bits.vb_int_flag) &&
	    (vdpo_dev[sel]->int_ctrl.bits.vb_int_en))
		return V_INT;
	else if ((vdpo_dev[sel]->int_ctrl.bits.line_match_int_flag) &&
		 (vdpo_dev[sel]->int_ctrl.bits.line_match_int_en))
		return L_INT;
	else
		return 0;
}

u32 __vdpo_clr_irq(u32 sel, u32 int_type)
{
	if (int_type == V_INT)
		vdpo_dev[sel]->int_ctrl.bits.vb_int_flag = 0;
	else if (int_type == L_INT)
		vdpo_dev[sel]->int_ctrl.bits.line_match_int_flag = 0;
	return 0;
}

void __vdpo_timing_set(u32 sel, u32 h_active, u32 h_bp, u32 v_active, u32 v_bp,
		       u32 v_total, u32 interlace, u32 itl_mode)
{
	vdpo_dev[sel]->h_timing.bits.h_active = h_active - 1;
	vdpo_dev[sel]->h_timing.bits.h_bp = h_bp - 1;
	vdpo_dev[sel]->v_timing.bits.v_active = v_active / (interlace + 1) - 1;
	vdpo_dev[sel]->v_timing.bits.v_bp = v_bp - 1;
	vdpo_dev[sel]->v_timing1.bits.v_total = v_total * 2 / (interlace + 1);
	if (interlace)
		vdpo_dev[sel]->v_timing1.bits.itl_mode = itl_mode;
}

#if defined(__DISP_TEMP_CODE__)
u32 __vdpo_reg_default_test(u32 sel, u32 addr_offset, u32 exp_value)
{
	u32 base_addr;

	base_addr = VDPO_BASE;
	if (exp_value != get_wvalue(base_addr + addr_offset))
		return RET_FAIL;
	else
		return RET_OK;
}

u32 __vdpo_reg_wr_test(u32 sel, u32 addr_offset, u32 mask, u32 wr_value)
{
	u32 base_addr, rd_value;

	base_addr = VDPO_BASE;
	wr_value &= mask;
	put_wvalue(base_addr + addr_offset, wr_value);
	rd_value = get_wvalue(base_addr + addr_offset);
	rd_value &= mask;
	if (wr_value != rd_value)
		return RET_FAIL;
	else
		return RET_OK;
}
#endif

void __vdpo_set_reg_base(u32 sel, void __iomem *base_addr)
{
	vdpo_dev[sel] = (struct __vdpo_dev *)base_addr;
}
