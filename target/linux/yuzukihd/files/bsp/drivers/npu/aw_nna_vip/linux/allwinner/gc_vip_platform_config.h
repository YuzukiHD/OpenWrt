/* SPDX-License-Identifier: GPL-2.0-or-later */
/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright (c) 2017 - 2021 Vivante Corporation
*
*    Permission is hereby granted, free of charge, to any person obtaining a
*    copy of this software and associated documentation files (the "Software"),
*    to deal in the Software without restriction, including without limitation
*    the rights to use, copy, modify, merge, publish, distribute, sublicense,
*    and/or sell copies of the Software, and to permit persons to whom the
*    Software is furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in
*    all copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*    DEALINGS IN THE SOFTWARE.
*
*****************************************************************************
*
*    The GPL License (GPL)
*
*    Copyright (C) 2017 - 2021 Vivante Corporation
*
*    This program is free software; you can redistribute it and/or
*    modify it under the terms of the GNU General Public License
*    as published by the Free Software Foundation; either version 2
*    of the License, or (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program;
*****************************************************************************
*
*    Note: This software is released under dual MIT and GPL licenses. A
*    recipient may use this file under the terms of either the MIT license or
*    GPL License. If you wish to use only one license not the other, you can
*    indicate your decision by deleting one of the above license notices in your
*    version of this file.
*
*****************************************************************************/

#ifndef _GC_VIP_PLATFORM_CONFIG_H
#define _GC_VIP_PLATFORM_CONFIG_H

#include "gc_vip_common.h"

/* the core number of VIP.
   It's for multiple VIP hardware. Please set gcdCORE_COUNT to 1 if is single core VIP
*/
#define  gcdCORE_COUNT                  1

/* the logic devices number and core number for each logical device.
 * we need configure this after create nbg files.
 * The core count of logical device should be matched with core count in NBG file.
 * for example: LOGIC_DEVICES_WITH_CORE[8] = {2,2,4,0,0,0,0,0}.
 * indicate that the current driver supports 3 logical device.
 * device[0] and device[1] have 2 cores, device[2] have 4 cores.
 * the others devices not available, each device have different core index.
 * NOTE:
 * LOGIC_DEVICES_WITH_CORE[8] = {2,1,0,4,0,0,0,0}. indicate that driver supports 2 logical device.
 * device[0] is 2 cores, device[1] is 1 core.  the 4 is invalid config.
*/
static const vip_uint32_t LOGIC_DEVICES_WITH_CORE[gcdCORE_COUNT] = {1};

/* default size 2M for system memory heap, access by CPU only */
/* NBinfo tool can get system memory size */
#define SYSTEM_MEMORY_HEAP_SIZE         (2 << 20)


/* NBinfo tool can get video memory size */
/* default size 4 bytes for video memory heap, access by VIP */
#if defined (USE_LINUX_RESERVE_MEM)
#define VIDEO_MEMORY_HEAP_SIZE          (16 << 20)
#else
#define VIDEO_MEMORY_HEAP_SIZE          (32 << 20)
#endif

/* defalut base pyhsical address of video memory heap */
#define VIDEO_MEMORY_HEAP_BASE_ADDRESS  0x30000000

/* AHB register base physical address for each core.
   NOTE: VSI replace these values are in the insmod command line parameter */
static const  vip_uint32_t AHB_REGISTER_BASE_ADDRESS[gcdCORE_COUNT] = {0x03050000};

/* The size of AHB register for each core. */
static const  vip_uint32_t AHB_REGISTER_SIZE[gcdCORE_COUNT] = {0x00020000};

/* irq line number for each core. */
static const  vip_uint32_t IRQ_LINE_NUMBER[gcdCORE_COUNT] = {190};

/* the size of VIP SRAM */
#define VIP_SRAM_SIZE               0x80000

/*
The base address of VIP SRAM.
VIP SRAM is a SRAM inside VIP core. It needs to be mapped to a 32 bits address space.
The VIP_SRAM_BASE_ADDRESS is a base address for mapping VIP SRAM, so the VIP SRAM has been mapped to
[VIP_SRAM_BASE_ADDRESS ~~ VIP_SRAM_BASE_ADDRESS + VIP_SRAM_SIZE] range.
After this mapping, VIP core access VIP SRAM through
VIP_SRAM_BASE_ADDRESS ~~ VIP_SRAM_BASE_ADDRESS+VIP_SRAM_SIZE address range.
Actually, The value of VIP_SRAM_BASE_ADDRESS may not be on DRAM.

How to config the VIP_SRAM_BASE_ADDRESS?
1. It can only be a 32bits value.
2. can't be config to zero.
3. It can't be configured to be close to 4Gbytes value.
   (VIP_SRAM_BASE_ADDRESS+vip_sram_size) can't be close to 4Gbytes.
4. It should be align to 64bytes.
5. can't be overlap with video memory range.

example:

The size of DRAM is 1G bytes. So DRAM memory address range is [0 ~~ 0x40000000].
In this case, you can set the value of vip_sram_address to 0x50000000. 0x50000000 is outside of DRAM.
0x50000000 is not a real physical address on SRAM.

If you need to specify address for VIP-SRAM, this value can be outside the range of video memory.
The address shoule be aligned to 64byte.

don't need configure VIP_SRAM_BASE_ADDRESS if set vpmdENABLE_MMU to 1.
Because driver will reserved memory space for VIP-SRAM in MMU page table.
We recomment that remap VIP-SRAM base address to 0x400000 when MMU is disabled.
*/
#define VIP_SRAM_BASE_ADDRESS           0x400000

/* the size of AXI SRAM, please set the value to zero if chip without AXI-SRAM.
   otherwise, follow chip real AXI-SRAM size setting.
*/
#define AXI_SRAM_SIZE               0x00
/* the physical base address of AXI SRAM. The value of AXI_SRAM_BASE_ADDRESS is should be
   real address of AXI-SRAM on chip if the chip have AXI-SRAM.
*/
#define AXI_SRAM_BASE_ADDRESS       0x00

/* PCIE bar.
   NOTE: VSI replace these values are in the insmod command line parameter */
static const  vip_uint32_t PCI_BARS[gcdCORE_COUNT] = {1};

#endif
