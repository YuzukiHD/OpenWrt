/**
 ******************************************************************************
 *
 * @file rwnx_mod_params.h
 *
 * @brief Declaration of module parameters
 *
 * Copyright (C) RivieraWaves 2012-2019
 *
 ******************************************************************************
 */

#ifndef _RWNX_MOD_PARAM_H_
#define _RWNX_MOD_PARAM_H_

#include <linux/module.h>
#include <linux/rtnetlink.h>

#include "rwnx_defs.h"
#include "rwnx_tx.h"
#include "hal_desc.h"
//#include "rwnx_cfgfile.h"
#include "rwnx_dini.h"
#include "reg_access.h"
#include "rwnx_compat.h"
#include "aic_bsp_export.h"


struct rwnx_mod_params {
	bool ht_on;
	bool vht_on;
	bool he_on;
	int mcs_map;
	int he_mcs_map;
	bool he_ul_on;
	bool ldpc_on;
	bool stbc_on;
	bool gf_rx_on;
	int phy_cfg;
	int uapsd_timeout;
	bool ap_uapsd_on;
	bool sgi;
	bool sgi80;
	bool use_2040;
	bool use_80;
	bool custregd;
	bool custchan;
	int nss;
	int amsdu_rx_max;
	bool bfmee;
	bool bfmer;
	bool mesh;
	bool murx;
	bool mutx;
	bool mutx_on;
	unsigned int roc_dur_max;
	int listen_itv;
	bool listen_bcmc;
	int lp_clk_ppm;
	bool ps_on;
	int tx_lft;
	int amsdu_maxnb;
	int uapsd_queues;
	bool tdls;
	bool uf;
	char *ftl;
	bool dpsm;
#ifdef CONFIG_RWNX_FULLMAC
	bool ant_div;
#endif /* CONFIG_RWNX_FULLMAC */
};

extern struct rwnx_mod_params rwnx_mod_params;

struct rwnx_hw;
struct wiphy;
int rwnx_handle_dynparams(struct rwnx_hw *rwnx_hw, struct wiphy *wiphy);
void rwnx_custregd(struct rwnx_hw *rwnx_hw, struct wiphy *wiphy);
void rwnx_enable_wapi(struct rwnx_hw *rwnx_hw);
void rwnx_enable_mfp(struct rwnx_hw *rwnx_hw);
void rwnx_get_countrycode_channels(struct wiphy *wiphy, struct ieee80211_regdomain *regdomain);
struct ieee80211_regdomain *getRegdomainFromRwnxDB(struct wiphy *wiphy, char *alpha2);


#endif /* _RWNX_MOD_PARAM_H_ */
