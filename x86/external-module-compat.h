#ifndef __ASSEMBLY__
/*
 * Compatibility header for building as an external module.
 */

#include <linux/compiler.h>
#include <linux/version.h>
#include <linux/kconfig.h>

#include <linux/types.h>

#include <asm/cpufeature.h>

#include "../external-module-compat-comm.h"

#include <asm/microcode.h>
#include <asm/msr.h>
#include <asm/msr-index.h>
#include <asm/asm.h>
#include <asm/desc.h>
#include <asm/thread_info.h>

#ifndef CONFIG_HAVE_KVM_EVENTFD
#define CONFIG_HAVE_KVM_EVENTFD 1
#endif

#ifndef CONFIG_KVM_GENERIC_DIRTYLOG_READ_PROTECT
#define CONFIG_KVM_GENERIC_DIRTYLOG_READ_PROTECT 1
#endif

#ifndef CONFIG_KVM_APIC_ARCHITECTURE
#define CONFIG_KVM_APIC_ARCHITECTURE
#endif

#ifndef CONFIG_KVM_MMIO
#define CONFIG_KVM_MMIO
#endif

#ifndef CONFIG_KVM_ASYNC_PF
#define CONFIG_KVM_ASYNC_PF 1
#endif

#ifndef CONFIG_HAVE_KVM_MSI
#define CONFIG_HAVE_KVM_MSI 1
#endif

#ifndef CONFIG_HAVE_KVM_IRQCHIP
#define CONFIG_HAVE_KVM_IRQCHIP 1
#endif

#ifndef CONFIG_HAVE_KVM_IRQ_ROUTING
#define CONFIG_HAVE_KVM_IRQ_ROUTING 1
#endif

#ifndef CONFIG_HAVE_KVM_IRQFD
#define CONFIG_HAVE_KVM_IRQFD 1
#endif

#ifndef CONFIG_HAVE_KVM_CPU_RELAX_INTERCEPT
#define CONFIG_HAVE_KVM_CPU_RELAX_INTERCEPT 1
#endif

#include <linux/smp.h>

#ifndef X86_FEATURE_SSBD
#define X86_FEATURE_SSBD		( 7*32+17) /* Speculative Store Bypass Disable */
#endif

#ifndef X86_FEATURE_LS_CFG_SSBD
#define X86_FEATURE_LS_CFG_SSBD		( 7*32+24)  /* "" AMD SSBD implementation via LS_CFG MSR */
#endif

#ifndef X86_FEATURE_CLDEMOTE
#define X86_FEATURE_CLDEMOTE		(16*32+25) /* CLDEMOTE instruction */
#endif

#ifndef X86_FEATURE_WBNOINVD
#define X86_FEATURE_WBNOINVD		(13*32+ 9) /* WBNOINVD instruction */
#endif

#ifndef X86_FEATURE_AMD_IBPB
#define X86_FEATURE_AMD_IBPB		(13*32+12) /* "" Indirect Branch Prediction Barrier */
#endif

#ifndef X86_FEATURE_AMD_IBRS
#define X86_FEATURE_AMD_IBRS		(13*32+14) /* "" Indirect Branch Restricted Speculation */
#endif

#ifndef X86_FEATURE_AMD_SSBD
#define X86_FEATURE_AMD_SSBD		(13*32+24) /* "" Speculative Store Bypass Disable */
#endif

#ifndef X86_FEATURE_VIRT_SSBD
#define X86_FEATURE_VIRT_SSBD		(13*32+25) /* Virtualized Speculative Store Bypass Disable */
#endif

#ifndef X86_FEATURE_AMD_SSB_NO
#define X86_FEATURE_AMD_SSB_NO		(13*32+26) /* "" Speculative Store Bypass is fixed in hardware. */
#endif

#ifndef X86_FEATURE_FLUSH_L1D
#define X86_FEATURE_FLUSH_L1D		(18*32+28) /* IA32_FLUSH_L1D MSR */
#endif

#ifndef X86_FEATURE_SPEC_CTRL_SSBD
#define X86_FEATURE_SPEC_CTRL_SSBD	(18*32+31) /* "" Speculative Store Bypass Disable */
#endif

