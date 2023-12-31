/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * Allwinner SoCs hdmi driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __HDMI_EDID_H_
#define __HDMI_EDID_H_

#define Abort_Current_Operation             0
#define Special_Offset_Address_Read         1
#define Explicit_Offset_Address_Write       2
#define Implicit_Offset_Address_Write       3
#define Explicit_Offset_Address_Read        4
#define Implicit_Offset_Address_Read        5
#define Explicit_Offset_Address_E_DDC_Read  6
#define Implicit_Offset_Address_E_DDC_Read  7

extern u8	Device_Support_VIC[516];
extern s32 hdmi_edid_parse(void);
/* extern s32 DDC_Read(char cmd,char pointer,
 * char offset,int nbyte,char * pbuf);
 */
/* extern void DDC_Init(void); */
/* extern void send_ini_sequence(void); */
extern u32 hdmi_edid_is_hdmi(void);
extern u32 hdmi_edid_is_yuv(void);
extern uintptr_t hdmi_edid_get_data(void);

#endif /* __HDMI_EDID_H_ */
