// SPDX-License-Identifier: GPL-2.0
/*
 * Compatibility shim for ZWRT's prebuilt npu.ko on a public
 * cnjn/immortalwrt 7.3 kernel.
 *
 * The extracted ZWRT npu.ko imports six symbols that exist only in the
 * private ZWRT netfilter/SQM patch set.  Its other imports (XDP, phylink,
 * page_pool, flow_block, nf_flow_table, xpcs_config_eee_mult_fact, etc.)
 * are all provided by cnjn's public 7.3 patches.
 *
 * These stubs are intentionally no-ops: they make module loading succeed
 * without emulating ZWRT's proprietary SQM offload.  LAN/PON datapath is
 * unaffected.
 *
 * AArch64 passes arguments in x0-x7, so an 8-argument stub is ABI-safe for
 * any real signature with <= 8 arguments.  Kernel config MUST have
 * CONFIG_MODVERSIONS=n and CONFIG_MODULE_SIG_FORCE=n.
 */
#include <linux/module.h>
#include <linux/types.h>

#define ZWRT_STUB(name)                                                       \
	unsigned long name(unsigned long a0, unsigned long a1,               \
			   unsigned long a2, unsigned long a3,               \
			   unsigned long a4, unsigned long a5,               \
			   unsigned long a6, unsigned long a7)                \
	{                                                                      \
		return 0;                                                      \
	}                                                                      \
	EXPORT_SYMBOL_GPL(name)

ZWRT_STUB(nf_flow_sqm_ctl_cmd);
ZWRT_STUB(nf_flow_sqm_fill_mac_snap);
ZWRT_STUB(nf_flow_sqm_fill_snap);
ZWRT_STUB(nf_flow_sqm_set_hw_ops);
ZWRT_STUB(nf_flow_sqm_set_proc_hidden);
ZWRT_STUB(nf_flow_table_hw_resync);

MODULE_DESCRIPTION("ZWRT npu.ko symbol compatibility shim");
MODULE_LICENSE("GPL");
