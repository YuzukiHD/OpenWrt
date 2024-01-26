/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * Allwinner SoCs hdmi2.0 driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#ifndef _ESM_HDCP_HDMI_TX_CMD_H_
#define _ESM_HDCP_HDMI_TX_CMD_H_

#include "esm_cmd.h"

#define ESM_CMD_HDCP_HDMI_TX_START	ESM_CMD_START  /* look at esm_cmd.h to get starting location */

/* External Commands Request / Responses (with 0 parameters) */
#define ESM_HDCP_HDMI_TX_CMD_NO_PARAM                  ESM_CMD_HDCP_HDMI_TX_START
#define ESM_HDCP_HDMI_TX_CMD_AKE_STOP_REQ             (ESM_HDCP_HDMI_TX_CMD_NO_PARAM + 0)
#define ESM_HDCP_HDMI_TX_CMD_AKE_STOP_RESP            (ESM_HDCP_HDMI_TX_CMD_NO_PARAM + 0)
#define ESM_HDCP_HDMI_TX_CMD_AKE_LAST_HDCP_ERROR_REQ  (ESM_HDCP_HDMI_TX_CMD_NO_PARAM + 1)
#define ESM_HDCP_HDMI_TX_CMD_AKE_LAST_HDCP_ERROR_RESP (ESM_HDCP_HDMI_TX_CMD_NO_PARAM + 1)
#define ESM_HDCP_HDMI_TX_CMD_AKE_SET_CAPABILITY_REQ   (ESM_HDCP_HDMI_TX_CMD_NO_PARAM + 2)
#define ESM_HDCP_HDMI_TX_CMD_AKE_SET_CAPABILITY_RESP  (ESM_HDCP_HDMI_TX_CMD_NO_PARAM + 2)
#define ESM_HDCP_HDMI_TX_CMD_LOAD_SRM_REQ             (ESM_HDCP_HDMI_TX_CMD_NO_PARAM + 3)
#define ESM_HDCP_HDMI_TX_CMD_LOAD_SRM_RESP            (ESM_HDCP_HDMI_TX_CMD_NO_PARAM + 3)
#define ESM_HDCP_HDMI_TX_CMD_ENABLE_LOW_VALUE_CONTENT_REQ  (ESM_HDCP_HDMI_TX_CMD_NO_PARAM + 4)
#define ESM_HDCP_HDMI_TX_CMD_ENABLE_LOW_VALUE_CONTENT_RESP (ESM_HDCP_HDMI_TX_CMD_NO_PARAM + 4)

/* External Commands Request / Responses (with 1 parameters) */
#define ESM_HDCP_HDMI_TX_CMD_WITH_1_PARAM            (ESM_CMD_HDCP_HDMI_TX_START + 16)
#define ESM_HDCP_HDMI_TX_CMD_AKE_START_REQ           (ESM_HDCP_HDMI_TX_CMD_WITH_1_PARAM + 0)
#define ESM_HDCP_HDMI_TX_CMD_AKE_START_RESP          (ESM_HDCP_HDMI_TX_CMD_WITH_1_PARAM + 0)
#define ESM_HDCP_HDMI_TX_CMD_AKE_PAIRING_REQ         (ESM_HDCP_HDMI_TX_CMD_WITH_1_PARAM + 1)
#define ESM_HDCP_HDMI_TX_CMD_AKE_PAIRING_RESP        (ESM_HDCP_HDMI_TX_CMD_WITH_1_PARAM + 1)
#define ESM_HDCP_HDMI_TX_CMD_AKE_INFO_REQ            (ESM_HDCP_HDMI_TX_CMD_WITH_1_PARAM + 2)
#define ESM_HDCP_HDMI_TX_CMD_AKE_INFO_RESP           (ESM_HDCP_HDMI_TX_CMD_WITH_1_PARAM + 2)
#define ESM_HDCP_HDMI_TX_CMD_WOOCOMPATABILITY_REQ    (ESM_HDCP_HDMI_TX_CMD_WITH_1_PARAM + 3)
#define ESM_HDCP_HDMI_TX_CMD_WOOCOMPATABILITY_RESP   (ESM_HDCP_HDMI_TX_CMD_WITH_1_PARAM + 3)
#define ESM_HDCP_HDMI_TX_CMD_I2C_SHORTREAD_REQ       (ESM_HDCP_HDMI_TX_CMD_WITH_1_PARAM + 4)
#define ESM_HDCP_HDMI_TX_CMD_I2C_SHORTREAD_RESP      (ESM_HDCP_HDMI_TX_CMD_WITH_1_PARAM + 4)

/* External Commands Request / Responses (with 2 parameters) */
#define ESM_HDCP_HDMI_TX_CMD_WITH_2_PARAM   (ESM_CMD_HDCP_HDMI_TX_START + 32)

#define ESM_HDCP_HMDI_TX_CMD_MAX            (ESM_HDCP_HDMI_TX_CMD_WITH_2_PARAM + 1)

#if ESM_HDCP_HMDI_TX_CMD_MAX >= ESM_CMD_MAX
	#error "ESM_HDCP_HMDI_TX_CMD_MAX exceeds total command size"
#endif

/* External AKE Info Enumerated Types */
#define ESM_HDCP_HDMI_TX_CMD_AKE_INFO_ENUM_GET_DOWNSTREAM_TYPE 0
#define ESM_HDCP_HDMI_TX_CMD_AKE_INFO_ENUM_GET_TOPO_INFO       1

#endif /* _ESM_HDCP_HDMI_TX_CMD_H_ */
