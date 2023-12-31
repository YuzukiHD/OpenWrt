/* SPDX-License-Identifier: GPL-2.0-only */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#ifndef _CCU_GATE_H_
#define _CCU_GATE_H_

#include <linux/clk-provider.h>

#include "ccu_common.h"

struct ccu_gate {
	u32			enable;
	u32			fixed_rate;

	struct ccu_common	common;
};

#define SUNXI_CCU_GATE_ASSOC(_struct, _name, _parent, _reg, _gate,	\
			     _assoc_reg, _assoc_val, _flags)		\
	struct ccu_gate _struct = {					\
		.enable	= _gate,					\
		.common	= {						\
			.reg		= _reg,				\
			.assoc_reg	= _assoc_reg,			\
			.assoc_val	= _assoc_val,			\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_gate_ops,	\
						      _flags),		\
			.features	= CCU_FEATURE_GATE_DOUBLE_REG	\
		}							\
	}

#define SUNXI_CCU_GATE_WITH_FIXED_RATE(_struct, _name, _parent, _reg,	\
				       _fixed_rate, _gate)	\
	struct ccu_gate _struct = {					\
		.enable		= _gate,				\
		.fixed_rate	= _fixed_rate,				\
		.common	= {						\
			.reg		= _reg,				\
			.features	= CCU_FEATURE_FIXED_RATE_GATE,	\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_gate_ops,	\
						      0),		\
		}							\
	}

#define SUNXI_CCU_GATE_WITH_PREDIV(_struct, _name, _parent, _reg,	\
				   _prediv, _gate, _flags)		\
	struct ccu_gate _struct = {					\
		.enable	= _gate,					\
		.common	= {						\
			.reg		= _reg,				\
			.prediv		= _prediv,			\
			.features	= CCU_FEATURE_ALL_PREDIV,	\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_gate_ops,	\
						      _flags),		\
		}							\
	}

#define SUNXI_CCU_GATE_WITH_KEY(_struct, _name, _parent, _reg,		\
				_key_value, _gate, _flags)		\
	struct ccu_gate _struct = {					\
		.enable	= _gate,					\
		.common	= {						\
			.reg		= _reg,				\
			.key_value	= _key_value,			\
			.features	= CCU_FEATURE_KEY_FIELD_MOD,	\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_gate_ops,	\
						      _flags),		\
		}							\
	}

#define SUNXI_CCU_GATE(_struct, _name, _parent, _reg, _gate, _flags)	\
	struct ccu_gate _struct = {					\
		.enable	= _gate,					\
		.common	= {						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_gate_ops,	\
						      _flags),		\
		}							\
	}

#define SUNXI_CCU_GATE_HW(_struct, _name, _parent, _reg, _gate, _flags)	\
	struct ccu_gate _struct = {					\
		.enable	= _gate,					\
		.common	= {						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT_HW(_name,		\
							 _parent,	\
							 &ccu_gate_ops,	\
							 _flags),	\
		}							\
	}

#define SUNXI_CCU_GATE_FW(_struct, _name, _parent, _reg, _gate, _flags)	\
	struct ccu_gate _struct = {					\
		.enable	= _gate,					\
		.common	= {						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT_FW_NAME(_name,	\
							      _parent,	\
							      &ccu_gate_ops, \
							      _flags),	\
		}							\
	}

/*
 * The following two macros allow the re-use of the data structure
 * holding the parent info.
 */
#define SUNXI_CCU_GATE_HWS(_struct, _name, _parent, _reg, _gate, _flags) \
	struct ccu_gate _struct = {					\
		.enable	= _gate,					\
		.common	= {						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT_HWS(_name,	\
							  _parent,	\
							  &ccu_gate_ops, \
							  _flags),	\
		}							\
	}

#define SUNXI_CCU_GATE_DATA(_struct, _name, _data, _reg, _gate, _flags)	\
	struct ccu_gate _struct = {					\
		.enable	= _gate,					\
		.common	= {						\
			.reg		= _reg,				\
			.hw.init	=				\
				CLK_HW_INIT_PARENTS_DATA(_name,		\
							 _data,		\
							 &ccu_gate_ops,	\
							 _flags),	\
		}							\
	}

static inline struct ccu_gate *hw_to_ccu_gate(struct clk_hw *hw)
{
	struct ccu_common *common = hw_to_ccu_common(hw);

	return container_of(common, struct ccu_gate, common);
}

void ccu_gate_helper_disable(struct ccu_common *common, u32 gate);
int ccu_gate_helper_enable(struct ccu_common *common, u32 gate);
int ccu_gate_helper_is_enabled(struct ccu_common *common, u32 gate);

extern const struct clk_ops ccu_gate_ops;

#endif /* _CCU_GATE_H_ */
