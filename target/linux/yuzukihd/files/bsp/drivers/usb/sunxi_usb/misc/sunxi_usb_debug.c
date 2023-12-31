/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * (C) Copyright 2010-2015
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * javen, 2010-12-20, create this file
 *
 * usb debug.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 */

#include  "../include/sunxi_usb_config.h"

void print_usb_reg_by_ep(spinlock_t *lock,
		void __iomem *usbc_base,
		__s32 ep_index,
		char *str)
{
	__u32 old_ep_index = 0;

	DMSG_INFO("\n");
	DMSG_INFO("----------------ep%d: %s----------------\n",
		ep_index, str);

	if (ep_index >= 0) {
		old_ep_index = USBC_Readw(usbc_base + USBC_REG_o_EPIND);
		USBC_Writew(ep_index, (usbc_base + USBC_REG_o_EPIND));
		DMSG_INFO("old_ep_index = %d, ep_index = %d\n",
			old_ep_index, ep_index);
	}

	DMSG_INFO("USBC_REG_o_FADDR = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_FADDR));
	DMSG_INFO("USBC_REG_o_PCTL  = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_PCTL));
	DMSG_INFO("USBC_REG_o_INTTx = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_INTTx));
	DMSG_INFO("USBC_REG_o_INTRx = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_INTRx));
	DMSG_INFO("USBC_REG_o_INTTxE = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_INTTxE));
	DMSG_INFO("USBC_REG_o_INTRxE = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_INTRxE));
	DMSG_INFO("USBC_REG_o_INTUSB = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_INTUSB));
	DMSG_INFO("USBC_REG_o_INTUSBE = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_INTUSBE));
	DMSG_INFO("USBC_REG_o_EPIND = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_EPIND));
	DMSG_INFO("USBC_REG_o_TXMAXP = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_TXMAXP));
	DMSG_INFO("USBC_REG_o_CSR0 = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_CSR0));
	DMSG_INFO("USBC_REG_o_TXCSR = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_TXCSR));
	DMSG_INFO("USBC_REG_o_RXMAXP = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_RXMAXP));
	DMSG_INFO("USBC_REG_o_RXCSR = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_RXCSR));

	DMSG_INFO("USBC_REG_o_COUNT0 = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_COUNT0));
	DMSG_INFO("USBC_REG_o_RXCOUNT = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_RXCOUNT));
	DMSG_INFO("USBC_REG_o_TXTYPE = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_TXTYPE));
	DMSG_INFO("USBC_REG_o_NAKLIMIT0 = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_NAKLIMIT0));
	DMSG_INFO("USBC_REG_o_TXINTERVAL = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_TXINTERVAL));
	DMSG_INFO("USBC_REG_o_RXTYPE = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_RXTYPE));
	DMSG_INFO("USBC_REG_o_RXINTERVAL = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_RXINTERVAL));
	DMSG_INFO("USBC_REG_o_CONFIGDATA = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_CONFIGDATA));

	DMSG_INFO("USBC_REG_o_DEVCTL = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_DEVCTL));
	DMSG_INFO("USBC_REG_o_TXFIFOSZ = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_TXFIFOSZ));
	DMSG_INFO("USBC_REG_o_RXFIFOSZ = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_RXFIFOSZ));
	DMSG_INFO("USBC_REG_o_TXFIFOAD = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_TXFIFOAD));
	DMSG_INFO("USBC_REG_o_RXFIFOAD = 0x%x\n",
		USBC_Readw(usbc_base + USBC_REG_o_RXFIFOAD));
	DMSG_INFO("USBC_REG_o_VEND0 = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_VEND0));
	DMSG_INFO("USBC_REG_o_VEND1 = 0x%x\n",
		USBC_Readb(usbc_base + USBC_REG_o_VEND1));

	DMSG_INFO("TXFADDRx(%d) = 0x%x\n",
		ep_index, USBC_Readb(usbc_base + USBC_REG_o_TXFADDRx));
	DMSG_INFO("TXHADDRx(%d) = 0x%x\n",
		ep_index, USBC_Readb(usbc_base + USBC_REG_o_TXHADDRx));
	DMSG_INFO("TXHPORTx(%d) = 0x%x\n",
		ep_index, USBC_Readb(usbc_base + USBC_REG_o_TXHPORTx));
	DMSG_INFO("RXFADDRx(%d) = 0x%x\n",
		ep_index, USBC_Readb(usbc_base + USBC_REG_o_RXFADDRx));
	DMSG_INFO("RXHADDRx(%d) = 0x%x\n",
		ep_index, USBC_Readb(usbc_base + USBC_REG_o_RXHADDRx));
	DMSG_INFO("RXHPORTx(%d) = 0x%x\n",
		ep_index, USBC_Readb(usbc_base + USBC_REG_o_RXHPORTx));
	DMSG_INFO("RPCOUNTx(%d) = 0x%x\n",
		ep_index, (u32)USBC_Readl(usbc_base + USBC_REG_o_RPCOUNT));

	DMSG_INFO("USBC_REG_o_ISCR = 0x%x\n",
		(u32)USBC_Readl(usbc_base + USBC_REG_o_ISCR));
	DMSG_INFO("USBC_REG_o_PHYCTL = 0x%x\n",
		(u32)USBC_Readl(usbc_base + USBC_REG_o_PHYCTL));
	DMSG_INFO("USBC_REG_o_PHYBIST = 0x%x\n",
		(u32)USBC_Readl(usbc_base + USBC_REG_o_PHYBIST));

	if (ep_index >= 0)
		USBC_Writew(old_ep_index, (usbc_base + USBC_REG_o_EPIND));

	DMSG_INFO("---------------------------------------------\n");
	DMSG_INFO("\n");
}

void print_all_usb_reg(spinlock_t *lock,
		void __iomem *usbc_base,
		__s32 ep_start,
		__u32 ep_end,
		char *str)
{
	__u32 i = 0;
	__u32 old_ep_index = 0;
	unsigned long flags = 0;

	if (lock) {
		spin_lock_irqsave(lock, flags);

		DMSG_INFO("\n");
		DMSG_INFO("--------print_all_usb_reg: %s--------\n", str);

		old_ep_index = USBC_Readw(usbc_base + USBC_REG_o_EPIND);

		for (i = ep_start; i <= ep_end; i++)
			print_usb_reg_by_ep(lock, usbc_base, i, str);

		USBC_Writew(old_ep_index, (usbc_base + USBC_REG_o_EPIND));

		DMSG_INFO("--------------------------------------\n");
		DMSG_INFO("\n");

		spin_unlock_irqrestore(lock, flags);
	} else {

		DMSG_INFO("\n");
		DMSG_INFO("--------print_all_usb_reg: %s---------\n", str);

		old_ep_index = USBC_Readw(usbc_base + USBC_REG_o_EPIND);

		for (i = ep_start; i <= ep_end; i++)
			print_usb_reg_by_ep(lock, usbc_base, i, str);

		USBC_Writew(old_ep_index, (usbc_base + USBC_REG_o_EPIND));

		DMSG_INFO("---------------------------------------\n");
		DMSG_INFO("\n");
	}
}

void clear_usb_reg(void __iomem *usb_base)
{
	__u32 reg_val = 0;
	__u32 i = 0;

	/* global control and status */
	reg_val = USBC_Readl(USBC_REG_EX_USB_GCS(usb_base));
	reg_val = 0x20;
	USBC_Writel(reg_val, USBC_REG_EX_USB_GCS(usb_base));

	/* endpoint interrupt flag */
	reg_val = USBC_Readl(USBC_REG_EX_USB_EPINTF(usb_base));
	reg_val = 0x44;
	USBC_Writel(reg_val, USBC_REG_EX_USB_EPINTF(usb_base));

	/* endpoint interrupt enable */
	reg_val = USBC_Readl(USBC_REG_EX_USB_EPINTE(usb_base));
	reg_val = 0x48;
	USBC_Writel(reg_val, USBC_REG_EX_USB_EPINTE(usb_base));

	/* bus interrupt flag */
	reg_val = USBC_Readl(USBC_REG_EX_USB_BUSINTF(usb_base));
	reg_val = 0x4c;
	USBC_Writel(reg_val, USBC_REG_EX_USB_BUSINTF(usb_base));

	/* bus interrupt enable */
	reg_val = USBC_Readl(USBC_REG_EX_USB_BUSINTE(usb_base));
	reg_val = 0x50;
	USBC_Writel(reg_val, USBC_REG_EX_USB_BUSINTE(usb_base));

	/* endpoint control status */
	for (i = 0; i < USBC_MAX_EP_NUM; i++) {
		USBC_Writeb(i, USBC_REG_EPIND(usb_base));

		/* endpoint control status */
		if (i == 0) {
			reg_val = USBC_Readl(USBC_REG_EX_USB_CSR0(usb_base));
			reg_val = 0x00;
			USBC_Writel(reg_val, USBC_REG_EX_USB_CSR0(usb_base));
		} else {
			/* TX endpoint control status */
			reg_val = USBC_Readl(USBC_REG_EX_USB_TXCSR(usb_base));
			reg_val = 0x00;
			USBC_Writel(reg_val, USBC_REG_EX_USB_TXCSR(usb_base));

			/* RX endpoint control status */
			reg_val = USBC_Readl(USBC_REG_EX_USB_RXCSR(usb_base));
			reg_val = 0x00;
			USBC_Writel(reg_val, USBC_REG_EX_USB_RXCSR(usb_base));
		}

		/* TX fifo seting */
		reg_val = USBC_Readl(USBC_REG_EX_USB_TXFIFO(usb_base));
		reg_val = 0x90;
		USBC_Writel(reg_val, USBC_REG_EX_USB_TXFIFO(usb_base));

		/* RX fifo seting */
		reg_val = USBC_Readl(USBC_REG_EX_USB_RXFIFO(usb_base));
		reg_val = 0x94;
		USBC_Writel(reg_val, USBC_REG_EX_USB_RXFIFO(usb_base));

		/* function address */
		reg_val = USBC_Readl(USBC_REG_EX_USB_FADDR(usb_base));
		reg_val = 0x00;
		USBC_Writel(reg_val, USBC_REG_EX_USB_FADDR(usb_base));
	}

	USBC_Writeb(0x00, USBC_REG_EPIND(usb_base));
}