#ifndef MSR_F15H_PERF_CTL
#define MSR_F15H_PERF_CTL               0xc0010200
#endif
#ifndef MSR_F15H_PERF_CTL0
#define MSR_F15H_PERF_CTL0              MSR_F15H_PERF_CTL
#endif
#ifndef MSR_F15H_PERF_CTL1
#define MSR_F15H_PERF_CTL1              (MSR_F15H_PERF_CTL + 2)
#endif
#ifndef MSR_F15H_PERF_CTL2
#define MSR_F15H_PERF_CTL2              (MSR_F15H_PERF_CTL + 4)
#endif
#ifndef MSR_F15H_PERF_CTL3
#define MSR_F15H_PERF_CTL3              (MSR_F15H_PERF_CTL + 6)
#endif
#ifndef MSR_F15H_PERF_CTL4
#define MSR_F15H_PERF_CTL4              (MSR_F15H_PERF_CTL + 8)
#endif
#ifndef MSR_F15H_PERF_CTL5
#define MSR_F15H_PERF_CTL5              (MSR_F15H_PERF_CTL + 10)
#endif

#ifndef MSR_F15H_PERF_CTR
#define MSR_F15H_PERF_CTR               0xc0010201
#endif
#ifndef MSR_F15H_PERF_CTR0
#define MSR_F15H_PERF_CTR0              MSR_F15H_PERF_CTR
#endif
#ifndef MSR_F15H_PERF_CTR1
#define MSR_F15H_PERF_CTR1              (MSR_F15H_PERF_CTR + 2)
#endif
#ifndef MSR_F15H_PERF_CTR2
#define MSR_F15H_PERF_CTR2              (MSR_F15H_PERF_CTR + 4)
#endif
#ifndef MSR_F15H_PERF_CTR3
#define MSR_F15H_PERF_CTR3              (MSR_F15H_PERF_CTR + 6)
#endif
#ifndef MSR_F15H_PERF_CTR4
#define MSR_F15H_PERF_CTR4              (MSR_F15H_PERF_CTR + 8)
#endif
#ifndef MSR_F15H_PERF_CTR5
#define MSR_F15H_PERF_CTR5              (MSR_F15H_PERF_CTR + 10)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(4,17,0)
static inline unsigned long cpu_kernelmode_gs_base(int cpu)
{
	unsigned long a;
	rdmsrl(MSR_GS_BASE, a);
	return a;
}

static inline void save_fsgs_for_kvm(void)
{
        savesegment(fs, current->thread.fsindex);
        savesegment(gs, current->thread.gsindex);
        if (unlikely(current->thread.fsindex != 0))
		current->thread.fsbase = 0;
        if (unlikely(current->thread.gsindex != 0))
		current->thread.gsbase = 0;
}
#endif

#ifndef _TIF_SSBD
static inline void x86_virt_spec_ctrl(u64 guest_spec_ctrl, u64 guest_virt_spec_ctrl, bool setguest)
{
	/* Is MSR_SPEC_CTRL implemented ? */
	if (static_cpu_has(X86_FEATURE_SPEC_CTRL) && guest_spec_ctrl != 0)
		wrmsrl(MSR_IA32_SPEC_CTRL, setguest ? guest_spec_ctrl : 0);
}
#endif

#ifndef X86_BUG_L1TF
#define KVM_KMOD_NEED_L1TF_DEFS

#define X86_BUG_L1TF			X86_BUG(18) /* CPU is affected by L1 Terminal Fault */

enum l1tf_mitigations {
        L1TF_MITIGATION_OFF,
        L1TF_MITIGATION_FLUSH_NOWARN,
        L1TF_MITIGATION_FLUSH,
        L1TF_MITIGATION_FLUSH_NOSMT,
        L1TF_MITIGATION_FULL,
        L1TF_MITIGATION_FULL_FORCE
};

#define l1tf_mitigation (L1TF_MITIGATION_OFF)

enum cpuhp_smt_control {
        CPU_SMT_ENABLED,
        CPU_SMT_DISABLED,
        CPU_SMT_FORCE_DISABLED,
        CPU_SMT_NOT_SUPPORTED,
};

#define cpu_smt_control                (CPU_SMT_ENABLED)

static inline bool kvm_get_cpu_l1tf_flush_l1d(void)
{
	return false;
}

static inline void kvm_clear_cpu_l1tf_flush_l1d(void)
{
}

#endif

#ifndef X86_VENDOR_HYGON
#define X86_VENDOR_HYGON 9
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(4,21,0)
#define intel_pt_validate_cap(caps, capability) 0
#define intel_pt_validate_hw_cap(capability) 0

#endif

#ifndef PT_CPUID_REGS_NUM
#define PT_CPUID_REGS_NUM 4
#endif
#ifndef PT_CPUID_LEAVES
#define PT_CPUID_LEAVES 2
#endif

#endif
