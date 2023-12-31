/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * Copyright (C) 2019 - Reuuimlla Limited
 * Yihuasheng <yihuasheng@allwinnertech.com>
 *
 * SUNXI SPI Slave Protocol Definition
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

/*
#define HEAD_LENGTH
#define OP_MASK		0
#define ADDR_MASK_0	1
#define ADDR_MASK_1	2
#define ADDR_MASK_2	3
#define LENGTH_MASK_0	4
#define LENGTH_MASK_1	5
#define LENGTH_MASK_2	6
#define SUNXI_OP_WRITE	0x01
#define SUNXI_OP_READ	0x03
*/

#define HEAD_LEN 5
#define PKT_MAX_LEN 0x40
#define STATUS_LEN 0x01

#define STATUS_WRITABLE 0x02
#define STATUS_NOTWRITABLE 0x03
#define STATUS_READABLE 0x04

#define OP_MASK		0
#define ADDR_MASK_0	1
#define ADDR_MASK_1	2
#define ADDR_MASK_2	3
#define LENGTH_MASK	4
#define SUNXI_OP_WRITE	0x01
#define SUNXI_OP_READ	0x03



struct sunxi_spi_slave_head {
	int op_code;
	int addr;
	int len;
};

struct device_data {
	unsigned char *tx_buf, *rx_buf;
	unsigned char len; /* max len is 64 */
};

struct sunxi_slave {
	struct sunxi_spi_slave_head *head;
	struct device_data *data;
	struct device_data *(*set_up_txdata)(struct sunxi_spi_slave_head *head);
};
