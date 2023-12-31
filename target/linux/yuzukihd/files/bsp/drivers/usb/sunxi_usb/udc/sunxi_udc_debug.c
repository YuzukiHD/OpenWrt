/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * (C) Copyright 2010-2015
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * javen, 2010-3-3, create this file
 *
 * usb udc debug.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ioport.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/list.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/clk.h>

#include <linux/debugfs.h>
#include <linux/seq_file.h>

#include  "sunxi_udc_config.h"
#include  "sunxi_udc_board.h"
#include  "sunxi_udc_debug.h"

void print_list_node(struct sunxi_udc_ep *ep, char *str)
{
#ifdef SW_UDC_DEBUG
	struct sunxi_udc_request	*req = NULL;
	spinlock_t lock;
	unsigned long flags = 0;

	spin_lock_init(&lock);
	spin_lock_irqsave(&lock, flags);

	DMSG_INFO("---------------ep%d: %s-------------\n", ep->num, str);
	list_for_each_entry(req, &ep->queue, queue) {
		DMSG_INFO("print_list_node: ep(0x%p, %d), req(0x%p, 0x%p, %d, %d)\n\n",
			ep, ep->num, req, &(req->req),
			req->req.length, req->req.actual);
	}
	DMSG_INFO("-------------------------------------\n");

	spin_unlock_irqrestore(&lock, flags);

	return;
#endif
}
