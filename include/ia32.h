/** @file */
#pragma once

#ifdef __KERNEL__

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

// mtrr physical base msrs
#define msr_ia32_mtrr_physbase0 0x00000200
#define msr_ia32_mtrr_physbase1 0x00000202
#define msr_ia32_mtrr_physbase2 0x00000204
#define msr_ia32_mtrr_physbase3 0x00000206
#define msr_ia32_mtrr_physbase4 0x00000208
#define msr_ia32_mtrr_physbase5 0x0000020a
#define msr_ia32_mtrr_physbase6 0x0000020c
#define msr_ia32_mtrr_physbase7 0x0000020e
#define msr_ia32_mtrr_physbase8 0x00000210
#define msr_ia32_mtrr_physbase9 0x00000212

// mtrr physical mask msrs
#define msr_ia32_mtrr_physmask0 0x00000201
#define msr_ia32_mtrr_physmask1 0x00000203
#define msr_ia32_mtrr_physmask2 0x00000205
#define msr_ia32_mtrr_physmask3 0x00000207
#define msr_ia32_mtrr_physmask4 0x00000209
#define msr_ia32_mtrr_physmask5 0x0000020b
#define msr_ia32_mtrr_physmask6 0x0000020d
#define msr_ia32_mtrr_physmask7 0x0000020f
#define msr_ia32_mtrr_physmask8 0x00000211
#define msr_ia32_mtrr_physmask9 0x00000213

// memory types
#define memory_type_uncacheable 0x00000000
#define memory_type_write_combining 0x00000001
#define memory_type_write_through 0x00000004
#define memory_type_write_protected 0x00000005
#define memory_type_write_back 0x00000006
#define memory_type_invalid 0x000000ff

// vmx ept & vpid capabilities msr
#define msr_ia32_vmx_ept_vpid_cap 0x0000048c

// mtrr def msr
#define msr_ia32_mtrr_def_type 0x000002ff

// mtrr capabilities msr
#define msr_ia32_mtrr_capabilities 0x000000fe

/**
 * @defgroup intel_manual \
 *           intel manual
 *
 * @remarks all references are based on <b>intel(r) 64 and ia-32 architectures software developer's manual combined volumes:
 *          1, 2a, 2b, 2c, 2d, 3a, 3b, 3c, 3d, and 4</b> (may 2018).
 * @{
 */
/**
 * @defgroup control_registers \
 *           control registers
 *
 * control registers (cr0, cr1, cr2, cr3, and cr4) determine operating mode of the processor and the characteristics of the
 * currently executing task. these registers are 32 bits in all 32-bit modes and compatibility mode.
 * in 64-bit mode, control registers are expanded to 64 bits. the mov crn instructions are used to manipulate the register
 * bits. operand-size prefixes for these instructions are ignored. the following is also true:
 * - the control registers can be read and loaded (or modified) using the move-to-or-from-control-registers forms of the
 * mov instruction. in protected mode, the mov instructions allow the control registers to be read or loaded (at privilege
 * level 0 only). this restriction means that application programs or operating-system procedures (running at privilege
 * levels 1, 2, or 3) are prevented from reading or loading the control registers.
 * - bits 63:32 of cr0 and cr4 are reserved and must be written with zeros. writing a nonzero value to any of the upper 32
 * bits results in a general-protection exception, \#gp(0).
 * - all 64 bits of cr2 are writable by software.
 * - bits 51:40 of cr3 are reserved and must be 0.
 * - the mov crn instructions do not check that addresses written to cr2 and cr3 are within the linear-address or
 * physical-address limitations of the implementation.
 * - register cr8 is available in 64-bit mode only. the control registers are summarized below, and each architecturally
 * defined control field in these control registers is described individually.
 * - cr0 - contains system control flags that control operating mode and states of the processor.
 * - cr1 - reserved.
 * - cr2 - contains the page-fault linear address (the linear address that caused a page fault).
 * - cr3 - contains the physical address of the base of the paging-structure hierarchy and two flags (pcd and pwt). only
 * the most-significant bits (less the lower 12 bits) of the base address are specified; the lower 12 bits of the address
 * are assumed to be 0. the first paging structure must thus be aligned to a page (4-kbyte) boundary. the pcd and pwt flags
 * control caching of that paging structure in the processor's internal data caches (they do not control tlb caching of
 * page-directory information). when using the physical address extension, the cr3 register contains the base address of
 * the page-directorypointer table. in ia-32e mode, the cr3 register contains the base address of the pml4 table.
 * - cr4 - contains a group of flags that enable several architectural extensions, and indicate operating system or
 * executive support for specific processor capabilities.
 * - cr8 - provides read and write access to the task priority register (tpr). it specifies the priority threshold value
 * that operating systems use to control the priority class of external interrupts allowed to interrupt the processor. this
 * register is available only in 64-bit mode. however, interrupt filtering continues to apply in compatibility mode.
 *
 * @see vol3a[2.5(control registers)] (reference)
 * @{
 */
typedef union {
	struct {
		/**
                 * @brief protection enable
                 *
                 * [bit 0] enables protected mode when set; enables real-address mode when clear. this flag does not enable paging
                 * directly. it only enables segment-level protection. to enable paging, both the pe and pg flags must be set.
                 *
                 * @see vol3a[9.9(mode switching)]
                 */
		uint64 protectionenable : 1;
#define cr0_protection_enable_bit 0
#define cr0_protection_enable_flag 0x01
#define cr0_protection_enable_mask 0x01
#define cr0_protection_enable(_) (((_) >> 0) & 0x01)

		/**
                 * @brief monitor coprocessor
                 *
                 * [bit 1] controls the interaction of the wait (or fwait) instruction with the ts flag (bit 3 of cr0). if the mp flag is
                 * set, a wait instruction generates a device-not-available exception (\#nm) if the ts flag is also set. if the mp flag is
                 * clear, the wait instruction ignores the setting of the ts flag.
                 */
		uint64 monitorcoprocessor : 1;
#define cr0_monitor_coprocessor_bit 1
#define cr0_monitor_coprocessor_flag 0x02
#define cr0_monitor_coprocessor_mask 0x01
#define cr0_monitor_coprocessor(_) (((_) >> 1) & 0x01)

		/**
                 * @brief fpu emulation
                 *
                 * [bit 2] indicates that the processor does not have an internal or external x87 fpu when set; indicates an x87 fpu is
                 * present when clear. this flag also affects the execution of mmx/sse/sse2/sse3/ssse3/sse4 instructions.
                 * when the em flag is set, execution of an x87 fpu instruction generates a device-not-available exception (\#nm). this
                 * flag must be set when the processor does not have an internal x87 fpu or is not connected to an external math
                 * coprocessor. setting this flag forces all floating-point instructions to be handled by software emulation.
                 * also, when the em flag is set, execution of an mmx instruction causes an invalid-opcode exception (\#ud) to be
                 * generated. thus, if an ia-32 or intel 64 processor incorporates mmx technology, the em flag must be set to 0 to enable
                 * execution of mmx instructions. similarly for sse/sse2/sse3/ssse3/sse4 extensions, when the em flag is set, execution of
                 * most sse/sse2/sse3/ssse3/sse4 instructions causes an invalid opcode exception (\#ud) to be generated. if an ia-32 or
                 * intel 64 processor incorporates the sse/sse2/sse3/ssse3/sse4 extensions, the em flag must be set to 0 to enable
                 * execution of these extensions. sse/sse2/sse3/ssse3/sse4 instructions not affected by the em flag include: pause,
                 * prefetchh, sfence, lfence, mfence, movnti, clflush, crc32, and popcnt.
                 */
		uint64 emulatefpu : 1;
#define cr0_emulate_fpu_bit 2
#define cr0_emulate_fpu_flag 0x04
#define cr0_emulate_fpu_mask 0x01
#define cr0_emulate_fpu(_) (((_) >> 2) & 0x01)

		/**
                 * @brief task switched
                 *
                 * [bit 3] allows the saving of the x87 fpu/mmx/sse/sse2/sse3/ssse3/sse4 context on a task switch to be delayed until an
                 * x87 fpu/mmx/sse/sse2/sse3/ssse3/sse4 instruction is actually executed by the new task. the processor sets this flag on
                 * every task switch and tests it when executing x87 fpu/mmx/sse/sse2/sse3/ssse3/sse4 instructions.
                 * - if the ts flag is set and the em flag (bit 2 of cr0) is clear, a device-not-available exception (\#nm) is raised prior
                 * to the execution of any x87 fpu/mmx/sse/sse2/sse3/ssse3/sse4 instruction; with the exception of pause, prefetchh,
                 * sfence, lfence, mfence, movnti, clflush, crc32, and popcnt.
                 * - if the ts flag is set and the mp flag (bit 1 of cr0) and em flag are clear, an \#nm exception is not raised prior to
                 * the execution of an x87 fpu wait/fwait instruction.
                 * - if the em flag is set, the setting of the ts flag has no effect on the execution of x87
                 * fpu/mmx/sse/sse2/sse3/ssse3/sse4 instructions.
                 *   the processor does not automatically save the context of the x87 fpu, xmm, and mxcsr registers on a task switch.
                 *   instead, it sets the ts flag, which causes the processor to raise an \#nm exception whenever it encounters an x87
                 *   fpu/mmx/sse/sse2/sse3/ssse3/sse4 instruction in the instruction stream for the new task (with the exception of the
                 *   instructions listed above).
                 *   the fault handler for the \#nm exception can then be used to clear the ts flag (with the clts instruction) and save
                 *   the context of the x87 fpu, xmm, and mxcsr registers. if the task never encounters an x87
                 *   fpu/mmx/sse/sse2/sse3/ssse3/sse4 instruction, the x87 fpu/mmx/sse/sse2/sse3/ssse3/sse4 context is never saved.
                 */
		uint64 taskswitched : 1;
#define cr0_task_switched_bit 3
#define cr0_task_switched_flag 0x08
#define cr0_task_switched_mask 0x01
#define cr0_task_switched(_) (((_) >> 3) & 0x01)

		/**
                 * @brief extension type
                 *
                 * [bit 4] reserved in the pentium 4, intel xeon, p6 family, and pentium processors. in the pentium 4, intel xeon, and p6
                 * family processors, this flag is hardcoded to 1. in the intel386 and intel486 processors, this flag indicates support of
                 * intel 387 dx math coprocessor instructions when set.
                 */
		uint64 extensiontype : 1;
#define cr0_extension_type_bit 4
#define cr0_extension_type_flag 0x10
#define cr0_extension_type_mask 0x01
#define cr0_extension_type(_) (((_) >> 4) & 0x01)

		/**
                 * @brief numeric error
                 *
                 * [bit 5] enables the native (internal) mechanism for reporting x87 fpu errors when set; enables the pc-style x87 fpu
                 * error reporting mechanism when clear. when the ne flag is clear and the ignne\# input is asserted, x87 fpu errors are
                 * ignored. when the ne flag is clear and the ignne\# input is deasserted, an unmasked x87 fpu error causes the processor
                 * to assert the ferr\# pin to generate an external interrupt and to stop instruction execution immediately before
                 * executing the next waiting floating-point instruction or wait/fwait instruction.
                 * the ferr\# pin is intended to drive an input to an external interrupt controller (the ferr\# pin emulates the error\#
                 * pin of the intel 287 and intel 387 dx math coprocessors). the ne flag, ignne\# pin, and ferr\# pin are used with
                 * external logic to implement pc-style error reporting. using ferr\# and ignne\# to handle floating-point exceptions is
                 * deprecated by modern operating systems; this non-native approach also limits newer processors to operate with one
                 * logical processor active.
                 *
                 * @see vol1[8.7(handling x87 fpu exceptions in software)]
                 * @see vol1[a.1(appendix a | eflags cross-reference)]
                 */
		uint64 numericerror : 1;
#define cr0_numeric_error_bit 5
#define cr0_numeric_error_flag 0x20
#define cr0_numeric_error_mask 0x01
#define cr0_numeric_error(_) (((_) >> 5) & 0x01)
		uint64 reserved1 : 10;

		/**
                 * @brief write protect
                 *
                 * [bit 16] when set, inhibits supervisor-level procedures from writing into readonly pages; when clear, allows
                 * supervisor-level procedures to write into read-only pages (regardless of the u/s bit setting). this flag facilitates
                 * implementation of the copy-onwrite method of creating a new process (forking) used by operating systems such as unix.
                 *
                 * @see vol3a[4.1.3(paging-mode modifiers)]
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 writeprotect : 1;
#define cr0_write_protect_bit 16
#define cr0_write_protect_flag 0x10000
#define cr0_write_protect_mask 0x01
#define cr0_write_protect(_) (((_) >> 16) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * @brief alignment mask
                 *
                 * [bit 18] enables automatic alignment checking when set; disables alignment checking when clear. alignment checking is
                 * performed only when the am flag is set, the ac flag in the eflags register is set, cpl is 3, and the processor is
                 * operating in either protected or virtual-8086 mode.
                 */
		uint64 alignmentmask : 1;
#define cr0_alignment_mask_bit 18
#define cr0_alignment_mask_flag 0x40000
#define cr0_alignment_mask_mask 0x01
#define cr0_alignment_mask(_) (((_) >> 18) & 0x01)
		uint64 reserved3 : 10;

		/**
                 * @brief not write-through
                 *
                 * [bit 29] when the nw and cd flags are clear, write-back (for pentium 4, intel xeon, p6 family, and pentium processors)
                 * or write-through (for intel486 processors) is enabled for writes that hit the cache and invalidation cycles are enabled.
                 */
		uint64 notwritethrough : 1;
#define cr0_not_write_through_bit 29
#define cr0_not_write_through_flag 0x20000000
#define cr0_not_write_through_mask 0x01
#define cr0_not_write_through(_) (((_) >> 29) & 0x01)

		/**
                 * @brief cache disable
                 *
                 * [bit 30] when the cd and nw flags are clear, caching of memory locations for the whole of physical memory in the
                 * processor's internal (and external) caches is enabled. when the cd flag is set, caching is restricted. to prevent the
                 * processor from accessing and updating its caches, the cd flag must be set and the caches must be invalidated so that no
                 * cache hits can occur.
                 *
                 * @see vol3a[11.5.3(preventing caching)]
                 * @see vol3a[11.5(cache control)]
                 */
		uint64 cachedisable : 1;
#define cr0_cache_disable_bit 30
#define cr0_cache_disable_flag 0x40000000
#define cr0_cache_disable_mask 0x01
#define cr0_cache_disable(_) (((_) >> 30) & 0x01)

		/**
                 * @brief paging enable
                 *
                 * [bit 31] enables paging when set; disables paging when clear. when paging is disabled, all linear addresses are treated
                 * as physical addresses. the pg flag has no effect if the pe flag (bit 0 of register cr0) is not also set; setting the pg
                 * flag when the pe flag is clear causes a general-protection exception (\#gp).
                 * on intel 64 processors, enabling and disabling ia-32e mode operation also requires modifying cr0.pg.
                 *
                 * @see vol3a[4(paging)]
                 */
		uint64 pagingenable : 1;
#define cr0_paging_enable_bit 31
#define cr0_paging_enable_flag 0x80000000
#define cr0_paging_enable_mask 0x01
#define cr0_paging_enable(_) (((_) >> 31) & 0x01)
		uint64 reserved4 : 32;
	};

	uint64 flags;
} cr0;

typedef union {
	struct {
		uint64 reserved1 : 3;

		/**
                 * @brief page-level write-through
                 *
                 * [bit 3] controls the memory type used to access the first paging structure of the current paging-structure hierarchy.
                 * this bit is not used if paging is disabled, with pae paging, or with 4-level paging if cr4.pcide=1.
                 *
                 * @see vol3a[4.9(paging and memory typing)]
                 */
		uint64 pagelevelwritethrough : 1;
#define cr3_page_level_write_through_bit 3
#define cr3_page_level_write_through_flag 0x08
#define cr3_page_level_write_through_mask 0x01
#define cr3_page_level_write_through(_) (((_) >> 3) & 0x01)

		/**
                 * @brief page-level cache disable
                 *
                 * [bit 4] controls the memory type used to access the first paging structure of the current paging-structure hierarchy.
                 * this bit is not used if paging is disabled, with pae paging, or with 4-level paging2 if cr4.pcide=1.
                 *
                 * @see vol3a[4.9(paging and memory typing)]
                 */
		uint64 pagelevelcachedisable : 1;
#define cr3_page_level_cache_disable_bit 4
#define cr3_page_level_cache_disable_flag 0x10
#define cr3_page_level_cache_disable_mask 0x01
#define cr3_page_level_cache_disable(_) (((_) >> 4) & 0x01)
		uint64 reserved2 : 7;

		/**
                 * @brief address of page directory
                 *
                 * [bits 47:12] physical address of the 4-kbyte aligned page directory (32-bit paging) or pml4 table (64-bit paging) used
                 * for linear-address translation.
                 *
                 * @see vol3a[4.3(32-bit paging)]
                 * @see vol3a[4.5(4-level paging)]
                 */
		uint64 addressofpagedirectory : 40;
#define cr3_address_of_page_directory_bit 12
#define cr3_address_of_page_directory_flag 0xfffffffff000
#define cr3_address_of_page_directory_mask 0xfffffffff
#define cr3_address_of_page_directory(_) (((_) >> 12) & 0xfffffffff)
		uint64 reserved3 : 12;
	};

	uint64 flags;
} cr3;

typedef union {
	struct {
		/**
                 * @brief virtual-8086 mode extensions
                 *
                 * [bit 0] enables interrupt- and exception-handling extensions in virtual-8086 mode when set; disables the extensions when
                 * clear. use of the virtual mode extensions can improve the performance of virtual-8086 applications by eliminating the
                 * overhead of calling the virtual- 8086 monitor to handle interrupts and exceptions that occur while executing an 8086
                 * program and, instead, redirecting the interrupts and exceptions back to the 8086 program's handlers. it also provides
                 * hardware support for a virtual interrupt flag (vif) to improve reliability of running 8086 programs in multitasking and
                 * multiple-processor environments.
                 *
                 * @see vol3b[20.3(interrupt and exception handling in virtual-8086 mode)]
                 */
		uint64 virtualmodeextensions : 1;
#define cr4_virtual_mode_extensions_bit 0
#define cr4_virtual_mode_extensions_flag 0x01
#define cr4_virtual_mode_extensions_mask 0x01
#define cr4_virtual_mode_extensions(_) (((_) >> 0) & 0x01)

		/**
                 * @brief protected-mode virtual interrupts
                 *
                 * [bit 1] enables hardware support for a virtual interrupt flag (vif) in protected mode when set; disables the vif flag in
                 * protected mode when clear.
                 *
                 * @see vol3b[20.4(protected-mode virtual interrupts)]
                 */
		uint64 protectedmodevirtualinterrupts : 1;
#define cr4_protected_mode_virtual_interrupts_bit 1
#define cr4_protected_mode_virtual_interrupts_flag 0x02
#define cr4_protected_mode_virtual_interrupts_mask 0x01
#define cr4_protected_mode_virtual_interrupts(_) (((_) >> 1) & 0x01)

		/**
                 * @brief time stamp disable
                 *
                 * [bit 2] restricts the execution of the rdtsc instruction to procedures running at privilege level 0 when set; allows
                 * rdtsc instruction to be executed at any privilege level when clear. this bit also applies to the rdtscp instruction if
                 * supported (if cpuid.80000001h:edx[27] = 1).
                 */
		uint64 timestampdisable : 1;
#define cr4_timestamp_disable_bit 2
#define cr4_timestamp_disable_flag 0x04
#define cr4_timestamp_disable_mask 0x01
#define cr4_timestamp_disable(_) (((_) >> 2) & 0x01)

		/**
                 * @brief debugging extensions
                 *
                 * [bit 3] references to debug registers dr4 and dr5 cause an undefined opcode (\#ud) exception to be generated when set;
                 * when clear, processor aliases references to registers dr4 and dr5 for compatibility with software written to run on
                 * earlier ia-32 processors.
                 *
                 * @see vol3b[17.2.2(debug registers dr4 and dr5)]
                 */
		uint64 debuggingextensions : 1;
#define cr4_debugging_extensions_bit 3
#define cr4_debugging_extensions_flag 0x08
#define cr4_debugging_extensions_mask 0x01
#define cr4_debugging_extensions(_) (((_) >> 3) & 0x01)

		/**
                 * @brief page size extensions
                 *
                 * [bit 4] enables 4-mbyte pages with 32-bit paging when set; restricts 32-bit paging to pages of 4 kbytes when clear.
                 *
                 * @see vol3a[4.3(32-bit paging)]
                 */
		uint64 pagesizeextensions : 1;
#define cr4_page_size_extensions_bit 4
#define cr4_page_size_extensions_flag 0x10
#define cr4_page_size_extensions_mask 0x01
#define cr4_page_size_extensions(_) (((_) >> 4) & 0x01)

		/**
                 * @brief physical address extension
                 *
                 * [bit 5] when set, enables paging to produce physical addresses with more than 32 bits. when clear, restricts physical
                 * addresses to 32 bits. pae must be set before entering ia-32e mode.
                 *
                 * @see vol3a[4(paging)]
                 */
		uint64 physicaladdressextension : 1;
#define cr4_physical_address_extension_bit 5
#define cr4_physical_address_extension_flag 0x20
#define cr4_physical_address_extension_mask 0x01
#define cr4_physical_address_extension(_) (((_) >> 5) & 0x01)

		/**
                 * @brief machine-check enable
                 *
                 * [bit 6] enables the machine-check exception when set; disables the machine-check exception when clear.
                 *
                 * @see vol3b[15(machine-check architecture)]
                 */
		uint64 machinecheckenable : 1;
#define cr4_machine_check_enable_bit 6
#define cr4_machine_check_enable_flag 0x40
#define cr4_machine_check_enable_mask 0x01
#define cr4_machine_check_enable(_) (((_) >> 6) & 0x01)

		/**
                 * @brief page global enable
                 *
                 * [bit 7] (introduced in the p6 family processors.) enables the global page feature when set; disables the global page
                 * feature when clear. the global page feature allows frequently used or shared pages to be marked as global to all users
                 * (done with the global flag, bit 8, in a page-directory or page-table entry). global pages are not flushed from the
                 * translation-lookaside buffer (tlb) on a task switch or a write to register cr3. when enabling the global page feature,
                 * paging must be enabled (by setting the pg flag in control register cr0) before the pge flag is set. reversing this
                 * sequence may affect program correctness, and processor performance will be impacted.
                 *
                 * @see vol3a[4.10(caching translation information)]
                 */
		uint64 pageglobalenable : 1;
#define cr4_page_global_enable_bit 7
#define cr4_page_global_enable_flag 0x80
#define cr4_page_global_enable_mask 0x01
#define cr4_page_global_enable(_) (((_) >> 7) & 0x01)

		/**
                 * @brief performance-monitoring counter enable
                 *
                 * [bit 8] enables execution of the rdpmc instruction for programs or procedures running at any protection level when set;
                 * rdpmc instruction can be executed only at protection level 0 when clear.
                 */
		uint64 performancemonitoringcounterenable : 1;
#define cr4_performance_monitoring_counter_enable_bit 8
#define cr4_performance_monitoring_counter_enable_flag 0x100
#define cr4_performance_monitoring_counter_enable_mask 0x01
#define cr4_performance_monitoring_counter_enable(_) (((_) >> 8) & 0x01)

		/**
                 * @brief operating system support for fxsave and fxrstor instructions
                 *
                 * [bit 9] when set, this flag:
                 * -# indicates to software that the operating system supports the use of the fxsave and fxrstor instructions,
                 * -# enables the fxsave and fxrstor instructions to save and restore the contents of the xmm and mxcsr registers along
                 * with the contents of the x87 fpu and mmx registers, and
                 * -# enables the processor to execute sse/sse2/sse3/ssse3/sse4 instructions, with the exception of the pause, prefetchh,
                 * sfence, lfence, mfence, movnti, clflush, crc32, and popcnt.
                 * if this flag is clear, the fxsave and fxrstor instructions will save and restore the contents of the x87 fpu and mmx
                 * registers, but they may not save and restore the contents of the xmm and mxcsr registers. also, the processor will
                 * generate an invalid opcode exception (\#ud) if it attempts to execute any sse/sse2/sse3 instruction, with the exception
                 * of pause, prefetchh, sfence, lfence, mfence, movnti, clflush, crc32, and popcnt. the operating system or executive must
                 * explicitly set this flag.
                 *
                 * @remarks cpuid feature flag fxsr indicates availability of the fxsave/fxrstor instructions. the osfxsr bit provides
                 *          operating system software with a means of enabling fxsave/fxrstor to save/restore the contents of the x87 fpu, xmm and
                 *          mxcsr registers. consequently osfxsr bit indicates that the operating system provides context switch support for
                 *          sse/sse2/sse3/ssse3/sse4.
                 */
		uint64 osfxsavefxrstorsupport : 1;
#define cr4_os_fxsave_fxrstor_support_bit 9
#define cr4_os_fxsave_fxrstor_support_flag 0x200
#define cr4_os_fxsave_fxrstor_support_mask 0x01
#define cr4_os_fxsave_fxrstor_support(_) (((_) >> 9) & 0x01)

		/**
                 * @brief operating system support for unmasked simd floating-point exceptions
                 *
                 * [bit 10] operating system support for unmasked simd floating-point exceptions - when set, indicates that the operating
                 * system supports the handling of unmasked simd floating-point exceptions through an exception handler that is invoked
                 * when a simd floating-point exception (\#xm) is generated. simd floating-point exceptions are only generated by
                 * sse/sse2/sse3/sse4.1 simd floatingpoint instructions.
                 * the operating system or executive must explicitly set this flag. if this flag is not set, the processor will generate an
                 * invalid opcode exception (\#ud) whenever it detects an unmasked simd floating-point exception.
                 */
		uint64 osxmmexceptionsupport : 1;
#define cr4_os_xmm_exception_support_bit 10
#define cr4_os_xmm_exception_support_flag 0x400
#define cr4_os_xmm_exception_support_mask 0x01
#define cr4_os_xmm_exception_support(_) (((_) >> 10) & 0x01)

		/**
                 * @brief user-mode instruction prevention
                 *
                 * [bit 11] when set, the following instructions cannot be executed if cpl > 0: sgdt, sidt, sldt, smsw, and str. an attempt
                 * at such execution causes a generalprotection exception (\#gp).
                 */
		uint64 usermodeinstructionprevention : 1;
#define cr4_usermode_instruction_prevention_bit 11
#define cr4_usermode_instruction_prevention_flag 0x800
#define cr4_usermode_instruction_prevention_mask 0x01
#define cr4_usermode_instruction_prevention(_) (((_) >> 11) & 0x01)
		uint64 reserved1 : 1;

		/**
                 * @brief vmx-enable
                 *
                 * [bit 13] enables vmx operation when set.
                 *
                 * @see vol3c[23(introduction to virtual machine extensions)]
                 */
		uint64 vmxenable : 1;
#define cr4_vmx_enable_bit 13
#define cr4_vmx_enable_flag 0x2000
#define cr4_vmx_enable_mask 0x01
#define cr4_vmx_enable(_) (((_) >> 13) & 0x01)

		/**
                 * @brief smx-enable
                 *
                 * [bit 14] enables smx operation when set.
                 *
                 * @see vol2[6(safer mode extensions reference)]
                 */
		uint64 smxenable : 1;
#define cr4_smx_enable_bit 14
#define cr4_smx_enable_flag 0x4000
#define cr4_smx_enable_mask 0x01
#define cr4_smx_enable(_) (((_) >> 14) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * @brief fsgsbase-enable
                 *
                 * [bit 16] enables the instructions rdfsbase, rdgsbase, wrfsbase, and wrgsbase.
                 */
		uint64 fsgsbaseenable : 1;
#define cr4_fsgsbase_enable_bit 16
#define cr4_fsgsbase_enable_flag 0x10000
#define cr4_fsgsbase_enable_mask 0x01
#define cr4_fsgsbase_enable(_) (((_) >> 16) & 0x01)

		/**
                 * @brief pcid-enable
                 *
                 * [bit 17] enables process-context identifiers (pcids) when set. can be set only in ia-32e mode (if ia32_efer.lma = 1).
                 *
                 * @see vol3a[4.10.1(process-context identifiers (pcids))]
                 */
		uint64 pcidenable : 1;
#define cr4_pcid_enable_bit 17
#define cr4_pcid_enable_flag 0x20000
#define cr4_pcid_enable_mask 0x01
#define cr4_pcid_enable(_) (((_) >> 17) & 0x01)

		/**
                 * @brief xsave and processor extended states-enable
                 *
                 * [bit 18] when set, this flag:
                 * -# indicates (via cpuid.01h:ecx.osxsave[bit 27]) that the operating system supports the use of the xgetbv, xsave and
                 * xrstor instructions by general software;
                 * -# enables the xsave and xrstor instructions to save and restore the x87 fpu state (including mmx registers), the sse
                 * state (xmm registers and mxcsr), along with other processor extended states enabled in xcr0;
                 * -# enables the processor to execute xgetbv and xsetbv instructions in order to read and write xcr0.
                 *
                 * @see vol3a[2.6(extended control registers (including xcr0))]
                 * @see vol3a[13(system programming for instruction set extensions and processor extended)]
                 */
		uint64 osxsave : 1;
#define cr4_os_xsave_bit 18
#define cr4_os_xsave_flag 0x40000
#define cr4_os_xsave_mask 0x01
#define cr4_os_xsave(_) (((_) >> 18) & 0x01)
		uint64 reserved3 : 1;

		/**
                 * @brief smep-enable
                 *
                 * [bit 20] enables supervisor-mode execution prevention (smep) when set.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 smepenable : 1;
#define cr4_smep_enable_bit 20
#define cr4_smep_enable_flag 0x100000
#define cr4_smep_enable_mask 0x01
#define cr4_smep_enable(_) (((_) >> 20) & 0x01)

		/**
                 * @brief smap-enable
                 *
                 * [bit 21] enables supervisor-mode access prevention (smap) when set.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 smapenable : 1;
#define cr4_smap_enable_bit 21
#define cr4_smap_enable_flag 0x200000
#define cr4_smap_enable_mask 0x01
#define cr4_smap_enable(_) (((_) >> 21) & 0x01)

		/**
                 * @brief protection-key-enable
                 *
                 * [bit 22] enables 4-level paging to associate each linear address with a protection key. the pkru register specifies, for
                 * each protection key, whether user-mode linear addresses with that protection key can be read or written. this bit also
                 * enables access to the pkru register using the rdpkru and wrpkru instructions.
                 */
		uint64 protectionkeyenable : 1;
#define cr4_protection_key_enable_bit 22
#define cr4_protection_key_enable_flag 0x400000
#define cr4_protection_key_enable_mask 0x01
#define cr4_protection_key_enable(_) (((_) >> 22) & 0x01)

		uint64 cetenabled : 1;

		uint64 pksenabled : 1;

		uint64 reserved4 : 39;
	};

	uint64 flags;
} cr4;

typedef union {
	struct {
		/**
                 * @brief task priority level
                 *
                 * [bits 3:0] this sets the threshold value corresponding to the highestpriority interrupt to be blocked. a value of 0
                 * means all interrupts are enabled. this field is available in 64- bit mode. a value of 15 means all interrupts will be
                 * disabled.
                 */
		uint64 taskprioritylevel : 4;
#define cr8_task_priority_level_bit 0
#define cr8_task_priority_level_flag 0x0f
#define cr8_task_priority_level_mask 0x0f
#define cr8_task_priority_level(_) (((_) >> 0) & 0x0f)

		/**
                 * @brief reserved
                 *
                 * [bits 63:4] reserved and must be written with zeros. failure to do this causes a general-protection exception.
                 */
		uint64 reserved : 60;
#define cr8_reserved_bit 4
#define cr8_reserved_flag 0xfffffffffffffff0
#define cr8_reserved_mask 0xfffffffffffffff
#define cr8_reserved(_) (((_) >> 4) & 0xfffffffffffffff)
	};

	uint64 flags;
} cr8;

/**
 * @}
 */

/**
 * @defgroup debug_registers \
 *           debug registers
 *
 * eight debug registers control the debug operation of the processor. these registers can be written to and read using the
 * move to/from debug register form of the mov instruction. a debug register may be the source or destination operand for
 * one of these instructions.
 * debug registers are privileged resources; a mov instruction that accesses these registers can only be executed in
 * real-address mode, in smm or in protected mode at a cpl of 0. an attempt to read or write the debug registers from any
 * other privilege level generates a general-protection exception (\#gp). the primary function of the debug registers is to
 * set up and monitor from 1 to 4 breakpoints, numbered 0 though 3. for each breakpoint, the following information can be
 * specified:
 * - the linear address where the breakpoint is to occur.
 * - the length of the breakpoint location: 1, 2, 4, or 8 bytes.
 * - the operation that must be performed at the address for a debug exception to be generated.
 * - whether the breakpoint is enabled.
 * - whether the breakpoint condition was present when the debug exception was generated.
 *
 * @see vol3b[17.2.4(debug control register (dr7))]
 * @see vol3b[17.2(debug registers)] (reference)
 * @{
 */
typedef union {
	struct {
		/**
                 * @brief b0 through b3 (breakpoint condition detected) flags
                 *
                 * [bits 3:0] indicates (when set) that its associated breakpoint condition was met when a debug exception was generated.
                 * these flags are set if the condition described for each breakpoint by the lenn, and r/wn flags in debug control register
                 * dr7 is true. they may or may not be set if the breakpoint is not enabled by the ln or the gn flags in register dr7.
                 * therefore on a \#db, a debug handler should check only those b0-b3 bits which correspond to an enabled breakpoint.
                 */
		uint64 breakpointcondition : 4;
#define dr6_breakpoint_condition_bit 0
#define dr6_breakpoint_condition_flag 0x0f
#define dr6_breakpoint_condition_mask 0x0f
#define dr6_breakpoint_condition(_) (((_) >> 0) & 0x0f)
		uint64 reserved1 : 9;

		/**
                 * @brief bd (debug register access detected) flag
                 *
                 * [bit 13] indicates that the next instruction in the instruction stream accesses one of the debug registers (dr0 through
                 * dr7). this flag is enabled when the gd (general detect) flag in debug control register dr7 is set.
                 *
                 * @see vol3b[17.2.4(debug control register (dr7))]
                 */
		uint64 debugregisteraccessdetected : 1;
#define dr6_debug_register_access_detected_bit 13
#define dr6_debug_register_access_detected_flag 0x2000
#define dr6_debug_register_access_detected_mask 0x01
#define dr6_debug_register_access_detected(_) (((_) >> 13) & 0x01)

		/**
                 * @brief bs (single step) flag
                 *
                 * [bit 14] indicates (when set) that the debug exception was triggered by the singlestep execution mode (enabled with the
                 * tf flag in the eflags register). the single-step mode is the highestpriority debug exception. when the bs flag is set,
                 * any of the other debug status bits also may be set.
                 */
		uint64 singleinstruction : 1;
#define dr6_single_instruction_bit 14
#define dr6_single_instruction_flag 0x4000
#define dr6_single_instruction_mask 0x01
#define dr6_single_instruction(_) (((_) >> 14) & 0x01)

		/**
                 * @brief bt (task switch) flag
                 *
                 * [bit 15] indicates (when set) that the debug exception was triggered by the singlestep execution mode (enabled with the
                 * tf flag in the eflags register). the single-step mode is the highestpriority debug exception. when the bs flag is set,
                 * any of the other debug status bits also may be set.
                 */
		uint64 taskswitch : 1;
#define dr6_task_switch_bit 15
#define dr6_task_switch_flag 0x8000
#define dr6_task_switch_mask 0x01
#define dr6_task_switch(_) (((_) >> 15) & 0x01)

		/**
                 * @brief
                 (restricted transactional memory) flag
                 *
                 * [bit 16] indicates (when clear) that a debug exception (\#db) or breakpoint exception (\#bp) occurred inside an rtm
                 * region while advanced debugging of rtm transactional regions was enabled. this bit is set for any other debug exception
                 * (including all those that occur when advanced debugging of rtm transactional regions is not enabled). this bit is always
                 * 1 if the processor does not support rtm.
                 *
                 * @see vol3b[17.3.3(debug exceptions, breakpoint exceptions, and restricted transactional memory (rtm))]
                 */
		uint64 restrictedtransactionalmemory : 1;
#define dr6_restricted_transactional_memory_bit 16
#define dr6_restricted_transactional_memory_flag 0x10000
#define dr6_restricted_transactional_memory_mask 0x01
#define dr6_restricted_transactional_memory(_) (((_) >> 16) & 0x01)
		uint64 reserved2 : 47;
	};

	uint64 flags;
} dr6;

typedef union {
	struct {
		/**
                 * @brief l0 through l3 (local breakpoint enable) flags (bits 0, 2, 4, and 6)
                 *
                 * [bit 0] enables (when set) the breakpoint condition for the associated breakpoint for the current task. when a
                 * breakpoint condition is detected and its associated ln flag is set, a debug exception is generated. the processor
                 * automatically clears these flags on every task switch to avoid unwanted breakpoint conditions in the new task.
                 */
		uint64 localbreakpoint0 : 1;
#define dr7_local_breakpoint_0_bit 0
#define dr7_local_breakpoint_0_flag 0x01
#define dr7_local_breakpoint_0_mask 0x01
#define dr7_local_breakpoint_0(_) (((_) >> 0) & 0x01)

		/**
                 * @brief g0 through g3 (global breakpoint enable) flags (bits 1, 3, 5, and 7)
                 *
                 * [bit 1] enables (when set) the breakpoint condition for the associated breakpoint for all tasks. when a breakpoint
                 * condition is detected and its associated gn flag is set, a debug exception is generated. the processor does not clear
                 * these flags on a task switch, allowing a breakpoint to be enabled for all tasks.
                 */
		uint64 globalbreakpoint0 : 1;
#define dr7_global_breakpoint_0_bit 1
#define dr7_global_breakpoint_0_flag 0x02
#define dr7_global_breakpoint_0_mask 0x01
#define dr7_global_breakpoint_0(_) (((_) >> 1) & 0x01)
		uint64 localbreakpoint1 : 1;
#define dr7_local_breakpoint_1_bit 2
#define dr7_local_breakpoint_1_flag 0x04
#define dr7_local_breakpoint_1_mask 0x01
#define dr7_local_breakpoint_1(_) (((_) >> 2) & 0x01)
		uint64 globalbreakpoint1 : 1;
#define dr7_global_breakpoint_1_bit 3
#define dr7_global_breakpoint_1_flag 0x08
#define dr7_global_breakpoint_1_mask 0x01
#define dr7_global_breakpoint_1(_) (((_) >> 3) & 0x01)
		uint64 localbreakpoint2 : 1;
#define dr7_local_breakpoint_2_bit 4
#define dr7_local_breakpoint_2_flag 0x10
#define dr7_local_breakpoint_2_mask 0x01
#define dr7_local_breakpoint_2(_) (((_) >> 4) & 0x01)
		uint64 globalbreakpoint2 : 1;
#define dr7_global_breakpoint_2_bit 5
#define dr7_global_breakpoint_2_flag 0x20
#define dr7_global_breakpoint_2_mask 0x01
#define dr7_global_breakpoint_2(_) (((_) >> 5) & 0x01)
		uint64 localbreakpoint3 : 1;
#define dr7_local_breakpoint_3_bit 6
#define dr7_local_breakpoint_3_flag 0x40
#define dr7_local_breakpoint_3_mask 0x01
#define dr7_local_breakpoint_3(_) (((_) >> 6) & 0x01)
		uint64 globalbreakpoint3 : 1;
#define dr7_global_breakpoint_3_bit 7
#define dr7_global_breakpoint_3_flag 0x80
#define dr7_global_breakpoint_3_mask 0x01
#define dr7_global_breakpoint_3(_) (((_) >> 7) & 0x01)

		/**
                 * @brief le (local exact breakpoint enable)
                 *
                 * [bit 8] this feature is not supported in the p6 family processors, later ia-32 processors, and intel 64 processors. when
                 * set, these flags cause the processor to detect the exact instruction that caused a data breakpoint condition. for
                 * backward and forward compatibility with other intel processors, we recommend that the le and ge flags be set to 1 if
                 * exact breakpoints are required.
                 */
		uint64 localexactbreakpoint : 1;
#define dr7_local_exact_breakpoint_bit 8
#define dr7_local_exact_breakpoint_flag 0x100
#define dr7_local_exact_breakpoint_mask 0x01
#define dr7_local_exact_breakpoint(_) (((_) >> 8) & 0x01)
		uint64 globalexactbreakpoint : 1;
#define dr7_global_exact_breakpoint_bit 9
#define dr7_global_exact_breakpoint_flag 0x200
#define dr7_global_exact_breakpoint_mask 0x01
#define dr7_global_exact_breakpoint(_) (((_) >> 9) & 0x01)
		uint64 reserved1 : 1;

		/**
                 * @brief rtm (restricted transactional memory) flag
                 *
                 * [bit 11] enables (when set) advanced debugging of rtm transactional regions. this advanced debugging is enabled only if
                 * ia32_debugctl.rtm is also set.
                 *
                 * @see vol3b[17.3.3(debug exceptions, breakpoint exceptions, and restricted transactional memory (rtm))]
                 */
		uint64 restrictedtransactionalmemory : 1;
#define dr7_restricted_transactional_memory_bit 11
#define dr7_restricted_transactional_memory_flag 0x800
#define dr7_restricted_transactional_memory_mask 0x01
#define dr7_restricted_transactional_memory(_) (((_) >> 11) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * @brief gd (general detect enable) flag
                 *
                 * [bit 13] enables (when set) debug-register protection, which causes a debug exception to be generated prior to any mov
                 * instruction that accesses a debug register. when such a condition is detected, the bd flag in debug status register dr6
                 * is set prior to generating the exception. this condition is provided to support in-circuit emulators.
                 * when the emulator needs to access the debug registers, emulator software can set the gd flag to prevent interference
                 * from the program currently executing on the processor.
                 * the processor clears the gd flag upon entering to the debug exception handler, to allow the handler access to the debug
                 * registers.
                 */
		uint64 generaldetect : 1;
#define dr7_general_detect_bit 13
#define dr7_general_detect_flag 0x2000
#define dr7_general_detect_mask 0x01
#define dr7_general_detect(_) (((_) >> 13) & 0x01)
		uint64 reserved3 : 2;

		/**
                 * @brief r/w0 through r/w3 (read/write) fields (bits 16, 17, 20, 21, 24, 25, 28, and 29)
                 *
                 * [bits 17:16] specifies the breakpoint condition for the corresponding breakpoint. the de (debug extensions) flag in
                 * control register cr4 determines how the bits in the r/wn fields are interpreted. when the de flag is set, the processor
                 * interprets bits as follows:
                 * - 00 - break on instruction execution only.
                 * - 01 - break on data writes only.
                 * - 10 - break on i/o reads or writes.
                 * - 11 - break on data reads or writes but not instruction fetches.
                 * when the de flag is clear, the processor interprets the r/wn bits the same as for the intel386(tm) and intel486(tm)
                 * processors, which is as follows:
                 * - 00 - break on instruction execution only.
                 * - 01 - break on data writes only.
                 * - 10 - undefined.
                 * - 11 - break on data reads or writes but not instruction fetches.
                 */
		uint64 readwrite0 : 2;
#define dr7_read_write_0_bit 16
#define dr7_read_write_0_flag 0x30000
#define dr7_read_write_0_mask 0x03
#define dr7_read_write_0(_) (((_) >> 16) & 0x03)

		/**
                 * @brief len0 through len3 (length) fields (bits 18, 19, 22, 23, 26, 27, 30, and 31)
                 *
                 * [bits 19:18] specify the size of the memory location at the address specified in the corresponding breakpoint address
                 * register (dr0 through dr3). these fields are interpreted as follows:
                 * - 00 - 1-byte length.
                 * - 01 - 2-byte length.
                 * - 10 - undefined (or 8 byte length, see note below).
                 * - 11 - 4-byte length.
                 * if the corresponding rwn field in register dr7 is 00 (instruction execution), then the lenn field should also be 00. the
                 * effect of using other lengths is undefined.
                 *
                 * @see vol3b[17.2.5(breakpoint field recognition)]
                 */
		uint64 length0 : 2;
#define dr7_length_0_bit 18
#define dr7_length_0_flag 0xc0000
#define dr7_length_0_mask 0x03
#define dr7_length_0(_) (((_) >> 18) & 0x03)
		uint64 readwrite1 : 2;
#define dr7_read_write_1_bit 20
#define dr7_read_write_1_flag 0x300000
#define dr7_read_write_1_mask 0x03
#define dr7_read_write_1(_) (((_) >> 20) & 0x03)
		uint64 length1 : 2;
#define dr7_length_1_bit 22
#define dr7_length_1_flag 0xc00000
#define dr7_length_1_mask 0x03
#define dr7_length_1(_) (((_) >> 22) & 0x03)
		uint64 readwrite2 : 2;
#define dr7_read_write_2_bit 24
#define dr7_read_write_2_flag 0x3000000
#define dr7_read_write_2_mask 0x03
#define dr7_read_write_2(_) (((_) >> 24) & 0x03)
		uint64 length2 : 2;
#define dr7_length_2_bit 26
#define dr7_length_2_flag 0xc000000
#define dr7_length_2_mask 0x03
#define dr7_length_2(_) (((_) >> 26) & 0x03)
		uint64 readwrite3 : 2;
#define dr7_read_write_3_bit 28
#define dr7_read_write_3_flag 0x30000000
#define dr7_read_write_3_mask 0x03
#define dr7_read_write_3(_) (((_) >> 28) & 0x03)
		uint64 length3 : 2;
#define dr7_length_3_bit 30
#define dr7_length_3_flag 0xc0000000
#define dr7_length_3_mask 0x03
#define dr7_length_3(_) (((_) >> 30) & 0x03)
		uint64 reserved4 : 32;
	};

	uint64 flags;
} dr7;

/**
 * @}
 */

/**
 * @defgroup cpuid \
 *           cpuid
 *
 * @see vol2a[3.2(cpuid)] (reference)
 * @{
 */
/**
 * @brief returns cpuid's highest value for basic processor information and the vendor identification string
 *
 * when cpuid executes with eax set to 0, the processor returns the highest value the cpuid recognizes for returning basic
 * processor information. the value is returned in the eax register and is processor specific.
 * a vendor identification string is also returned in ebx, edx, and ecx. for intel processors, the string is "genuineintel"
 * and is expressed:
 * - ebx <- 756e6547h (* "genu", with g in the low eight bits of bl *)
 * - edx <- 49656e69h (* "inei", with i in the low eight bits of dl *)
 * - ecx <- 6c65746eh (* "ntel", with n in the low eight bits of cl *)
 */
#define cpuid_signature 0x00000000
typedef struct {
	/**
         * @brief eax
         *
         * maximum input value for basic cpuid information.
         */
	uint32 maxcpuidinputvalue;

	/**
         * @brief ebx
         *
         * "genu"
         */
	uint32 ebxvaluegenu;

	/**
         * @brief ecx
         *
         * "ntel"
         */
	uint32 ecxvaluentel;

	/**
         * @brief edx
         *
         * "inei"
         */
	uint32 edxvalueinei;
} cpuid_eax_00;

/**
 * @brief returns model, family, stepping information, additional information and feature information
 *
 * returns:
 *   * model, family, stepping information in eax
 *   * additional information in ebx
 *   * feature information in ecx and edx
 */
#define cpuid_version_information 0x00000001
typedef struct {
	/**
         * @brief when cpuid executes with eax set to 01h, version information is returned in eax
         */
	union {
		struct {
			uint32 steppingid : 4;
#define cpuid_version_information_stepping_id_bit 0
#define cpuid_version_information_stepping_id_flag 0x0f
#define cpuid_version_information_stepping_id_mask 0x0f
#define cpuid_version_information_stepping_id(_) (((_) >> 0) & 0x0f)
			uint32 model : 4;
#define cpuid_version_information_model_bit 4
#define cpuid_version_information_model_flag 0xf0
#define cpuid_version_information_model_mask 0x0f
#define cpuid_version_information_model(_) (((_) >> 4) & 0x0f)
			uint32 familyid : 4;
#define cpuid_version_information_family_id_bit 8
#define cpuid_version_information_family_id_flag 0xf00
#define cpuid_version_information_family_id_mask 0x0f
#define cpuid_version_information_family_id(_) (((_) >> 8) & 0x0f)

			/**
                         * [bits 13:12] - 0 - original oem processor
                         * - 1 - intel overdrive(r) processor
                         * - 2 - dual processor (not applicable to intel486 processors)
                         * - 3 - intel reserved
                         */
			uint32 processortype : 2;
#define cpuid_version_information_processor_type_bit 12
#define cpuid_version_information_processor_type_flag 0x3000
#define cpuid_version_information_processor_type_mask 0x03
#define cpuid_version_information_processor_type(_) (((_) >> 12) & 0x03)
			uint32 reserved1 : 2;

			/**
                         * [bits 19:16] the extended model id needs to be examined only when the family id is 06h or 0fh.
                         */
			uint32 extendedmodelid : 4;
#define cpuid_version_information_extended_model_id_bit 16
#define cpuid_version_information_extended_model_id_flag 0xf0000
#define cpuid_version_information_extended_model_id_mask 0x0f
#define cpuid_version_information_extended_model_id(_) (((_) >> 16) & 0x0f)

			/**
                         * [bits 27:20] the extended family id needs to be examined only when the family id is 0fh.
                         */
			uint32 extendedfamilyid : 8;
#define cpuid_version_information_extended_family_id_bit 20
#define cpuid_version_information_extended_family_id_flag 0xff00000
#define cpuid_version_information_extended_family_id_mask 0xff
#define cpuid_version_information_extended_family_id(_) (((_) >> 20) & 0xff)
			uint32 reserved2 : 4;
		};

		uint32 flags;
	} cpuidversioninformation;

	/**
         * @brief when cpuid executes with eax set to 01h, additional information is returned to the ebx register
         */
	union {
		struct {
			/**
                         * [bits 7:0] this number provides an entry into a brand string table that contains brand strings for ia-32 processors.
                         * more information about this field is provided later in this section.
                         */
			uint32 brandindex : 8;
#define cpuid_additional_information_brand_index_bit 0
#define cpuid_additional_information_brand_index_flag 0xff
#define cpuid_additional_information_brand_index_mask 0xff
#define cpuid_additional_information_brand_index(_) (((_) >> 0) & 0xff)

			/**
                         * @brief value * 8 = cache line size in bytes; used also by clflushopt
                         *
                         * [bits 15:8] this number indicates the size of the cache line flushed by the clflush and clflushopt instructions in
                         * 8-byte increments. this field was introduced in the pentium 4 processor.
                         */
			uint32 clflushlinesize : 8;
#define cpuid_additional_information_clflush_line_size_bit 8
#define cpuid_additional_information_clflush_line_size_flag 0xff00
#define cpuid_additional_information_clflush_line_size_mask 0xff
#define cpuid_additional_information_clflush_line_size(_) (((_) >> 8) & 0xff)

			/**
                         * [bits 23:16] maximum number of addressable ids for logical processors in this physical package.
                         *
                         * @remarks the nearest power-of-2 integer that is not smaller than ebx[23:16] is the number of unique initial apic ids
                         *          reserved for addressing different logical processors in a physical package. this field is only valid if
                         *          cpuid.1.edx.htt[bit 28] = 1.
                         */
			uint32 maxaddressableids : 8;
#define cpuid_additional_information_max_addressable_ids_bit 16
#define cpuid_additional_information_max_addressable_ids_flag 0xff0000
#define cpuid_additional_information_max_addressable_ids_mask 0xff
#define cpuid_additional_information_max_addressable_ids(_) (((_) >> 16) & 0xff)

			/**
                         * [bits 31:24] this number is the 8-bit id that is assigned to the local apic on the processor during power up. this field
                         * was introduced in the pentium 4 processor.
                         */
			uint32 initialapicid : 8;
#define cpuid_additional_information_initial_apic_id_bit 24
#define cpuid_additional_information_initial_apic_id_flag 0xff000000
#define cpuid_additional_information_initial_apic_id_mask 0xff
#define cpuid_additional_information_initial_apic_id(_) (((_) >> 24) & 0xff)
		};

		uint32 flags;
	} cpuidadditionalinformation;

	/**
         * @brief when cpuid executes with eax set to 01h, feature information is returned in ecx and edx
         */
	union {
		struct {
			/**
                         * @brief streaming simd extensions 3 (sse3)
                         *
                         * [bit 0] a value of 1 indicates the processor supports this technology.
                         */
			uint32 streamingsimdextensions3 : 1;
#define cpuid_feature_information_ecx_streaming_simd_extensions_3_bit 0
#define cpuid_feature_information_ecx_streaming_simd_extensions_3_flag 0x01
#define cpuid_feature_information_ecx_streaming_simd_extensions_3_mask 0x01
#define cpuid_feature_information_ecx_streaming_simd_extensions_3(_) \
	(((_) >> 0) & 0x01)

			/**
                         * @brief pclmulqdq instruction
                         *
                         * [bit 1] a value of 1 indicates the processor supports the pclmulqdq instruction.
                         */
			uint32 pclmulqdqinstruction : 1;
#define cpuid_feature_information_ecx_pclmulqdq_instruction_bit 1
#define cpuid_feature_information_ecx_pclmulqdq_instruction_flag 0x02
#define cpuid_feature_information_ecx_pclmulqdq_instruction_mask 0x01
#define cpuid_feature_information_ecx_pclmulqdq_instruction(_) \
	(((_) >> 1) & 0x01)

			/**
                         * @brief 64-bit ds area
                         *
                         * [bit 2] a value of 1 indicates the processor supports ds area using 64-bit layout.
                         */
			uint32 dsarea64bitlayout : 1;
#define cpuid_feature_information_ecx_ds_area_64bit_layout_bit 2
#define cpuid_feature_information_ecx_ds_area_64bit_layout_flag 0x04
#define cpuid_feature_information_ecx_ds_area_64bit_layout_mask 0x01
#define cpuid_feature_information_ecx_ds_area_64bit_layout(_) \
	(((_) >> 2) & 0x01)

			/**
                         * @brief monitor/mwait instruction
                         *
                         * [bit 3] a value of 1 indicates the processor supports this feature.
                         */
			uint32 monitormwaitinstruction : 1;
#define cpuid_feature_information_ecx_monitor_mwait_instruction_bit 3
#define cpuid_feature_information_ecx_monitor_mwait_instruction_flag 0x08
#define cpuid_feature_information_ecx_monitor_mwait_instruction_mask 0x01
#define cpuid_feature_information_ecx_monitor_mwait_instruction(_) \
	(((_) >> 3) & 0x01)

			/**
                         * @brief cpl qualified debug store
                         *
                         * [bit 4] a value of 1 indicates the processor supports the extensions to the debug store feature to allow for branch
                         * message storage qualified by cpl.
                         */
			uint32 cplqualifieddebugstore : 1;
#define cpuid_feature_information_ecx_cpl_qualified_debug_store_bit 4
#define cpuid_feature_information_ecx_cpl_qualified_debug_store_flag 0x10
#define cpuid_feature_information_ecx_cpl_qualified_debug_store_mask 0x01
#define cpuid_feature_information_ecx_cpl_qualified_debug_store(_) \
	(((_) >> 4) & 0x01)

			/**
                         * @brief virtual machine extensions
                         *
                         * [bit 5] a value of 1 indicates that the processor supports this technology.
                         */
			uint32 virtualmachineextensions : 1;
#define cpuid_feature_information_ecx_virtual_machine_extensions_bit 5
#define cpuid_feature_information_ecx_virtual_machine_extensions_flag 0x20
#define cpuid_feature_information_ecx_virtual_machine_extensions_mask 0x01
#define cpuid_feature_information_ecx_virtual_machine_extensions(_) \
	(((_) >> 5) & 0x01)

			/**
                         * @brief safer mode extensions
                         *
                         * [bit 6] a value of 1 indicates that the processor supports this technology.
                         *
                         * @see vol2[6(safer mode extensions reference)]
                         */
			uint32 safermodeextensions : 1;
#define cpuid_feature_information_ecx_safer_mode_extensions_bit 6
#define cpuid_feature_information_ecx_safer_mode_extensions_flag 0x40
#define cpuid_feature_information_ecx_safer_mode_extensions_mask 0x01
#define cpuid_feature_information_ecx_safer_mode_extensions(_) \
	(((_) >> 6) & 0x01)

			/**
                         * @brief enhanced intel speedstep(r) technology
                         *
                         * [bit 7] a value of 1 indicates that the processor supports this technology.
                         */
			uint32 enhancedintelspeedsteptechnology : 1;
#define cpuid_feature_information_ecx_enhanced_intel_speedstep_technology_bit 7
#define cpuid_feature_information_ecx_enhanced_intel_speedstep_technology_flag \
	0x80
#define cpuid_feature_information_ecx_enhanced_intel_speedstep_technology_mask \
	0x01
#define cpuid_feature_information_ecx_enhanced_intel_speedstep_technology(_) \
	(((_) >> 7) & 0x01)

			/**
                         * @brief thermal monitor 2
                         *
                         * [bit 8] a value of 1 indicates whether the processor supports this technology.
                         */
			uint32 thermalmonitor2 : 1;
#define cpuid_feature_information_ecx_thermal_monitor_2_bit 8
#define cpuid_feature_information_ecx_thermal_monitor_2_flag 0x100
#define cpuid_feature_information_ecx_thermal_monitor_2_mask 0x01
#define cpuid_feature_information_ecx_thermal_monitor_2(_) (((_) >> 8) & 0x01)

			/**
                         * @brief supplemental streaming simd extensions 3 (ssse3)
                         *
                         * [bit 9] a value of 1 indicates the presence of the supplemental streaming simd extensions 3 (ssse3). a value of 0
                         * indicates the instruction extensions are not present in the processor.
                         */
			uint32 supplementalstreamingsimdextensions3 : 1;
#define cpuid_feature_information_ecx_supplemental_streaming_simd_extensions_3_bit \
	9
#define cpuid_feature_information_ecx_supplemental_streaming_simd_extensions_3_flag \
	0x200
#define cpuid_feature_information_ecx_supplemental_streaming_simd_extensions_3_mask \
	0x01
#define cpuid_feature_information_ecx_supplemental_streaming_simd_extensions_3( \
	_)                                                                      \
	(((_) >> 9) & 0x01)

			/**
                         * @brief l1 context id
                         *
                         * [bit 10] a value of 1 indicates the l1 data cache mode can be set to either adaptive mode or shared mode. a value of 0
                         * indicates this feature is not supported. see definition of the ia32_misc_enable msr bit 24 (l1 data cache context mode)
                         * for details.
                         */
			uint32 l1contextid : 1;
#define cpuid_feature_information_ecx_l1_context_id_bit 10
#define cpuid_feature_information_ecx_l1_context_id_flag 0x400
#define cpuid_feature_information_ecx_l1_context_id_mask 0x01
#define cpuid_feature_information_ecx_l1_context_id(_) (((_) >> 10) & 0x01)

			/**
                         * @brief ia32_debug_interface msr for silicon debug
                         *
                         * [bit 11] a value of 1 indicates the processor supports ia32_debug_interface msr for silicon debug.
                         */
			uint32 silicondebug : 1;
#define cpuid_feature_information_ecx_silicon_debug_bit 11
#define cpuid_feature_information_ecx_silicon_debug_flag 0x800
#define cpuid_feature_information_ecx_silicon_debug_mask 0x01
#define cpuid_feature_information_ecx_silicon_debug(_) (((_) >> 11) & 0x01)

			/**
                         * @brief fma extensions using ymm state
                         *
                         * [bit 12] a value of 1 indicates the processor supports fma (fused multiple add) extensions using ymm state.
                         */
			uint32 fmaextensions : 1;
#define cpuid_feature_information_ecx_fma_extensions_bit 12
#define cpuid_feature_information_ecx_fma_extensions_flag 0x1000
#define cpuid_feature_information_ecx_fma_extensions_mask 0x01
#define cpuid_feature_information_ecx_fma_extensions(_) (((_) >> 12) & 0x01)

			/**
                         * @brief cmpxchg16b instruction
                         *
                         * [bit 13] a value of 1 indicates that the feature is available.
                         */
			uint32 cmpxchg16binstruction : 1;
#define cpuid_feature_information_ecx_cmpxchg16b_instruction_bit 13
#define cpuid_feature_information_ecx_cmpxchg16b_instruction_flag 0x2000
#define cpuid_feature_information_ecx_cmpxchg16b_instruction_mask 0x01
#define cpuid_feature_information_ecx_cmpxchg16b_instruction(_) \
	(((_) >> 13) & 0x01)

			/**
                         * @brief xtpr update control
                         *
                         * [bit 14] a value of 1 indicates that the processor supports changing ia32_misc_enable[bit 23].
                         */
			uint32 xtprupdatecontrol : 1;
#define cpuid_feature_information_ecx_xtpr_update_control_bit 14
#define cpuid_feature_information_ecx_xtpr_update_control_flag 0x4000
#define cpuid_feature_information_ecx_xtpr_update_control_mask 0x01
#define cpuid_feature_information_ecx_xtpr_update_control(_) \
	(((_) >> 14) & 0x01)

			/**
                         * @brief perfmon and debug capability
                         *
                         * [bit 15] a value of 1 indicates the processor supports the performance and debug feature indication msr
                         * ia32_perf_capabilities.
                         */
			uint32 perfmonanddebugcapability : 1;
#define cpuid_feature_information_ecx_perfmon_and_debug_capability_bit 15
#define cpuid_feature_information_ecx_perfmon_and_debug_capability_flag 0x8000
#define cpuid_feature_information_ecx_perfmon_and_debug_capability_mask 0x01
#define cpuid_feature_information_ecx_perfmon_and_debug_capability(_) \
	(((_) >> 15) & 0x01)
			uint32 reserved1 : 1;

			/**
                         * @brief process-context identifiers
                         *
                         * [bit 17] a value of 1 indicates that the processor supports pcids and that software may set cr4.pcide to 1.
                         */
			uint32 processcontextidentifiers : 1;
#define cpuid_feature_information_ecx_process_context_identifiers_bit 17
#define cpuid_feature_information_ecx_process_context_identifiers_flag 0x20000
#define cpuid_feature_information_ecx_process_context_identifiers_mask 0x01
#define cpuid_feature_information_ecx_process_context_identifiers(_) \
	(((_) >> 17) & 0x01)

			/**
                         * @brief direct cache access
                         *
                         * [bit 18] a value of 1 indicates the processor supports the ability to prefetch data from a memory mapped device (direct
                         * cache access).
                         */
			uint32 directcacheaccess : 1;
#define cpuid_feature_information_ecx_direct_cache_access_bit 18
#define cpuid_feature_information_ecx_direct_cache_access_flag 0x40000
#define cpuid_feature_information_ecx_direct_cache_access_mask 0x01
#define cpuid_feature_information_ecx_direct_cache_access(_) \
	(((_) >> 18) & 0x01)

			/**
                         * @brief sse4.1 support
                         *
                         * [bit 19] a value of 1 indicates that the processor supports sse4.1.
                         */
			uint32 sse41support : 1;
#define cpuid_feature_information_ecx_sse41_support_bit 19
#define cpuid_feature_information_ecx_sse41_support_flag 0x80000
#define cpuid_feature_information_ecx_sse41_support_mask 0x01
#define cpuid_feature_information_ecx_sse41_support(_) (((_) >> 19) & 0x01)

			/**
                         * @brief sse4.2 support
                         *
                         * [bit 20] a value of 1 indicates that the processor supports sse4.2.
                         */
			uint32 sse42support : 1;
#define cpuid_feature_information_ecx_sse42_support_bit 20
#define cpuid_feature_information_ecx_sse42_support_flag 0x100000
#define cpuid_feature_information_ecx_sse42_support_mask 0x01
#define cpuid_feature_information_ecx_sse42_support(_) (((_) >> 20) & 0x01)

			/**
                         * @brief x2apic support
                         *
                         * [bit 21] a value of 1 indicates that the processor supports x2apic feature.
                         */
			uint32 x2apicsupport : 1;
#define cpuid_feature_information_ecx_x2apic_support_bit 21
#define cpuid_feature_information_ecx_x2apic_support_flag 0x200000
#define cpuid_feature_information_ecx_x2apic_support_mask 0x01
#define cpuid_feature_information_ecx_x2apic_support(_) (((_) >> 21) & 0x01)

			/**
                         * @brief movbe instruction
                         *
                         * [bit 22] a value of 1 indicates that the processor supports movbe instruction.
                         */
			uint32 movbeinstruction : 1;
#define cpuid_feature_information_ecx_movbe_instruction_bit 22
#define cpuid_feature_information_ecx_movbe_instruction_flag 0x400000
#define cpuid_feature_information_ecx_movbe_instruction_mask 0x01
#define cpuid_feature_information_ecx_movbe_instruction(_) (((_) >> 22) & 0x01)

			/**
                         * @brief popcnt instruction
                         *
                         * [bit 23] a value of 1 indicates that the processor supports the popcnt instruction.
                         */
			uint32 popcntinstruction : 1;
#define cpuid_feature_information_ecx_popcnt_instruction_bit 23
#define cpuid_feature_information_ecx_popcnt_instruction_flag 0x800000
#define cpuid_feature_information_ecx_popcnt_instruction_mask 0x01
#define cpuid_feature_information_ecx_popcnt_instruction(_) (((_) >> 23) & 0x01)

			/**
                         * @brief tsc deadline
                         *
                         * [bit 24] a value of 1 indicates that the processor's local apic timer supports one-shot operation using a tsc deadline
                         * value.
                         */
			uint32 tscdeadline : 1;
#define cpuid_feature_information_ecx_tsc_deadline_bit 24
#define cpuid_feature_information_ecx_tsc_deadline_flag 0x1000000
#define cpuid_feature_information_ecx_tsc_deadline_mask 0x01
#define cpuid_feature_information_ecx_tsc_deadline(_) (((_) >> 24) & 0x01)

			/**
                         * @brief aesni instruction extensions
                         *
                         * [bit 25] a value of 1 indicates that the processor supports the aesni instruction extensions.
                         */
			uint32 aesniinstructionextensions : 1;
#define cpuid_feature_information_ecx_aesni_instruction_extensions_bit 25
#define cpuid_feature_information_ecx_aesni_instruction_extensions_flag \
	0x2000000
#define cpuid_feature_information_ecx_aesni_instruction_extensions_mask 0x01
#define cpuid_feature_information_ecx_aesni_instruction_extensions(_) \
	(((_) >> 25) & 0x01)

			/**
                         * @brief xsave/xrstor instruction extensions
                         *
                         * [bit 26] a value of 1 indicates that the processor supports the xsave/xrstor processor extended states feature, the
                         * xsetbv/xgetbv instructions, and xcr0.
                         */
			uint32 xsavexrstorinstruction : 1;
#define cpuid_feature_information_ecx_xsave_xrstor_instruction_bit 26
#define cpuid_feature_information_ecx_xsave_xrstor_instruction_flag 0x4000000
#define cpuid_feature_information_ecx_xsave_xrstor_instruction_mask 0x01
#define cpuid_feature_information_ecx_xsave_xrstor_instruction(_) \
	(((_) >> 26) & 0x01)

			/**
                         * @brief cr4.osxsave[bit 18] set
                         *
                         * [bit 27] a value of 1 indicates that the os has set cr4.osxsave[bit 18] to enable xsetbv/xgetbv instructions to access
                         * xcr0 and to support processor extended state management using xsave/xrstor.
                         */
			uint32 osxsave : 1;
#define cpuid_feature_information_ecx_osx_save_bit 27
#define cpuid_feature_information_ecx_osx_save_flag 0x8000000
#define cpuid_feature_information_ecx_osx_save_mask 0x01
#define cpuid_feature_information_ecx_osx_save(_) (((_) >> 27) & 0x01)

			/**
                         * @brief avx instruction extensions support
                         *
                         * [bit 28] a value of 1 indicates the processor supports the avx instruction extensions.
                         */
			uint32 avxsupport : 1;
#define cpuid_feature_information_ecx_avx_support_bit 28
#define cpuid_feature_information_ecx_avx_support_flag 0x10000000
#define cpuid_feature_information_ecx_avx_support_mask 0x01
#define cpuid_feature_information_ecx_avx_support(_) (((_) >> 28) & 0x01)

			/**
                         * @brief 16-bit floating-point conversion instructions support
                         *
                         * [bit 29] a value of 1 indicates that processor supports 16-bit floating-point conversion instructions.
                         */
			uint32 halfprecisionconversioninstructions : 1;
#define cpuid_feature_information_ecx_half_precision_conversion_instructions_bit \
	29
#define cpuid_feature_information_ecx_half_precision_conversion_instructions_flag \
	0x20000000
#define cpuid_feature_information_ecx_half_precision_conversion_instructions_mask \
	0x01
#define cpuid_feature_information_ecx_half_precision_conversion_instructions( \
	_)                                                                    \
	(((_) >> 29) & 0x01)

			/**
                         * @brief rdrand instruction support
                         *
                         * [bit 30] a value of 1 indicates that processor supports rdrand instruction.
                         */
			uint32 rdrandinstruction : 1;
#define cpuid_feature_information_ecx_rdrand_instruction_bit 30
#define cpuid_feature_information_ecx_rdrand_instruction_flag 0x40000000
#define cpuid_feature_information_ecx_rdrand_instruction_mask 0x01
#define cpuid_feature_information_ecx_rdrand_instruction(_) (((_) >> 30) & 0x01)
			uint32 reserved2 : 1;
		};

		uint32 flags;
	} cpuidfeatureinformationecx;

	/**
         * @brief when cpuid executes with eax set to 01h, feature information is returned in ecx and edx
         */
	union {
		struct {
			/**
                         * @brief floating point unit on-chip
                         *
                         * [bit 0] the processor contains an x87 fpu.
                         */
			uint32 floatingpointunitonchip : 1;
#define cpuid_feature_information_edx_floating_point_unit_on_chip_bit 0
#define cpuid_feature_information_edx_floating_point_unit_on_chip_flag 0x01
#define cpuid_feature_information_edx_floating_point_unit_on_chip_mask 0x01
#define cpuid_feature_information_edx_floating_point_unit_on_chip(_) \
	(((_) >> 0) & 0x01)

			/**
                         * @brief virtual 8086 mode enhancements
                         *
                         * [bit 1] virtual 8086 mode enhancements, including cr4.vme for controlling the feature, cr4.pvi for protected mode
                         * virtual interrupts, software interrupt indirection, expansion of the tss with the software indirection bitmap, and
                         * eflags.vif and eflags.vip flags.
                         */
			uint32 virtual8086modeenhancements : 1;
#define cpuid_feature_information_edx_virtual_8086_mode_enhancements_bit 1
#define cpuid_feature_information_edx_virtual_8086_mode_enhancements_flag 0x02
#define cpuid_feature_information_edx_virtual_8086_mode_enhancements_mask 0x01
#define cpuid_feature_information_edx_virtual_8086_mode_enhancements(_) \
	(((_) >> 1) & 0x01)

			/**
                         * @brief debugging extensions
                         *
                         * [bit 2] support for i/o breakpoints, including cr4.de for controlling the feature, and optional trapping of accesses to
                         * dr4 and dr5.
                         */
			uint32 debuggingextensions : 1;
#define cpuid_feature_information_edx_debugging_extensions_bit 2
#define cpuid_feature_information_edx_debugging_extensions_flag 0x04
#define cpuid_feature_information_edx_debugging_extensions_mask 0x01
#define cpuid_feature_information_edx_debugging_extensions(_) \
	(((_) >> 2) & 0x01)

			/**
                         * @brief page size extension
                         *
                         * [bit 3] large pages of size 4 mbyte are supported, including cr4.pse for controlling the feature, the defined dirty bit
                         * in pde (page directory entries), optional reserved bit trapping in cr3, pdes, and ptes.
                         */
			uint32 pagesizeextension : 1;
#define cpuid_feature_information_edx_page_size_extension_bit 3
#define cpuid_feature_information_edx_page_size_extension_flag 0x08
#define cpuid_feature_information_edx_page_size_extension_mask 0x01
#define cpuid_feature_information_edx_page_size_extension(_) (((_) >> 3) & 0x01)

			/**
                         * @brief time stamp counter
                         *
                         * [bit 4] the rdtsc instruction is supported, including cr4.tsd for controlling privilege.
                         */
			uint32 timestampcounter : 1;
#define cpuid_feature_information_edx_timestamp_counter_bit 4
#define cpuid_feature_information_edx_timestamp_counter_flag 0x10
#define cpuid_feature_information_edx_timestamp_counter_mask 0x01
#define cpuid_feature_information_edx_timestamp_counter(_) (((_) >> 4) & 0x01)

			/**
                         * @brief model specific registers rdmsr and wrmsr instructions
                         *
                         * [bit 5] the rdmsr and wrmsr instructions are supported. some of the msrs are implementation dependent.
                         */
			uint32 rdmsrwrmsrinstructions : 1;
#define cpuid_feature_information_edx_rdmsr_wrmsr_instructions_bit 5
#define cpuid_feature_information_edx_rdmsr_wrmsr_instructions_flag 0x20
#define cpuid_feature_information_edx_rdmsr_wrmsr_instructions_mask 0x01
#define cpuid_feature_information_edx_rdmsr_wrmsr_instructions(_) \
	(((_) >> 5) & 0x01)

			/**
                         * @brief physical address extension
                         *
                         * [bit 6] physical addresses greater than 32 bits are supported: extended page table entry formats, an extra level in the
                         * page translation tables is defined, 2-mbyte pages are supported instead of 4 mbyte pages if pae bit is 1.
                         */
			uint32 physicaladdressextension : 1;
#define cpuid_feature_information_edx_physical_address_extension_bit 6
#define cpuid_feature_information_edx_physical_address_extension_flag 0x40
#define cpuid_feature_information_edx_physical_address_extension_mask 0x01
#define cpuid_feature_information_edx_physical_address_extension(_) \
	(((_) >> 6) & 0x01)

			/**
                         * @brief machine check exception
                         *
                         * [bit 7] exception 18 is defined for machine checks, including cr4.mce for controlling the feature. this feature does not
                         * define the model-specific implementations of machine-check error logging, reporting, and processor shutdowns. machine
                         * check exception handlers may have to depend on processor version to do model specific processing of the exception, or
                         * test for the presence of the machine check feature.
                         */
			uint32 machinecheckexception : 1;
#define cpuid_feature_information_edx_machine_check_exception_bit 7
#define cpuid_feature_information_edx_machine_check_exception_flag 0x80
#define cpuid_feature_information_edx_machine_check_exception_mask 0x01
#define cpuid_feature_information_edx_machine_check_exception(_) \
	(((_) >> 7) & 0x01)

			/**
                         * @brief cmpxchg8b instruction
                         *
                         * [bit 8] the compare-and-exchange 8 bytes (64 bits) instruction is supported (implicitly locked and atomic).
                         */
			uint32 cmpxchg8b : 1;
#define cpuid_feature_information_edx_cmpxchg8b_bit 8
#define cpuid_feature_information_edx_cmpxchg8b_flag 0x100
#define cpuid_feature_information_edx_cmpxchg8b_mask 0x01
#define cpuid_feature_information_edx_cmpxchg8b(_) (((_) >> 8) & 0x01)

			/**
                         * @brief apic on-chip
                         *
                         * [bit 9] the processor contains an advanced programmable interrupt controller (apic), responding to memory mapped
                         * commands in the physical address range fffe0000h to fffe0fffh (by default - some processors permit the apic to be
                         * relocated).
                         */
			uint32 apiconchip : 1;
#define cpuid_feature_information_edx_apic_on_chip_bit 9
#define cpuid_feature_information_edx_apic_on_chip_flag 0x200
#define cpuid_feature_information_edx_apic_on_chip_mask 0x01
#define cpuid_feature_information_edx_apic_on_chip(_) (((_) >> 9) & 0x01)
			uint32 reserved1 : 1;

			/**
                         * @brief sysenter and sysexit instructions
                         *
                         * [bit 11] the sysenter and sysexit and associated msrs are supported.
                         */
			uint32 sysentersysexitinstructions : 1;
#define cpuid_feature_information_edx_sysenter_sysexit_instructions_bit 11
#define cpuid_feature_information_edx_sysenter_sysexit_instructions_flag 0x800
#define cpuid_feature_information_edx_sysenter_sysexit_instructions_mask 0x01
#define cpuid_feature_information_edx_sysenter_sysexit_instructions(_) \
	(((_) >> 11) & 0x01)

			/**
                         * @brief memory type range registers
                         *
                         * [bit 12] mtrrs are supported. the mtrrcap msr contains feature bits that describe what memory types are supported, how
                         * many variable mtrrs are supported, and whether fixed mtrrs are supported.
                         */
			uint32 memorytyperangeregisters : 1;
#define cpuid_feature_information_edx_memory_type_range_registers_bit 12
#define cpuid_feature_information_edx_memory_type_range_registers_flag 0x1000
#define cpuid_feature_information_edx_memory_type_range_registers_mask 0x01
#define cpuid_feature_information_edx_memory_type_range_registers(_) \
	(((_) >> 12) & 0x01)

			/**
                         * @brief page global bit
                         *
                         * [bit 13] the global bit is supported in paging-structure entries that map a page, indicating tlb entries that are common
                         * to different processes and need not be flushed. the cr4.pge bit controls this feature.
                         */
			uint32 pageglobalbit : 1;
#define cpuid_feature_information_edx_page_global_bit_bit 13
#define cpuid_feature_information_edx_page_global_bit_flag 0x2000
#define cpuid_feature_information_edx_page_global_bit_mask 0x01
#define cpuid_feature_information_edx_page_global_bit(_) (((_) >> 13) & 0x01)

			/**
                         * @brief machine check architecture
                         *
                         * [bit 14] a value of 1 indicates the machine check architecture of reporting machine errors is supported. the mcg_cap msr
                         * contains feature bits describing how many banks of error reporting msrs are supported.
                         */
			uint32 machinecheckarchitecture : 1;
#define cpuid_feature_information_edx_machine_check_architecture_bit 14
#define cpuid_feature_information_edx_machine_check_architecture_flag 0x4000
#define cpuid_feature_information_edx_machine_check_architecture_mask 0x01
#define cpuid_feature_information_edx_machine_check_architecture(_) \
	(((_) >> 14) & 0x01)

			/**
                         * @brief conditional move instructions
                         *
                         * [bit 15] the conditional move instruction cmov is supported. in addition, if x87 fpu is present as indicated by the
                         * cpuid.fpu feature bit, then the fcomi and fcmov instructions are supported
                         */
			uint32 conditionalmoveinstructions : 1;
#define cpuid_feature_information_edx_conditional_move_instructions_bit 15
#define cpuid_feature_information_edx_conditional_move_instructions_flag 0x8000
#define cpuid_feature_information_edx_conditional_move_instructions_mask 0x01
#define cpuid_feature_information_edx_conditional_move_instructions(_) \
	(((_) >> 15) & 0x01)

			/**
                         * @brief page attribute table
                         *
                         * [bit 16] page attribute table is supported. this feature augments the memory type range registers (mtrrs), allowing an
                         * operating system to specify attributes of memory accessed through a linear address on a 4kb granularity.
                         */
			uint32 pageattributetable : 1;
#define cpuid_feature_information_edx_page_attribute_table_bit 16
#define cpuid_feature_information_edx_page_attribute_table_flag 0x10000
#define cpuid_feature_information_edx_page_attribute_table_mask 0x01
#define cpuid_feature_information_edx_page_attribute_table(_) \
	(((_) >> 16) & 0x01)

			/**
                         * @brief 36-bit page size extension
                         *
                         * [bit 17] 4-mbyte pages addressing physical memory beyond 4 gbytes are supported with 32-bit paging. this feature
                         * indicates that upper bits of the physical address of a 4-mbyte page are encoded in bits 20:13 of the page-directory
                         * entry. such physical addresses are limited by maxphyaddr and may be up to 40 bits in size.
                         */
			uint32 pagesizeextension36bit : 1;
#define cpuid_feature_information_edx_page_size_extension_36bit_bit 17
#define cpuid_feature_information_edx_page_size_extension_36bit_flag 0x20000
#define cpuid_feature_information_edx_page_size_extension_36bit_mask 0x01
#define cpuid_feature_information_edx_page_size_extension_36bit(_) \
	(((_) >> 17) & 0x01)

			/**
                         * @brief processor serial number
                         *
                         * [bit 18] the processor supports the 96-bit processor identification number feature and the feature is enabled.
                         */
			uint32 processorserialnumber : 1;
#define cpuid_feature_information_edx_processor_serial_number_bit 18
#define cpuid_feature_information_edx_processor_serial_number_flag 0x40000
#define cpuid_feature_information_edx_processor_serial_number_mask 0x01
#define cpuid_feature_information_edx_processor_serial_number(_) \
	(((_) >> 18) & 0x01)

			/**
                         * @brief clflush instruction
                         *
                         * [bit 19] clflush instruction is supported.
                         */
			uint32 clflush : 1;
#define cpuid_feature_information_edx_clflush_bit 19
#define cpuid_feature_information_edx_clflush_flag 0x80000
#define cpuid_feature_information_edx_clflush_mask 0x01
#define cpuid_feature_information_edx_clflush(_) (((_) >> 19) & 0x01)
			uint32 reserved2 : 1;

			/**
                         * @brief debug store
                         *
                         * [bit 21] the processor supports the ability to write debug information into a memory resident buffer. this feature is
                         * used by the branch trace store (bts) and processor event-based sampling (pebs) facilities.
                         *
                         * @see vol3c[23(introduction to virtual machine extensions)]
                         */
			uint32 debugstore : 1;
#define cpuid_feature_information_edx_debug_store_bit 21
#define cpuid_feature_information_edx_debug_store_flag 0x200000
#define cpuid_feature_information_edx_debug_store_mask 0x01
#define cpuid_feature_information_edx_debug_store(_) (((_) >> 21) & 0x01)

			/**
                         * @brief thermal monitor and software controlled clock facilities
                         *
                         * [bit 22] the processor implements internal msrs that allow processor temperature to be monitored and processor
                         * performance to be modulated in predefined duty cycles under software control.
                         */
			uint32 thermalcontrolmsrsforacpi : 1;
#define cpuid_feature_information_edx_thermal_control_msrs_for_acpi_bit 22
#define cpuid_feature_information_edx_thermal_control_msrs_for_acpi_flag \
	0x400000
#define cpuid_feature_information_edx_thermal_control_msrs_for_acpi_mask 0x01
#define cpuid_feature_information_edx_thermal_control_msrs_for_acpi(_) \
	(((_) >> 22) & 0x01)

			/**
                         * @brief intel mmx technology
                         *
                         * [bit 23] the processor supports the intel mmx technology.
                         */
			uint32 mmxsupport : 1;
#define cpuid_feature_information_edx_mmx_support_bit 23
#define cpuid_feature_information_edx_mmx_support_flag 0x800000
#define cpuid_feature_information_edx_mmx_support_mask 0x01
#define cpuid_feature_information_edx_mmx_support(_) (((_) >> 23) & 0x01)

			/**
                         * @brief fxsave and fxrstor instructions
                         *
                         * [bit 24] the fxsave and fxrstor instructions are supported for fast save and restore of the floating point context.
                         * presence of this bit also indicates that cr4.osfxsr is available for an operating system to indicate that it supports
                         * the fxsave and fxrstor instructions.
                         */
			uint32 fxsavefxrstorinstructions : 1;
#define cpuid_feature_information_edx_fxsave_fxrstor_instructions_bit 24
#define cpuid_feature_information_edx_fxsave_fxrstor_instructions_flag 0x1000000
#define cpuid_feature_information_edx_fxsave_fxrstor_instructions_mask 0x01
#define cpuid_feature_information_edx_fxsave_fxrstor_instructions(_) \
	(((_) >> 24) & 0x01)

			/**
                         * @brief sse extensions support
                         *
                         * [bit 25] the processor supports the sse extensions.
                         */
			uint32 ssesupport : 1;
#define cpuid_feature_information_edx_sse_support_bit 25
#define cpuid_feature_information_edx_sse_support_flag 0x2000000
#define cpuid_feature_information_edx_sse_support_mask 0x01
#define cpuid_feature_information_edx_sse_support(_) (((_) >> 25) & 0x01)

			/**
                         * @brief sse2 extensions support
                         *
                         * [bit 26] the processor supports the sse2 extensions.
                         */
			uint32 sse2support : 1;
#define cpuid_feature_information_edx_sse2_support_bit 26
#define cpuid_feature_information_edx_sse2_support_flag 0x4000000
#define cpuid_feature_information_edx_sse2_support_mask 0x01
#define cpuid_feature_information_edx_sse2_support(_) (((_) >> 26) & 0x01)

			/**
                         * @brief self snoop
                         *
                         * [bit 27] the processor supports the management of conflicting memory types by performing a snoop of its own cache
                         * structure for transactions issued to the bus.
                         */
			uint32 selfsnoop : 1;
#define cpuid_feature_information_edx_self_snoop_bit 27
#define cpuid_feature_information_edx_self_snoop_flag 0x8000000
#define cpuid_feature_information_edx_self_snoop_mask 0x01
#define cpuid_feature_information_edx_self_snoop(_) (((_) >> 27) & 0x01)

			/**
                         * @brief max apic ids reserved field is valid
                         *
                         * [bit 28] a value of 0 for htt indicates there is only a single logical processor in the package and software should
                         * assume only a single apic id is reserved. a value of 1 for htt indicates the value in cpuid.1.ebx[23:16] (the maximum
                         * number of addressable ids for logical processors in this package) is valid for the package.
                         */
			uint32 hyperthreadingtechnology : 1;
#define cpuid_feature_information_edx_hyper_threading_technology_bit 28
#define cpuid_feature_information_edx_hyper_threading_technology_flag 0x10000000
#define cpuid_feature_information_edx_hyper_threading_technology_mask 0x01
#define cpuid_feature_information_edx_hyper_threading_technology(_) \
	(((_) >> 28) & 0x01)

			/**
                         * @brief thermal monitor
                         *
                         * [bit 29] the processor implements the thermal monitor automatic thermal control circuitry (tcc).
                         */
			uint32 thermalmonitor : 1;
#define cpuid_feature_information_edx_thermal_monitor_bit 29
#define cpuid_feature_information_edx_thermal_monitor_flag 0x20000000
#define cpuid_feature_information_edx_thermal_monitor_mask 0x01
#define cpuid_feature_information_edx_thermal_monitor(_) (((_) >> 29) & 0x01)
			uint32 reserved3 : 1;

			/**
                         * @brief pending break enable
                         *
                         * [bit 31] the processor supports the use of the ferr\#/pbe\# pin when the processor is in the stop-clock state (stpclk\#
                         * is asserted) to signal the processor that an interrupt is pending and that the processor should return to normal
                         * operation to handle the interrupt. bit 10 (pbe enable) in the ia32_misc_enable msr enables this capability.
                         */
			uint32 pendingbreakenable : 1;
#define cpuid_feature_information_edx_pending_break_enable_bit 31
#define cpuid_feature_information_edx_pending_break_enable_flag 0x80000000
#define cpuid_feature_information_edx_pending_break_enable_mask 0x01
#define cpuid_feature_information_edx_pending_break_enable(_) \
	(((_) >> 31) & 0x01)
		};

		uint32 flags;
	} cpuidfeatureinformationedx;

} cpuid_eax_01;

/**
 * @brief deterministic cache parameters leaf
 *
 * when cpuid executes with eax set to 04h and ecx contains an index value, the processor returns encoded data that
 * describe a set of deterministic cache parameters (for the cache level associated with the input in ecx). valid index
 * values start from 0.
 * software can enumerate the deterministic cache parameters for each level of the cache hierarchy starting with an index
 * value of 0, until the parameters report the value associated with the cache type field is 0. the architecturally defined
 * fields reported by deterministic cache parameters are documented in table 3-8.
 * this cache size in bytes
 * - = (ways + 1) * (partitions + 1) * (line_size + 1) * (sets + 1)
 * - = (ebx[31:22] + 1) * (ebx[21:12] + 1) * (ebx[11:0] + 1) * (ecx + 1)
 * the cpuid leaf 04h also reports data that can be used to derive the topology of processor cores in a physical package.
 * this information is constant for all valid index values. software can query the raw data reported by executing cpuid
 * with eax=04h and ecx=0 and use it as part of the topology enumeration algorithm.
 *
 * @see vol3a[8(multiple-processor management)]
 */
#define cpuid_cache_parameters 0x00000004
typedef struct {
	union {
		struct {
			/**
                         * [bits 4:0] - 0 = null - no more caches.
                         * - 1 = data cache.
                         * - 2 = instruction cache.
                         * - 3 = unified cache.
                         * - 4-31 = reserved.
                         */
			uint32 cachetypefield : 5;
#define cpuid_eax_cache_type_field_bit 0
#define cpuid_eax_cache_type_field_flag 0x1f
#define cpuid_eax_cache_type_field_mask 0x1f
#define cpuid_eax_cache_type_field(_) (((_) >> 0) & 0x1f)

			/**
                         * [bits 7:5] cache level (starts at 1).
                         */
			uint32 cachelevel : 3;
#define cpuid_eax_cache_level_bit 5
#define cpuid_eax_cache_level_flag 0xe0
#define cpuid_eax_cache_level_mask 0x07
#define cpuid_eax_cache_level(_) (((_) >> 5) & 0x07)

			/**
                         * [bit 8] self initializing cache level (does not need sw initialization).
                         */
			uint32 selfinitializingcachelevel : 1;
#define cpuid_eax_self_initializing_cache_level_bit 8
#define cpuid_eax_self_initializing_cache_level_flag 0x100
#define cpuid_eax_self_initializing_cache_level_mask 0x01
#define cpuid_eax_self_initializing_cache_level(_) (((_) >> 8) & 0x01)

			/**
                         * [bit 9] fully associative cache.
                         */
			uint32 fullyassociativecache : 1;
#define cpuid_eax_fully_associative_cache_bit 9
#define cpuid_eax_fully_associative_cache_flag 0x200
#define cpuid_eax_fully_associative_cache_mask 0x01
#define cpuid_eax_fully_associative_cache(_) (((_) >> 9) & 0x01)
			uint32 reserved1 : 4;

			/**
                         * [bits 25:14] maximum number of addressable ids for logical processors sharing this cache.
                         *
                         * @note add one to the return value to get the result.
                         *       the nearest power-of-2 integer that is not smaller than (1 + eax[25:14]) is the number of unique initial apic ids
                         *       reserved for addressing different logical processors sharing this cache.
                         */
			uint32 maxaddressableidsforlogicalprocessorssharingthiscache : 12;
#define cpuid_eax_max_addressable_ids_for_logical_processors_sharing_this_cache_bit \
	14
#define cpuid_eax_max_addressable_ids_for_logical_processors_sharing_this_cache_flag \
	0x3ffc000
#define cpuid_eax_max_addressable_ids_for_logical_processors_sharing_this_cache_mask \
	0xfff
#define cpuid_eax_max_addressable_ids_for_logical_processors_sharing_this_cache( \
	_)                                                                       \
	(((_) >> 14) & 0xfff)

			/**
                         * [bits 31:26] maximum number of addressable ids for processor cores in the physical package.
                         *
                         * @note add one to the return value to get the result.
                         *       the nearest power-of-2 integer that is not smaller than (1 + eax[31:26]) is the number of unique core_ids reserved for
                         *       addressing different processor cores in a physical package. core id is a subset of bits of the initial apic id.
                         *       the returned value is constant for valid initial values in ecx. valid ecx values start from 0.
                         */
			uint32 maxaddressableidsforprocessorcoresinphysicalpackage : 6;
#define cpuid_eax_max_addressable_ids_for_processor_cores_in_physical_package_bit \
	26
#define cpuid_eax_max_addressable_ids_for_processor_cores_in_physical_package_flag \
	0xfc000000
#define cpuid_eax_max_addressable_ids_for_processor_cores_in_physical_package_mask \
	0x3f
#define cpuid_eax_max_addressable_ids_for_processor_cores_in_physical_package( \
	_)                                                                     \
	(((_) >> 26) & 0x3f)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 11:0] system coherency line size.
                         *
                         * @note add one to the return value to get the result.
                         */
			uint32 systemcoherencylinesize : 12;
#define cpuid_ebx_system_coherency_line_size_bit 0
#define cpuid_ebx_system_coherency_line_size_flag 0xfff
#define cpuid_ebx_system_coherency_line_size_mask 0xfff
#define cpuid_ebx_system_coherency_line_size(_) (((_) >> 0) & 0xfff)

			/**
                         * [bits 21:12] physical line partitions.
                         *
                         * @note add one to the return value to get the result.
                         */
			uint32 physicallinepartitions : 10;
#define cpuid_ebx_physical_line_partitions_bit 12
#define cpuid_ebx_physical_line_partitions_flag 0x3ff000
#define cpuid_ebx_physical_line_partitions_mask 0x3ff
#define cpuid_ebx_physical_line_partitions(_) (((_) >> 12) & 0x3ff)

			/**
                         * [bits 31:22] ways of associativity.
                         *
                         * @note add one to the return value to get the result.
                         */
			uint32 waysofassociativity : 10;
#define cpuid_ebx_ways_of_associativity_bit 22
#define cpuid_ebx_ways_of_associativity_flag 0xffc00000
#define cpuid_ebx_ways_of_associativity_mask 0x3ff
#define cpuid_ebx_ways_of_associativity(_) (((_) >> 22) & 0x3ff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] number of sets.
                         *
                         * @note add one to the return value to get the result.
                         */
			uint32 numberofsets : 32;
#define cpuid_ecx_number_of_sets_bit 0
#define cpuid_ecx_number_of_sets_flag 0xffffffff
#define cpuid_ecx_number_of_sets_mask 0xffffffff
#define cpuid_ecx_number_of_sets(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * @brief write-back invalidate/invalidate
                         *
                         * [bit 0] - 0 = wbinvd/invd from threads sharing this cache acts upon lower level caches for threads sharing this cache.
                         * - 1 = wbinvd/invd is not guaranteed to act upon lower level caches of non-originating threads sharing this cache.
                         */
			uint32 writebackinvalidate : 1;
#define cpuid_edx_write_back_invalidate_bit 0
#define cpuid_edx_write_back_invalidate_flag 0x01
#define cpuid_edx_write_back_invalidate_mask 0x01
#define cpuid_edx_write_back_invalidate(_) (((_) >> 0) & 0x01)

			/**
                         * @brief cache inclusiveness
                         *
                         * [bit 1] - 0 = cache is not inclusive of lower cache levels.
                         * - 1 = cache is inclusive of lower cache levels.
                         */
			uint32 cacheinclusiveness : 1;
#define cpuid_edx_cache_inclusiveness_bit 1
#define cpuid_edx_cache_inclusiveness_flag 0x02
#define cpuid_edx_cache_inclusiveness_mask 0x01
#define cpuid_edx_cache_inclusiveness(_) (((_) >> 1) & 0x01)

			/**
                         * @brief complex cache indexing
                         *
                         * [bit 2] - 0 = direct mapped cache.
                         * - 1 = a complex function is used to index the cache, potentially using all address bits.
                         */
			uint32 complexcacheindexing : 1;
#define cpuid_edx_complex_cache_indexing_bit 2
#define cpuid_edx_complex_cache_indexing_flag 0x04
#define cpuid_edx_complex_cache_indexing_mask 0x01
#define cpuid_edx_complex_cache_indexing(_) (((_) >> 2) & 0x01)
			uint32 reserved1 : 29;
		};

		uint32 flags;
	} edx;

} cpuid_eax_04;

/**
 * @brief monitor/mwait leaf
 *
 * when cpuid executes with eax set to 05h, the processor returns information about features available to monitor/mwait
 * instructions. the monitor instruction is used for address-range monitoring in conjunction with mwait instruction. the
 * mwait instruction optionally provides additional extensions for advanced power management.
 */
#define cpuid_monitor_mwait 0x00000005
typedef struct {
	union {
		struct {
			/**
                         * [bits 15:0] smallest monitor-line size in bytes (default is processor's monitor granularity).
                         */
			uint32 smallestmonitorlinesize : 16;
#define cpuid_eax_smallest_monitor_line_size_bit 0
#define cpuid_eax_smallest_monitor_line_size_flag 0xffff
#define cpuid_eax_smallest_monitor_line_size_mask 0xffff
#define cpuid_eax_smallest_monitor_line_size(_) (((_) >> 0) & 0xffff)
			uint32 reserved1 : 16;
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 15:0] largest monitor-line size in bytes (default is processor's monitor granularity).
                         */
			uint32 largestmonitorlinesize : 16;
#define cpuid_ebx_largest_monitor_line_size_bit 0
#define cpuid_ebx_largest_monitor_line_size_flag 0xffff
#define cpuid_ebx_largest_monitor_line_size_mask 0xffff
#define cpuid_ebx_largest_monitor_line_size(_) (((_) >> 0) & 0xffff)
			uint32 reserved1 : 16;
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bit 0] enumeration of monitor-mwait extensions (beyond eax and ebx registers) supported.
                         */
			uint32 enumerationofmonitormwaitextensions : 1;
#define cpuid_ecx_enumeration_of_monitor_mwait_extensions_bit 0
#define cpuid_ecx_enumeration_of_monitor_mwait_extensions_flag 0x01
#define cpuid_ecx_enumeration_of_monitor_mwait_extensions_mask 0x01
#define cpuid_ecx_enumeration_of_monitor_mwait_extensions(_) (((_) >> 0) & 0x01)

			/**
                         * [bit 1] supports treating interrupts as break-event for mwait, even when interrupts disabled.
                         */
			uint32 supportstreatinginterruptsasbreakeventformwait : 1;
#define cpuid_ecx_supports_treating_interrupts_as_break_event_for_mwait_bit 1
#define cpuid_ecx_supports_treating_interrupts_as_break_event_for_mwait_flag \
	0x02
#define cpuid_ecx_supports_treating_interrupts_as_break_event_for_mwait_mask \
	0x01
#define cpuid_ecx_supports_treating_interrupts_as_break_event_for_mwait(_) \
	(((_) >> 1) & 0x01)
			uint32 reserved1 : 30;
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 3:0] number of c0 sub c-states supported using mwait.
                         */
			uint32 numberofc0subcstates : 4;
#define cpuid_edx_number_of_c0_sub_c_states_bit 0
#define cpuid_edx_number_of_c0_sub_c_states_flag 0x0f
#define cpuid_edx_number_of_c0_sub_c_states_mask 0x0f
#define cpuid_edx_number_of_c0_sub_c_states(_) (((_) >> 0) & 0x0f)

			/**
                         * [bits 7:4] number of c1 sub c-states supported using mwait.
                         */
			uint32 numberofc1subcstates : 4;
#define cpuid_edx_number_of_c1_sub_c_states_bit 4
#define cpuid_edx_number_of_c1_sub_c_states_flag 0xf0
#define cpuid_edx_number_of_c1_sub_c_states_mask 0x0f
#define cpuid_edx_number_of_c1_sub_c_states(_) (((_) >> 4) & 0x0f)

			/**
                         * [bits 11:8] number of c2 sub c-states supported using mwait.
                         */
			uint32 numberofc2subcstates : 4;
#define cpuid_edx_number_of_c2_sub_c_states_bit 8
#define cpuid_edx_number_of_c2_sub_c_states_flag 0xf00
#define cpuid_edx_number_of_c2_sub_c_states_mask 0x0f
#define cpuid_edx_number_of_c2_sub_c_states(_) (((_) >> 8) & 0x0f)

			/**
                         * [bits 15:12] number of c3 sub c-states supported using mwait.
                         */
			uint32 numberofc3subcstates : 4;
#define cpuid_edx_number_of_c3_sub_c_states_bit 12
#define cpuid_edx_number_of_c3_sub_c_states_flag 0xf000
#define cpuid_edx_number_of_c3_sub_c_states_mask 0x0f
#define cpuid_edx_number_of_c3_sub_c_states(_) (((_) >> 12) & 0x0f)

			/**
                         * [bits 19:16] number of c4 sub c-states supported using mwait.
                         */
			uint32 numberofc4subcstates : 4;
#define cpuid_edx_number_of_c4_sub_c_states_bit 16
#define cpuid_edx_number_of_c4_sub_c_states_flag 0xf0000
#define cpuid_edx_number_of_c4_sub_c_states_mask 0x0f
#define cpuid_edx_number_of_c4_sub_c_states(_) (((_) >> 16) & 0x0f)

			/**
                         * [bits 23:20] number of c5 sub c-states supported using mwait.
                         */
			uint32 numberofc5subcstates : 4;
#define cpuid_edx_number_of_c5_sub_c_states_bit 20
#define cpuid_edx_number_of_c5_sub_c_states_flag 0xf00000
#define cpuid_edx_number_of_c5_sub_c_states_mask 0x0f
#define cpuid_edx_number_of_c5_sub_c_states(_) (((_) >> 20) & 0x0f)

			/**
                         * [bits 27:24] number of c6 sub c-states supported using mwait.
                         */
			uint32 numberofc6subcstates : 4;
#define cpuid_edx_number_of_c6_sub_c_states_bit 24
#define cpuid_edx_number_of_c6_sub_c_states_flag 0xf000000
#define cpuid_edx_number_of_c6_sub_c_states_mask 0x0f
#define cpuid_edx_number_of_c6_sub_c_states(_) (((_) >> 24) & 0x0f)

			/**
                         * [bits 31:28] number of c7 sub c-states supported using mwait.
                         */
			uint32 numberofc7subcstates : 4;
#define cpuid_edx_number_of_c7_sub_c_states_bit 28
#define cpuid_edx_number_of_c7_sub_c_states_flag 0xf0000000
#define cpuid_edx_number_of_c7_sub_c_states_mask 0x0f
#define cpuid_edx_number_of_c7_sub_c_states(_) (((_) >> 28) & 0x0f)
		};

		uint32 flags;
	} edx;

} cpuid_eax_05;

/**
 * @brief thermal and power management leaf
 *
 * when cpuid executes with eax set to 06h, the processor returns information about thermal and power management features.
 */
#define cpuid_thermal_and_power_management 0x00000006
typedef struct {
	union {
		struct {
			/**
                         * [bit 0] digital temperature sensor is supported if set.
                         */
			uint32 temperaturesensorsupported : 1;
#define cpuid_eax_temperature_sensor_supported_bit 0
#define cpuid_eax_temperature_sensor_supported_flag 0x01
#define cpuid_eax_temperature_sensor_supported_mask 0x01
#define cpuid_eax_temperature_sensor_supported(_) (((_) >> 0) & 0x01)

			/**
                         * [bit 1] intel turbo boost technology available (see description of ia32_misc_enable[38]).
                         */
			uint32 intelturboboosttechnologyavailable : 1;
#define cpuid_eax_intel_turbo_boost_technology_available_bit 1
#define cpuid_eax_intel_turbo_boost_technology_available_flag 0x02
#define cpuid_eax_intel_turbo_boost_technology_available_mask 0x01
#define cpuid_eax_intel_turbo_boost_technology_available(_) (((_) >> 1) & 0x01)

			/**
                         * [bit 2] arat. apic-timer-always-running feature is supported if set.
                         */
			uint32 apictimeralwaysrunning : 1;
#define cpuid_eax_apic_timer_always_running_bit 2
#define cpuid_eax_apic_timer_always_running_flag 0x04
#define cpuid_eax_apic_timer_always_running_mask 0x01
#define cpuid_eax_apic_timer_always_running(_) (((_) >> 2) & 0x01)
			uint32 reserved1 : 1;

			/**
                         * [bit 4] pln. power limit notification controls are supported if set.
                         */
			uint32 powerlimitnotification : 1;
#define cpuid_eax_power_limit_notification_bit 4
#define cpuid_eax_power_limit_notification_flag 0x10
#define cpuid_eax_power_limit_notification_mask 0x01
#define cpuid_eax_power_limit_notification(_) (((_) >> 4) & 0x01)

			/**
                         * [bit 5] ecmd. clock modulation duty cycle extension is supported if set.
                         */
			uint32 clockmodulationduty : 1;
#define cpuid_eax_clock_modulation_duty_bit 5
#define cpuid_eax_clock_modulation_duty_flag 0x20
#define cpuid_eax_clock_modulation_duty_mask 0x01
#define cpuid_eax_clock_modulation_duty(_) (((_) >> 5) & 0x01)

			/**
                         * [bit 6] ptm. package thermal management is supported if set.
                         */
			uint32 packagethermalmanagement : 1;
#define cpuid_eax_package_thermal_management_bit 6
#define cpuid_eax_package_thermal_management_flag 0x40
#define cpuid_eax_package_thermal_management_mask 0x01
#define cpuid_eax_package_thermal_management(_) (((_) >> 6) & 0x01)

			/**
                         * [bit 7] hwp. hwp base registers (ia32_pm_enable[bit 0], ia32_hwp_capabilities, ia32_hwp_request, ia32_hwp_status) are
                         * supported if set.
                         */
			uint32 hwpbaseregisters : 1;
#define cpuid_eax_hwp_base_registers_bit 7
#define cpuid_eax_hwp_base_registers_flag 0x80
#define cpuid_eax_hwp_base_registers_mask 0x01
#define cpuid_eax_hwp_base_registers(_) (((_) >> 7) & 0x01)

			/**
                         * [bit 8] hwp_notification. ia32_hwp_interrupt msr is supported if set.
                         */
			uint32 hwpnotification : 1;
#define cpuid_eax_hwp_notification_bit 8
#define cpuid_eax_hwp_notification_flag 0x100
#define cpuid_eax_hwp_notification_mask 0x01
#define cpuid_eax_hwp_notification(_) (((_) >> 8) & 0x01)

			/**
                         * [bit 9] hwp_activity_window. ia32_hwp_request[bits 41:32] is supported if set.
                         */
			uint32 hwpactivitywindow : 1;
#define cpuid_eax_hwp_activity_window_bit 9
#define cpuid_eax_hwp_activity_window_flag 0x200
#define cpuid_eax_hwp_activity_window_mask 0x01
#define cpuid_eax_hwp_activity_window(_) (((_) >> 9) & 0x01)

			/**
                         * [bit 10] hwp_energy_performance_preference. ia32_hwp_request[bits 31:24] is supported if set.
                         */
			uint32 hwpenergyperformancepreference : 1;
#define cpuid_eax_hwp_energy_performance_preference_bit 10
#define cpuid_eax_hwp_energy_performance_preference_flag 0x400
#define cpuid_eax_hwp_energy_performance_preference_mask 0x01
#define cpuid_eax_hwp_energy_performance_preference(_) (((_) >> 10) & 0x01)

			/**
                         * [bit 11] hwp_package_level_request. ia32_hwp_request_pkg msr is supported if set.
                         */
			uint32 hwppackagelevelrequest : 1;
#define cpuid_eax_hwp_package_level_request_bit 11
#define cpuid_eax_hwp_package_level_request_flag 0x800
#define cpuid_eax_hwp_package_level_request_mask 0x01
#define cpuid_eax_hwp_package_level_request(_) (((_) >> 11) & 0x01)
			uint32 reserved2 : 1;

			/**
                         * [bit 13] hdc. hdc base registers ia32_pkg_hdc_ctl, ia32_pm_ctl1, ia32_thread_stall msrs are supported if set.
                         */
			uint32 hdc : 1;
#define cpuid_eax_hdc_bit 13
#define cpuid_eax_hdc_flag 0x2000
#define cpuid_eax_hdc_mask 0x01
#define cpuid_eax_hdc(_) (((_) >> 13) & 0x01)

			/**
                         * [bit 14] intel(r) turbo boost max technology 3.0 available.
                         */
			uint32 intelturboboostmaxtechnology3available : 1;
#define cpuid_eax_intel_turbo_boost_max_technology_3_available_bit 14
#define cpuid_eax_intel_turbo_boost_max_technology_3_available_flag 0x4000
#define cpuid_eax_intel_turbo_boost_max_technology_3_available_mask 0x01
#define cpuid_eax_intel_turbo_boost_max_technology_3_available(_) \
	(((_) >> 14) & 0x01)

			/**
                         * [bit 15] hwp capabilities. highest performance change is supported if set.
                         */
			uint32 hwpcapabilities : 1;
#define cpuid_eax_hwp_capabilities_bit 15
#define cpuid_eax_hwp_capabilities_flag 0x8000
#define cpuid_eax_hwp_capabilities_mask 0x01
#define cpuid_eax_hwp_capabilities(_) (((_) >> 15) & 0x01)

			/**
                         * [bit 16] hwp peci override is supported if set.
                         */
			uint32 hwppecioverride : 1;
#define cpuid_eax_hwp_peci_override_bit 16
#define cpuid_eax_hwp_peci_override_flag 0x10000
#define cpuid_eax_hwp_peci_override_mask 0x01
#define cpuid_eax_hwp_peci_override(_) (((_) >> 16) & 0x01)

			/**
                         * [bit 17] flexible hwp is supported if set.
                         */
			uint32 flexiblehwp : 1;
#define cpuid_eax_flexible_hwp_bit 17
#define cpuid_eax_flexible_hwp_flag 0x20000
#define cpuid_eax_flexible_hwp_mask 0x01
#define cpuid_eax_flexible_hwp(_) (((_) >> 17) & 0x01)

			/**
                         * [bit 18] fast access mode for the ia32_hwp_request msr is supported if set.
                         */
			uint32 fastaccessmodeforhwprequestmsr : 1;
#define cpuid_eax_fast_access_mode_for_hwp_request_msr_bit 18
#define cpuid_eax_fast_access_mode_for_hwp_request_msr_flag 0x40000
#define cpuid_eax_fast_access_mode_for_hwp_request_msr_mask 0x01
#define cpuid_eax_fast_access_mode_for_hwp_request_msr(_) (((_) >> 18) & 0x01)
			uint32 reserved3 : 1;

			/**
                         * [bit 20] ignoring idle logical processor hwp request is supported if set.
                         */
			uint32 ignoringidlelogicalprocessorhwprequest : 1;
#define cpuid_eax_ignoring_idle_logical_processor_hwp_request_bit 20
#define cpuid_eax_ignoring_idle_logical_processor_hwp_request_flag 0x100000
#define cpuid_eax_ignoring_idle_logical_processor_hwp_request_mask 0x01
#define cpuid_eax_ignoring_idle_logical_processor_hwp_request(_) \
	(((_) >> 20) & 0x01)
			uint32 reserved4 : 11;
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 3:0] number of interrupt thresholds in digital thermal sensor.
                         */
			uint32 numberofinterruptthresholdsinthermalsensor : 4;
#define cpuid_ebx_number_of_interrupt_thresholds_in_thermal_sensor_bit 0
#define cpuid_ebx_number_of_interrupt_thresholds_in_thermal_sensor_flag 0x0f
#define cpuid_ebx_number_of_interrupt_thresholds_in_thermal_sensor_mask 0x0f
#define cpuid_ebx_number_of_interrupt_thresholds_in_thermal_sensor(_) \
	(((_) >> 0) & 0x0f)
			uint32 reserved1 : 28;
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bit 0] hardware coordination feedback capability (presence of ia32_mperf and ia32_aperf). the capability to provide a
                         * measure of delivered processor performance (since last reset of the counters), as a percentage of the expected processor
                         * performance when running at the tsc frequency.
                         */
			uint32 hardwarecoordinationfeedbackcapability : 1;
#define cpuid_ecx_hardware_coordination_feedback_capability_bit 0
#define cpuid_ecx_hardware_coordination_feedback_capability_flag 0x01
#define cpuid_ecx_hardware_coordination_feedback_capability_mask 0x01
#define cpuid_ecx_hardware_coordination_feedback_capability(_) \
	(((_) >> 0) & 0x01)
			uint32 reserved1 : 2;

			/**
                         * [bit 3] the processor supports performance-energy bias preference if cpuid.06h:ecx.setbh[bit 3] is set and it also
                         * implies the presence of a new architectural msr called ia32_energy_perf_bias (1b0h).
                         */
			uint32 performanceenergybiaspreference : 1;
#define cpuid_ecx_performance_energy_bias_preference_bit 3
#define cpuid_ecx_performance_energy_bias_preference_flag 0x08
#define cpuid_ecx_performance_energy_bias_preference_mask 0x01
#define cpuid_ecx_performance_energy_bias_preference(_) (((_) >> 3) & 0x01)
			uint32 reserved2 : 28;
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] edx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_06;

#define msr_ia32_tsx_ctrl 0x122
#define ia32_arch_capabilities 0x10a
/**
 * @brief structured extended feature flags enumeration leaf (output depends on ecx input value)
 *
 * when cpuid executes with eax set to 07h and ecx = 0, the processor returns information about the maximum input value for
 * sub-leaves that contain extended feature flags.
 * when cpuid executes with eax set to 07h and the input value of ecx is invalid (see leaf 07h entry in table 3-8), the
 * processor returns 0 in eax/ebx/ecx/edx. in subleaf 0, eax returns the maximum input value of the highest leaf 7
 * sub-leaf, and ebx, ecx & edx contain information of extended feature flags.
 */
#define cpuid_structured_extended_feature_flags 0x00000007
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] reports the maximum input value for supported leaf 7 sub-leaves.
                         */
			uint32 numberofsubleaves : 32;
#define cpuid_eax_number_of_sub_leaves_bit 0
#define cpuid_eax_number_of_sub_leaves_flag 0xffffffff
#define cpuid_eax_number_of_sub_leaves_mask 0xffffffff
#define cpuid_eax_number_of_sub_leaves(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bit 0] supports rdfsbase/rdgsbase/wrfsbase/wrgsbase if 1.
                         */
			uint32 fsgsbase : 1;
#define cpuid_ebx_fsgsbase_bit 0
#define cpuid_ebx_fsgsbase_flag 0x01
#define cpuid_ebx_fsgsbase_mask 0x01
#define cpuid_ebx_fsgsbase(_) (((_) >> 0) & 0x01)

			/**
                         * [bit 1] ia32_tsc_adjust msr is supported if 1.
                         */
			uint32 ia32tscadjustmsr : 1;
#define cpuid_ebx_ia32_tsc_adjust_msr_bit 1
#define cpuid_ebx_ia32_tsc_adjust_msr_flag 0x02
#define cpuid_ebx_ia32_tsc_adjust_msr_mask 0x01
#define cpuid_ebx_ia32_tsc_adjust_msr(_) (((_) >> 1) & 0x01)

			/**
                         * [bit 2] supports intel(r) software guard extensions (intel(r) sgx extensions) if 1.
                         */
			uint32 sgx : 1;
#define cpuid_ebx_sgx_bit 2
#define cpuid_ebx_sgx_flag 0x04
#define cpuid_ebx_sgx_mask 0x01
#define cpuid_ebx_sgx(_) (((_) >> 2) & 0x01)

			/**
                         * [bit 3] bmi1.
                         */
			uint32 bmi1 : 1;
#define cpuid_ebx_bmi1_bit 3
#define cpuid_ebx_bmi1_flag 0x08
#define cpuid_ebx_bmi1_mask 0x01
#define cpuid_ebx_bmi1(_) (((_) >> 3) & 0x01)

			/**
                         * [bit 4] hle.
                         */
			uint32 hle : 1;
#define cpuid_ebx_hle_bit 4
#define cpuid_ebx_hle_flag 0x10
#define cpuid_ebx_hle_mask 0x01
#define cpuid_ebx_hle(_) (((_) >> 4) & 0x01)

			/**
                         * [bit 5] avx2.
                         */
			uint32 avx2 : 1;
#define cpuid_ebx_avx2_bit 5
#define cpuid_ebx_avx2_flag 0x20
#define cpuid_ebx_avx2_mask 0x01
#define cpuid_ebx_avx2(_) (((_) >> 5) & 0x01)

			/**
                         * [bit 6] x87 fpu data pointer updated only on x87 exceptions if 1.
                         */
			uint32 fdpexcptnonly : 1;
#define cpuid_ebx_fdp_excptn_only_bit 6
#define cpuid_ebx_fdp_excptn_only_flag 0x40
#define cpuid_ebx_fdp_excptn_only_mask 0x01
#define cpuid_ebx_fdp_excptn_only(_) (((_) >> 6) & 0x01)

			/**
                         * [bit 7] supports supervisor-mode execution prevention if 1.
                         */
			uint32 smep : 1;
#define cpuid_ebx_smep_bit 7
#define cpuid_ebx_smep_flag 0x80
#define cpuid_ebx_smep_mask 0x01
#define cpuid_ebx_smep(_) (((_) >> 7) & 0x01)

			/**
                         * [bit 8] bmi2.
                         */
			uint32 bmi2 : 1;
#define cpuid_ebx_bmi2_bit 8
#define cpuid_ebx_bmi2_flag 0x100
#define cpuid_ebx_bmi2_mask 0x01
#define cpuid_ebx_bmi2(_) (((_) >> 8) & 0x01)

			/**
                         * [bit 9] supports enhanced rep movsb/stosb if 1.
                         */
			uint32 enhancedrepmovsbstosb : 1;
#define cpuid_ebx_enhanced_rep_movsb_stosb_bit 9
#define cpuid_ebx_enhanced_rep_movsb_stosb_flag 0x200
#define cpuid_ebx_enhanced_rep_movsb_stosb_mask 0x01
#define cpuid_ebx_enhanced_rep_movsb_stosb(_) (((_) >> 9) & 0x01)

			/**
                         * [bit 10] if 1, supports invpcid instruction for system software that manages process-context identifiers.
                         */
			uint32 invpcid : 1;
#define cpuid_ebx_invpcid_bit 10
#define cpuid_ebx_invpcid_flag 0x400
#define cpuid_ebx_invpcid_mask 0x01
#define cpuid_ebx_invpcid(_) (((_) >> 10) & 0x01)

			/**
                         * [bit 11] rtm.
                         */
			uint32 rtm : 1;
#define cpuid_ebx_rtm_bit 11
#define cpuid_ebx_rtm_flag 0x800
#define cpuid_ebx_rtm_mask 0x01
#define cpuid_ebx_rtm(_) (((_) >> 11) & 0x01)

			/**
                         * [bit 12] supports intel(r) resource director technology (intel(r) rdt) monitoring capability if 1.
                         */
			uint32 rdtm : 1;
#define cpuid_ebx_rdt_m_bit 12
#define cpuid_ebx_rdt_m_flag 0x1000
#define cpuid_ebx_rdt_m_mask 0x01
#define cpuid_ebx_rdt_m(_) (((_) >> 12) & 0x01)

			/**
                         * [bit 13] deprecates fpu cs and fpu ds values if 1.
                         */
			uint32 deprecates : 1;
#define cpuid_ebx_deprecates_bit 13
#define cpuid_ebx_deprecates_flag 0x2000
#define cpuid_ebx_deprecates_mask 0x01
#define cpuid_ebx_deprecates(_) (((_) >> 13) & 0x01)

			/**
                         * [bit 14] supports intel(r) memory protection extensions if 1.
                         */
			uint32 mpx : 1;
#define cpuid_ebx_mpx_bit 14
#define cpuid_ebx_mpx_flag 0x4000
#define cpuid_ebx_mpx_mask 0x01
#define cpuid_ebx_mpx(_) (((_) >> 14) & 0x01)

			/**
                         * [bit 15] supports intel(r) resource director technology (intel(r) rdt) allocation capability if 1.
                         */
			uint32 rdt : 1;
#define cpuid_ebx_rdt_bit 15
#define cpuid_ebx_rdt_flag 0x8000
#define cpuid_ebx_rdt_mask 0x01
#define cpuid_ebx_rdt(_) (((_) >> 15) & 0x01)

			/**
                         * [bit 16] avx512f.
                         */
			uint32 avx512f : 1;
#define cpuid_ebx_avx512f_bit 16
#define cpuid_ebx_avx512f_flag 0x10000
#define cpuid_ebx_avx512f_mask 0x01
#define cpuid_ebx_avx512f(_) (((_) >> 16) & 0x01)

			/**
                         * [bit 17] avx512dq.
                         */
			uint32 avx512dq : 1;
#define cpuid_ebx_avx512dq_bit 17
#define cpuid_ebx_avx512dq_flag 0x20000
#define cpuid_ebx_avx512dq_mask 0x01
#define cpuid_ebx_avx512dq(_) (((_) >> 17) & 0x01)

			/**
                         * [bit 18] rdseed.
                         */
			uint32 rdseed : 1;
#define cpuid_ebx_rdseed_bit 18
#define cpuid_ebx_rdseed_flag 0x40000
#define cpuid_ebx_rdseed_mask 0x01
#define cpuid_ebx_rdseed(_) (((_) >> 18) & 0x01)

			/**
                         * [bit 19] adx.
                         */
			uint32 adx : 1;
#define cpuid_ebx_adx_bit 19
#define cpuid_ebx_adx_flag 0x80000
#define cpuid_ebx_adx_mask 0x01
#define cpuid_ebx_adx(_) (((_) >> 19) & 0x01)

			/**
                         * [bit 20] supports supervisor-mode access prevention (and the clac/stac instructions) if 1.
                         */
			uint32 smap : 1;
#define cpuid_ebx_smap_bit 20
#define cpuid_ebx_smap_flag 0x100000
#define cpuid_ebx_smap_mask 0x01
#define cpuid_ebx_smap(_) (((_) >> 20) & 0x01)

			/**
                         * [bit 21] avx512_ifma.
                         */
			uint32 avx512ifma : 1;
#define cpuid_ebx_avx512_ifma_bit 21
#define cpuid_ebx_avx512_ifma_flag 0x200000
#define cpuid_ebx_avx512_ifma_mask 0x01
#define cpuid_ebx_avx512_ifma(_) (((_) >> 21) & 0x01)
			uint32 reserved1 : 1;

			/**
                         * [bit 23] clflushopt.
                         */
			uint32 clflushopt : 1;
#define cpuid_ebx_clflushopt_bit 23
#define cpuid_ebx_clflushopt_flag 0x800000
#define cpuid_ebx_clflushopt_mask 0x01
#define cpuid_ebx_clflushopt(_) (((_) >> 23) & 0x01)

			/**
                         * [bit 24] clwb.
                         */
			uint32 clwb : 1;
#define cpuid_ebx_clwb_bit 24
#define cpuid_ebx_clwb_flag 0x1000000
#define cpuid_ebx_clwb_mask 0x01
#define cpuid_ebx_clwb(_) (((_) >> 24) & 0x01)

			/**
                         * [bit 25] intel processor trace.
                         */
			uint32 intel : 1;
#define cpuid_ebx_intel_bit 25
#define cpuid_ebx_intel_flag 0x2000000
#define cpuid_ebx_intel_mask 0x01
#define cpuid_ebx_intel(_) (((_) >> 25) & 0x01)

			/**
                         * [bit 26] (intel(r) xeon phi(tm) only).
                         */
			uint32 avx512pf : 1;
#define cpuid_ebx_avx512pf_bit 26
#define cpuid_ebx_avx512pf_flag 0x4000000
#define cpuid_ebx_avx512pf_mask 0x01
#define cpuid_ebx_avx512pf(_) (((_) >> 26) & 0x01)

			/**
                         * [bit 27] (intel(r) xeon phi(tm) only).
                         */
			uint32 avx512er : 1;
#define cpuid_ebx_avx512er_bit 27
#define cpuid_ebx_avx512er_flag 0x8000000
#define cpuid_ebx_avx512er_mask 0x01
#define cpuid_ebx_avx512er(_) (((_) >> 27) & 0x01)

			/**
                         * [bit 28] avx512cd.
                         */
			uint32 avx512cd : 1;
#define cpuid_ebx_avx512cd_bit 28
#define cpuid_ebx_avx512cd_flag 0x10000000
#define cpuid_ebx_avx512cd_mask 0x01
#define cpuid_ebx_avx512cd(_) (((_) >> 28) & 0x01)

			/**
                         * [bit 29] supports intel(r) secure hash algorithm extensions (intel(r) sha extensions) if 1.
                         */
			uint32 sha : 1;
#define cpuid_ebx_sha_bit 29
#define cpuid_ebx_sha_flag 0x20000000
#define cpuid_ebx_sha_mask 0x01
#define cpuid_ebx_sha(_) (((_) >> 29) & 0x01)

			/**
                         * [bit 30] avx512bw.
                         */
			uint32 avx512bw : 1;
#define cpuid_ebx_avx512bw_bit 30
#define cpuid_ebx_avx512bw_flag 0x40000000
#define cpuid_ebx_avx512bw_mask 0x01
#define cpuid_ebx_avx512bw(_) (((_) >> 30) & 0x01)

			/**
                         * [bit 31] avx512vl.
                         */
			uint32 avx512vl : 1;
#define cpuid_ebx_avx512vl_bit 31
#define cpuid_ebx_avx512vl_flag 0x80000000
#define cpuid_ebx_avx512vl_mask 0x01
#define cpuid_ebx_avx512vl(_) (((_) >> 31) & 0x01)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bit 0] (intel(r) xeon phi(tm) only).
                         */
			uint32 prefetchwt1 : 1;
#define cpuid_ecx_prefetchwt1_bit 0
#define cpuid_ecx_prefetchwt1_flag 0x01
#define cpuid_ecx_prefetchwt1_mask 0x01
#define cpuid_ecx_prefetchwt1(_) (((_) >> 0) & 0x01)

			/**
                         * [bit 1] avx512_vbmi.
                         */
			uint32 avx512vbmi : 1;
#define cpuid_ecx_avx512_vbmi_bit 1
#define cpuid_ecx_avx512_vbmi_flag 0x02
#define cpuid_ecx_avx512_vbmi_mask 0x01
#define cpuid_ecx_avx512_vbmi(_) (((_) >> 1) & 0x01)

			/**
                         * [bit 2] supports user-mode instruction prevention if 1.
                         */
			uint32 umip : 1;
#define cpuid_ecx_umip_bit 2
#define cpuid_ecx_umip_flag 0x04
#define cpuid_ecx_umip_mask 0x01
#define cpuid_ecx_umip(_) (((_) >> 2) & 0x01)

			/**
                         * [bit 3] supports protection keys for user-mode pages if 1.
                         */
			uint32 pku : 1;
#define cpuid_ecx_pku_bit 3
#define cpuid_ecx_pku_flag 0x08
#define cpuid_ecx_pku_mask 0x01
#define cpuid_ecx_pku(_) (((_) >> 3) & 0x01)

			/**
                         * [bit 4] if 1, os has set cr4.pke to enable protection keys (and the rdpkru/wrpkru instructions).
                         */
			uint32 ospke : 1;
#define cpuid_ecx_ospke_bit 4
#define cpuid_ecx_ospke_flag 0x10
#define cpuid_ecx_ospke_mask 0x01
#define cpuid_ecx_ospke(_) (((_) >> 4) & 0x01)
			uint32 reserved1 : 12;

			/**
                         * [bits 21:17] the value of mawau used by the bndldx and bndstx instructions in 64-bit mode.
                         */
			uint32 mawau : 5;
#define cpuid_ecx_mawau_bit 17
#define cpuid_ecx_mawau_flag 0x3e0000
#define cpuid_ecx_mawau_mask 0x1f
#define cpuid_ecx_mawau(_) (((_) >> 17) & 0x1f)

			/**
                         * [bit 22] rdpid and ia32_tsc_aux are available if 1.
                         */
			uint32 rdpid : 1;
#define cpuid_ecx_rdpid_bit 22
#define cpuid_ecx_rdpid_flag 0x400000
#define cpuid_ecx_rdpid_mask 0x01
#define cpuid_ecx_rdpid(_) (((_) >> 22) & 0x01)
			uint32 reserved2 : 7;

			/**
                         * [bit 30] supports sgx launch configuration if 1.
                         */
			uint32 sgxlc : 1;
#define cpuid_ecx_sgx_lc_bit 30
#define cpuid_ecx_sgx_lc_flag 0x40000000
#define cpuid_ecx_sgx_lc_mask 0x01
#define cpuid_ecx_sgx_lc(_) (((_) >> 30) & 0x01)
			uint32 reserved3 : 1;
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] edx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_07;

/**
 * @brief direct cache access information leaf
 *
 * when cpuid executes with eax set to 09h, the processor returns information about direct cache access capabilities.
 */
#define cpuid_direct_cache_access_information 0x00000009
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] value of bits [31:0] of ia32_platform_dca_cap msr (address 1f8h).
                         */
			uint32 ia32platformdcacap : 32;
#define cpuid_eax_ia32_platform_dca_cap_bit 0
#define cpuid_eax_ia32_platform_dca_cap_flag 0xffffffff
#define cpuid_eax_ia32_platform_dca_cap_mask 0xffffffff
#define cpuid_eax_ia32_platform_dca_cap(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] ebx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ebx_reserved_bit 0
#define cpuid_ebx_reserved_flag 0xffffffff
#define cpuid_ebx_reserved_mask 0xffffffff
#define cpuid_ebx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] ecx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ecx_reserved_bit 0
#define cpuid_ecx_reserved_flag 0xffffffff
#define cpuid_ecx_reserved_mask 0xffffffff
#define cpuid_ecx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] edx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_09;

/**
 * @brief architectural performance monitoring leaf
 *
 * when cpuid executes with eax set to 0ah, the processor returns information about support for architectural performance
 * monitoring capabilities. architectural performance monitoring is supported if the version id is greater than pn 0. for
 * each version of architectural performance monitoring capability, software must enumerate this leaf to discover the
 * programming facilities and the architectural performance events available in the processor.
 *
 * @see vol3c[23(introduction to virtual-machine extensions)]
 */
#define cpuid_architectural_performance_monitoring 0x0000000a
typedef struct {
	union {
		struct {
			/**
                         * [bits 7:0] version id of architectural performance monitoring.
                         */
			uint32 versionidofarchitecturalperformancemonitoring : 8;
#define cpuid_eax_version_id_of_architectural_performance_monitoring_bit 0
#define cpuid_eax_version_id_of_architectural_performance_monitoring_flag 0xff
#define cpuid_eax_version_id_of_architectural_performance_monitoring_mask 0xff
#define cpuid_eax_version_id_of_architectural_performance_monitoring(_) \
	(((_) >> 0) & 0xff)

			/**
                         * [bits 15:8] number of general-purpose performance monitoring counter per logical processor.
                         */
			uint32 numberofperformancemonitoringcounterperlogicalprocessor : 8;
#define cpuid_eax_number_of_performance_monitoring_counter_per_logical_processor_bit \
	8
#define cpuid_eax_number_of_performance_monitoring_counter_per_logical_processor_flag \
	0xff00
#define cpuid_eax_number_of_performance_monitoring_counter_per_logical_processor_mask \
	0xff
#define cpuid_eax_number_of_performance_monitoring_counter_per_logical_processor( \
	_)                                                                        \
	(((_) >> 8) & 0xff)

			/**
                         * [bits 23:16] bit width of general-purpose, performance monitoring counter.
                         */
			uint32 bitwidthofperformancemonitoringcounter : 8;
#define cpuid_eax_bit_width_of_performance_monitoring_counter_bit 16
#define cpuid_eax_bit_width_of_performance_monitoring_counter_flag 0xff0000
#define cpuid_eax_bit_width_of_performance_monitoring_counter_mask 0xff
#define cpuid_eax_bit_width_of_performance_monitoring_counter(_) \
	(((_) >> 16) & 0xff)

			/**
                         * [bits 31:24] length of ebx bit list to enumerate architectural performance monitoring events.
                         */
			uint32 ebxbitlistlength : 8;
#define cpuid_eax_ebx_bit_list_length_bit 24
#define cpuid_eax_ebx_bit_list_length_flag 0xff000000
#define cpuid_eax_ebx_bit_list_length_mask 0xff
#define cpuid_eax_ebx_bit_list_length(_) (((_) >> 24) & 0xff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bit 0] core cycle event not available if 1.
                         */
			uint32 corecycleeventnotavailable : 1;
#define cpuid_ebx_core_cycle_event_not_available_bit 0
#define cpuid_ebx_core_cycle_event_not_available_flag 0x01
#define cpuid_ebx_core_cycle_event_not_available_mask 0x01
#define cpuid_ebx_core_cycle_event_not_available(_) (((_) >> 0) & 0x01)

			/**
                         * [bit 1] instruction retired event not available if 1.
                         */
			uint32 instructionretiredeventnotavailable : 1;
#define cpuid_ebx_instruction_retired_event_not_available_bit 1
#define cpuid_ebx_instruction_retired_event_not_available_flag 0x02
#define cpuid_ebx_instruction_retired_event_not_available_mask 0x01
#define cpuid_ebx_instruction_retired_event_not_available(_) (((_) >> 1) & 0x01)

			/**
                         * [bit 2] reference cycles event not available if 1.
                         */
			uint32 referencecycleseventnotavailable : 1;
#define cpuid_ebx_reference_cycles_event_not_available_bit 2
#define cpuid_ebx_reference_cycles_event_not_available_flag 0x04
#define cpuid_ebx_reference_cycles_event_not_available_mask 0x01
#define cpuid_ebx_reference_cycles_event_not_available(_) (((_) >> 2) & 0x01)

			/**
                         * [bit 3] last-level cache reference event not available if 1.
                         */
			uint32 lastlevelcachereferenceeventnotavailable : 1;
#define cpuid_ebx_last_level_cache_reference_event_not_available_bit 3
#define cpuid_ebx_last_level_cache_reference_event_not_available_flag 0x08
#define cpuid_ebx_last_level_cache_reference_event_not_available_mask 0x01
#define cpuid_ebx_last_level_cache_reference_event_not_available(_) \
	(((_) >> 3) & 0x01)

			/**
                         * [bit 4] last-level cache misses event not available if 1.
                         */
			uint32 lastlevelcachemisseseventnotavailable : 1;
#define cpuid_ebx_last_level_cache_misses_event_not_available_bit 4
#define cpuid_ebx_last_level_cache_misses_event_not_available_flag 0x10
#define cpuid_ebx_last_level_cache_misses_event_not_available_mask 0x01
#define cpuid_ebx_last_level_cache_misses_event_not_available(_) \
	(((_) >> 4) & 0x01)

			/**
                         * [bit 5] branch instruction retired event not available if 1.
                         */
			uint32 branchinstructionretiredeventnotavailable : 1;
#define cpuid_ebx_branch_instruction_retired_event_not_available_bit 5
#define cpuid_ebx_branch_instruction_retired_event_not_available_flag 0x20
#define cpuid_ebx_branch_instruction_retired_event_not_available_mask 0x01
#define cpuid_ebx_branch_instruction_retired_event_not_available(_) \
	(((_) >> 5) & 0x01)

			/**
                         * [bit 6] branch mispredict retired event not available if 1.
                         */
			uint32 branchmispredictretiredeventnotavailable : 1;
#define cpuid_ebx_branch_mispredict_retired_event_not_available_bit 6
#define cpuid_ebx_branch_mispredict_retired_event_not_available_flag 0x40
#define cpuid_ebx_branch_mispredict_retired_event_not_available_mask 0x01
#define cpuid_ebx_branch_mispredict_retired_event_not_available(_) \
	(((_) >> 6) & 0x01)
			uint32 reserved1 : 25;
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] ecx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ecx_reserved_bit 0
#define cpuid_ecx_reserved_flag 0xffffffff
#define cpuid_ecx_reserved_mask 0xffffffff
#define cpuid_ecx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 4:0] number of fixed-function performance counters (if version id > 1).
                         */
			uint32 numberoffixedfunctionperformancecounters : 5;
#define cpuid_edx_number_of_fixed_function_performance_counters_bit 0
#define cpuid_edx_number_of_fixed_function_performance_counters_flag 0x1f
#define cpuid_edx_number_of_fixed_function_performance_counters_mask 0x1f
#define cpuid_edx_number_of_fixed_function_performance_counters(_) \
	(((_) >> 0) & 0x1f)

			/**
                         * [bits 12:5] bit width of fixed-function performance counters (if version id > 1).
                         */
			uint32 bitwidthoffixedfunctionperformancecounters : 8;
#define cpuid_edx_bit_width_of_fixed_function_performance_counters_bit 5
#define cpuid_edx_bit_width_of_fixed_function_performance_counters_flag 0x1fe0
#define cpuid_edx_bit_width_of_fixed_function_performance_counters_mask 0xff
#define cpuid_edx_bit_width_of_fixed_function_performance_counters(_) \
	(((_) >> 5) & 0xff)
			uint32 reserved1 : 2;

			/**
                         * [bit 15] anythread deprecation.
                         */
			uint32 anythreaddeprecation : 1;
#define cpuid_edx_any_thread_deprecation_bit 15
#define cpuid_edx_any_thread_deprecation_flag 0x8000
#define cpuid_edx_any_thread_deprecation_mask 0x01
#define cpuid_edx_any_thread_deprecation(_) (((_) >> 15) & 0x01)
			uint32 reserved2 : 16;
		};

		uint32 flags;
	} edx;

} cpuid_eax_0a;

/**
 * @brief extended topology enumeration leaf
 *
 * when cpuid executes with eax set to 0bh, the processor returns information about extended topology enumeration data.
 * software must detect the presence of cpuid leaf 0bh by verifying
 * - the highest leaf index supported by cpuid is >= 0bh, and
 * - cpuid.0bh:ebx[15:0] reports a non-zero value.
 *
 * @note most of leaf 0bh output depends on the initial value in ecx. the edx output of leaf 0bh is always valid and does
 *       not vary with input value in ecx. output value in ecx[7:0] always equals input value in ecx[7:0]. sub-leaf index 0
 *       enumerates smt level. each subsequent higher sub-leaf index enumerates a higherlevel topological entity in hierarchical
 *       order. for sub-leaves that return an invalid level-type of 0 in ecx[15:8]; eax and ebx will return 0. if an input value
 *       n in ecx returns the invalid level-type of 0 in ecx[15:8], other input values with ecx > n also return 0 in ecx[15:8].
 */
#define cpuid_extended_topology 0x0000000b
typedef struct {
	union {
		struct {
			/**
                         * [bits 4:0] number of bits to shift right on x2apic id to get a unique topology id of the next level type. all logical
                         * processors with the same next level id share current level.
                         *
                         * @note software should use this field (eax[4:0]) to enumerate processor topology of the system.
                         */
			uint32 x2apicidtouniquetopologyidshift : 5;
#define cpuid_eax_x2apic_id_to_unique_topology_id_shift_bit 0
#define cpuid_eax_x2apic_id_to_unique_topology_id_shift_flag 0x1f
#define cpuid_eax_x2apic_id_to_unique_topology_id_shift_mask 0x1f
#define cpuid_eax_x2apic_id_to_unique_topology_id_shift(_) (((_) >> 0) & 0x1f)
			uint32 reserved1 : 27;
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 15:0] number of logical processors at this level type. the number reflects configuration as shipped by intel.
                         *
                         * @note software must not use ebx[15:0] to enumerate processor topology of the system. this value in this field
                         *       (ebx[15:0]) is only intended for display/diagnostic purposes. the actual number of logical processors available to
                         *       bios/os/applications may be different from the value of ebx[15:0], depending on software and platform hardware
                         *       configurations.
                         */
			uint32 numberoflogicalprocessorsatthisleveltype : 16;
#define cpuid_ebx_number_of_logical_processors_at_this_level_type_bit 0
#define cpuid_ebx_number_of_logical_processors_at_this_level_type_flag 0xffff
#define cpuid_ebx_number_of_logical_processors_at_this_level_type_mask 0xffff
#define cpuid_ebx_number_of_logical_processors_at_this_level_type(_) \
	(((_) >> 0) & 0xffff)
			uint32 reserved1 : 16;
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 7:0] level number. same value in ecx input.
                         */
			uint32 levelnumber : 8;
#define cpuid_ecx_level_number_bit 0
#define cpuid_ecx_level_number_flag 0xff
#define cpuid_ecx_level_number_mask 0xff
#define cpuid_ecx_level_number(_) (((_) >> 0) & 0xff)

			/**
                         * [bits 15:8] level type.
                         *
                         * @note the value of the "level type" field is not related to level numbers in any way, higher "level type" values do not
                         *       mean higher levels. level type field has the following encoding:
                         *       - 0: invalid.
                         *       - 1: smt.
                         *       - 2: core.
                         *       - 3-255: reserved.
                         */
			uint32 leveltype : 8;
#define cpuid_ecx_level_type_bit 8
#define cpuid_ecx_level_type_flag 0xff00
#define cpuid_ecx_level_type_mask 0xff
#define cpuid_ecx_level_type(_) (((_) >> 8) & 0xff)
			uint32 reserved1 : 16;
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] x2apic id the current logical processor.
                         */
			uint32 x2apicid : 32;
#define cpuid_edx_x2apic_id_bit 0
#define cpuid_edx_x2apic_id_flag 0xffffffff
#define cpuid_edx_x2apic_id_mask 0xffffffff
#define cpuid_edx_x2apic_id(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_0b;

/**
 * @defgroup cpuid_eax_0d \
 *           eax = 0x0d
 *
 * when cpuid executes with eax set to 0dh and ecx = 0, the processor returns information about the bit-list
 * representation of all processor state extensions that are supported in the processor and storage size requirements of
 * the xsave/xrstor area.
 * when cpuid executes with eax set to 0dh and ecx = n (n > 1, and is a valid sub-leaf index), the processor returns
 * information about the size and offset of each processor extended state save area within the xsave/xrstor area. software
 * can use the forward-extendable technique depicted below to query the valid sub-leaves and obtain size and offset
 * information for each processor extended state save area:
 * <pre> for i = 2 to 62 // sub-leaf 1 is reserved if (cpuid.(eax=0dh, ecx=0):list[i] = 1) // list is the 64-bit value
 * of edx:eax execute cpuid.(eax=0dh, ecx = i) to examine size and offset for sub-leaf i; fi; </pre>
 * @{
 */
#define cpuid_extended_state_information 0x0000000d
/**
 * @brief processor extended state enumeration main leaf (eax = 0dh, ecx = 0)
 */
typedef struct {
	/**
         * @brief reports the supported bits of the lower 32 bits of xcr0. xcr0[n] can be set to 1 only if eax[n] is 1
         */
	union {
		struct {
			/**
                         * [bit 0] x87 state.
                         */
			uint32 x87state : 1;
#define cpuid_eax_x87_state_bit 0
#define cpuid_eax_x87_state_flag 0x01
#define cpuid_eax_x87_state_mask 0x01
#define cpuid_eax_x87_state(_) (((_) >> 0) & 0x01)

			/**
                         * [bit 1] sse state.
                         */
			uint32 ssestate : 1;
#define cpuid_eax_sse_state_bit 1
#define cpuid_eax_sse_state_flag 0x02
#define cpuid_eax_sse_state_mask 0x01
#define cpuid_eax_sse_state(_) (((_) >> 1) & 0x01)

			/**
                         * [bit 2] avx state.
                         */
			uint32 avxstate : 1;
#define cpuid_eax_avx_state_bit 2
#define cpuid_eax_avx_state_flag 0x04
#define cpuid_eax_avx_state_mask 0x01
#define cpuid_eax_avx_state(_) (((_) >> 2) & 0x01)

			/**
                         * [bits 4:3] mpx state.
                         */
			uint32 mpxstate : 2;
#define cpuid_eax_mpx_state_bit 3
#define cpuid_eax_mpx_state_flag 0x18
#define cpuid_eax_mpx_state_mask 0x03
#define cpuid_eax_mpx_state(_) (((_) >> 3) & 0x03)

			/**
                         * [bits 7:5] avx-512 state.
                         */
			uint32 avx512state : 3;
#define cpuid_eax_avx_512_state_bit 5
#define cpuid_eax_avx_512_state_flag 0xe0
#define cpuid_eax_avx_512_state_mask 0x07
#define cpuid_eax_avx_512_state(_) (((_) >> 5) & 0x07)

			/**
                         * [bit 8] used for ia32_xss.
                         */
			uint32 usedforia32xss1 : 1;
#define cpuid_eax_used_for_ia32_xss_1_bit 8
#define cpuid_eax_used_for_ia32_xss_1_flag 0x100
#define cpuid_eax_used_for_ia32_xss_1_mask 0x01
#define cpuid_eax_used_for_ia32_xss_1(_) (((_) >> 8) & 0x01)

			/**
                         * [bit 9] pkru state.
                         */
			uint32 pkrustate : 1;
#define cpuid_eax_pkru_state_bit 9
#define cpuid_eax_pkru_state_flag 0x200
#define cpuid_eax_pkru_state_mask 0x01
#define cpuid_eax_pkru_state(_) (((_) >> 9) & 0x01)
			uint32 reserved1 : 3;

			/**
                         * [bit 13] used for ia32_xss.
                         */
			uint32 usedforia32xss2 : 1;
#define cpuid_eax_used_for_ia32_xss_2_bit 13
#define cpuid_eax_used_for_ia32_xss_2_flag 0x2000
#define cpuid_eax_used_for_ia32_xss_2_mask 0x01
#define cpuid_eax_used_for_ia32_xss_2(_) (((_) >> 13) & 0x01)
			uint32 reserved2 : 18;
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] maximum size (bytes, from the beginning of the xsave/xrstor save area) required by enabled features in xcr0.
                         * may be different than ecx if some features at the end of the xsave save area are not enabled.
                         */
			uint32 maxsizerequiredbyenabledfeaturesinxcr0 : 32;
#define cpuid_ebx_max_size_required_by_enabled_features_in_xcr0_bit 0
#define cpuid_ebx_max_size_required_by_enabled_features_in_xcr0_flag 0xffffffff
#define cpuid_ebx_max_size_required_by_enabled_features_in_xcr0_mask 0xffffffff
#define cpuid_ebx_max_size_required_by_enabled_features_in_xcr0(_) \
	(((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] maximum size (bytes, from the beginning of the xsave/xrstor save area) of the xsave/xrstor save area
                         * required by all supported features in the processor, i.e., all the valid bit fields in xcr0.
                         */
			uint32 maxsizeofxsavexrstorsavearea : 32;
#define cpuid_ecx_max_size_of_xsave_xrstor_save_area_bit 0
#define cpuid_ecx_max_size_of_xsave_xrstor_save_area_flag 0xffffffff
#define cpuid_ecx_max_size_of_xsave_xrstor_save_area_mask 0xffffffff
#define cpuid_ecx_max_size_of_xsave_xrstor_save_area(_) \
	(((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] reports the supported bits of the upper 32 bits of xcr0. xcr0[n+32] can be set to 1 only if edx[n] is 1.
                         */
			uint32 xcr0supportedbits : 32;
#define cpuid_edx_xcr0_supported_bits_bit 0
#define cpuid_edx_xcr0_supported_bits_flag 0xffffffff
#define cpuid_edx_xcr0_supported_bits_mask 0xffffffff
#define cpuid_edx_xcr0_supported_bits(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_0d_ecx_00;

/**
 * @brief direct cache access information leaf
 */
typedef struct {
	union {
		struct {
			uint32 reserved1 : 1;

			/**
                         * [bit 1] supports xsavec and the compacted form of xrstor if set.
                         */
			uint32 supportsxsavecandcompactedxrstor : 1;
#define cpuid_eax_supports_xsavec_and_compacted_xrstor_bit 1
#define cpuid_eax_supports_xsavec_and_compacted_xrstor_flag 0x02
#define cpuid_eax_supports_xsavec_and_compacted_xrstor_mask 0x01
#define cpuid_eax_supports_xsavec_and_compacted_xrstor(_) (((_) >> 1) & 0x01)

			/**
                         * [bit 2] supports xgetbv with ecx = 1 if set.
                         */
			uint32 supportsxgetbvwithecx1 : 1;
#define cpuid_eax_supports_xgetbv_with_ecx_1_bit 2
#define cpuid_eax_supports_xgetbv_with_ecx_1_flag 0x04
#define cpuid_eax_supports_xgetbv_with_ecx_1_mask 0x01
#define cpuid_eax_supports_xgetbv_with_ecx_1(_) (((_) >> 2) & 0x01)

			/**
                         * [bit 3] supports xsaves/xrstors and ia32_xss if set.
                         */
			uint32 supportsxsavexrstorandia32xss : 1;
#define cpuid_eax_supports_xsave_xrstor_and_ia32_xss_bit 3
#define cpuid_eax_supports_xsave_xrstor_and_ia32_xss_flag 0x08
#define cpuid_eax_supports_xsave_xrstor_and_ia32_xss_mask 0x01
#define cpuid_eax_supports_xsave_xrstor_and_ia32_xss(_) (((_) >> 3) & 0x01)
			uint32 reserved2 : 28;
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] the size in bytes of the xsave area containing all states enabled by xcro | ia32_xss.
                         */
			uint32 sizeofxsavearead : 32;
#define cpuid_ebx_size_of_xsave_aread_bit 0
#define cpuid_ebx_size_of_xsave_aread_flag 0xffffffff
#define cpuid_ebx_size_of_xsave_aread_mask 0xffffffff
#define cpuid_ebx_size_of_xsave_aread(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 7:0] used for xcr0.
                         */
			uint32 usedforxcr01 : 8;
#define cpuid_ecx_used_for_xcr0_1_bit 0
#define cpuid_ecx_used_for_xcr0_1_flag 0xff
#define cpuid_ecx_used_for_xcr0_1_mask 0xff
#define cpuid_ecx_used_for_xcr0_1(_) (((_) >> 0) & 0xff)

			/**
                         * [bit 8] pt state.
                         */
			uint32 ptstate : 1;
#define cpuid_ecx_pt_state_bit 8
#define cpuid_ecx_pt_state_flag 0x100
#define cpuid_ecx_pt_state_mask 0x01
#define cpuid_ecx_pt_state(_) (((_) >> 8) & 0x01)

			/**
                         * [bit 9] used for xcr0.
                         */
			uint32 usedforxcr02 : 1;
#define cpuid_ecx_used_for_xcr0_2_bit 9
#define cpuid_ecx_used_for_xcr0_2_flag 0x200
#define cpuid_ecx_used_for_xcr0_2_mask 0x01
#define cpuid_ecx_used_for_xcr0_2(_) (((_) >> 9) & 0x01)
			uint32 reserved1 : 3;

			/**
                         * [bit 13] hwp state.
                         */
			uint32 hwpstate : 1;
#define cpuid_ecx_hwp_state_bit 13
#define cpuid_ecx_hwp_state_flag 0x2000
#define cpuid_ecx_hwp_state_mask 0x01
#define cpuid_ecx_hwp_state(_) (((_) >> 13) & 0x01)
			uint32 reserved2 : 18;
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] edx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_0d_ecx_01;

/**
 * @brief processor extended state enumeration sub-leaves (eax = 0dh, ecx = n, n > 1)
 *
 * @note leaf 0dh output depends on the initial value in ecx. each sub-leaf index (starting at position 2) is supported if
 *       it corresponds to a supported bit in either the xcr0 register or the ia32_xss msr.
 *       if ecx contains an invalid sub-leaf index, eax/ebx/ecx/edx return 0. sub-leaf n (0 <= n <= 31) is invalid if sub-leaf 0
 *       returns 0 in eax[n] and sub-leaf 1 returns 0 in ecx[n]. sub-leaf n (32 <= n <= 63) is invalid if sub-leaf 0 returns 0 in
 *       edx[n-32] and sub-leaf 1 returns 0 in edx[n-32].
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] the size in bytes (from the offset specified in ebx) of the save area for an extended state feature
                         * associated with a valid sub-leaf index, n.
                         */
			uint32 ia32platformdcacap : 32;
#define cpuid_eax_ia32_platform_dca_cap_bit 0
#define cpuid_eax_ia32_platform_dca_cap_flag 0xffffffff
#define cpuid_eax_ia32_platform_dca_cap_mask 0xffffffff
#define cpuid_eax_ia32_platform_dca_cap(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] the offset in bytes of this extended state component's save area from the beginning of the xsave/xrstor
                         * area.
                         * this field reports 0 if the sub-leaf index, n, does not map to a valid bit in the xcr0 register.
                         */
			uint32 reserved : 32;
#define cpuid_ebx_reserved_bit 0
#define cpuid_ebx_reserved_flag 0xffffffff
#define cpuid_ebx_reserved_mask 0xffffffff
#define cpuid_ebx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bit 0] is set if the bit n (corresponding to the sub-leaf index) is supported in the ia32_xss msr; it is clear if bit n
                         * is instead supported in xcr0.
                         */
			uint32 ecx2 : 1;
#define cpuid_ecx_ecx_2_bit 0
#define cpuid_ecx_ecx_2_flag 0x01
#define cpuid_ecx_ecx_2_mask 0x01
#define cpuid_ecx_ecx_2(_) (((_) >> 0) & 0x01)

			/**
                         * [bit 1] is set if, when the compacted format of an xsave area is used, this extended state component located on the next
                         * 64-byte boundary following the preceding state component (otherwise, it is located immediately following the preceding
                         * state component).
                         */
			uint32 ecx1 : 1;
#define cpuid_ecx_ecx_1_bit 1
#define cpuid_ecx_ecx_1_flag 0x02
#define cpuid_ecx_ecx_1_mask 0x01
#define cpuid_ecx_ecx_1(_) (((_) >> 1) & 0x01)
			uint32 reserved1 : 30;
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] this field reports 0 if the sub-leaf index, n, is invalid; otherwise it is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_0d_ecx_n;

/**
 * @}
 */

/**
 * @defgroup cpuid_eax_0f \
 *           eax = 0x0f
 *
 * when cpuid executes with eax set to 0fh and ecx = 0, the processor returns information about the bit-list
 * representation of qos monitoring resource types that are supported in the processor and maximum range of rmid values the
 * processor can use to monitor of any supported resource types. each bit, starting from bit 1, corresponds to a specific
 * resource type if the bit is set. the bit position corresponds to the sub-leaf index (or resid) that software must use to
 * query qos monitoring capability available for that type. see table 3-8.
 * when cpuid executes with eax set to 0fh and ecx = n (n >= 1, and is a valid resid), the processor returns information
 * software can use to program ia32_pqr_assoc, ia32_qm_evtsel msrs before reading qos data from the ia32_qm_ctr msr.
 * @{
 */
#define cpuid_intel_resource_director_technology_monitoring_information \
	0x0000000f
/**
 * @brief intel resource director technology (intel rdt) monitoring enumeration sub-leaf (eax = 0fh, ecx = 0)
 *
 * @note leaf 0fh output depends on the initial value in ecx. sub-leaf index 0 reports valid resource type starting at bit
 *       position 1 of edx.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] eax is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_eax_reserved_bit 0
#define cpuid_eax_reserved_flag 0xffffffff
#define cpuid_eax_reserved_mask 0xffffffff
#define cpuid_eax_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] maximum range (zero-based) of rmid within this physical processor of all types.
                         */
			uint32 rmidmaxrange : 32;
#define cpuid_ebx_rmid_max_range_bit 0
#define cpuid_ebx_rmid_max_range_flag 0xffffffff
#define cpuid_ebx_rmid_max_range_mask 0xffffffff
#define cpuid_ebx_rmid_max_range(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] ecx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ecx_reserved_bit 0
#define cpuid_ecx_reserved_flag 0xffffffff
#define cpuid_ecx_reserved_mask 0xffffffff
#define cpuid_ecx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			uint32 reserved1 : 1;

			/**
                         * [bit 1] supports l3 cache intel rdt monitoring if 1.
                         */
			uint32 supportsl3cacheintelrdtmonitoring : 1;
#define cpuid_edx_supports_l3_cache_intel_rdt_monitoring_bit 1
#define cpuid_edx_supports_l3_cache_intel_rdt_monitoring_flag 0x02
#define cpuid_edx_supports_l3_cache_intel_rdt_monitoring_mask 0x01
#define cpuid_edx_supports_l3_cache_intel_rdt_monitoring(_) (((_) >> 1) & 0x01)
			uint32 reserved2 : 30;
		};

		uint32 flags;
	} edx;

} cpuid_eax_0f_ecx_00;

/**
 * @brief l3 cache intel rdt monitoring capability enumeration sub-leaf (eax = 0fh, ecx = 1)
 *
 * @note leaf 0fh output depends on the initial value in ecx.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] eax is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_eax_reserved_bit 0
#define cpuid_eax_reserved_flag 0xffffffff
#define cpuid_eax_reserved_mask 0xffffffff
#define cpuid_eax_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] conversion factor from reported ia32_qm_ctr value to occupancy metric (bytes).
                         */
			uint32 conversionfactor : 32;
#define cpuid_ebx_conversion_factor_bit 0
#define cpuid_ebx_conversion_factor_flag 0xffffffff
#define cpuid_ebx_conversion_factor_mask 0xffffffff
#define cpuid_ebx_conversion_factor(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] maximum range (zero-based) of rmid within this physical processor of all types.
                         */
			uint32 rmidmaxrange : 32;
#define cpuid_ecx_rmid_max_range_bit 0
#define cpuid_ecx_rmid_max_range_flag 0xffffffff
#define cpuid_ecx_rmid_max_range_mask 0xffffffff
#define cpuid_ecx_rmid_max_range(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bit 0] supports l3 occupancy monitoring if 1.
                         */
			uint32 supportsl3occupancymonitoring : 1;
#define cpuid_edx_supports_l3_occupancy_monitoring_bit 0
#define cpuid_edx_supports_l3_occupancy_monitoring_flag 0x01
#define cpuid_edx_supports_l3_occupancy_monitoring_mask 0x01
#define cpuid_edx_supports_l3_occupancy_monitoring(_) (((_) >> 0) & 0x01)

			/**
                         * [bit 1] supports l3 total bandwidth monitoring if 1.
                         */
			uint32 supportsl3totalbandwidthmonitoring : 1;
#define cpuid_edx_supports_l3_total_bandwidth_monitoring_bit 1
#define cpuid_edx_supports_l3_total_bandwidth_monitoring_flag 0x02
#define cpuid_edx_supports_l3_total_bandwidth_monitoring_mask 0x01
#define cpuid_edx_supports_l3_total_bandwidth_monitoring(_) (((_) >> 1) & 0x01)

			/**
                         * [bit 2] supports l3 local bandwidth monitoring if 1.
                         */
			uint32 supportsl3localbandwidthmonitoring : 1;
#define cpuid_edx_supports_l3_local_bandwidth_monitoring_bit 2
#define cpuid_edx_supports_l3_local_bandwidth_monitoring_flag 0x04
#define cpuid_edx_supports_l3_local_bandwidth_monitoring_mask 0x01
#define cpuid_edx_supports_l3_local_bandwidth_monitoring(_) (((_) >> 2) & 0x01)
			uint32 reserved1 : 29;
		};

		uint32 flags;
	} edx;

} cpuid_eax_0f_ecx_01;

/**
 * @}
 */

/**
 * @defgroup cpuid_eax_10 \
 *           eax = 0x10
 *
 * when cpuid executes with eax set to 10h and ecx = 0, the processor returns information about the bit-list
 * representation of qos enforcement resource types that are supported in the processor. each bit, starting from bit 1,
 * corresponds to a specific resource type if the bit is set. the bit position corresponds to the sub-leaf index (or resid)
 * that software must use to query qos enforcement capability available for that type.
 * when cpuid executes with eax set to 10h and ecx = n (n >= 1, and is a valid resid), the processor returns information
 * about available classes of service and range of qos mask msrs that software can use to configure each class of services
 * using capability bit masks in the qos mask registers, ia32_resourcetype_mask_n.
 * @{
 */
#define cpuid_intel_resource_director_technology_allocation_information \
	0x00000010
/**
 * @brief intel resource director technology (intel rdt) allocation enumeration sub-leaf (eax = 10h, ecx = 0)
 *
 * @note leaf 10h output depends on the initial value in ecx. sub-leaf index 0 reports valid resource identification
 *       (resid) starting at bit position 1 of ebx.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] value of bits [31:0] of ia32_platform_dca_cap msr (address 1f8h).
                         */
			uint32 ia32platformdcacap : 32;
#define cpuid_eax_ia32_platform_dca_cap_bit 0
#define cpuid_eax_ia32_platform_dca_cap_flag 0xffffffff
#define cpuid_eax_ia32_platform_dca_cap_mask 0xffffffff
#define cpuid_eax_ia32_platform_dca_cap(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			uint32 reserved1 : 1;

			/**
                         * [bit 1] supports l3 cache allocation technology if 1.
                         */
			uint32 supportsl3cacheallocationtechnology : 1;
#define cpuid_ebx_supports_l3_cache_allocation_technology_bit 1
#define cpuid_ebx_supports_l3_cache_allocation_technology_flag 0x02
#define cpuid_ebx_supports_l3_cache_allocation_technology_mask 0x01
#define cpuid_ebx_supports_l3_cache_allocation_technology(_) (((_) >> 1) & 0x01)

			/**
                         * [bit 2] supports l2 cache allocation technology if 1.
                         */
			uint32 supportsl2cacheallocationtechnology : 1;
#define cpuid_ebx_supports_l2_cache_allocation_technology_bit 2
#define cpuid_ebx_supports_l2_cache_allocation_technology_flag 0x04
#define cpuid_ebx_supports_l2_cache_allocation_technology_mask 0x01
#define cpuid_ebx_supports_l2_cache_allocation_technology(_) (((_) >> 2) & 0x01)

			/**
                         * [bit 3] supports memory bandwidth allocation if 1.
                         */
			uint32 supportsmemorybandwidthallocation : 1;
#define cpuid_ebx_supports_memory_bandwidth_allocation_bit 3
#define cpuid_ebx_supports_memory_bandwidth_allocation_flag 0x08
#define cpuid_ebx_supports_memory_bandwidth_allocation_mask 0x01
#define cpuid_ebx_supports_memory_bandwidth_allocation(_) (((_) >> 3) & 0x01)
			uint32 reserved2 : 28;
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] ecx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ecx_reserved_bit 0
#define cpuid_ecx_reserved_flag 0xffffffff
#define cpuid_ecx_reserved_mask 0xffffffff
#define cpuid_ecx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] edx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_10_ecx_00;

/**
 * @brief l3 cache allocation technology enumeration sub-leaf (eax = 10h, ecx = resid = 1)
 *
 * @note leaf 10h output depends on the initial value in ecx.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 4:0] length of the capacity bit mask for the corresponding resid using minus-one notation.
                         */
			uint32 lengthofcapacitybitmask : 5;
#define cpuid_eax_length_of_capacity_bit_mask_bit 0
#define cpuid_eax_length_of_capacity_bit_mask_flag 0x1f
#define cpuid_eax_length_of_capacity_bit_mask_mask 0x1f
#define cpuid_eax_length_of_capacity_bit_mask(_) (((_) >> 0) & 0x1f)
			uint32 reserved1 : 27;
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] bit-granular map of isolation/contention of allocation units.
                         */
			uint32 ebx0 : 32;
#define cpuid_ebx_ebx_0_bit 0
#define cpuid_ebx_ebx_0_flag 0xffffffff
#define cpuid_ebx_ebx_0_mask 0xffffffff
#define cpuid_ebx_ebx_0(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			uint32 reserved1 : 2;

			/**
                         * [bit 2] code and data prioritization technology supported if 1.
                         */
			uint32 codeanddatapriorizationtechnologysupported : 1;
#define cpuid_ecx_code_and_data_priorization_technology_supported_bit 2
#define cpuid_ecx_code_and_data_priorization_technology_supported_flag 0x04
#define cpuid_ecx_code_and_data_priorization_technology_supported_mask 0x01
#define cpuid_ecx_code_and_data_priorization_technology_supported(_) \
	(((_) >> 2) & 0x01)
			uint32 reserved2 : 29;
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 15:0] highest cos number supported for this resid.
                         */
			uint32 highestcosnumbersupported : 16;
#define cpuid_edx_highest_cos_number_supported_bit 0
#define cpuid_edx_highest_cos_number_supported_flag 0xffff
#define cpuid_edx_highest_cos_number_supported_mask 0xffff
#define cpuid_edx_highest_cos_number_supported(_) (((_) >> 0) & 0xffff)
			uint32 reserved1 : 16;
		};

		uint32 flags;
	} edx;

} cpuid_eax_10_ecx_01;

/**
 * @brief l2 cache allocation technology enumeration sub-leaf (eax = 10h, ecx = resid = 2)
 *
 * @note leaf 10h output depends on the initial value in ecx.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 4:0] length of the capacity bit mask for the corresponding resid using minus-one notation.
                         */
			uint32 lengthofcapacitybitmask : 5;
#define cpuid_eax_length_of_capacity_bit_mask_bit 0
#define cpuid_eax_length_of_capacity_bit_mask_flag 0x1f
#define cpuid_eax_length_of_capacity_bit_mask_mask 0x1f
#define cpuid_eax_length_of_capacity_bit_mask(_) (((_) >> 0) & 0x1f)
			uint32 reserved1 : 27;
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] bit-granular map of isolation/contention of allocation units.
                         */
			uint32 ebx0 : 32;
#define cpuid_ebx_ebx_0_bit 0
#define cpuid_ebx_ebx_0_flag 0xffffffff
#define cpuid_ebx_ebx_0_mask 0xffffffff
#define cpuid_ebx_ebx_0(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] ecx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ecx_reserved_bit 0
#define cpuid_ecx_reserved_flag 0xffffffff
#define cpuid_ecx_reserved_mask 0xffffffff
#define cpuid_ecx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 15:0] highest cos number supported for this resid.
                         */
			uint32 highestcosnumbersupported : 16;
#define cpuid_edx_highest_cos_number_supported_bit 0
#define cpuid_edx_highest_cos_number_supported_flag 0xffff
#define cpuid_edx_highest_cos_number_supported_mask 0xffff
#define cpuid_edx_highest_cos_number_supported(_) (((_) >> 0) & 0xffff)
			uint32 reserved1 : 16;
		};

		uint32 flags;
	} edx;

} cpuid_eax_10_ecx_02;

/**
 * @brief memory bandwidth allocation enumeration sub-leaf (eax = 10h, ecx = resid = 3)
 *
 * @note leaf 10h output depends on the initial value in ecx.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 11:0] reports the maximum mba throttling value supported for the corresponding resid using minus-one notation.
                         */
			uint32 maxmbathrottlingvalue : 12;
#define cpuid_eax_max_mba_throttling_value_bit 0
#define cpuid_eax_max_mba_throttling_value_flag 0xfff
#define cpuid_eax_max_mba_throttling_value_mask 0xfff
#define cpuid_eax_max_mba_throttling_value(_) (((_) >> 0) & 0xfff)
			uint32 reserved1 : 20;
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] ebx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ebx_reserved_bit 0
#define cpuid_ebx_reserved_flag 0xffffffff
#define cpuid_ebx_reserved_mask 0xffffffff
#define cpuid_ebx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			uint32 reserved1 : 2;

			/**
                         * [bit 2] reports whether the response of the delay values is linear.
                         */
			uint32 responseofdelayislinear : 1;
#define cpuid_ecx_response_of_delay_is_linear_bit 2
#define cpuid_ecx_response_of_delay_is_linear_flag 0x04
#define cpuid_ecx_response_of_delay_is_linear_mask 0x01
#define cpuid_ecx_response_of_delay_is_linear(_) (((_) >> 2) & 0x01)
			uint32 reserved2 : 29;
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 15:0] highest cos number supported for this resid.
                         */
			uint32 highestcosnumbersupported : 16;
#define cpuid_edx_highest_cos_number_supported_bit 0
#define cpuid_edx_highest_cos_number_supported_flag 0xffff
#define cpuid_edx_highest_cos_number_supported_mask 0xffff
#define cpuid_edx_highest_cos_number_supported(_) (((_) >> 0) & 0xffff)
			uint32 reserved1 : 16;
		};

		uint32 flags;
	} edx;

} cpuid_eax_10_ecx_03;

/**
 * @}
 */

/**
 * @defgroup cpuid_eax_12 \
 *           eax = 0x12
 *
 * when cpuid executes with eax set to 12h and ecx = 0h, the processor returns information about intel sgx capabilities.
 * when cpuid executes with eax set to 12h and ecx = 1h, the processor returns information about intel sgx attributes.
 * when cpuid executes with eax set to 12h and ecx = n (n > 1), the processor returns information about intel sgx enclave
 * page cache.
 * @{
 */
#define cpuid_intel_sgx 0x00000012
/**
 * @brief intel sgx capability enumeration leaf, sub-leaf 0 (eax = 12h, ecx = 0)
 *
 * @note leaf 12h sub-leaf 0 (ecx = 0) is supported if cpuid.(eax=07h, ecx=0h):ebx[sgx] = 1.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bit 0] if 1, indicates intel sgx supports the collection of sgx1 leaf functions.
                         */
			uint32 sgx1 : 1;
#define cpuid_eax_sgx1_bit 0
#define cpuid_eax_sgx1_flag 0x01
#define cpuid_eax_sgx1_mask 0x01
#define cpuid_eax_sgx1(_) (((_) >> 0) & 0x01)

			/**
                         * [bit 1] if 1, indicates intel sgx supports the collection of sgx2 leaf functions.
                         */
			uint32 sgx2 : 1;
#define cpuid_eax_sgx2_bit 1
#define cpuid_eax_sgx2_flag 0x02
#define cpuid_eax_sgx2_mask 0x01
#define cpuid_eax_sgx2(_) (((_) >> 1) & 0x01)
			uint32 reserved1 : 3;

			/**
                         * [bit 5] if 1, indicates intel sgx supports enclv instruction leaves eincvirtchild, edecvirtchild, and esetcontext.
                         */
			uint32 sgxenclvadvanced : 1;
#define cpuid_eax_sgx_enclv_advanced_bit 5
#define cpuid_eax_sgx_enclv_advanced_flag 0x20
#define cpuid_eax_sgx_enclv_advanced_mask 0x01
#define cpuid_eax_sgx_enclv_advanced(_) (((_) >> 5) & 0x01)

			/**
                         * [bit 6] if 1, indicates intel sgx supports encls instruction leaves etrackc, erdinfo, eldbc, and elduc.
                         */
			uint32 sgxenclsadvanced : 1;
#define cpuid_eax_sgx_encls_advanced_bit 6
#define cpuid_eax_sgx_encls_advanced_flag 0x40
#define cpuid_eax_sgx_encls_advanced_mask 0x01
#define cpuid_eax_sgx_encls_advanced(_) (((_) >> 6) & 0x01)
			uint32 reserved2 : 25;
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] bit list of supported extended sgx features.
                         */
			uint32 miscselect : 32;
#define cpuid_ebx_miscselect_bit 0
#define cpuid_ebx_miscselect_flag 0xffffffff
#define cpuid_ebx_miscselect_mask 0xffffffff
#define cpuid_ebx_miscselect(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] ecx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ecx_reserved_bit 0
#define cpuid_ecx_reserved_flag 0xffffffff
#define cpuid_ecx_reserved_mask 0xffffffff
#define cpuid_ecx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 7:0] the maximum supported enclave size in non-64-bit mode is 2^(edx[7:0]).
                         */
			uint32 maxenclavesizenot64 : 8;
#define cpuid_edx_max_enclave_size_not64_bit 0
#define cpuid_edx_max_enclave_size_not64_flag 0xff
#define cpuid_edx_max_enclave_size_not64_mask 0xff
#define cpuid_edx_max_enclave_size_not64(_) (((_) >> 0) & 0xff)

			/**
                         * [bits 15:8] the maximum supported enclave size in 64-bit mode is 2^(edx[15:8]).
                         */
			uint32 maxenclavesize64 : 8;
#define cpuid_edx_max_enclave_size_64_bit 8
#define cpuid_edx_max_enclave_size_64_flag 0xff00
#define cpuid_edx_max_enclave_size_64_mask 0xff
#define cpuid_edx_max_enclave_size_64(_) (((_) >> 8) & 0xff)
			uint32 reserved1 : 16;
		};

		uint32 flags;
	} edx;

} cpuid_eax_12_ecx_00;

/**
 * @brief intel sgx attributes enumeration leaf, sub-leaf 1 (eax = 12h, ecx = 1)
 *
 * @note leaf 12h sub-leaf 1 (ecx = 1) is supported if cpuid.(eax=07h, ecx=0h):ebx[sgx] = 1.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] reports the valid bits of secs.attributes[31:0] that software can set with ecreate.
                         */
			uint32 validsecsattributes0 : 32;
#define cpuid_eax_valid_secs_attributes_0_bit 0
#define cpuid_eax_valid_secs_attributes_0_flag 0xffffffff
#define cpuid_eax_valid_secs_attributes_0_mask 0xffffffff
#define cpuid_eax_valid_secs_attributes_0(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] reports the valid bits of secs.attributes[63:32] that software can set with ecreate.
                         */
			uint32 validsecsattributes1 : 32;
#define cpuid_ebx_valid_secs_attributes_1_bit 0
#define cpuid_ebx_valid_secs_attributes_1_flag 0xffffffff
#define cpuid_ebx_valid_secs_attributes_1_mask 0xffffffff
#define cpuid_ebx_valid_secs_attributes_1(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] reports the valid bits of secs.attributes[95:64] that software can set with ecreate.
                         */
			uint32 validsecsattributes2 : 32;
#define cpuid_ecx_valid_secs_attributes_2_bit 0
#define cpuid_ecx_valid_secs_attributes_2_flag 0xffffffff
#define cpuid_ecx_valid_secs_attributes_2_mask 0xffffffff
#define cpuid_ecx_valid_secs_attributes_2(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] reports the valid bits of secs.attributes[127:96] that software can set with ecreate.
                         */
			uint32 validsecsattributes3 : 32;
#define cpuid_edx_valid_secs_attributes_3_bit 0
#define cpuid_edx_valid_secs_attributes_3_flag 0xffffffff
#define cpuid_edx_valid_secs_attributes_3_mask 0xffffffff
#define cpuid_edx_valid_secs_attributes_3(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_12_ecx_01;

/**
 * @brief intel sgx epc enumeration leaf, sub-leaves (eax = 12h, ecx = 2 or higher)
 *
 * @note leaf 12h sub-leaf 2 or higher (ecx >= 2) is supported if cpuid.(eax=07h, ecx=0h):ebx[sgx] = 1.
 *       this structure describes sub-leaf type 0.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 3:0] sub-leaf type 0. indicates this sub-leaf is invalid.
                         */
			uint32 subleaftype : 4;
#define cpuid_eax_sub_leaf_type_bit 0
#define cpuid_eax_sub_leaf_type_flag 0x0f
#define cpuid_eax_sub_leaf_type_mask 0x0f
#define cpuid_eax_sub_leaf_type(_) (((_) >> 0) & 0x0f)
			uint32 reserved1 : 28;
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] ebx is zero.
                         */
			uint32 zero : 32;
#define cpuid_ebx_zero_bit 0
#define cpuid_ebx_zero_flag 0xffffffff
#define cpuid_ebx_zero_mask 0xffffffff
#define cpuid_ebx_zero(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] ecx is zero.
                         */
			uint32 zero : 32;
#define cpuid_ecx_zero_bit 0
#define cpuid_ecx_zero_flag 0xffffffff
#define cpuid_ecx_zero_mask 0xffffffff
#define cpuid_ecx_zero(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] edx is zero.
                         */
			uint32 zero : 32;
#define cpuid_edx_zero_bit 0
#define cpuid_edx_zero_flag 0xffffffff
#define cpuid_edx_zero_mask 0xffffffff
#define cpuid_edx_zero(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_12_ecx_02p_slt_0;

/**
 * @brief intel sgx epc enumeration leaf, sub-leaves (eax = 12h, ecx = 2 or higher)
 *
 * @note leaf 12h sub-leaf 2 or higher (ecx >= 2) is supported if cpuid.(eax=07h, ecx=0h):ebx[sgx] = 1.
 *       this structure describes sub-leaf type 1.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 3:0] sub-leaf type 1. this sub-leaf enumerates an epc section. ebx:eax and edx:ecx provide information on the
                         * enclave page cache (epc) section.
                         */
			uint32 subleaftype : 4;
#define cpuid_eax_sub_leaf_type_bit 0
#define cpuid_eax_sub_leaf_type_flag 0x0f
#define cpuid_eax_sub_leaf_type_mask 0x0f
#define cpuid_eax_sub_leaf_type(_) (((_) >> 0) & 0x0f)
			uint32 reserved1 : 8;

			/**
                         * [bits 31:12] bits 31:12 of the physical address of the base of the epc section.
                         */
			uint32 epcbasephysicaladdress1 : 20;
#define cpuid_eax_epc_base_physical_address_1_bit 12
#define cpuid_eax_epc_base_physical_address_1_flag 0xfffff000
#define cpuid_eax_epc_base_physical_address_1_mask 0xfffff
#define cpuid_eax_epc_base_physical_address_1(_) (((_) >> 12) & 0xfffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 19:0] bits 51:32 of the physical address of the base of the epc section.
                         */
			uint32 epcbasephysicaladdress2 : 20;
#define cpuid_ebx_epc_base_physical_address_2_bit 0
#define cpuid_ebx_epc_base_physical_address_2_flag 0xfffff
#define cpuid_ebx_epc_base_physical_address_2_mask 0xfffff
#define cpuid_ebx_epc_base_physical_address_2(_) (((_) >> 0) & 0xfffff)
			uint32 reserved1 : 12;
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 3:0] epc section property encoding defined as follows:
                         * - if eax[3:0] 0000b, then all bits of the edx:ecx pair are enumerated as 0.
                         * - if eax[3:0] 0001b, then this section has confidentiality and integrity protection.
                         * all other encodings are reserved.
                         */
			uint32 epcsectionproperty : 4;
#define cpuid_ecx_epc_section_property_bit 0
#define cpuid_ecx_epc_section_property_flag 0x0f
#define cpuid_ecx_epc_section_property_mask 0x0f
#define cpuid_ecx_epc_section_property(_) (((_) >> 0) & 0x0f)
			uint32 reserved1 : 8;

			/**
                         * [bits 31:12] bits 31:12 of the size of the corresponding epc section within the processor reserved memory.
                         */
			uint32 epcsize1 : 20;
#define cpuid_ecx_epc_size_1_bit 12
#define cpuid_ecx_epc_size_1_flag 0xfffff000
#define cpuid_ecx_epc_size_1_mask 0xfffff
#define cpuid_ecx_epc_size_1(_) (((_) >> 12) & 0xfffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 19:0] bits 51:32 of the size of the corresponding epc section within the processor reserved memory.
                         */
			uint32 epcsize2 : 20;
#define cpuid_edx_epc_size_2_bit 0
#define cpuid_edx_epc_size_2_flag 0xfffff
#define cpuid_edx_epc_size_2_mask 0xfffff
#define cpuid_edx_epc_size_2(_) (((_) >> 0) & 0xfffff)
			uint32 reserved1 : 12;
		};

		uint32 flags;
	} edx;

} cpuid_eax_12_ecx_02p_slt_1;

/**
 * @}
 */

/**
 * @defgroup cpuid_eax_14 \
 *           eax = 0x14
 *
 * when cpuid executes with eax set to 14h and ecx = 0h, the processor returns information about intel processor trace
 * extensions.
 * when cpuid executes with eax set to 14h and ecx = n (n > 0 and less than the number of non-zero bits in cpuid.(eax=14h,
 * ecx= 0h).eax), the processor returns information about packet generation in intel processor trace.
 * @{
 */
#define cpuid_intel_processor_trace_information 0x00000014
/**
 * @brief intel processor trace enumeration main leaf (eax = 14h, ecx = 0)
 *
 * @note leaf 14h main leaf (ecx = 0).
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] reports the maximum sub-leaf supported in leaf 14h.
                         */
			uint32 maxsubleaf : 32;
#define cpuid_eax_max_sub_leaf_bit 0
#define cpuid_eax_max_sub_leaf_flag 0xffffffff
#define cpuid_eax_max_sub_leaf_mask 0xffffffff
#define cpuid_eax_max_sub_leaf(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bit 0] if 1, indicates that ia32_rtit_ctl.cr3filter can be set to 1, and that ia32_rtit_cr3_match msr can be accessed.
                         */
			uint32 flag0 : 1;
#define cpuid_ebx_flag0_bit 0
#define cpuid_ebx_flag0_flag 0x01
#define cpuid_ebx_flag0_mask 0x01
#define cpuid_ebx_flag0(_) (((_) >> 0) & 0x01)

			/**
                         * [bit 1] if 1, indicates support of configurable psb and cycle-accurate mode.
                         */
			uint32 flag1 : 1;
#define cpuid_ebx_flag1_bit 1
#define cpuid_ebx_flag1_flag 0x02
#define cpuid_ebx_flag1_mask 0x01
#define cpuid_ebx_flag1(_) (((_) >> 1) & 0x01)

			/**
                         * [bit 2] if 1, indicates support of ip filtering, tracestop filtering, and preservation of intel pt msrs across warm
                         * reset.
                         */
			uint32 flag2 : 1;
#define cpuid_ebx_flag2_bit 2
#define cpuid_ebx_flag2_flag 0x04
#define cpuid_ebx_flag2_mask 0x01
#define cpuid_ebx_flag2(_) (((_) >> 2) & 0x01)

			/**
                         * [bit 3] if 1, indicates support of mtc timing packet and suppression of cofi-based packets.
                         */
			uint32 flag3 : 1;
#define cpuid_ebx_flag3_bit 3
#define cpuid_ebx_flag3_flag 0x08
#define cpuid_ebx_flag3_mask 0x01
#define cpuid_ebx_flag3(_) (((_) >> 3) & 0x01)

			/**
                         * [bit 4] if 1, indicates support of ptwrite. writes can set ia32_rtit_ctl[12] (ptwen) and ia32_rtit_ctl[5] (fuponptw),
                         * and ptwrite can generate packets.
                         */
			uint32 flag4 : 1;
#define cpuid_ebx_flag4_bit 4
#define cpuid_ebx_flag4_flag 0x10
#define cpuid_ebx_flag4_mask 0x01
#define cpuid_ebx_flag4(_) (((_) >> 4) & 0x01)

			/**
                         * [bit 5] if 1, indicates support of power event trace. writes can set ia32_rtit_ctl[4] (pwrevten), enabling power event
                         * trace packet generation.
                         */
			uint32 flag5 : 1;
#define cpuid_ebx_flag5_bit 5
#define cpuid_ebx_flag5_flag 0x20
#define cpuid_ebx_flag5_mask 0x01
#define cpuid_ebx_flag5(_) (((_) >> 5) & 0x01)
			uint32 reserved1 : 26;
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bit 0] if 1, tracing can be enabled with ia32_rtit_ctl.topa = 1, hence utilizing the topa output scheme;
                         * ia32_rtit_output_base and ia32_rtit_output_mask_ptrs msrs can be accessed.
                         */
			uint32 flag0 : 1;
#define cpuid_ecx_flag0_bit 0
#define cpuid_ecx_flag0_flag 0x01
#define cpuid_ecx_flag0_mask 0x01
#define cpuid_ecx_flag0(_) (((_) >> 0) & 0x01)

			/**
                         * [bit 1] if 1, topa tables can hold any number of output entries, up to the maximum allowed by the maskortableoffset
                         * field of ia32_rtit_output_mask_ptrs.
                         */
			uint32 flag1 : 1;
#define cpuid_ecx_flag1_bit 1
#define cpuid_ecx_flag1_flag 0x02
#define cpuid_ecx_flag1_mask 0x01
#define cpuid_ecx_flag1(_) (((_) >> 1) & 0x01)

			/**
                         * [bit 2] if 1, indicates support of single-range output scheme.
                         */
			uint32 flag2 : 1;
#define cpuid_ecx_flag2_bit 2
#define cpuid_ecx_flag2_flag 0x04
#define cpuid_ecx_flag2_mask 0x01
#define cpuid_ecx_flag2(_) (((_) >> 2) & 0x01)

			/**
                         * [bit 3] if 1, indicates support of output to trace transport subsystem.
                         */
			uint32 flag3 : 1;
#define cpuid_ecx_flag3_bit 3
#define cpuid_ecx_flag3_flag 0x08
#define cpuid_ecx_flag3_mask 0x01
#define cpuid_ecx_flag3(_) (((_) >> 3) & 0x01)
			uint32 reserved1 : 27;

			/**
                         * [bit 31] if 1, generated packets which contain ip payloads have lip values, which include the cs base component.
                         */
			uint32 flag31 : 1;
#define cpuid_ecx_flag31_bit 31
#define cpuid_ecx_flag31_flag 0x80000000
#define cpuid_ecx_flag31_mask 0x01
#define cpuid_ecx_flag31(_) (((_) >> 31) & 0x01)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] edx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_14_ecx_00;

/**
 * @brief intel processor trace enumeration sub-leaf (eax = 14h, ecx = 1)
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 2:0] number of configurable address ranges for filtering.
                         */
			uint32 numberofconfigurableaddressrangesforfiltering : 3;
#define cpuid_eax_number_of_configurable_address_ranges_for_filtering_bit 0
#define cpuid_eax_number_of_configurable_address_ranges_for_filtering_flag 0x07
#define cpuid_eax_number_of_configurable_address_ranges_for_filtering_mask 0x07
#define cpuid_eax_number_of_configurable_address_ranges_for_filtering(_) \
	(((_) >> 0) & 0x07)
			uint32 reserved1 : 13;

			/**
                         * [bits 31:16] bitmap of supported mtc period encodings.
                         */
			uint32 bitmapofsupportedmtcperiodencodings : 16;
#define cpuid_eax_bitmap_of_supported_mtc_period_encodings_bit 16
#define cpuid_eax_bitmap_of_supported_mtc_period_encodings_flag 0xffff0000
#define cpuid_eax_bitmap_of_supported_mtc_period_encodings_mask 0xffff
#define cpuid_eax_bitmap_of_supported_mtc_period_encodings(_) \
	(((_) >> 16) & 0xffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 15:0] bitmap of supported cycle threshold value encodings.
                         */
			uint32 bitmapofsupportedcyclethresholdvalueencodings : 16;
#define cpuid_ebx_bitmap_of_supported_cycle_threshold_value_encodings_bit 0
#define cpuid_ebx_bitmap_of_supported_cycle_threshold_value_encodings_flag \
	0xffff
#define cpuid_ebx_bitmap_of_supported_cycle_threshold_value_encodings_mask \
	0xffff
#define cpuid_ebx_bitmap_of_supported_cycle_threshold_value_encodings(_) \
	(((_) >> 0) & 0xffff)

			/**
                         * [bits 31:16] bitmap of supported configurable psb frequency encodings.
                         */
			uint32 bitmapofsupportedconfigurablepsbfrequencyencodings : 16;
#define cpuid_ebx_bitmap_of_supported_configurable_psb_frequency_encodings_bit \
	16
#define cpuid_ebx_bitmap_of_supported_configurable_psb_frequency_encodings_flag \
	0xffff0000
#define cpuid_ebx_bitmap_of_supported_configurable_psb_frequency_encodings_mask \
	0xffff
#define cpuid_ebx_bitmap_of_supported_configurable_psb_frequency_encodings(_) \
	(((_) >> 16) & 0xffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] ecx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ecx_reserved_bit 0
#define cpuid_ecx_reserved_flag 0xffffffff
#define cpuid_ecx_reserved_mask 0xffffffff
#define cpuid_ecx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] edx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_14_ecx_01;

/**
 * @}
 */

/**
 * @brief stamp counter and nominal core crystal clock information leaf
 *
 * when cpuid executes with eax set to 15h and ecx = 0h, the processor returns information about time stamp counter and
 * core crystal clock.
 *
 * @note if ebx[31:0] is 0, the tsc/"core crystal clock" ratio is not enumerated. ebx[31:0]/eax[31:0] indicates the ratio
 *       of the tsc frequency and the core crystal clock frequency.
 *       if ecx is 0, the nominal core crystal clock frequency is not enumerated. "tsc frequency" = "core crystal clock
 *       frequency" * ebx/eax.
 */
#define cpuid_time_stamp_counter_information 0x00000015
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] an unsigned integer which is the denominator of the tsc/"core crystal clock" ratio.
                         */
			uint32 denominator : 32;
#define cpuid_eax_denominator_bit 0
#define cpuid_eax_denominator_flag 0xffffffff
#define cpuid_eax_denominator_mask 0xffffffff
#define cpuid_eax_denominator(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] an unsigned integer which is the numerator of the tsc/"core crystal clock" ratio.
                         */
			uint32 numerator : 32;
#define cpuid_ebx_numerator_bit 0
#define cpuid_ebx_numerator_flag 0xffffffff
#define cpuid_ebx_numerator_mask 0xffffffff
#define cpuid_ebx_numerator(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] an unsigned integer which is the nominal frequency of the core crystal clock in hz.
                         */
			uint32 nominalfrequency : 32;
#define cpuid_ecx_nominal_frequency_bit 0
#define cpuid_ecx_nominal_frequency_flag 0xffffffff
#define cpuid_ecx_nominal_frequency_mask 0xffffffff
#define cpuid_ecx_nominal_frequency(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] edx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_15;

/**
 * @brief processor frequency information leaf
 *
 * when cpuid executes with eax set to 16h, the processor returns information about processor frequency information.
 *
 * @note data is returned from this interface in accordance with the processor's specification and does not reflect actual
 *       values. suitable use of this data includes the display of processor information in like manner to the processor brand
 *       string and for determining the appropriate range to use when displaying processor information e.g. frequency history
 *       graphs. the returned information should not be used for any other purpose as the returned information does not
 *       accurately correlate to information / counters returned by other processor interfaces.
 *       while a processor may support the processor frequency information leaf, fields that return a value of zero are not
 *       supported.
 */
#define cpuid_processor_frequency_information 0x00000016
typedef struct {
	union {
		struct {
			/**
                         * [bits 15:0] processor base frequency (in mhz).
                         */
			uint32 procesorbasefrequencymhz : 16;
#define cpuid_eax_procesor_base_frequency_mhz_bit 0
#define cpuid_eax_procesor_base_frequency_mhz_flag 0xffff
#define cpuid_eax_procesor_base_frequency_mhz_mask 0xffff
#define cpuid_eax_procesor_base_frequency_mhz(_) (((_) >> 0) & 0xffff)
			uint32 reserved1 : 16;
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 15:0] maximum frequency (in mhz).
                         */
			uint32 processormaximumfrequencymhz : 16;
#define cpuid_ebx_processor_maximum_frequency_mhz_bit 0
#define cpuid_ebx_processor_maximum_frequency_mhz_flag 0xffff
#define cpuid_ebx_processor_maximum_frequency_mhz_mask 0xffff
#define cpuid_ebx_processor_maximum_frequency_mhz(_) (((_) >> 0) & 0xffff)
			uint32 reserved1 : 16;
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 15:0] bus (reference) frequency (in mhz).
                         */
			uint32 busfrequencymhz : 16;
#define cpuid_ecx_bus_frequency_mhz_bit 0
#define cpuid_ecx_bus_frequency_mhz_flag 0xffff
#define cpuid_ecx_bus_frequency_mhz_mask 0xffff
#define cpuid_ecx_bus_frequency_mhz(_) (((_) >> 0) & 0xffff)
			uint32 reserved1 : 16;
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] edx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_16;

/**
 * @defgroup cpuid_eax_17 \
 *           eax = 0x17
 *
 * when cpuid executes with eax set to 17h, the processor returns information about the system-on-chip vendor attribute
 * enumeration.
 * @{
 */
#define cpuid_soc_vendor_information 0x00000017
/**
 * @brief system-on-chip vendor attribute enumeration main leaf (eax = 17h, ecx = 0)
 *
 * @note leaf 17h main leaf (ecx = 0). leaf 17h output depends on the initial value in ecx. leaf 17h sub-leaves 1 through 3
 *       reports soc vendor brand string. leaf 17h is valid if maxsocid_index >= 3. leaf 17h sub-leaves 4 and above are reserved.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] reports the maximum input value of supported sub-leaf in leaf 17h.
                         */
			uint32 maxsocidindex : 32;
#define cpuid_eax_max_soc_id_index_bit 0
#define cpuid_eax_max_soc_id_index_flag 0xffffffff
#define cpuid_eax_max_soc_id_index_mask 0xffffffff
#define cpuid_eax_max_soc_id_index(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 15:0] soc vendor id.
                         */
			uint32 socvendorid : 16;
#define cpuid_ebx_soc_vendor_id_bit 0
#define cpuid_ebx_soc_vendor_id_flag 0xffff
#define cpuid_ebx_soc_vendor_id_mask 0xffff
#define cpuid_ebx_soc_vendor_id(_) (((_) >> 0) & 0xffff)

			/**
                         * [bit 16] if 1, the soc vendor id field is assigned via an industry standard enumeration scheme. otherwise, the soc
                         * vendor id field is assigned by intel.
                         */
			uint32 isvendorscheme : 1;
#define cpuid_ebx_is_vendor_scheme_bit 16
#define cpuid_ebx_is_vendor_scheme_flag 0x10000
#define cpuid_ebx_is_vendor_scheme_mask 0x01
#define cpuid_ebx_is_vendor_scheme(_) (((_) >> 16) & 0x01)
			uint32 reserved1 : 15;
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] a unique number an soc vendor assigns to its soc projects.
                         */
			uint32 projectid : 32;
#define cpuid_ecx_project_id_bit 0
#define cpuid_ecx_project_id_flag 0xffffffff
#define cpuid_ecx_project_id_mask 0xffffffff
#define cpuid_ecx_project_id(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] a unique number within an soc project that an soc vendor assigns.
                         */
			uint32 steppingid : 32;
#define cpuid_edx_stepping_id_bit 0
#define cpuid_edx_stepping_id_flag 0xffffffff
#define cpuid_edx_stepping_id_mask 0xffffffff
#define cpuid_edx_stepping_id(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_17_ecx_00;

/**
 * @brief system-on-chip vendor attribute enumeration sub-leaf (eax = 17h, ecx = 1..3)
 *
 * @note leaf 17h output depends on the initial value in ecx. soc vendor brand string is a utf-8 encoded string padded with
 *       trailing bytes of 00h. the complete soc vendor brand string is constructed by concatenating in ascending order of
 *       eax:ebx:ecx:edx and from the sub-leaf 1 fragment towards sub-leaf 3.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] soc vendor brand string. utf-8 encoded string.
                         */
			uint32 socvendorbrandstring : 32;
#define cpuid_eax_soc_vendor_brand_string_bit 0
#define cpuid_eax_soc_vendor_brand_string_flag 0xffffffff
#define cpuid_eax_soc_vendor_brand_string_mask 0xffffffff
#define cpuid_eax_soc_vendor_brand_string(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] soc vendor brand string. utf-8 encoded string.
                         */
			uint32 socvendorbrandstring : 32;
#define cpuid_ebx_soc_vendor_brand_string_bit 0
#define cpuid_ebx_soc_vendor_brand_string_flag 0xffffffff
#define cpuid_ebx_soc_vendor_brand_string_mask 0xffffffff
#define cpuid_ebx_soc_vendor_brand_string(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] soc vendor brand string. utf-8 encoded string.
                         */
			uint32 socvendorbrandstring : 32;
#define cpuid_ecx_soc_vendor_brand_string_bit 0
#define cpuid_ecx_soc_vendor_brand_string_flag 0xffffffff
#define cpuid_ecx_soc_vendor_brand_string_mask 0xffffffff
#define cpuid_ecx_soc_vendor_brand_string(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] soc vendor brand string. utf-8 encoded string.
                         */
			uint32 socvendorbrandstring : 32;
#define cpuid_edx_soc_vendor_brand_string_bit 0
#define cpuid_edx_soc_vendor_brand_string_flag 0xffffffff
#define cpuid_edx_soc_vendor_brand_string_mask 0xffffffff
#define cpuid_edx_soc_vendor_brand_string(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_17_ecx_01_03;

/**
 * @brief system-on-chip vendor attribute enumeration sub-leaves (eax = 17h, ecx > maxsocid_index)
 *
 * @note leaf 17h output depends on the initial value in ecx.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] reserved = 0.
                         */
			uint32 reserved : 32;
#define cpuid_eax_reserved_bit 0
#define cpuid_eax_reserved_flag 0xffffffff
#define cpuid_eax_reserved_mask 0xffffffff
#define cpuid_eax_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] reserved = 0.
                         */
			uint32 reserved : 32;
#define cpuid_ebx_reserved_bit 0
#define cpuid_ebx_reserved_flag 0xffffffff
#define cpuid_ebx_reserved_mask 0xffffffff
#define cpuid_ebx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] reserved = 0.
                         */
			uint32 reserved : 32;
#define cpuid_ecx_reserved_bit 0
#define cpuid_ecx_reserved_flag 0xffffffff
#define cpuid_ecx_reserved_mask 0xffffffff
#define cpuid_ecx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] reserved = 0.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_17_ecx_n;

/**
 * @}
 */

/**
 * @defgroup cpuid_eax_18 \
 *           eax = 0x18
 *
 * when cpuid executes with eax set to 18h, the processor returns information about the deterministic address translation
 * parameters.
 * @{
 */
#define cpuid_deterministic_address_translation_parameters 0x00000018
/**
 * @brief deterministic address translation parameters main leaf (eax = 18h, ecx = 0)
 *
 * @note each sub-leaf enumerates a different address translation structure.
 *       if ecx contains an invalid sub-leaf index, eax/ebx/ecx/edx return 0. sub-leaf index n is invalid if n exceeds the value
 *       that sub-leaf 0 returns in eax. a sub-leaf index is also invalid if edx[4:0] returns 0. valid sub-leaves do not need to
 *       be contiguous or in any particular order. a valid sub-leaf may be in a higher input ecx value than an invalid sub-leaf
 *       or than a valid sub-leaf of a higher or lower-level structure.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] reports the maximum input value of supported sub-leaf in leaf 18h.
                         */
			uint32 maxsubleaf : 32;
#define cpuid_eax_max_sub_leaf_bit 0
#define cpuid_eax_max_sub_leaf_flag 0xffffffff
#define cpuid_eax_max_sub_leaf_mask 0xffffffff
#define cpuid_eax_max_sub_leaf(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bit 0] 4k page size entries supported by this structure.
                         */
			uint32 pageentries4kbsupported : 1;
#define cpuid_ebx_page_entries_4kb_supported_bit 0
#define cpuid_ebx_page_entries_4kb_supported_flag 0x01
#define cpuid_ebx_page_entries_4kb_supported_mask 0x01
#define cpuid_ebx_page_entries_4kb_supported(_) (((_) >> 0) & 0x01)

			/**
                         * [bit 1] 2mb page size entries supported by this structure.
                         */
			uint32 pageentries2mbsupported : 1;
#define cpuid_ebx_page_entries_2mb_supported_bit 1
#define cpuid_ebx_page_entries_2mb_supported_flag 0x02
#define cpuid_ebx_page_entries_2mb_supported_mask 0x01
#define cpuid_ebx_page_entries_2mb_supported(_) (((_) >> 1) & 0x01)

			/**
                         * [bit 2] 4mb page size entries supported by this structure.
                         */
			uint32 pageentries4mbsupported : 1;
#define cpuid_ebx_page_entries_4mb_supported_bit 2
#define cpuid_ebx_page_entries_4mb_supported_flag 0x04
#define cpuid_ebx_page_entries_4mb_supported_mask 0x01
#define cpuid_ebx_page_entries_4mb_supported(_) (((_) >> 2) & 0x01)

			/**
                         * [bit 3] 1 gb page size entries supported by this structure.
                         */
			uint32 pageentries1gbsupported : 1;
#define cpuid_ebx_page_entries_1gb_supported_bit 3
#define cpuid_ebx_page_entries_1gb_supported_flag 0x08
#define cpuid_ebx_page_entries_1gb_supported_mask 0x01
#define cpuid_ebx_page_entries_1gb_supported(_) (((_) >> 3) & 0x01)
			uint32 reserved1 : 4;

			/**
                         * [bits 10:8] partitioning (0: soft partitioning between the logical processors sharing this structure).
                         */
			uint32 partitioning : 3;
#define cpuid_ebx_partitioning_bit 8
#define cpuid_ebx_partitioning_flag 0x700
#define cpuid_ebx_partitioning_mask 0x07
#define cpuid_ebx_partitioning(_) (((_) >> 8) & 0x07)
			uint32 reserved2 : 5;

			/**
                         * [bits 31:16] w = ways of associativity.
                         */
			uint32 waysofassociativity00 : 16;
#define cpuid_ebx_ways_of_associativity_00_bit 16
#define cpuid_ebx_ways_of_associativity_00_flag 0xffff0000
#define cpuid_ebx_ways_of_associativity_00_mask 0xffff
#define cpuid_ebx_ways_of_associativity_00(_) (((_) >> 16) & 0xffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] number of sets.
                         */
			uint32 numberofsets : 32;
#define cpuid_ecx_number_of_sets_bit 0
#define cpuid_ecx_number_of_sets_flag 0xffffffff
#define cpuid_ecx_number_of_sets_mask 0xffffffff
#define cpuid_ecx_number_of_sets(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 4:0] translation cache type field.
                         * - 00000b: null (indicates this sub-leaf is not valid).
                         * - 00001b: data tlb.
                         * - 00010b: instruction tlb.
                         * - 00011b: unified tlb.
                         * all other encodings are reserved.
                         *
                         * @note some unified tlbs will allow a single tlb entry to satisfy data read/write and instruction fetches. others will
                         *       require separate entries (e.g., one loaded on data read/write and another loaded on an instruction fetch) . please see
                         *       the intel(r) 64 and ia-32 architectures optimization reference manual for details of a particular product.
                         */
			uint32 translationcachetypefield : 5;
#define cpuid_edx_translation_cache_type_field_bit 0
#define cpuid_edx_translation_cache_type_field_flag 0x1f
#define cpuid_edx_translation_cache_type_field_mask 0x1f
#define cpuid_edx_translation_cache_type_field(_) (((_) >> 0) & 0x1f)

			/**
                         * [bits 7:5] translation cache level (starts at 1).
                         */
			uint32 translationcachelevel : 3;
#define cpuid_edx_translation_cache_level_bit 5
#define cpuid_edx_translation_cache_level_flag 0xe0
#define cpuid_edx_translation_cache_level_mask 0x07
#define cpuid_edx_translation_cache_level(_) (((_) >> 5) & 0x07)

			/**
                         * [bit 8] fully associative structure.
                         */
			uint32 fullyassociativestructure : 1;
#define cpuid_edx_fully_associative_structure_bit 8
#define cpuid_edx_fully_associative_structure_flag 0x100
#define cpuid_edx_fully_associative_structure_mask 0x01
#define cpuid_edx_fully_associative_structure(_) (((_) >> 8) & 0x01)
			uint32 reserved1 : 5;

			/**
                         * [bits 25:14] maximum number of addressable ids for logical processors sharing this translation cache.
                         *
                         * @note add one to the return value to get the result.
                         */
			uint32 maxaddressableidsforlogicalprocessors : 12;
#define cpuid_edx_max_addressable_ids_for_logical_processors_bit 14
#define cpuid_edx_max_addressable_ids_for_logical_processors_flag 0x3ffc000
#define cpuid_edx_max_addressable_ids_for_logical_processors_mask 0xfff
#define cpuid_edx_max_addressable_ids_for_logical_processors(_) \
	(((_) >> 14) & 0xfff)
			uint32 reserved2 : 6;
		};

		uint32 flags;
	} edx;

} cpuid_eax_18_ecx_00;

/**
 * @brief deterministic address translation parameters sub-leaf (eax = 18h, ecx >= 1)
 *
 * @note each sub-leaf enumerates a different address translation structure.
 *       if ecx contains an invalid sub-leaf index, eax/ebx/ecx/edx return 0. sub-leaf index n is invalid if n exceeds the value
 *       that sub-leaf 0 returns in eax. a sub-leaf index is also invalid if edx[4:0] returns 0. valid sub-leaves do not need to
 *       be contiguous or in any particular order. a valid sub-leaf may be in a higher input ecx value than an invalid sub-leaf
 *       or than a valid sub-leaf of a higher or lower-level structure.
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] eax is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_eax_reserved_bit 0
#define cpuid_eax_reserved_flag 0xffffffff
#define cpuid_eax_reserved_mask 0xffffffff
#define cpuid_eax_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bit 0] 4k page size entries supported by this structure.
                         */
			uint32 pageentries4kbsupported : 1;
#define cpuid_ebx_page_entries_4kb_supported_bit 0
#define cpuid_ebx_page_entries_4kb_supported_flag 0x01
#define cpuid_ebx_page_entries_4kb_supported_mask 0x01
#define cpuid_ebx_page_entries_4kb_supported(_) (((_) >> 0) & 0x01)

			/**
                         * [bit 1] 2mb page size entries supported by this structure.
                         */
			uint32 pageentries2mbsupported : 1;
#define cpuid_ebx_page_entries_2mb_supported_bit 1
#define cpuid_ebx_page_entries_2mb_supported_flag 0x02
#define cpuid_ebx_page_entries_2mb_supported_mask 0x01
#define cpuid_ebx_page_entries_2mb_supported(_) (((_) >> 1) & 0x01)

			/**
                         * [bit 2] 4mb page size entries supported by this structure.
                         */
			uint32 pageentries4mbsupported : 1;
#define cpuid_ebx_page_entries_4mb_supported_bit 2
#define cpuid_ebx_page_entries_4mb_supported_flag 0x04
#define cpuid_ebx_page_entries_4mb_supported_mask 0x01
#define cpuid_ebx_page_entries_4mb_supported(_) (((_) >> 2) & 0x01)

			/**
                         * [bit 3] 1 gb page size entries supported by this structure.
                         */
			uint32 pageentries1gbsupported : 1;
#define cpuid_ebx_page_entries_1gb_supported_bit 3
#define cpuid_ebx_page_entries_1gb_supported_flag 0x08
#define cpuid_ebx_page_entries_1gb_supported_mask 0x01
#define cpuid_ebx_page_entries_1gb_supported(_) (((_) >> 3) & 0x01)
			uint32 reserved1 : 4;

			/**
                         * [bits 10:8] partitioning (0: soft partitioning between the logical processors sharing this structure).
                         */
			uint32 partitioning : 3;
#define cpuid_ebx_partitioning_bit 8
#define cpuid_ebx_partitioning_flag 0x700
#define cpuid_ebx_partitioning_mask 0x07
#define cpuid_ebx_partitioning(_) (((_) >> 8) & 0x07)
			uint32 reserved2 : 5;

			/**
                         * [bits 31:16] w = ways of associativity.
                         */
			uint32 waysofassociativity01 : 16;
#define cpuid_ebx_ways_of_associativity_01_bit 16
#define cpuid_ebx_ways_of_associativity_01_flag 0xffff0000
#define cpuid_ebx_ways_of_associativity_01_mask 0xffff
#define cpuid_ebx_ways_of_associativity_01(_) (((_) >> 16) & 0xffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] number of sets.
                         */
			uint32 numberofsets : 32;
#define cpuid_ecx_number_of_sets_bit 0
#define cpuid_ecx_number_of_sets_flag 0xffffffff
#define cpuid_ecx_number_of_sets_mask 0xffffffff
#define cpuid_ecx_number_of_sets(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 4:0] translation cache type field.
                         * - 00000b: null (indicates this sub-leaf is not valid).
                         * - 00001b: data tlb.
                         * - 00010b: instruction tlb.
                         * - 00011b: unified tlb.
                         * all other encodings are reserved.
                         *
                         * @note some unified tlbs will allow a single tlb entry to satisfy data read/write and instruction fetches. others will
                         *       require separate entries (e.g., one loaded on data read/write and another loaded on an instruction fetch) . please see
                         *       the intel(r) 64 and ia-32 architectures optimization reference manual for details of a particular product.
                         */
			uint32 translationcachetypefield : 5;
#define cpuid_edx_translation_cache_type_field_bit 0
#define cpuid_edx_translation_cache_type_field_flag 0x1f
#define cpuid_edx_translation_cache_type_field_mask 0x1f
#define cpuid_edx_translation_cache_type_field(_) (((_) >> 0) & 0x1f)

			/**
                         * [bits 7:5] translation cache level (starts at 1).
                         */
			uint32 translationcachelevel : 3;
#define cpuid_edx_translation_cache_level_bit 5
#define cpuid_edx_translation_cache_level_flag 0xe0
#define cpuid_edx_translation_cache_level_mask 0x07
#define cpuid_edx_translation_cache_level(_) (((_) >> 5) & 0x07)

			/**
                         * [bit 8] fully associative structure.
                         */
			uint32 fullyassociativestructure : 1;
#define cpuid_edx_fully_associative_structure_bit 8
#define cpuid_edx_fully_associative_structure_flag 0x100
#define cpuid_edx_fully_associative_structure_mask 0x01
#define cpuid_edx_fully_associative_structure(_) (((_) >> 8) & 0x01)
			uint32 reserved1 : 5;

			/**
                         * [bits 25:14] maximum number of addressable ids for logical processors sharing this translation cache.
                         *
                         * @note add one to the return value to get the result.
                         */
			uint32 maxaddressableidsforlogicalprocessors : 12;
#define cpuid_edx_max_addressable_ids_for_logical_processors_bit 14
#define cpuid_edx_max_addressable_ids_for_logical_processors_flag 0x3ffc000
#define cpuid_edx_max_addressable_ids_for_logical_processors_mask 0xfff
#define cpuid_edx_max_addressable_ids_for_logical_processors(_) \
	(((_) >> 14) & 0xfff)
			uint32 reserved2 : 6;
		};

		uint32 flags;
	} edx;

} cpuid_eax_18_ecx_01p;

/**
 * @}
 */

/**
 * @brief extended function cpuid information
 *
 * when cpuid executes with eax set to 80000000h, the processor returns the highest value the processor recognizes for
 * returning extended processor information. the value is returned in the eax register and is processor specific.
 */
#define cpuid_extended_function_information 0x80000000
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] maximum input value for extended function cpuid information.
                         */
			uint32 maxextendedfunctions : 32;
#define cpuid_eax_max_extended_functions_bit 0
#define cpuid_eax_max_extended_functions_flag 0xffffffff
#define cpuid_eax_max_extended_functions_mask 0xffffffff
#define cpuid_eax_max_extended_functions(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] ebx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ebx_reserved_bit 0
#define cpuid_ebx_reserved_flag 0xffffffff
#define cpuid_ebx_reserved_mask 0xffffffff
#define cpuid_ebx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] ecx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ecx_reserved_bit 0
#define cpuid_ecx_reserved_flag 0xffffffff
#define cpuid_ecx_reserved_mask 0xffffffff
#define cpuid_ecx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] edx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_80000000;

/**
 * extended function cpuid information.
 */
#define cpuid_extended_cpu_signature 0x80000001
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] eax is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_eax_reserved_bit 0
#define cpuid_eax_reserved_flag 0xffffffff
#define cpuid_eax_reserved_mask 0xffffffff
#define cpuid_eax_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] ebx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ebx_reserved_bit 0
#define cpuid_ebx_reserved_flag 0xffffffff
#define cpuid_ebx_reserved_mask 0xffffffff
#define cpuid_ebx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bit 0] lahf/sahf available in 64-bit mode.
                         */
			uint32 lahfsahfavailablein64bitmode : 1;
#define cpuid_ecx_lahf_sahf_available_in_64_bit_mode_bit 0
#define cpuid_ecx_lahf_sahf_available_in_64_bit_mode_flag 0x01
#define cpuid_ecx_lahf_sahf_available_in_64_bit_mode_mask 0x01
#define cpuid_ecx_lahf_sahf_available_in_64_bit_mode(_) (((_) >> 0) & 0x01)
			uint32 reserved1 : 4;

			/**
                         * [bit 5] lzcnt.
                         */
			uint32 lzcnt : 1;
#define cpuid_ecx_lzcnt_bit 5
#define cpuid_ecx_lzcnt_flag 0x20
#define cpuid_ecx_lzcnt_mask 0x01
#define cpuid_ecx_lzcnt(_) (((_) >> 5) & 0x01)
			uint32 reserved2 : 2;

			/**
                         * [bit 8] prefetchw.
                         */
			uint32 prefetchw : 1;
#define cpuid_ecx_prefetchw_bit 8
#define cpuid_ecx_prefetchw_flag 0x100
#define cpuid_ecx_prefetchw_mask 0x01
#define cpuid_ecx_prefetchw(_) (((_) >> 8) & 0x01)
			uint32 reserved3 : 23;
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			uint32 reserved1 : 11;

			/**
                         * [bit 11] syscall/sysret available in 64-bit mode.
                         */
			uint32 syscallsysretavailablein64bitmode : 1;
#define cpuid_edx_syscall_sysret_available_in_64_bit_mode_bit 11
#define cpuid_edx_syscall_sysret_available_in_64_bit_mode_flag 0x800
#define cpuid_edx_syscall_sysret_available_in_64_bit_mode_mask 0x01
#define cpuid_edx_syscall_sysret_available_in_64_bit_mode(_) \
	(((_) >> 11) & 0x01)
			uint32 reserved2 : 8;

			/**
                         * [bit 20] execute disable bit available.
                         */
			uint32 executedisablebitavailable : 1;
#define cpuid_edx_execute_disable_bit_available_bit 20
#define cpuid_edx_execute_disable_bit_available_flag 0x100000
#define cpuid_edx_execute_disable_bit_available_mask 0x01
#define cpuid_edx_execute_disable_bit_available(_) (((_) >> 20) & 0x01)
			uint32 reserved3 : 5;

			/**
                         * [bit 26] 1-gbyte pages are available if 1.
                         */
			uint32 pages1gbavailable : 1;
#define cpuid_edx_pages_1gb_available_bit 26
#define cpuid_edx_pages_1gb_available_flag 0x4000000
#define cpuid_edx_pages_1gb_available_mask 0x01
#define cpuid_edx_pages_1gb_available(_) (((_) >> 26) & 0x01)

			/**
                         * [bit 27] rdtscp and ia32_tsc_aux are available if 1.
                         */
			uint32 rdtscpavailable : 1;
#define cpuid_edx_rdtscp_available_bit 27
#define cpuid_edx_rdtscp_available_flag 0x8000000
#define cpuid_edx_rdtscp_available_mask 0x01
#define cpuid_edx_rdtscp_available(_) (((_) >> 27) & 0x01)
			uint32 reserved4 : 1;

			/**
                         * [bit 29] intel(r) 64 architecture available if 1.
                         */
			uint32 ia64available : 1;
#define cpuid_edx_ia64_available_bit 29
#define cpuid_edx_ia64_available_flag 0x20000000
#define cpuid_edx_ia64_available_mask 0x01
#define cpuid_edx_ia64_available(_) (((_) >> 29) & 0x01)
			uint32 reserved5 : 2;
		};

		uint32 flags;
	} edx;

} cpuid_eax_80000001;

/**
 * extended function cpuid information.
 */
#define cpuid_brand_string1 0x80000002

/**
 * extended function cpuid information.
 */
#define cpuid_brand_string2 0x80000003

/**
 * extended function cpuid information.
 */
#define cpuid_brand_string3 0x80000004
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] processor brand string.
                         */
			uint32 processorbrandstring1 : 32;
#define cpuid_eax_processor_brand_string_1_bit 0
#define cpuid_eax_processor_brand_string_1_flag 0xffffffff
#define cpuid_eax_processor_brand_string_1_mask 0xffffffff
#define cpuid_eax_processor_brand_string_1(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] processor brand string continued.
                         */
			uint32 processorbrandstring2 : 32;
#define cpuid_ebx_processor_brand_string_2_bit 0
#define cpuid_ebx_processor_brand_string_2_flag 0xffffffff
#define cpuid_ebx_processor_brand_string_2_mask 0xffffffff
#define cpuid_ebx_processor_brand_string_2(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] processor brand string continued.
                         */
			uint32 processorbrandstring3 : 32;
#define cpuid_ecx_processor_brand_string_3_bit 0
#define cpuid_ecx_processor_brand_string_3_flag 0xffffffff
#define cpuid_ecx_processor_brand_string_3_mask 0xffffffff
#define cpuid_ecx_processor_brand_string_3(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] processor brand string continued.
                         */
			uint32 processorbrandstring4 : 32;
#define cpuid_edx_processor_brand_string_4_bit 0
#define cpuid_edx_processor_brand_string_4_flag 0xffffffff
#define cpuid_edx_processor_brand_string_4_mask 0xffffffff
#define cpuid_edx_processor_brand_string_4(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_80000002;

/**
 * @brief extended function cpuid information
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] processor brand string continued.
                         */
			uint32 processorbrandstring5 : 32;
#define cpuid_eax_processor_brand_string_5_bit 0
#define cpuid_eax_processor_brand_string_5_flag 0xffffffff
#define cpuid_eax_processor_brand_string_5_mask 0xffffffff
#define cpuid_eax_processor_brand_string_5(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] processor brand string continued.
                         */
			uint32 processorbrandstring6 : 32;
#define cpuid_ebx_processor_brand_string_6_bit 0
#define cpuid_ebx_processor_brand_string_6_flag 0xffffffff
#define cpuid_ebx_processor_brand_string_6_mask 0xffffffff
#define cpuid_ebx_processor_brand_string_6(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] processor brand string continued.
                         */
			uint32 processorbrandstring7 : 32;
#define cpuid_ecx_processor_brand_string_7_bit 0
#define cpuid_ecx_processor_brand_string_7_flag 0xffffffff
#define cpuid_ecx_processor_brand_string_7_mask 0xffffffff
#define cpuid_ecx_processor_brand_string_7(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] processor brand string continued.
                         */
			uint32 processorbrandstring8 : 32;
#define cpuid_edx_processor_brand_string_8_bit 0
#define cpuid_edx_processor_brand_string_8_flag 0xffffffff
#define cpuid_edx_processor_brand_string_8_mask 0xffffffff
#define cpuid_edx_processor_brand_string_8(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_80000003;

/**
 * @brief extended function cpuid information
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] processor brand string continued.
                         */
			uint32 processorbrandstring9 : 32;
#define cpuid_eax_processor_brand_string_9_bit 0
#define cpuid_eax_processor_brand_string_9_flag 0xffffffff
#define cpuid_eax_processor_brand_string_9_mask 0xffffffff
#define cpuid_eax_processor_brand_string_9(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] processor brand string continued.
                         */
			uint32 processorbrandstring10 : 32;
#define cpuid_ebx_processor_brand_string_10_bit 0
#define cpuid_ebx_processor_brand_string_10_flag 0xffffffff
#define cpuid_ebx_processor_brand_string_10_mask 0xffffffff
#define cpuid_ebx_processor_brand_string_10(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] processor brand string continued.
                         */
			uint32 processorbrandstring11 : 32;
#define cpuid_ecx_processor_brand_string_11_bit 0
#define cpuid_ecx_processor_brand_string_11_flag 0xffffffff
#define cpuid_ecx_processor_brand_string_11_mask 0xffffffff
#define cpuid_ecx_processor_brand_string_11(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] processor brand string continued.
                         */
			uint32 processorbrandstring12 : 32;
#define cpuid_edx_processor_brand_string_12_bit 0
#define cpuid_edx_processor_brand_string_12_flag 0xffffffff
#define cpuid_edx_processor_brand_string_12_mask 0xffffffff
#define cpuid_edx_processor_brand_string_12(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_80000004;

/**
 * @brief extended function cpuid information
 */
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] eax is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_eax_reserved_bit 0
#define cpuid_eax_reserved_flag 0xffffffff
#define cpuid_eax_reserved_mask 0xffffffff
#define cpuid_eax_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] ebx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ebx_reserved_bit 0
#define cpuid_ebx_reserved_flag 0xffffffff
#define cpuid_ebx_reserved_mask 0xffffffff
#define cpuid_ebx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] ecx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ecx_reserved_bit 0
#define cpuid_ecx_reserved_flag 0xffffffff
#define cpuid_ecx_reserved_mask 0xffffffff
#define cpuid_ecx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] edx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_80000005;

/**
 * extended function cpuid information.
 */
#define cpuid_extended_cache_info 0x80000006
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] eax is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_eax_reserved_bit 0
#define cpuid_eax_reserved_flag 0xffffffff
#define cpuid_eax_reserved_mask 0xffffffff
#define cpuid_eax_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] ebx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ebx_reserved_bit 0
#define cpuid_ebx_reserved_flag 0xffffffff
#define cpuid_ebx_reserved_mask 0xffffffff
#define cpuid_ebx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 7:0] cache line size in bytes.
                         */
			uint32 cachelinesizeinbytes : 8;
#define cpuid_ecx_cache_line_size_in_bytes_bit 0
#define cpuid_ecx_cache_line_size_in_bytes_flag 0xff
#define cpuid_ecx_cache_line_size_in_bytes_mask 0xff
#define cpuid_ecx_cache_line_size_in_bytes(_) (((_) >> 0) & 0xff)
			uint32 reserved1 : 4;

			/**
                         * [bits 15:12] l2 associativity field.
                         * l2 associativity field encodings:
                         * - 00h - disabled.
                         * - 01h - direct mapped.
                         * - 02h - 2-way.
                         * - 04h - 4-way.
                         * - 06h - 8-way.
                         * - 08h - 16-way.
                         * - 0fh - fully associative.
                         */
			uint32 l2associativityfield : 4;
#define cpuid_ecx_l2_associativity_field_bit 12
#define cpuid_ecx_l2_associativity_field_flag 0xf000
#define cpuid_ecx_l2_associativity_field_mask 0x0f
#define cpuid_ecx_l2_associativity_field(_) (((_) >> 12) & 0x0f)

			/**
                         * [bits 31:16] cache size in 1k units.
                         */
			uint32 cachesizein1kunits : 16;
#define cpuid_ecx_cache_size_in_1k_units_bit 16
#define cpuid_ecx_cache_size_in_1k_units_flag 0xffff0000
#define cpuid_ecx_cache_size_in_1k_units_mask 0xffff
#define cpuid_ecx_cache_size_in_1k_units(_) (((_) >> 16) & 0xffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			/**
                         * [bits 31:0] edx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_edx_reserved_bit 0
#define cpuid_edx_reserved_flag 0xffffffff
#define cpuid_edx_reserved_mask 0xffffffff
#define cpuid_edx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} edx;

} cpuid_eax_80000006;

/**
 * extended function cpuid information.
 */
#define cpuid_extended_time_stamp_counter 0x80000007
typedef struct {
	union {
		struct {
			/**
                         * [bits 31:0] eax is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_eax_reserved_bit 0
#define cpuid_eax_reserved_flag 0xffffffff
#define cpuid_eax_reserved_mask 0xffffffff
#define cpuid_eax_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} eax;

	union {
		struct {
			/**
                         * [bits 31:0] ebx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ebx_reserved_bit 0
#define cpuid_ebx_reserved_flag 0xffffffff
#define cpuid_ebx_reserved_mask 0xffffffff
#define cpuid_ebx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ebx;

	union {
		struct {
			/**
                         * [bits 31:0] ecx is reserved.
                         */
			uint32 reserved : 32;
#define cpuid_ecx_reserved_bit 0
#define cpuid_ecx_reserved_flag 0xffffffff
#define cpuid_ecx_reserved_mask 0xffffffff
#define cpuid_ecx_reserved(_) (((_) >> 0) & 0xffffffff)
		};

		uint32 flags;
	} ecx;

	union {
		struct {
			uint32 reserved1 : 8;

			/**
                         * [bit 8] invariant tsc available if 1.
                         */
			uint32 invarianttscavailable : 1;
#define cpuid_edx_invariant_tsc_available_bit 8
#define cpuid_edx_invariant_tsc_available_flag 0x100
#define cpuid_edx_invariant_tsc_available_mask 0x01
#define cpuid_edx_invariant_tsc_available(_) (((_) >> 8) & 0x01)
			uint32 reserved2 : 23;
		};

		uint32 flags;
	} edx;

} cpuid_eax_80000007;

/**
 * @}
 */

/**
 * @defgroup model_specific_registers \
 *           model specific registers
 *
 * @see vol2a[3.2(cpuid)] (reference)
 * @{
 */
/**
 * @defgroup ia32_p5_mc \
 *           ia32_p5_mc_(x)
 *
 * when machine-check exceptions are enabled for the pentium processor (mce flag is set in control register cr4), the
 * machine-check exception handler uses the rdmsr instruction to read the error type from the p5_mc_type register and the
 * machine check address from the p5_mc_addr register. the handler then normally reports these register values to the
 * system console before aborting execution.
 *
 * @see vol3b[15.10.2(pentium processor machine-check exception handling)] (reference)
 * @{
 */
/**
 * machine-check exception address.
 *
 * @remarks 05_01h
 * @see vol4[2.22(msrs in pentium processors)]
 */
#define ia32_p5_mc_addr 0x00000000

/**
 * machine-check exception type.
 *
 * @remarks 05_01h
 * @see vol4[2.22(msrs in pentium processors)]
 */
#define ia32_p5_mc_type 0x00000001
/**
 * @}
 */

/**
 * system coherence line size.
 *
 * @remarks 0f_03h
 * @see vol3a[8.10.5(monitor/mwait address range determination)]
 * @see vol3a[8.10.5(monitor/mwait address range determination)] (reference)
 */
#define ia32_monitor_filter_line_size 0x00000006

/**
 * value as returned by instruction rdtsc.
 *
 * @remarks 05_01h
 * @see vol3b[17.17(time-stamp counter)]
 */
#define ia32_time_stamp_counter 0x00000010

/**
 * the operating system can use this msr to determine "slot" information for the processor and the proper microcode update
 * to load.
 *
 * @remarks 06_01h
 */
#define ia32_platform_id 0x00000017
typedef union {
	struct {
		uint64 reserved1 : 50;

		/**
                 * @brief platform id <b>(ro)</b>
                 *
                 * [bits 52:50] contains information concerning the intended platform for the processor.
                 *
                 *
                 * 52 | 51 | 50 | _
                 * --:|:--:|:---|-----------------
                 * 0  | 0  | 0  | processor flag 0
                 * 0  | 0  | 1  | processor flag 1
                 * 0  | 1  | 0  | processor flag 2
                 * 0  | 1  | 1  | processor flag 3
                 * 1  | 0  | 0  | processor flag 4
                 * 1  | 0  | 1  | processor flag 5
                 * 1  | 1  | 0  | processor flag 6
                 * 1  | 1  | 1  | processor flag 7
                 */
		uint64 platformid : 3;
#define ia32_platform_id_platform_id_bit 50
#define ia32_platform_id_platform_id_flag 0x1c000000000000
#define ia32_platform_id_platform_id_mask 0x07
#define ia32_platform_id_platform_id(_) (((_) >> 50) & 0x07)
		uint64 reserved2 : 11;
	};

	uint64 flags;
} ia32_platform_id_register;

/**
 * this register holds the apic base address, permitting the relocation of the apic memory map.
 *
 * @remarks 06_01h
 * @see vol3a[10.4.4(local apic status and location)]
 * @see vol3a[10.4.5(relocating the local apic registers)]
 */
#define ia32_apic_base 0x0000001b
typedef union {
	struct {
		uint64 reserved1 : 8;

		/**
                 * [bit 8] bsp flag.
                 */
		uint64 bspflag : 1;
#define ia32_apic_base_bsp_flag_bit 8
#define ia32_apic_base_bsp_flag_flag 0x100
#define ia32_apic_base_bsp_flag_mask 0x01
#define ia32_apic_base_bsp_flag(_) (((_) >> 8) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * [bit 10] enable x2apic mode.
                 */
		uint64 enablex2apicmode : 1;
#define ia32_apic_base_enable_x2apic_mode_bit 10
#define ia32_apic_base_enable_x2apic_mode_flag 0x400
#define ia32_apic_base_enable_x2apic_mode_mask 0x01
#define ia32_apic_base_enable_x2apic_mode(_) (((_) >> 10) & 0x01)

		/**
                 * [bit 11] apic global enable.
                 */
		uint64 apicglobalenable : 1;
#define ia32_apic_base_apic_global_enable_bit 11
#define ia32_apic_base_apic_global_enable_flag 0x800
#define ia32_apic_base_apic_global_enable_mask 0x01
#define ia32_apic_base_apic_global_enable(_) (((_) >> 11) & 0x01)

		/**
                 * [bits 47:12] apic base.
                 */
		uint64 apicbase : 36;
#define ia32_apic_base_apic_base_bit 12
#define ia32_apic_base_apic_base_flag 0xfffffffff000
#define ia32_apic_base_apic_base_mask 0xfffffffff
#define ia32_apic_base_apic_base(_) (((_) >> 12) & 0xfffffffff)
		uint64 reserved3 : 16;
	};

	uint64 flags;
} ia32_apic_base_register;

/**
 * control features in intel 64 processor.
 *
 * @remarks if any one enumeration condition for defined bit field holds.
 */
#define ia32_feature_control 0x0000003a
typedef union {
	struct {
		/**
                 * @brief lock bit <b>(r/wo)</b>
                 *
                 * [bit 0] when set, locks this msr from being written; writes to this bit will result in gp(0).
                 *
                 * @note once the lock bit is set, the contents of this register cannot be modified. therefore the lock bit must be set
                 *       after configuring support for intel virtualization technology and prior to transferring control to an option rom or the
                 *       os. hence, once the lock bit is set, the entire ia32_feature_control contents are preserved across reset when pwrgood is
                 *       not deasserted.
                 * @remarks if any one enumeration condition for defined bit field position greater than bit 0 holds.
                 */
		uint64 lockbit : 1;
#define ia32_feature_control_lock_bit_bit 0
#define ia32_feature_control_lock_bit_flag 0x01
#define ia32_feature_control_lock_bit_mask 0x01
#define ia32_feature_control_lock_bit(_) (((_) >> 0) & 0x01)

		/**
                 * @brief enable vmx inside smx operation <b>(r/wl)</b>
                 *
                 * [bit 1] this bit enables a system executive to use vmx in conjunction with smx to support intel(r) trusted execution
                 * technology. bios must set this bit only when the cpuid function 1 returns vmx feature flag and smx feature flag set (ecx
                 * bits 5 and 6 respectively).
                 *
                 * @remarks if cpuid.01h:ecx[5] = 1 && cpuid.01h:ecx[6] = 1
                 */
		uint64 enablevmxinsidesmx : 1;
#define ia32_feature_control_enable_vmx_inside_smx_bit 1
#define ia32_feature_control_enable_vmx_inside_smx_flag 0x02
#define ia32_feature_control_enable_vmx_inside_smx_mask 0x01
#define ia32_feature_control_enable_vmx_inside_smx(_) (((_) >> 1) & 0x01)

		/**
                 * @brief enable vmx outside smx operation <b>(r/wl)</b>
                 *
                 * [bit 2] this bit enables vmx for a system executive that does not require smx. bios must set this bit only when the
                 * cpuid function 1 returns the vmx feature flag set (ecx bit 5).
                 *
                 * @remarks if cpuid.01h:ecx[5] = 1
                 */
		uint64 enablevmxoutsidesmx : 1;
#define ia32_feature_control_enable_vmx_outside_smx_bit 2
#define ia32_feature_control_enable_vmx_outside_smx_flag 0x04
#define ia32_feature_control_enable_vmx_outside_smx_mask 0x01
#define ia32_feature_control_enable_vmx_outside_smx(_) (((_) >> 2) & 0x01)
		uint64 reserved1 : 5;

		/**
                 * @brief senter local function enable <b>(r/wl)</b>
                 *
                 * [bits 14:8] when set, each bit in the field represents an enable control for a corresponding senter function. this field
                 * is supported only if cpuid.1:ecx.[bit 6] is set.
                 *
                 * @remarks if cpuid.01h:ecx[6] = 1
                 */
		uint64 senterlocalfunctionenables : 7;
#define ia32_feature_control_senter_local_function_enables_bit 8
#define ia32_feature_control_senter_local_function_enables_flag 0x7f00
#define ia32_feature_control_senter_local_function_enables_mask 0x7f
#define ia32_feature_control_senter_local_function_enables(_) \
	(((_) >> 8) & 0x7f)

		/**
                 * @brief senter global enable <b>(r/wl)</b>
                 *
                 * [bit 15] this bit must be set to enable senter leaf functions. this bit is supported only if cpuid.1:ecx.[bit 6] is set.
                 *
                 * @remarks if cpuid.01h:ecx[6] = 1
                 */
		uint64 senterglobalenable : 1;
#define ia32_feature_control_senter_global_enable_bit 15
#define ia32_feature_control_senter_global_enable_flag 0x8000
#define ia32_feature_control_senter_global_enable_mask 0x01
#define ia32_feature_control_senter_global_enable(_) (((_) >> 15) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * @brief sgx launch control enable <b>(r/wl)</b>
                 *
                 * [bit 17] this bit must be set to enable runtime reconfiguration of sgx launch control via the ia32_sgxlepubkeyhashn msr.
                 *
                 * @remarks if cpuid.(eax=07h, ecx=0h): ecx[30] = 1
                 */
		uint64 sgxlaunchcontrolenable : 1;
#define ia32_feature_control_sgx_launch_control_enable_bit 17
#define ia32_feature_control_sgx_launch_control_enable_flag 0x20000
#define ia32_feature_control_sgx_launch_control_enable_mask 0x01
#define ia32_feature_control_sgx_launch_control_enable(_) (((_) >> 17) & 0x01)

		/**
                 * @brief sgx global enable <b>(r/wl)</b>
                 *
                 * [bit 18] this bit must be set to enable sgx leaf functions.
                 *
                 * @remarks if cpuid.(eax=07h, ecx=0h): ebx[2] = 1
                 */
		uint64 sgxglobalenable : 1;
#define ia32_feature_control_sgx_global_enable_bit 18
#define ia32_feature_control_sgx_global_enable_flag 0x40000
#define ia32_feature_control_sgx_global_enable_mask 0x01
#define ia32_feature_control_sgx_global_enable(_) (((_) >> 18) & 0x01)
		uint64 reserved3 : 1;

		/**
                 * @brief lmce on <b>(r/wl)</b>
                 *
                 * [bit 20] when set, system software can program the msrs associated with lmce to configure delivery of some machine check
                 * exceptions to a single logical processor.
                 *
                 * @remarks if ia32_mcg_cap[27] = 1
                 */
		uint64 lmceon : 1;
#define ia32_feature_control_lmce_on_bit 20
#define ia32_feature_control_lmce_on_flag 0x100000
#define ia32_feature_control_lmce_on_mask 0x01
#define ia32_feature_control_lmce_on(_) (((_) >> 20) & 0x01)
		uint64 reserved4 : 43;
	};

	uint64 flags;
} ia32_feature_control_register;

/**
 * per logical processor tsc adjust.
 *
 * @remarks if cpuid.(eax=07h, ecx=0h): ebx[1] = 1
 */
#define ia32_tsc_adjust 0x0000003b
typedef struct {
	/**
         * local offset value of the ia32_tsc for a logical processor. reset value is zero. a write to ia32_tsc will modify the
         * local offset in ia32_tsc_adjust and the content of ia32_tsc, but does not affect the internal invariant tsc hardware.
         */
	uint64 threadadjust;
} ia32_tsc_adjust_register;

/**
 * @brief bios update trigger <b>(w)</b>
 *
 * executing a wrmsr instruction to this msr causes a microcode update to be loaded into the processor. a processor may
 * prevent writing to this msr when loading guest states on vm entries or saving guest states on vm exits.
 *
 * @remarks 06_01h
 * @see vol3a[9.11.6(microcode update loader)]
 */
#define ia32_bios_update_trigger 0x00000079

/**
 * @brief bios update signature <b>(ro)</b>
 *
 * returns the microcode update signature following the execution of cpuid.01h. a processor may prevent writing to this msr
 * when loading guest states on vm entries or saving guest states on vm exits.
 *
 * @remarks 06_01h
 */
#define ia32_bios_update_signature 0x0000008b
typedef union {
	struct {
		/**
                 * [bits 31:0] reserved.
                 */
		uint64 reserved : 32;
#define ia32_bios_update_signature_reserved_bit 0
#define ia32_bios_update_signature_reserved_flag 0xffffffff
#define ia32_bios_update_signature_reserved_mask 0xffffffff
#define ia32_bios_update_signature_reserved(_) (((_) >> 0) & 0xffffffff)

		/**
                 * @brief microcode update signature
                 *
                 * [bits 63:32] this field contains the signature of the currently loaded microcode update when read following the
                 * execution of the cpuid instruction, function 1. it is required that this register field be pre-loaded with zero prior to
                 * executing the cpuid, function 1. if the field remains equal to zero, then there is no microcode update loaded. another
                 * nonzero value will be the signature.
                 *
                 * @see vol3a[9.11.7.1(determining the signature)] (reference)
                 */
		uint64 microcodeupdatesignature : 32;
#define ia32_bios_update_signature_microcode_update_signature_bit 32
#define ia32_bios_update_signature_microcode_update_signature_flag \
	0xffffffff00000000
#define ia32_bios_update_signature_microcode_update_signature_mask 0xffffffff
#define ia32_bios_update_signature_microcode_update_signature(_) \
	(((_) >> 32) & 0xffffffff)
	};

	uint64 flags;
} ia32_bios_update_signature_register;

/**
 * @defgroup ia32_sgxlepubkeyhash \
 *           ia32_sgxlepubkeyhash[(64*n+63):(64*n)]
 *
 * bits (64*n+63):(64*n) of the sha256 digest of the sigstruct.modulus for sgx launch enclave. on reset, the default value
 * is the digest of intel's signing key.
 *
 * @remarks read permitted if cpuid.(eax=12h,ecx=0h): eax[0]=1 && cpuid.(eax=07h,ecx=0h):ecx[30]=1. write permitted if
 *          cpuid.(eax=12h,ecx=0h): eax[0]=1 && ia32_feature_control[17] = 1 && ia32_feature_control[0] = 1.
 * @{
 */
#define ia32_sgxlepubkeyhash0 0x0000008c
#define ia32_sgxlepubkeyhash1 0x0000008d
#define ia32_sgxlepubkeyhash2 0x0000008e
#define ia32_sgxlepubkeyhash3 0x0000008f
/**
 * @}
 */

/**
 * smm monitor configuration.
 *
 * @remarks if cpuid.01h: ecx[5]=1 || cpuid.01h: ecx[6] = 1
 */
#define ia32_smm_monitor_ctl 0x0000009b
typedef union {
	struct {
		/**
                 * @brief valid <b>(r/w)</b>
                 *
                 * [bit 0] the stm may be invoked using vmcall only if this bit is 1. because vmcall is used to activate the dual-monitor
                 * treatment, the dual-monitor treatment cannot be activated if the bit is 0. this bit is cleared when the logical
                 * processor is reset.
                 *
                 * @see vol3c[34.15.6(activating the dual-monitor treatment)]
                 * @see vol3c[34.15.5(enabling the dual-monitor treatment)] (reference)
                 */
		uint64 valid : 1;
#define ia32_smm_monitor_ctl_valid_bit 0
#define ia32_smm_monitor_ctl_valid_flag 0x01
#define ia32_smm_monitor_ctl_valid_mask 0x01
#define ia32_smm_monitor_ctl_valid(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 1;

		/**
                 * @brief controls smi unblocking by vmxoff
                 *
                 * [bit 2] determines whether executions of vmxoff unblock smis under the default treatment of smis and smm. executions of
                 * vmxoff unblock smis unless bit 2 is 1 (the value of bit 0 is irrelevant).
                 *
                 * @remarks if ia32_vmx_misc[28]
                 * @see vol3c[34.14.4(vmxoff and smi unblocking)]
                 * @see vol3c[34.15.5(enabling the dual-monitor treatment)] (reference)
                 */
		uint64 smiunblockingbyvmxoff : 1;
#define ia32_smm_monitor_ctl_smi_unblocking_by_vmxoff_bit 2
#define ia32_smm_monitor_ctl_smi_unblocking_by_vmxoff_flag 0x04
#define ia32_smm_monitor_ctl_smi_unblocking_by_vmxoff_mask 0x01
#define ia32_smm_monitor_ctl_smi_unblocking_by_vmxoff(_) (((_) >> 2) & 0x01)
		uint64 reserved2 : 9;

		/**
                 * @brief mseg base <b>(r/w)</b>
                 *
                 * [bits 31:12] value that, when shifted left 12 bits, is the physical address of mseg (the mseg base address).
                 *
                 * @see vol3c[34.15.5(enabling the dual-monitor treatment)] (reference)
                 */
		uint64 msegbase : 20;
#define ia32_smm_monitor_ctl_mseg_base_bit 12
#define ia32_smm_monitor_ctl_mseg_base_flag 0xfffff000
#define ia32_smm_monitor_ctl_mseg_base_mask 0xfffff
#define ia32_smm_monitor_ctl_mseg_base(_) (((_) >> 12) & 0xfffff)
		uint64 reserved3 : 32;
	};

	uint64 flags;
} ia32_smm_monitor_ctl_register;

typedef struct {
	/**
         * @brief mseg revision identifier
         *
         * different processors may use different mseg revision identifiers. these identifiers enable software to avoid using an
         * mseg header formatted for one processor on a processor that uses a different format. software can discover the mseg
         * revision identifier that a processor uses by reading the vmx capability msr ia32_vmx_misc.
         *
         * @see vol3d[a.6(miscellaneous data)]
         */
	uint32 msegheaderrevision;

	/**
         * @brief smm-transfer monitor features field
         *
         * bits 31:1 of this field are reserved and must be zero. bit 0 of the field is the ia-32e mode smm feature bit. it
         * indicates whether the logical processor will be in ia-32e mode after the stm is activated.
         *
         * @see vol3c[34.15.6(activating the dual-monitor treatment)]
         */
	uint32 monitorfeatures;

	/**
         * define values for the monitorfeatures field of mseg_header.
         */
#define ia32_stm_features_ia32e 0x00000001

	/**
         * fields that determine how processor state is loaded when the stm is activated. smm code should establish these fields so
         * that activating of the stm invokes the stm's initialization code.
         *
         * @see vol3c[34.15.6.5(loading host state)]
         */
	uint32 gdtrlimit;
	uint32 gdtrbaseoffset;
	uint32 csselector;
	uint32 eipoffset;
	uint32 espoffset;
	uint32 cr3offset;
} ia32_mseg_header;

/**
 * base address of the logical processor's smram image.
 *
 * @remarks if ia32_vmx_misc[15]
 */
#define ia32_smbase 0x0000009e
/**
 * @defgroup ia32_pmc \
 *           ia32_pmc(n)
 *
 * general performance counters.
 *
 * @remarks if cpuid.0ah: eax[15:8] > n
 * @{
 */
#define ia32_pmc0 0x000000c1
#define ia32_pmc1 0x000000c2
#define ia32_pmc2 0x000000c3
#define ia32_pmc3 0x000000c4
#define ia32_pmc4 0x000000c5
#define ia32_pmc5 0x000000c6
#define ia32_pmc6 0x000000c7
#define ia32_pmc7 0x000000c8
/**
 * @}
 */

/**
 * tsc frequency clock counter.
 *
 * @remarks if cpuid.06h: ecx[0] = 1
 */
#define ia32_mperf 0x000000e7
typedef struct {
	/**
         * @brief c0 tsc frequency clock count
         *
         * increments at fixed interval (relative to tsc freq.) when the logical processor is in c0. cleared upon overflow /
         * wrap-around of ia32_aperf.
         */
	uint64 c0mcnt;
} ia32_mperf_register;

/**
 * actual performance clock counter
 *
 * @remarks if cpuid.06h: ecx[0] = 1
 */
#define ia32_aperf 0x000000e8
typedef struct {
	/**
         * @brief c0 actual frequency clock count
         *
         * accumulates core clock counts at the coordinated clock frequency, when the logical processor is in c0. cleared upon
         * overflow / wrap-around of ia32_mperf.
         */
	uint64 c0acnt;
} ia32_aperf_register;

/**
 * mtrr capability.
 *
 * @see vol3a[11.11.2.1(ia32_mtrr_def_type msr)]
 * @see vol3a[11.11.1(mtrr feature identification)] (reference)
 */
#define ia32_mtrr_capabilities 0x000000fe
typedef union {
	struct {
		/**
                 * @brief vcnt (variable range registers count) field
                 *
                 * [bits 7:0] indicates the number of variable ranges implemented on the processor.
                 */
		uint64 variablerangecount : 8;
#define ia32_mtrr_capabilities_variable_range_count_bit 0
#define ia32_mtrr_capabilities_variable_range_count_flag 0xff
#define ia32_mtrr_capabilities_variable_range_count_mask 0xff
#define ia32_mtrr_capabilities_variable_range_count(_) (((_) >> 0) & 0xff)

		/**
                 * @brief fix (fixed range registers supported) flag
                 *
                 * [bit 8] fixed range mtrrs (ia32_mtrr_fix64k_00000 through ia32_mtrr_fix4k_0f8000) are supported when set; no fixed range
                 * registers are supported when clear.
                 */
		uint64 fixedrangesupported : 1;
#define ia32_mtrr_capabilities_fixed_range_supported_bit 8
#define ia32_mtrr_capabilities_fixed_range_supported_flag 0x100
#define ia32_mtrr_capabilities_fixed_range_supported_mask 0x01
#define ia32_mtrr_capabilities_fixed_range_supported(_) (((_) >> 8) & 0x01)
		uint64 reserved1 : 1;

		/**
                 * @brief wc (write combining) flag
                 *
                 * [bit 10] the write-combining (wc) memory type is supported when set; the wc type is not supported when clear.
                 */
		uint64 wcsupported : 1;
#define ia32_mtrr_capabilities_wc_supported_bit 10
#define ia32_mtrr_capabilities_wc_supported_flag 0x400
#define ia32_mtrr_capabilities_wc_supported_mask 0x01
#define ia32_mtrr_capabilities_wc_supported(_) (((_) >> 10) & 0x01)

		/**
                 * @brief smrr (system-management range register) flag
                 *
                 * [bit 11] the system-management range register (smrr) interface is supported when bit 11 is set; the smrr interface is
                 * not supported when clear.
                 */
		uint64 smrrsupported : 1;
#define ia32_mtrr_capabilities_smrr_supported_bit 11
#define ia32_mtrr_capabilities_smrr_supported_flag 0x800
#define ia32_mtrr_capabilities_smrr_supported_mask 0x01
#define ia32_mtrr_capabilities_smrr_supported(_) (((_) >> 11) & 0x01)
		uint64 reserved2 : 52;
	};

	uint64 flags;
} ia32_mtrr_capabilities_register;

/**
 * @brief sysenter_cs_msr <b>(r/w)</b>
 *
 * the lower 16 bits of this msr are the segment selector for the privilege level 0 code segment. this value is also used
 * to determine the segment selector of the privilege level 0 stack segment. this value cannot indicate a null selector.
 *
 * @remarks 06_01h
 * @see vol2b[4.3(instructions (m-u) | syscall - fast system call)] (reference)
 */
#define ia32_sysenter_cs 0x00000174
typedef union {
	struct {
		/**
                 * [bits 15:0] cs selector.
                 */
		uint64 csselector : 16;
#define ia32_sysenter_cs_cs_selector_bit 0
#define ia32_sysenter_cs_cs_selector_flag 0xffff
#define ia32_sysenter_cs_cs_selector_mask 0xffff
#define ia32_sysenter_cs_cs_selector(_) (((_) >> 0) & 0xffff)

		/**
                 * [bits 31:16] not used.
                 *
                 * @remarks can be read and written.
                 */
		uint64 notused1 : 16;
#define ia32_sysenter_cs_not_used_1_bit 16
#define ia32_sysenter_cs_not_used_1_flag 0xffff0000
#define ia32_sysenter_cs_not_used_1_mask 0xffff
#define ia32_sysenter_cs_not_used_1(_) (((_) >> 16) & 0xffff)

		/**
                 * [bits 63:32] not used.
                 *
                 * @remarks writes ignored; reads return zero.
                 */
		uint64 notused2 : 32;
#define ia32_sysenter_cs_not_used_2_bit 32
#define ia32_sysenter_cs_not_used_2_flag 0xffffffff00000000
#define ia32_sysenter_cs_not_used_2_mask 0xffffffff
#define ia32_sysenter_cs_not_used_2(_) (((_) >> 32) & 0xffffffff)
	};

	uint64 flags;
} ia32_sysenter_cs_register;

/**
 * @brief sysenter_esp_msr <b>(r/w)</b>
 *
 * the value of this msr is loaded into rsp (thus, this value contains the stack pointer for the privilege level 0 stack).
 * this value cannot represent a non-canonical address. in protected mode, only bits 31:0 are loaded.
 *
 * @remarks 06_01h
 * @see vol2b[4.3(instructions (m-u) | syscall - fast system call)] (reference)
 */
#define ia32_sysenter_esp 0x00000175

/**
 * @brief sysenter_eip_msr <b>(r/w)</b>
 *
 * the value of this msr is loaded into rip (thus, this value references the first instruction of the selected operating
 * procedure or routine). in protected mode, only bits 31:0 are loaded.
 *
 * @remarks 06_01h
 * @see vol2b[4.3(instructions (m-u) | syscall - fast system call)] (reference)
 */
#define ia32_sysenter_eip 0x00000176

/**
 * global machine check capability.
 *
 * @remarks 06_01h
 */
#define ia32_mcg_cap 0x00000179
typedef union {
	struct {
		/**
                 * [bits 7:0] number of reporting banks.
                 */
		uint64 count : 8;
#define ia32_mcg_cap_count_bit 0
#define ia32_mcg_cap_count_flag 0xff
#define ia32_mcg_cap_count_mask 0xff
#define ia32_mcg_cap_count(_) (((_) >> 0) & 0xff)

		/**
                 * [bit 8] ia32_mcg_ctl is present if this bit is set.
                 */
		uint64 mcgctlp : 1;
#define ia32_mcg_cap_mcg_ctl_p_bit 8
#define ia32_mcg_cap_mcg_ctl_p_flag 0x100
#define ia32_mcg_cap_mcg_ctl_p_mask 0x01
#define ia32_mcg_cap_mcg_ctl_p(_) (((_) >> 8) & 0x01)

		/**
                 * [bit 9] extended machine check state registers are present if this bit is set.
                 */
		uint64 mcgextp : 1;
#define ia32_mcg_cap_mcg_ext_p_bit 9
#define ia32_mcg_cap_mcg_ext_p_flag 0x200
#define ia32_mcg_cap_mcg_ext_p_mask 0x01
#define ia32_mcg_cap_mcg_ext_p(_) (((_) >> 9) & 0x01)

		/**
                 * [bit 10] support for corrected mc error event is present.
                 *
                 * @remarks 06_01h
                 */
		uint64 mcpcmcip : 1;
#define ia32_mcg_cap_mcp_cmci_p_bit 10
#define ia32_mcg_cap_mcp_cmci_p_flag 0x400
#define ia32_mcg_cap_mcp_cmci_p_mask 0x01
#define ia32_mcg_cap_mcp_cmci_p(_) (((_) >> 10) & 0x01)

		/**
                 * [bit 11] threshold-based error status register are present if this bit is set.
                 */
		uint64 mcgtesp : 1;
#define ia32_mcg_cap_mcg_tes_p_bit 11
#define ia32_mcg_cap_mcg_tes_p_flag 0x800
#define ia32_mcg_cap_mcg_tes_p_mask 0x01
#define ia32_mcg_cap_mcg_tes_p(_) (((_) >> 11) & 0x01)
		uint64 reserved1 : 4;

		/**
                 * [bits 23:16] number of extended machine check state registers present.
                 */
		uint64 mcgextcnt : 8;
#define ia32_mcg_cap_mcg_ext_cnt_bit 16
#define ia32_mcg_cap_mcg_ext_cnt_flag 0xff0000
#define ia32_mcg_cap_mcg_ext_cnt_mask 0xff
#define ia32_mcg_cap_mcg_ext_cnt(_) (((_) >> 16) & 0xff)

		/**
                 * [bit 24] the processor supports software error recovery if this bit is set.
                 */
		uint64 mcgserp : 1;
#define ia32_mcg_cap_mcg_ser_p_bit 24
#define ia32_mcg_cap_mcg_ser_p_flag 0x1000000
#define ia32_mcg_cap_mcg_ser_p_mask 0x01
#define ia32_mcg_cap_mcg_ser_p(_) (((_) >> 24) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * [bit 26] indicates that the processor allows platform firmware to be invoked when an error is detected so that it may
                 * provide additional platform specific information in an acpi format "generic error data entry" that augments the data
                 * included in machine check bank registers.
                 *
                 * @remarks 06_3eh
                 */
		uint64 mcgelogp : 1;
#define ia32_mcg_cap_mcg_elog_p_bit 26
#define ia32_mcg_cap_mcg_elog_p_flag 0x4000000
#define ia32_mcg_cap_mcg_elog_p_mask 0x01
#define ia32_mcg_cap_mcg_elog_p(_) (((_) >> 26) & 0x01)

		/**
                 * [bit 27] indicates that the processor supports extended state in ia32_mcg_status and associated msr necessary to
                 * configure local machine check exception (lmce).
                 *
                 * @remarks 06_3eh
                 */
		uint64 mcglmcep : 1;
#define ia32_mcg_cap_mcg_lmce_p_bit 27
#define ia32_mcg_cap_mcg_lmce_p_flag 0x8000000
#define ia32_mcg_cap_mcg_lmce_p_mask 0x01
#define ia32_mcg_cap_mcg_lmce_p(_) (((_) >> 27) & 0x01)
		uint64 reserved3 : 36;
	};

	uint64 flags;
} ia32_mcg_cap_register;

/**
 * global machine check status.
 *
 * @remarks 06_01h
 */
#define ia32_mcg_status 0x0000017a
typedef union {
	struct {
		/**
                 * [bit 0] restart ip valid.
                 *
                 * @remarks 06_01h
                 */
		uint64 ripv : 1;
#define ia32_mcg_status_ripv_bit 0
#define ia32_mcg_status_ripv_flag 0x01
#define ia32_mcg_status_ripv_mask 0x01
#define ia32_mcg_status_ripv(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] error ip valid.
                 *
                 * @remarks 06_01h
                 */
		uint64 eipv : 1;
#define ia32_mcg_status_eipv_bit 1
#define ia32_mcg_status_eipv_flag 0x02
#define ia32_mcg_status_eipv_mask 0x01
#define ia32_mcg_status_eipv(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] machine check in progress.
                 *
                 * @remarks 06_01h
                 */
		uint64 mcip : 1;
#define ia32_mcg_status_mcip_bit 2
#define ia32_mcg_status_mcip_flag 0x04
#define ia32_mcg_status_mcip_mask 0x01
#define ia32_mcg_status_mcip(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] if ia32_mcg_cap.lmce_p[27] = 1.
                 */
		uint64 lmces : 1;
#define ia32_mcg_status_lmce_s_bit 3
#define ia32_mcg_status_lmce_s_flag 0x08
#define ia32_mcg_status_lmce_s_mask 0x01
#define ia32_mcg_status_lmce_s(_) (((_) >> 3) & 0x01)
		uint64 reserved1 : 60;
	};

	uint64 flags;
} ia32_mcg_status_register;

/**
 * global machine check control.
 *
 * @remarks if ia32_mcg_cap.ctl_p[8] = 1
 */
#define ia32_mcg_ctl 0x0000017b
/**
 * @defgroup ia32_perfevtsel \
 *           ia32_perfevtsel(n)
 *
 * performance event select register n.
 *
 * @remarks if cpuid.0ah: eax[15:8] > n
 * @{
 */
#define ia32_perfevtsel0 0x00000186
#define ia32_perfevtsel1 0x00000187
#define ia32_perfevtsel2 0x00000188
#define ia32_perfevtsel3 0x00000189
typedef union {
	struct {
		/**
                 * [bits 7:0] selects a performance event logic unit.
                 */
		uint64 eventselect : 8;
#define ia32_perfevtsel_event_select_bit 0
#define ia32_perfevtsel_event_select_flag 0xff
#define ia32_perfevtsel_event_select_mask 0xff
#define ia32_perfevtsel_event_select(_) (((_) >> 0) & 0xff)

		/**
                 * [bits 15:8] qualifies the microarchitectural condition to detect on the selected event logic.
                 */
		uint64 umask : 8;
#define ia32_perfevtsel_u_mask_bit 8
#define ia32_perfevtsel_u_mask_flag 0xff00
#define ia32_perfevtsel_u_mask_mask 0xff
#define ia32_perfevtsel_u_mask(_) (((_) >> 8) & 0xff)

		/**
                 * [bit 16] counts while in privilege level is not ring 0.
                 */
		uint64 usr : 1;
#define ia32_perfevtsel_usr_bit 16
#define ia32_perfevtsel_usr_flag 0x10000
#define ia32_perfevtsel_usr_mask 0x01
#define ia32_perfevtsel_usr(_) (((_) >> 16) & 0x01)

		/**
                 * [bit 17] counts while in privilege level is ring 0.
                 */
		uint64 os : 1;
#define ia32_perfevtsel_os_bit 17
#define ia32_perfevtsel_os_flag 0x20000
#define ia32_perfevtsel_os_mask 0x01
#define ia32_perfevtsel_os(_) (((_) >> 17) & 0x01)

		/**
                 * [bit 18] enables edge detection if set.
                 */
		uint64 edge : 1;
#define ia32_perfevtsel_edge_bit 18
#define ia32_perfevtsel_edge_flag 0x40000
#define ia32_perfevtsel_edge_mask 0x01
#define ia32_perfevtsel_edge(_) (((_) >> 18) & 0x01)

		/**
                 * [bit 19] enables pin control.
                 */
		uint64 pc : 1;
#define ia32_perfevtsel_pc_bit 19
#define ia32_perfevtsel_pc_flag 0x80000
#define ia32_perfevtsel_pc_mask 0x01
#define ia32_perfevtsel_pc(_) (((_) >> 19) & 0x01)

		/**
                 * [bit 20] enables interrupt on counter overflow.
                 */
		uint64 intr : 1;
#define ia32_perfevtsel_intr_bit 20
#define ia32_perfevtsel_intr_flag 0x100000
#define ia32_perfevtsel_intr_mask 0x01
#define ia32_perfevtsel_intr(_) (((_) >> 20) & 0x01)

		/**
                 * [bit 21] when set to 1, it enables counting the associated event conditions occurring across all logical processors
                 * sharing a processor core. when set to 0, the counter only increments the associated event conditions occurring in the
                 * logical processor which programmed the msr.
                 */
		uint64 anythread : 1;
#define ia32_perfevtsel_any_thread_bit 21
#define ia32_perfevtsel_any_thread_flag 0x200000
#define ia32_perfevtsel_any_thread_mask 0x01
#define ia32_perfevtsel_any_thread(_) (((_) >> 21) & 0x01)

		/**
                 * [bit 22] enables the corresponding performance counter to commence counting when this bit is set.
                 */
		uint64 en : 1;
#define ia32_perfevtsel_en_bit 22
#define ia32_perfevtsel_en_flag 0x400000
#define ia32_perfevtsel_en_mask 0x01
#define ia32_perfevtsel_en(_) (((_) >> 22) & 0x01)

		/**
                 * [bit 23] invert the cmask.
                 */
		uint64 inv : 1;
#define ia32_perfevtsel_inv_bit 23
#define ia32_perfevtsel_inv_flag 0x800000
#define ia32_perfevtsel_inv_mask 0x01
#define ia32_perfevtsel_inv(_) (((_) >> 23) & 0x01)

		/**
                 * [bits 31:24] when cmask is not zero, the corresponding performance counter increments each cycle if the event count is
                 * greater than or equal to the cmask.
                 */
		uint64 cmask : 8;
#define ia32_perfevtsel_cmask_bit 24
#define ia32_perfevtsel_cmask_flag 0xff000000
#define ia32_perfevtsel_cmask_mask 0xff
#define ia32_perfevtsel_cmask(_) (((_) >> 24) & 0xff)
		uint64 reserved1 : 32;
	};

	uint64 flags;
} ia32_perfevtsel_register;

/**
 * @}
 */

/**
 * current performance status.
 *
 * @remarks 0f_03h
 * @see vol3b[14.1.1(software interface for initiating performance state transitions)]
 */
#define ia32_perf_status 0x00000198
typedef union {
	struct {
		/**
                 * [bits 15:0] current performance state value.
                 */
		uint64 statevalue : 16;
#define ia32_perf_status_state_value_bit 0
#define ia32_perf_status_state_value_flag 0xffff
#define ia32_perf_status_state_value_mask 0xffff
#define ia32_perf_status_state_value(_) (((_) >> 0) & 0xffff)
		uint64 reserved1 : 48;
	};

	uint64 flags;
} ia32_perf_status_register;

/**
 * @brief performance control <b>(r/w)</b>
 *
 * performance control. software makes a request for a new performance state (p-state) by writing this msr.
 *
 * @remarks 0f_03h
 * @see vol3b[14.1.1(software interface for initiating performance state transitions)]
 */
#define ia32_perf_ctl 0x00000199
typedef union {
	struct {
		/**
                 * [bits 15:0] target performance state value.
                 */
		uint64 targetstatevalue : 16;
#define ia32_perf_ctl_target_state_value_bit 0
#define ia32_perf_ctl_target_state_value_flag 0xffff
#define ia32_perf_ctl_target_state_value_mask 0xffff
#define ia32_perf_ctl_target_state_value(_) (((_) >> 0) & 0xffff)
		uint64 reserved1 : 16;

		/**
                 * [bit 32] ida engage.
                 *
                 * @remarks 06_0fh (mobile only)
                 */
		uint64 idaengage : 1;
#define ia32_perf_ctl_ida_engage_bit 32
#define ia32_perf_ctl_ida_engage_flag 0x100000000
#define ia32_perf_ctl_ida_engage_mask 0x01
#define ia32_perf_ctl_ida_engage(_) (((_) >> 32) & 0x01)
		uint64 reserved2 : 31;
	};

	uint64 flags;
} ia32_perf_ctl_register;

/**
 * clock modulation control.
 *
 * @remarks if cpuid.01h:edx[22] = 1
 * @see vol3b[14.7.3(software controlled clock modulation)]
 */
#define ia32_clock_modulation 0x0000019a
typedef union {
	struct {
		/**
                 * [bit 0] extended on-demand clock modulation duty cycle.
                 *
                 * @remarks if cpuid.06h:eax[5] = 1
                 */
		uint64 extendedondemandclockmodulationdutycycle : 1;
#define ia32_clock_modulation_extended_on_demand_clock_modulation_duty_cycle_bit \
	0
#define ia32_clock_modulation_extended_on_demand_clock_modulation_duty_cycle_flag \
	0x01
#define ia32_clock_modulation_extended_on_demand_clock_modulation_duty_cycle_mask \
	0x01
#define ia32_clock_modulation_extended_on_demand_clock_modulation_duty_cycle( \
	_)                                                                    \
	(((_) >> 0) & 0x01)

		/**
                 * @brief on-demand clock modulation duty cycle
                 *
                 * [bits 3:1] on-demand clock modulation duty cycle: specific encoded values for target duty cycle modulation.
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 ondemandclockmodulationdutycycle : 3;
#define ia32_clock_modulation_on_demand_clock_modulation_duty_cycle_bit 1
#define ia32_clock_modulation_on_demand_clock_modulation_duty_cycle_flag 0x0e
#define ia32_clock_modulation_on_demand_clock_modulation_duty_cycle_mask 0x07
#define ia32_clock_modulation_on_demand_clock_modulation_duty_cycle(_) \
	(((_) >> 1) & 0x07)

		/**
                 * @brief on-demand clock modulation enable
                 *
                 * [bit 4] on-demand clock modulation enable: set 1 to enable modulation.
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 ondemandclockmodulationenable : 1;
#define ia32_clock_modulation_on_demand_clock_modulation_enable_bit 4
#define ia32_clock_modulation_on_demand_clock_modulation_enable_flag 0x10
#define ia32_clock_modulation_on_demand_clock_modulation_enable_mask 0x01
#define ia32_clock_modulation_on_demand_clock_modulation_enable(_) \
	(((_) >> 4) & 0x01)
		uint64 reserved1 : 59;
	};

	uint64 flags;
} ia32_clock_modulation_register;

/**
 * @brief thermal interrupt control <b>(r/w)</b>
 *
 * thermal interrupt control. enables and disables the generation of an interrupt on temperature transitions detected with
 * the processor's thermal sensors and thermal monitor.
 *
 * @remarks if cpuid.01h:edx[22] = 1
 * @see vol3b[14.7.2(thermal monitor)]
 */
#define ia32_therm_interrupt 0x0000019b
typedef union {
	struct {
		/**
                 * [bit 0] high-temperature interrupt enable.
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 hightemperatureinterruptenable : 1;
#define ia32_therm_interrupt_high_temperature_interrupt_enable_bit 0
#define ia32_therm_interrupt_high_temperature_interrupt_enable_flag 0x01
#define ia32_therm_interrupt_high_temperature_interrupt_enable_mask 0x01
#define ia32_therm_interrupt_high_temperature_interrupt_enable(_) \
	(((_) >> 0) & 0x01)

		/**
                 * [bit 1] low-temperature interrupt enable.
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 lowtemperatureinterruptenable : 1;
#define ia32_therm_interrupt_low_temperature_interrupt_enable_bit 1
#define ia32_therm_interrupt_low_temperature_interrupt_enable_flag 0x02
#define ia32_therm_interrupt_low_temperature_interrupt_enable_mask 0x01
#define ia32_therm_interrupt_low_temperature_interrupt_enable(_) \
	(((_) >> 1) & 0x01)

		/**
                 * [bit 2] prochot\# interrupt enable.
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 prochotinterruptenable : 1;
#define ia32_therm_interrupt_prochot_interrupt_enable_bit 2
#define ia32_therm_interrupt_prochot_interrupt_enable_flag 0x04
#define ia32_therm_interrupt_prochot_interrupt_enable_mask 0x01
#define ia32_therm_interrupt_prochot_interrupt_enable(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] forcepr\# interrupt enable.
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 forceprinterruptenable : 1;
#define ia32_therm_interrupt_forcepr_interrupt_enable_bit 3
#define ia32_therm_interrupt_forcepr_interrupt_enable_flag 0x08
#define ia32_therm_interrupt_forcepr_interrupt_enable_mask 0x01
#define ia32_therm_interrupt_forcepr_interrupt_enable(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] critical temperature interrupt enable.
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 criticaltemperatureinterruptenable : 1;
#define ia32_therm_interrupt_critical_temperature_interrupt_enable_bit 4
#define ia32_therm_interrupt_critical_temperature_interrupt_enable_flag 0x10
#define ia32_therm_interrupt_critical_temperature_interrupt_enable_mask 0x01
#define ia32_therm_interrupt_critical_temperature_interrupt_enable(_) \
	(((_) >> 4) & 0x01)
		uint64 reserved1 : 3;

		/**
                 * [bits 14:8] threshold \#1 value
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 threshold1value : 7;
#define ia32_therm_interrupt_threshold1_value_bit 8
#define ia32_therm_interrupt_threshold1_value_flag 0x7f00
#define ia32_therm_interrupt_threshold1_value_mask 0x7f
#define ia32_therm_interrupt_threshold1_value(_) (((_) >> 8) & 0x7f)

		/**
                 * [bit 15] threshold \#1 interrupt enable.
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 threshold1interruptenable : 1;
#define ia32_therm_interrupt_threshold1_interrupt_enable_bit 15
#define ia32_therm_interrupt_threshold1_interrupt_enable_flag 0x8000
#define ia32_therm_interrupt_threshold1_interrupt_enable_mask 0x01
#define ia32_therm_interrupt_threshold1_interrupt_enable(_) (((_) >> 15) & 0x01)

		/**
                 * [bits 22:16] threshold \#2 value.
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 threshold2value : 7;
#define ia32_therm_interrupt_threshold2_value_bit 16
#define ia32_therm_interrupt_threshold2_value_flag 0x7f0000
#define ia32_therm_interrupt_threshold2_value_mask 0x7f
#define ia32_therm_interrupt_threshold2_value(_) (((_) >> 16) & 0x7f)

		/**
                 * [bit 23] threshold \#2 interrupt enable.
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 threshold2interruptenable : 1;
#define ia32_therm_interrupt_threshold2_interrupt_enable_bit 23
#define ia32_therm_interrupt_threshold2_interrupt_enable_flag 0x800000
#define ia32_therm_interrupt_threshold2_interrupt_enable_mask 0x01
#define ia32_therm_interrupt_threshold2_interrupt_enable(_) (((_) >> 23) & 0x01)

		/**
                 * [bit 24] power limit notification enable.
                 *
                 * @remarks if cpuid.06h:eax[4] = 1
                 */
		uint64 powerlimitnotificationenable : 1;
#define ia32_therm_interrupt_power_limit_notification_enable_bit 24
#define ia32_therm_interrupt_power_limit_notification_enable_flag 0x1000000
#define ia32_therm_interrupt_power_limit_notification_enable_mask 0x01
#define ia32_therm_interrupt_power_limit_notification_enable(_) \
	(((_) >> 24) & 0x01)
		uint64 reserved2 : 39;
	};

	uint64 flags;
} ia32_therm_interrupt_register;

/**
 * @brief thermal status information <b>(ro)</b>
 *
 * thermal status information. contains status information about the processor's thermal sensor and automatic thermal
 * monitoring facilities.
 *
 * @remarks if cpuid.01h:edx[22] = 1
 * @see vol3b[14.7.2(thermal monitor)]
 */
#define ia32_therm_status 0x0000019c
typedef union {
	struct {
		/**
                 * [bit 0] thermal status
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 thermalstatus : 1;
#define ia32_therm_status_thermal_status_bit 0
#define ia32_therm_status_thermal_status_flag 0x01
#define ia32_therm_status_thermal_status_mask 0x01
#define ia32_therm_status_thermal_status(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] thermal status log
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 thermalstatuslog : 1;
#define ia32_therm_status_thermal_status_log_bit 1
#define ia32_therm_status_thermal_status_log_flag 0x02
#define ia32_therm_status_thermal_status_log_mask 0x01
#define ia32_therm_status_thermal_status_log(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] prochot \# or forcepr\# event
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 prochotforceprevent : 1;
#define ia32_therm_status_prochot_forcepr_event_bit 2
#define ia32_therm_status_prochot_forcepr_event_flag 0x04
#define ia32_therm_status_prochot_forcepr_event_mask 0x01
#define ia32_therm_status_prochot_forcepr_event(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] prochot \# or forcepr\# log
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 prochotforceprlog : 1;
#define ia32_therm_status_prochot_forcepr_log_bit 3
#define ia32_therm_status_prochot_forcepr_log_flag 0x08
#define ia32_therm_status_prochot_forcepr_log_mask 0x01
#define ia32_therm_status_prochot_forcepr_log(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] critical temperature status
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 criticaltemperaturestatus : 1;
#define ia32_therm_status_critical_temperature_status_bit 4
#define ia32_therm_status_critical_temperature_status_flag 0x10
#define ia32_therm_status_critical_temperature_status_mask 0x01
#define ia32_therm_status_critical_temperature_status(_) (((_) >> 4) & 0x01)

		/**
                 * [bit 5] critical temperature status log
                 *
                 * @remarks if cpuid.01h:edx[22] = 1
                 */
		uint64 criticaltemperaturestatuslog : 1;
#define ia32_therm_status_critical_temperature_status_log_bit 5
#define ia32_therm_status_critical_temperature_status_log_flag 0x20
#define ia32_therm_status_critical_temperature_status_log_mask 0x01
#define ia32_therm_status_critical_temperature_status_log(_) (((_) >> 5) & 0x01)

		/**
                 * [bit 6] thermal threshold \#1 status
                 *
                 * @remarks if cpuid.01h:ecx[8] = 1
                 */
		uint64 thermalthreshold1status : 1;
#define ia32_therm_status_thermal_threshold1_status_bit 6
#define ia32_therm_status_thermal_threshold1_status_flag 0x40
#define ia32_therm_status_thermal_threshold1_status_mask 0x01
#define ia32_therm_status_thermal_threshold1_status(_) (((_) >> 6) & 0x01)

		/**
                 * [bit 7] thermal threshold \#1 log
                 *
                 * @remarks if cpuid.01h:ecx[8] = 1
                 */
		uint64 thermalthreshold1log : 1;
#define ia32_therm_status_thermal_threshold1_log_bit 7
#define ia32_therm_status_thermal_threshold1_log_flag 0x80
#define ia32_therm_status_thermal_threshold1_log_mask 0x01
#define ia32_therm_status_thermal_threshold1_log(_) (((_) >> 7) & 0x01)

		/**
                 * [bit 8] thermal threshold \#2 status
                 *
                 * @remarks if cpuid.01h:ecx[8] = 1
                 */
		uint64 thermalthreshold2status : 1;
#define ia32_therm_status_thermal_threshold2_status_bit 8
#define ia32_therm_status_thermal_threshold2_status_flag 0x100
#define ia32_therm_status_thermal_threshold2_status_mask 0x01
#define ia32_therm_status_thermal_threshold2_status(_) (((_) >> 8) & 0x01)

		/**
                 * [bit 9] thermal threshold \#2 log
                 *
                 * @remarks if cpuid.01h:ecx[8] = 1
                 */
		uint64 thermalthreshold2log : 1;
#define ia32_therm_status_thermal_threshold2_log_bit 9
#define ia32_therm_status_thermal_threshold2_log_flag 0x200
#define ia32_therm_status_thermal_threshold2_log_mask 0x01
#define ia32_therm_status_thermal_threshold2_log(_) (((_) >> 9) & 0x01)

		/**
                 * [bit 10] power limitation status
                 *
                 * @remarks if cpuid.06h:eax[4] = 1
                 */
		uint64 powerlimitationstatus : 1;
#define ia32_therm_status_power_limitation_status_bit 10
#define ia32_therm_status_power_limitation_status_flag 0x400
#define ia32_therm_status_power_limitation_status_mask 0x01
#define ia32_therm_status_power_limitation_status(_) (((_) >> 10) & 0x01)

		/**
                 * [bit 11] power limitation log
                 *
                 * @remarks if cpuid.06h:eax[4] = 1
                 */
		uint64 powerlimitationlog : 1;
#define ia32_therm_status_power_limitation_log_bit 11
#define ia32_therm_status_power_limitation_log_flag 0x800
#define ia32_therm_status_power_limitation_log_mask 0x01
#define ia32_therm_status_power_limitation_log(_) (((_) >> 11) & 0x01)

		/**
                 * [bit 12] current limit status
                 *
                 * @remarks if cpuid.06h:eax[7] = 1
                 */
		uint64 currentlimitstatus : 1;
#define ia32_therm_status_current_limit_status_bit 12
#define ia32_therm_status_current_limit_status_flag 0x1000
#define ia32_therm_status_current_limit_status_mask 0x01
#define ia32_therm_status_current_limit_status(_) (((_) >> 12) & 0x01)

		/**
                 * [bit 13] current limit log
                 *
                 * @remarks if cpuid.06h:eax[7] = 1
                 */
		uint64 currentlimitlog : 1;
#define ia32_therm_status_current_limit_log_bit 13
#define ia32_therm_status_current_limit_log_flag 0x2000
#define ia32_therm_status_current_limit_log_mask 0x01
#define ia32_therm_status_current_limit_log(_) (((_) >> 13) & 0x01)

		/**
                 * [bit 14] cross domain limit status
                 *
                 * @remarks if cpuid.06h:eax[7] = 1
                 */
		uint64 crossdomainlimitstatus : 1;
#define ia32_therm_status_cross_domain_limit_status_bit 14
#define ia32_therm_status_cross_domain_limit_status_flag 0x4000
#define ia32_therm_status_cross_domain_limit_status_mask 0x01
#define ia32_therm_status_cross_domain_limit_status(_) (((_) >> 14) & 0x01)

		/**
                 * [bit 15] cross domain limit log
                 *
                 * @remarks if cpuid.06h:eax[7] = 1
                 */
		uint64 crossdomainlimitlog : 1;
#define ia32_therm_status_cross_domain_limit_log_bit 15
#define ia32_therm_status_cross_domain_limit_log_flag 0x8000
#define ia32_therm_status_cross_domain_limit_log_mask 0x01
#define ia32_therm_status_cross_domain_limit_log(_) (((_) >> 15) & 0x01)

		/**
                 * [bits 22:16] digital readout
                 *
                 * @remarks if cpuid.06h:eax[0] = 1
                 */
		uint64 digitalreadout : 7;
#define ia32_therm_status_digital_readout_bit 16
#define ia32_therm_status_digital_readout_flag 0x7f0000
#define ia32_therm_status_digital_readout_mask 0x7f
#define ia32_therm_status_digital_readout(_) (((_) >> 16) & 0x7f)
		uint64 reserved1 : 4;

		/**
                 * [bits 30:27] resolution in degrees celsius
                 *
                 * @remarks if cpuid.06h:eax[0] = 1
                 */
		uint64 resolutionindegreescelsius : 4;
#define ia32_therm_status_resolution_in_degrees_celsius_bit 27
#define ia32_therm_status_resolution_in_degrees_celsius_flag 0x78000000
#define ia32_therm_status_resolution_in_degrees_celsius_mask 0x0f
#define ia32_therm_status_resolution_in_degrees_celsius(_) (((_) >> 27) & 0x0f)

		/**
                 * [bit 31] reading valid
                 *
                 * @remarks if cpuid.06h:eax[0] = 1
                 */
		uint64 readingvalid : 1;
#define ia32_therm_status_reading_valid_bit 31
#define ia32_therm_status_reading_valid_flag 0x80000000
#define ia32_therm_status_reading_valid_mask 0x01
#define ia32_therm_status_reading_valid(_) (((_) >> 31) & 0x01)
		uint64 reserved2 : 32;
	};

	uint64 flags;
} ia32_therm_status_register;

/**
 * @brief enable misc. processor features <b>(r/w)</b>
 *
 * allows a variety of processor functions to be enabled and disabled.
 */
#define ia32_misc_enable 0x000001a0
typedef union {
	struct {
		/**
                 * @brief fast-strings enable
                 *
                 * [bit 0] when set, the fast-strings feature (for rep movs and rep stors) is enabled (default). when clear, fast-strings
                 * are disabled.
                 *
                 * @remarks 0f_0h
                 */
		uint64 faststringsenable : 1;
#define ia32_misc_enable_fast_strings_enable_bit 0
#define ia32_misc_enable_fast_strings_enable_flag 0x01
#define ia32_misc_enable_fast_strings_enable_mask 0x01
#define ia32_misc_enable_fast_strings_enable(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 2;

		/**
                 * @brief automatic thermal control circuit enable <b>(r/w)</b>
                 *
                 * [bit 3] - 1 = setting this bit enables the thermal control circuit (tcc) portion of the intel thermal monitor feature.
                 * this allows the processor to automatically reduce power consumption in response to tcc activation.
                 * - 0 = disabled.
                 *
                 * @note in some products clearing this bit might be ignored in critical thermal conditions, and tm1, tm2 and adaptive
                 *       thermal throttling will still be activated. the default value of this field varies with product.
                 * @remarks 0f_0h
                 */
		uint64 automaticthermalcontrolcircuitenable : 1;
#define ia32_misc_enable_automatic_thermal_control_circuit_enable_bit 3
#define ia32_misc_enable_automatic_thermal_control_circuit_enable_flag 0x08
#define ia32_misc_enable_automatic_thermal_control_circuit_enable_mask 0x01
#define ia32_misc_enable_automatic_thermal_control_circuit_enable(_) \
	(((_) >> 3) & 0x01)
		uint64 reserved2 : 3;

		/**
                 * @brief performance monitoring available <b>(r)</b>
                 *
                 * [bit 7] - 1 = performance monitoring enabled.
                 * - 0 = performance monitoring disabled.
                 *
                 * @remarks 0f_0h
                 */
		uint64 performancemonitoringavailable : 1;
#define ia32_misc_enable_performance_monitoring_available_bit 7
#define ia32_misc_enable_performance_monitoring_available_flag 0x80
#define ia32_misc_enable_performance_monitoring_available_mask 0x01
#define ia32_misc_enable_performance_monitoring_available(_) (((_) >> 7) & 0x01)
		uint64 reserved3 : 3;

		/**
                 * @brief branch trace storage unavailable <b>(ro)</b>
                 *
                 * [bit 11] - 1 = processor doesn't support branch trace storage (bts).
                 * - 0 = bts is supported.
                 *
                 * @remarks 0f_0h
                 */
		uint64 branchtracestorageunavailable : 1;
#define ia32_misc_enable_branch_trace_storage_unavailable_bit 11
#define ia32_misc_enable_branch_trace_storage_unavailable_flag 0x800
#define ia32_misc_enable_branch_trace_storage_unavailable_mask 0x01
#define ia32_misc_enable_branch_trace_storage_unavailable(_) \
	(((_) >> 11) & 0x01)

		/**
                 * @brief processor event based sampling (pebs) unavailable <b>(ro)</b>
                 *
                 * [bit 12] - 1 = pebs is not supported.
                 * - 0 = pebs is supported.
                 *
                 * @remarks 06_0fh
                 */
		uint64 processoreventbasedsamplingunavailable : 1;
#define ia32_misc_enable_processor_event_based_sampling_unavailable_bit 12
#define ia32_misc_enable_processor_event_based_sampling_unavailable_flag 0x1000
#define ia32_misc_enable_processor_event_based_sampling_unavailable_mask 0x01
#define ia32_misc_enable_processor_event_based_sampling_unavailable(_) \
	(((_) >> 12) & 0x01)
		uint64 reserved4 : 3;

		/**
                 * @brief enhanced intel speedstep technology enable <b>(r/w)</b>
                 *
                 * [bit 16] - 0 = enhanced intel speedstep technology disabled.
                 * - 1 = enhanced intel speedstep technology enabled.
                 *
                 * @remarks if cpuid.01h: ecx[7] = 1
                 */
		uint64 enhancedintelspeedsteptechnologyenable : 1;
#define ia32_misc_enable_enhanced_intel_speedstep_technology_enable_bit 16
#define ia32_misc_enable_enhanced_intel_speedstep_technology_enable_flag 0x10000
#define ia32_misc_enable_enhanced_intel_speedstep_technology_enable_mask 0x01
#define ia32_misc_enable_enhanced_intel_speedstep_technology_enable(_) \
	(((_) >> 16) & 0x01)
		uint64 reserved5 : 1;

		/**
                 * @brief enable monitor fsm <b>(r/w)</b>
                 *
                 * [bit 18] when this bit is set to 0, the monitor feature flag is not set (cpuid.01h:ecx[bit3] = 0). this indicates that
                 * monitor/mwait are not supported. software attempts to execute monitor/mwait will cause \#ud when this bit is 0.
                 * when this bit is set to 1 (default), monitor/mwait are supported (cpuid.01h:ecx[bit 3] = 1). if the sse3 feature flag
                 * ecx[0] is not set (cpuid.01h:ecx[bit 0] = 0), the os must not attempt to alter this bit. bios must leave it in the
                 * default state. writing this bit when the sse3 feature flag is set to 0 may generate a \#gp exception.
                 *
                 * @remarks 0f_03h
                 */
		uint64 enablemonitorfsm : 1;
#define ia32_misc_enable_enable_monitor_fsm_bit 18
#define ia32_misc_enable_enable_monitor_fsm_flag 0x40000
#define ia32_misc_enable_enable_monitor_fsm_mask 0x01
#define ia32_misc_enable_enable_monitor_fsm(_) (((_) >> 18) & 0x01)
		uint64 reserved6 : 3;

		/**
                 * @brief limit cpuid maxval <b>(r/w)</b>
                 *
                 * [bit 22] when this bit is set to 1, cpuid.00h returns a maximum value in eax[7:0] of 2. bios should contain a setup
                 * question that allows users to specify when the installed os does not support cpuid functions greater than 2.
                 * before setting this bit, bios must execute the cpuid.0h and examine the maximum value returned in eax[7:0]. if the
                 * maximum value is greater than 2, this bit is supported.
                 * otherwise, this bit is not supported. setting this bit when the maximum value is not greater than 2 may generate a \#gp
                 * exception. setting this bit may cause unexpected behavior in software that depends on the availability of cpuid leaves
                 * greater than 2.
                 *
                 * @remarks 0f_03h
                 */
		uint64 limitcpuidmaxval : 1;
#define ia32_misc_enable_limit_cpuid_maxval_bit 22
#define ia32_misc_enable_limit_cpuid_maxval_flag 0x400000
#define ia32_misc_enable_limit_cpuid_maxval_mask 0x01
#define ia32_misc_enable_limit_cpuid_maxval(_) (((_) >> 22) & 0x01)

		/**
                 * @brief xtpr message disable <b>(r/w)</b>
                 *
                 * [bit 23] when set to 1, xtpr messages are disabled. xtpr messages are optional messages that allow the processor to
                 * inform the chipset of its priority.
                 *
                 * @remarks if cpuid.01h:ecx[14] = 1
                 */
		uint64 xtprmessagedisable : 1;
#define ia32_misc_enable_xtpr_message_disable_bit 23
#define ia32_misc_enable_xtpr_message_disable_flag 0x800000
#define ia32_misc_enable_xtpr_message_disable_mask 0x01
#define ia32_misc_enable_xtpr_message_disable(_) (((_) >> 23) & 0x01)
		uint64 reserved7 : 10;

		/**
                 * @brief xd bit disable <b>(r/w)</b>
                 *
                 * [bit 34] when set to 1, the execute disable bit feature (xd bit) is disabled and the xd bit extended feature flag will
                 * be clear (cpuid.80000001h: edx[20]=0).
                 * when set to a 0 (default), the execute disable bit feature (if available) allows the os to enable pae paging and take
                 * advantage of data only pages.
                 * bios must not alter the contents of this bit location, if xd bit is not supported. writing this bit to 1 when the xd bit
                 * extended feature flag is set to 0 may generate a \#gp exception.
                 *
                 * @remarks if cpuid.80000001h:edx[20] = 1
                 */
		uint64 xdbitdisable : 1;
#define ia32_misc_enable_xd_bit_disable_bit 34
#define ia32_misc_enable_xd_bit_disable_flag 0x400000000
#define ia32_misc_enable_xd_bit_disable_mask 0x01
#define ia32_misc_enable_xd_bit_disable(_) (((_) >> 34) & 0x01)
		uint64 reserved8 : 29;
	};

	uint64 flags;
} ia32_misc_enable_register;

/**
 * performance energy bias hint.
 *
 * @remarks if cpuid.6h:ecx[3] = 1
 */
#define ia32_energy_perf_bias 0x000001b0
typedef union {
	struct {
		/**
                 * @brief power policy preference
                 *
                 * [bits 3:0] - 0 indicates preference to highest performance.
                 * - 15 indicates preference to maximize energy saving.
                 */
		uint64 powerpolicypreference : 4;
#define ia32_energy_perf_bias_power_policy_preference_bit 0
#define ia32_energy_perf_bias_power_policy_preference_flag 0x0f
#define ia32_energy_perf_bias_power_policy_preference_mask 0x0f
#define ia32_energy_perf_bias_power_policy_preference(_) (((_) >> 0) & 0x0f)
		uint64 reserved1 : 60;
	};

	uint64 flags;
} ia32_energy_perf_bias_register;

/**
 * @brief package thermal status information <b>(ro)</b>
 *
 * package thermal status information. contains status information about the package's thermal sensor.
 *
 * @remarks if cpuid.06h: eax[6] = 1
 * @see vol3b[14.8(package level thermal management)]
 */
#define ia32_package_therm_status 0x000001b1
typedef union {
	struct {
		/**
                 * [bit 0] pkg thermal status
                 */
		uint64 thermalstatus : 1;
#define ia32_package_therm_status_thermal_status_bit 0
#define ia32_package_therm_status_thermal_status_flag 0x01
#define ia32_package_therm_status_thermal_status_mask 0x01
#define ia32_package_therm_status_thermal_status(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] pkg thermal status log
                 */
		uint64 thermalstatuslog : 1;
#define ia32_package_therm_status_thermal_status_log_bit 1
#define ia32_package_therm_status_thermal_status_log_flag 0x02
#define ia32_package_therm_status_thermal_status_log_mask 0x01
#define ia32_package_therm_status_thermal_status_log(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] pkg prochot \# event
                 */
		uint64 prochotevent : 1;
#define ia32_package_therm_status_prochot_event_bit 2
#define ia32_package_therm_status_prochot_event_flag 0x04
#define ia32_package_therm_status_prochot_event_mask 0x01
#define ia32_package_therm_status_prochot_event(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] pkg prochot \# log
                 */
		uint64 prochotlog : 1;
#define ia32_package_therm_status_prochot_log_bit 3
#define ia32_package_therm_status_prochot_log_flag 0x08
#define ia32_package_therm_status_prochot_log_mask 0x01
#define ia32_package_therm_status_prochot_log(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] pkg critical temperature status
                 */
		uint64 criticaltemperaturestatus : 1;
#define ia32_package_therm_status_critical_temperature_status_bit 4
#define ia32_package_therm_status_critical_temperature_status_flag 0x10
#define ia32_package_therm_status_critical_temperature_status_mask 0x01
#define ia32_package_therm_status_critical_temperature_status(_) \
	(((_) >> 4) & 0x01)

		/**
                 * [bit 5] pkg critical temperature status log
                 */
		uint64 criticaltemperaturestatuslog : 1;
#define ia32_package_therm_status_critical_temperature_status_log_bit 5
#define ia32_package_therm_status_critical_temperature_status_log_flag 0x20
#define ia32_package_therm_status_critical_temperature_status_log_mask 0x01
#define ia32_package_therm_status_critical_temperature_status_log(_) \
	(((_) >> 5) & 0x01)

		/**
                 * [bit 6] pkg thermal threshold \#1 status
                 */
		uint64 thermalthreshold1status : 1;
#define ia32_package_therm_status_thermal_threshold1_status_bit 6
#define ia32_package_therm_status_thermal_threshold1_status_flag 0x40
#define ia32_package_therm_status_thermal_threshold1_status_mask 0x01
#define ia32_package_therm_status_thermal_threshold1_status(_) \
	(((_) >> 6) & 0x01)

		/**
                 * [bit 7] pkg thermal threshold \#1 log
                 */
		uint64 thermalthreshold1log : 1;
#define ia32_package_therm_status_thermal_threshold1_log_bit 7
#define ia32_package_therm_status_thermal_threshold1_log_flag 0x80
#define ia32_package_therm_status_thermal_threshold1_log_mask 0x01
#define ia32_package_therm_status_thermal_threshold1_log(_) (((_) >> 7) & 0x01)

		/**
                 * [bit 8] pkg thermal threshold \#2 status
                 */
		uint64 thermalthreshold2status : 1;
#define ia32_package_therm_status_thermal_threshold2_status_bit 8
#define ia32_package_therm_status_thermal_threshold2_status_flag 0x100
#define ia32_package_therm_status_thermal_threshold2_status_mask 0x01
#define ia32_package_therm_status_thermal_threshold2_status(_) \
	(((_) >> 8) & 0x01)

		/**
                 * [bit 9] pkg thermal threshold \#2 log
                 */
		uint64 thermalthreshold2log : 1;
#define ia32_package_therm_status_thermal_threshold2_log_bit 9
#define ia32_package_therm_status_thermal_threshold2_log_flag 0x200
#define ia32_package_therm_status_thermal_threshold2_log_mask 0x01
#define ia32_package_therm_status_thermal_threshold2_log(_) (((_) >> 9) & 0x01)

		/**
                 * [bit 10] pkg power limitation status
                 */
		uint64 powerlimitationstatus : 1;
#define ia32_package_therm_status_power_limitation_status_bit 10
#define ia32_package_therm_status_power_limitation_status_flag 0x400
#define ia32_package_therm_status_power_limitation_status_mask 0x01
#define ia32_package_therm_status_power_limitation_status(_) \
	(((_) >> 10) & 0x01)

		/**
                 * [bit 11] pkg power limitation log
                 */
		uint64 powerlimitationlog : 1;
#define ia32_package_therm_status_power_limitation_log_bit 11
#define ia32_package_therm_status_power_limitation_log_flag 0x800
#define ia32_package_therm_status_power_limitation_log_mask 0x01
#define ia32_package_therm_status_power_limitation_log(_) (((_) >> 11) & 0x01)
		uint64 reserved1 : 4;

		/**
                 * [bits 22:16] pkg digital readout
                 */
		uint64 digitalreadout : 7;
#define ia32_package_therm_status_digital_readout_bit 16
#define ia32_package_therm_status_digital_readout_flag 0x7f0000
#define ia32_package_therm_status_digital_readout_mask 0x7f
#define ia32_package_therm_status_digital_readout(_) (((_) >> 16) & 0x7f)
		uint64 reserved2 : 41;
	};

	uint64 flags;
} ia32_package_therm_status_register;

/**
 * @brief package thermal interrupt control <b>(ro)</b>
 *
 * enables and disables the generation of an interrupt on temperature transitions detected with the package's thermal
 * sensor.
 *
 * @remarks if cpuid.06h: eax[6] = 1
 * @see vol3b[14.8(package level thermal management)]
 */
#define ia32_package_therm_interrupt 0x000001b2
typedef union {
	struct {
		/**
                 * [bit 0] pkg high-temperature interrupt enable.
                 */
		uint64 hightemperatureinterruptenable : 1;
#define ia32_package_therm_interrupt_high_temperature_interrupt_enable_bit 0
#define ia32_package_therm_interrupt_high_temperature_interrupt_enable_flag 0x01
#define ia32_package_therm_interrupt_high_temperature_interrupt_enable_mask 0x01
#define ia32_package_therm_interrupt_high_temperature_interrupt_enable(_) \
	(((_) >> 0) & 0x01)

		/**
                 * [bit 1] pkg low-temperature interrupt enable.
                 */
		uint64 lowtemperatureinterruptenable : 1;
#define ia32_package_therm_interrupt_low_temperature_interrupt_enable_bit 1
#define ia32_package_therm_interrupt_low_temperature_interrupt_enable_flag 0x02
#define ia32_package_therm_interrupt_low_temperature_interrupt_enable_mask 0x01
#define ia32_package_therm_interrupt_low_temperature_interrupt_enable(_) \
	(((_) >> 1) & 0x01)

		/**
                 * [bit 2] pkg prochot\# interrupt enable.
                 */
		uint64 prochotinterruptenable : 1;
#define ia32_package_therm_interrupt_prochot_interrupt_enable_bit 2
#define ia32_package_therm_interrupt_prochot_interrupt_enable_flag 0x04
#define ia32_package_therm_interrupt_prochot_interrupt_enable_mask 0x01
#define ia32_package_therm_interrupt_prochot_interrupt_enable(_) \
	(((_) >> 2) & 0x01)
		uint64 reserved1 : 1;

		/**
                 * [bit 4] pkg overheat interrupt enable.
                 */
		uint64 overheatinterruptenable : 1;
#define ia32_package_therm_interrupt_overheat_interrupt_enable_bit 4
#define ia32_package_therm_interrupt_overheat_interrupt_enable_flag 0x10
#define ia32_package_therm_interrupt_overheat_interrupt_enable_mask 0x01
#define ia32_package_therm_interrupt_overheat_interrupt_enable(_) \
	(((_) >> 4) & 0x01)
		uint64 reserved2 : 3;

		/**
                 * [bits 14:8] pkg threshold \#1 value
                 */
		uint64 threshold1value : 7;
#define ia32_package_therm_interrupt_threshold1_value_bit 8
#define ia32_package_therm_interrupt_threshold1_value_flag 0x7f00
#define ia32_package_therm_interrupt_threshold1_value_mask 0x7f
#define ia32_package_therm_interrupt_threshold1_value(_) (((_) >> 8) & 0x7f)

		/**
                 * [bit 15] pkg threshold \#1 interrupt enable.
                 */
		uint64 threshold1interruptenable : 1;
#define ia32_package_therm_interrupt_threshold1_interrupt_enable_bit 15
#define ia32_package_therm_interrupt_threshold1_interrupt_enable_flag 0x8000
#define ia32_package_therm_interrupt_threshold1_interrupt_enable_mask 0x01
#define ia32_package_therm_interrupt_threshold1_interrupt_enable(_) \
	(((_) >> 15) & 0x01)

		/**
                 * [bits 22:16] pkg threshold \#2 value.
                 */
		uint64 threshold2value : 7;
#define ia32_package_therm_interrupt_threshold2_value_bit 16
#define ia32_package_therm_interrupt_threshold2_value_flag 0x7f0000
#define ia32_package_therm_interrupt_threshold2_value_mask 0x7f
#define ia32_package_therm_interrupt_threshold2_value(_) (((_) >> 16) & 0x7f)

		/**
                 * [bit 23] pkg threshold \#2 interrupt enable.
                 */
		uint64 threshold2interruptenable : 1;
#define ia32_package_therm_interrupt_threshold2_interrupt_enable_bit 23
#define ia32_package_therm_interrupt_threshold2_interrupt_enable_flag 0x800000
#define ia32_package_therm_interrupt_threshold2_interrupt_enable_mask 0x01
#define ia32_package_therm_interrupt_threshold2_interrupt_enable(_) \
	(((_) >> 23) & 0x01)

		/**
                 * [bit 24] pkg power limit notification enable.
                 */
		uint64 powerlimitnotificationenable : 1;
#define ia32_package_therm_interrupt_power_limit_notification_enable_bit 24
#define ia32_package_therm_interrupt_power_limit_notification_enable_flag \
	0x1000000
#define ia32_package_therm_interrupt_power_limit_notification_enable_mask 0x01
#define ia32_package_therm_interrupt_power_limit_notification_enable(_) \
	(((_) >> 24) & 0x01)
		uint64 reserved3 : 39;
	};

	uint64 flags;
} ia32_package_therm_interrupt_register;

/**
 * trace/profile resource control.
 *
 * @remarks 06_0eh
 */
#define ia32_debugctl 0x000001d9
typedef union {
	struct {
		/**
                 * [bit 0] setting this bit to 1 enables the processor to record a running trace of the most recent branches taken by the
                 * processor in the lbr stack.
                 *
                 * @remarks 06_01h
                 */
		uint64 lbr : 1;
#define ia32_debugctl_lbr_bit 0
#define ia32_debugctl_lbr_flag 0x01
#define ia32_debugctl_lbr_mask 0x01
#define ia32_debugctl_lbr(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] setting this bit to 1 enables the processor to treat eflags.tf as single-step on branches instead of single-step
                 * on instructions.
                 *
                 * @remarks 06_01h
                 */
		uint64 btf : 1;
#define ia32_debugctl_btf_bit 1
#define ia32_debugctl_btf_flag 0x02
#define ia32_debugctl_btf_mask 0x01
#define ia32_debugctl_btf(_) (((_) >> 1) & 0x01)
		uint64 reserved1 : 4;

		/**
                 * [bit 6] setting this bit to 1 enables branch trace messages to be sent.
                 *
                 * @remarks 06_0eh
                 */
		uint64 tr : 1;
#define ia32_debugctl_tr_bit 6
#define ia32_debugctl_tr_flag 0x40
#define ia32_debugctl_tr_mask 0x01
#define ia32_debugctl_tr(_) (((_) >> 6) & 0x01)

		/**
                 * [bit 7] setting this bit enables branch trace messages (btms) to be logged in a bts buffer.
                 *
                 * @remarks 06_0eh
                 */
		uint64 bts : 1;
#define ia32_debugctl_bts_bit 7
#define ia32_debugctl_bts_flag 0x80
#define ia32_debugctl_bts_mask 0x01
#define ia32_debugctl_bts(_) (((_) >> 7) & 0x01)

		/**
                 * [bit 8] when clear, btms are logged in a bts buffer in circular fashion. when this bit is set, an interrupt is generated
                 * by the bts facility when the bts buffer is full.
                 *
                 * @remarks 06_0eh
                 */
		uint64 btint : 1;
#define ia32_debugctl_btint_bit 8
#define ia32_debugctl_btint_flag 0x100
#define ia32_debugctl_btint_mask 0x01
#define ia32_debugctl_btint(_) (((_) >> 8) & 0x01)

		/**
                 * [bit 9] when set, bts or btm is skipped if cpl = 0.
                 *
                 * @remarks 06_0fh
                 */
		uint64 btsoffos : 1;
#define ia32_debugctl_bts_off_os_bit 9
#define ia32_debugctl_bts_off_os_flag 0x200
#define ia32_debugctl_bts_off_os_mask 0x01
#define ia32_debugctl_bts_off_os(_) (((_) >> 9) & 0x01)

		/**
                 * [bit 10] when set, bts or btm is skipped if cpl > 0.
                 *
                 * @remarks 06_0fh
                 */
		uint64 btsoffusr : 1;
#define ia32_debugctl_bts_off_usr_bit 10
#define ia32_debugctl_bts_off_usr_flag 0x400
#define ia32_debugctl_bts_off_usr_mask 0x01
#define ia32_debugctl_bts_off_usr(_) (((_) >> 10) & 0x01)

		/**
                 * [bit 11] when set, the lbr stack is frozen on a pmi request.
                 *
                 * @remarks if cpuid.01h: ecx[15] = 1 && cpuid.0ah: eax[7:0] > 1
                 */
		uint64 freezelbrsonpmi : 1;
#define ia32_debugctl_freeze_lbrs_on_pmi_bit 11
#define ia32_debugctl_freeze_lbrs_on_pmi_flag 0x800
#define ia32_debugctl_freeze_lbrs_on_pmi_mask 0x01
#define ia32_debugctl_freeze_lbrs_on_pmi(_) (((_) >> 11) & 0x01)

		/**
                 * [bit 12] when set, each enable bit of the global counter control msr are frozen (address 38fh) on a pmi request.
                 *
                 * @remarks if cpuid.01h: ecx[15] = 1 && cpuid.0ah: eax[7:0] > 1
                 */
		uint64 freezeperfmononpmi : 1;
#define ia32_debugctl_freeze_perfmon_on_pmi_bit 12
#define ia32_debugctl_freeze_perfmon_on_pmi_flag 0x1000
#define ia32_debugctl_freeze_perfmon_on_pmi_mask 0x01
#define ia32_debugctl_freeze_perfmon_on_pmi(_) (((_) >> 12) & 0x01)

		/**
                 * [bit 13] when set, enables the logical processor to receive and generate pmi on behalf of the uncore.
                 *
                 * @remarks 06_1ah
                 */
		uint64 enableuncorepmi : 1;
#define ia32_debugctl_enable_uncore_pmi_bit 13
#define ia32_debugctl_enable_uncore_pmi_flag 0x2000
#define ia32_debugctl_enable_uncore_pmi_mask 0x01
#define ia32_debugctl_enable_uncore_pmi(_) (((_) >> 13) & 0x01)

		/**
                 * [bit 14] when set, freezes perfmon and trace messages while in smm.
                 *
                 * @remarks if ia32_perf_capabilities[12] = 1
                 */
		uint64 freezewhilesmm : 1;
#define ia32_debugctl_freeze_while_smm_bit 14
#define ia32_debugctl_freeze_while_smm_flag 0x4000
#define ia32_debugctl_freeze_while_smm_mask 0x01
#define ia32_debugctl_freeze_while_smm(_) (((_) >> 14) & 0x01)

		/**
                 * [bit 15] when set, enables dr7 debug bit on xbegin.
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=0):ebx[11] = 1)
                 */
		uint64 rtmdebug : 1;
#define ia32_debugctl_rtm_debug_bit 15
#define ia32_debugctl_rtm_debug_flag 0x8000
#define ia32_debugctl_rtm_debug_mask 0x01
#define ia32_debugctl_rtm_debug(_) (((_) >> 15) & 0x01)
		uint64 reserved2 : 48;
	};

	uint64 flags;
} ia32_debugctl_register;

/**
 * @brief smrr base address <b>(writeable only in smm)</b>
 *
 * smrr base address. base address of smm memory range.
 *
 * @remarks if ia32_mtrrcap.smrr[11] = 1
 */
#define ia32_smrr_physbase 0x000001f2
typedef union {
	struct {
		/**
                 * @brief type
                 *
                 * [bits 7:0] type. specifies memory type of the range.
                 */
		uint64 type : 8;
#define ia32_smrr_physbase_type_bit 0
#define ia32_smrr_physbase_type_flag 0xff
#define ia32_smrr_physbase_type_mask 0xff
#define ia32_smrr_physbase_type(_) (((_) >> 0) & 0xff)
		uint64 reserved1 : 4;

		/**
                 * [bits 31:12] smrr physical base address.
                 */
		uint64 smrrphysicalbaseaddress : 20;
#define ia32_smrr_physbase_smrr_physical_base_address_bit 12
#define ia32_smrr_physbase_smrr_physical_base_address_flag 0xfffff000
#define ia32_smrr_physbase_smrr_physical_base_address_mask 0xfffff
#define ia32_smrr_physbase_smrr_physical_base_address(_) (((_) >> 12) & 0xfffff)
		uint64 reserved2 : 32;
	};

	uint64 flags;
} ia32_smrr_physbase_register;

/**
 * @brief smrr range mask <b>(writeable only in smm)</b>
 *
 * range mask of smm memory range.
 *
 * @remarks if ia32_mtrrcap[smrr] = 1
 */
#define ia32_smrr_physmask 0x000001f3
typedef union {
	struct {
		uint64 reserved1 : 11;

		/**
                 * [bit 11] enable range mask.
                 */
		uint64 enablerangemask : 1;
#define ia32_smrr_physmask_enable_range_mask_bit 11
#define ia32_smrr_physmask_enable_range_mask_flag 0x800
#define ia32_smrr_physmask_enable_range_mask_mask 0x01
#define ia32_smrr_physmask_enable_range_mask(_) (((_) >> 11) & 0x01)

		/**
                 * [bits 31:12] smrr address range mask.
                 */
		uint64 smrraddressrangemask : 20;
#define ia32_smrr_physmask_smrr_address_range_mask_bit 12
#define ia32_smrr_physmask_smrr_address_range_mask_flag 0xfffff000
#define ia32_smrr_physmask_smrr_address_range_mask_mask 0xfffff
#define ia32_smrr_physmask_smrr_address_range_mask(_) (((_) >> 12) & 0xfffff)
		uint64 reserved2 : 32;
	};

	uint64 flags;
} ia32_smrr_physmask_register;

/**
 * dca capability.
 *
 * @remarks if cpuid.01h: ecx[18] = 1
 */
#define ia32_platform_dca_cap 0x000001f8

/**
 * if set, cpu supports prefetch-hint type.
 *
 * @remarks if cpuid.01h: ecx[18] = 1
 */
#define ia32_cpu_dca_cap 0x000001f9

/**
 * dca type 0 status and control register.
 *
 * @remarks if cpuid.01h: ecx[18] = 1
 */
#define ia32_dca_0_cap 0x000001fa
typedef union {
	struct {
		/**
                 * [bit 0] set by hw when dca is fuseenabled and no defeatures are set.
                 */
		uint64 dcaactive : 1;
#define ia32_dca_0_cap_dca_active_bit 0
#define ia32_dca_0_cap_dca_active_flag 0x01
#define ia32_dca_0_cap_dca_active_mask 0x01
#define ia32_dca_0_cap_dca_active(_) (((_) >> 0) & 0x01)

		/**
                 * [bits 2:1] transaction.
                 */
		uint64 transaction : 2;
#define ia32_dca_0_cap_transaction_bit 1
#define ia32_dca_0_cap_transaction_flag 0x06
#define ia32_dca_0_cap_transaction_mask 0x03
#define ia32_dca_0_cap_transaction(_) (((_) >> 1) & 0x03)

		/**
                 * [bits 6:3] dca_type.
                 */
		uint64 dcatype : 4;
#define ia32_dca_0_cap_dca_type_bit 3
#define ia32_dca_0_cap_dca_type_flag 0x78
#define ia32_dca_0_cap_dca_type_mask 0x0f
#define ia32_dca_0_cap_dca_type(_) (((_) >> 3) & 0x0f)

		/**
                 * [bits 10:7] dca_queue_size.
                 */
		uint64 dcaqueuesize : 4;
#define ia32_dca_0_cap_dca_queue_size_bit 7
#define ia32_dca_0_cap_dca_queue_size_flag 0x780
#define ia32_dca_0_cap_dca_queue_size_mask 0x0f
#define ia32_dca_0_cap_dca_queue_size(_) (((_) >> 7) & 0x0f)
		uint64 reserved1 : 2;

		/**
                 * [bits 16:13] writes will update the register but have no hw side-effect.
                 */
		uint64 dcadelay : 4;
#define ia32_dca_0_cap_dca_delay_bit 13
#define ia32_dca_0_cap_dca_delay_flag 0x1e000
#define ia32_dca_0_cap_dca_delay_mask 0x0f
#define ia32_dca_0_cap_dca_delay(_) (((_) >> 13) & 0x0f)
		uint64 reserved2 : 7;

		/**
                 * [bit 24] sw can request dca block by setting this bit.
                 */
		uint64 swblock : 1;
#define ia32_dca_0_cap_sw_block_bit 24
#define ia32_dca_0_cap_sw_block_flag 0x1000000
#define ia32_dca_0_cap_sw_block_mask 0x01
#define ia32_dca_0_cap_sw_block(_) (((_) >> 24) & 0x01)
		uint64 reserved3 : 1;

		/**
                 * [bit 26] set when dca is blocked by hw (e.g. cr0.cd = 1).
                 */
		uint64 hwblock : 1;
#define ia32_dca_0_cap_hw_block_bit 26
#define ia32_dca_0_cap_hw_block_flag 0x4000000
#define ia32_dca_0_cap_hw_block_mask 0x01
#define ia32_dca_0_cap_hw_block(_) (((_) >> 26) & 0x01)
		uint64 reserved4 : 37;
	};

	uint64 flags;
} ia32_dca_0_cap_register;

/**
 * @defgroup ia32_mtrr_physbase \
 *           ia32_mtrr_physbase(n)
 *
 * ia32_mtrr_physbase(0-9).
 *
 * @remarks if cpuid.01h: edx.mtrr[12] = 1
 * @see vol3a[11.11.2.3(variable range mtrrs)]
 * @{
 */
typedef union {
	struct {
		/**
                 * [bits 7:0] specifies the memory type for the range.
                 */
		uint64 type : 8;
#define ia32_mtrr_physbase_type_bit 0
#define ia32_mtrr_physbase_type_flag 0xff
#define ia32_mtrr_physbase_type_mask 0xff
#define ia32_mtrr_physbase_type(_) (((_) >> 0) & 0xff)
		uint64 reserved1 : 4;

		/**
                 * [bits 47:12] specifies the base address of the address range. this 24-bit value, in the case where maxphyaddr is 36
                 * bits, is extended by 12 bits at the low end to form the base address (this automatically aligns the address on a 4-kbyte
                 * boundary).
                 */
		uint64 pageframenumber : 36;
#define ia32_mtrr_physbase_page_frame_number_bit 12
#define ia32_mtrr_physbase_page_frame_number_flag 0xfffffffff000
#define ia32_mtrr_physbase_page_frame_number_mask 0xfffffffff
#define ia32_mtrr_physbase_page_frame_number(_) (((_) >> 12) & 0xfffffffff)
		uint64 reserved2 : 16;
	};

	uint64 flags;
} ia32_mtrr_physbase_register;

#define ia32_mtrr_physbase0 0x00000200
#define ia32_mtrr_physbase1 0x00000202
#define ia32_mtrr_physbase2 0x00000204
#define ia32_mtrr_physbase3 0x00000206
#define ia32_mtrr_physbase4 0x00000208
#define ia32_mtrr_physbase5 0x0000020a
#define ia32_mtrr_physbase6 0x0000020c
#define ia32_mtrr_physbase7 0x0000020e
#define ia32_mtrr_physbase8 0x00000210
#define ia32_mtrr_physbase9 0x00000212
/**
 * @}
 */

/**
 * @defgroup ia32_mtrr_physmask \
 *           ia32_mtrr_physmask(n)
 *
 * ia32_mtrr_physmask(0-9).
 *
 * @remarks if cpuid.01h: edx.mtrr[12] = 1
 * @see vol3a[11.11.2.3(variable range mtrrs)]
 * @{
 */
typedef union {
	struct {
		/**
                 * [bits 7:0] specifies the memory type for the range.
                 */
		uint64 type : 8;
#define ia32_mtrr_physmask_type_bit 0
#define ia32_mtrr_physmask_type_flag 0xff
#define ia32_mtrr_physmask_type_mask 0xff
#define ia32_mtrr_physmask_type(_) (((_) >> 0) & 0xff)
		uint64 reserved1 : 3;

		/**
                 * [bit 11] enables the register pair when set; disables register pair when clear.
                 */
		uint64 valid : 1;
#define ia32_mtrr_physmask_valid_bit 11
#define ia32_mtrr_physmask_valid_flag 0x800
#define ia32_mtrr_physmask_valid_mask 0x01
#define ia32_mtrr_physmask_valid(_) (((_) >> 11) & 0x01)

		/**
                 * [bits 47:12] specifies a mask (24 bits if the maximum physical address size is 36 bits, 28 bits if the maximum physical
                 * address size is 40 bits). the mask determines the range of the region being mapped, according to the following
                 * relationships:
                 * - address_within_range and physmask = physbase and physmask
                 * - this value is extended by 12 bits at the low end to form the mask value.
                 * - the width of the physmask field depends on the maximum physical address size supported by the processor.
                 * cpuid.80000008h reports the maximum physical address size supported by the processor. if cpuid.80000008h is not
                 * available, software may assume that the processor supports a 36-bit physical address size.
                 *
                 * @see vol3a[11.11.3(example base and mask calculations)]
                 */
		uint64 pageframenumber : 36;
#define ia32_mtrr_physmask_page_frame_number_bit 12
#define ia32_mtrr_physmask_page_frame_number_flag 0xfffffffff000
#define ia32_mtrr_physmask_page_frame_number_mask 0xfffffffff
#define ia32_mtrr_physmask_page_frame_number(_) (((_) >> 12) & 0xfffffffff)
		uint64 reserved2 : 16;
	};

	uint64 flags;
} ia32_mtrr_physmask_register;

#define ia32_mtrr_physmask0 0x00000201
#define ia32_mtrr_physmask1 0x00000203
#define ia32_mtrr_physmask2 0x00000205
#define ia32_mtrr_physmask3 0x00000207
#define ia32_mtrr_physmask4 0x00000209
#define ia32_mtrr_physmask5 0x0000020b
#define ia32_mtrr_physmask6 0x0000020d
#define ia32_mtrr_physmask7 0x0000020f
#define ia32_mtrr_physmask8 0x00000211
#define ia32_mtrr_physmask9 0x00000213
/**
 * @}
 */

/**
 * @defgroup ia32_mtrr_fix \
 *           ia32_mtrr_fix(x)
 *
 * ia32_mtrr_fix(x).
 *
 * @remarks if cpuid.01h: edx.mtrr[12] = 1
 * @see vol3a[11.11.2.2(fixed range mtrrs)]
 * @{
 */
/**
 * @defgroup ia32_mtrr_fix64k \
 *           ia32_mtrr_fix64k(x)
 *
 * ia32_mtrr_fix64k(x).
 * @{
 */
#define ia32_mtrr_fix64k_base 0x00000000
#define ia32_mtrr_fix64k_size 0x00010000
#define ia32_mtrr_fix64k_00000 0x00000250
/**
 * @}
 */

/**
 * @defgroup ia32_mtrr_fix16k \
 *           ia32_mtrr_fix16k(x)
 *
 * ia32_mtrr_fix16k(x).
 * @{
 */
#define ia32_mtrr_fix16k_base 0x00080000
#define ia32_mtrr_fix16k_size 0x00004000
#define ia32_mtrr_fix16k_80000 0x00000258
#define ia32_mtrr_fix16k_a0000 0x00000259
/**
 * @}
 */

/**
 * @defgroup ia32_mtrr_fix4k \
 *           ia32_mtrr_fix4k(x)
 *
 * ia32_mtrr_fix4k(x).
 * @{
 */
#define ia32_mtrr_fix4k_base 0x000c0000
#define ia32_mtrr_fix4k_size 0x00001000
#define ia32_mtrr_fix4k_c0000 0x00000268
#define ia32_mtrr_fix4k_c8000 0x00000269
#define ia32_mtrr_fix4k_d0000 0x0000026a
#define ia32_mtrr_fix4k_d8000 0x0000026b
#define ia32_mtrr_fix4k_e0000 0x0000026c
#define ia32_mtrr_fix4k_e8000 0x0000026d
#define ia32_mtrr_fix4k_f0000 0x0000026e
#define ia32_mtrr_fix4k_f8000 0x0000026f
/**
 * @}
 */

/**
 * architecture defined number of fixed range mtrrs (1 for 64k, 2 for 16k, 8 for 4k).
 */
#define ia32_mtrr_fix_count ((1 + 2 + 8) * 8)

/**
 * architecture defined number of variable range mtrrs.
 */
#define ia32_mtrr_variable_count 0x000000ff

/**
 * a size of array to store all possible mtrrs.
 */
#define ia32_mtrr_count (ia32_mtrr_fix_count + ia32_mtrr_variable_count)
/**
 * @}
 */

/**
 * ia32_pat.
 *
 * @remarks if cpuid.01h: edx.mtrr[16] = 1
 */
#define ia32_pat 0x00000277
typedef union {
	struct {
		/**
                 * [bits 2:0] pa0.
                 */
		uint64 pa0 : 3;
#define ia32_pat_pa0_bit 0
#define ia32_pat_pa0_flag 0x07
#define ia32_pat_pa0_mask 0x07
#define ia32_pat_pa0(_) (((_) >> 0) & 0x07)
		uint64 reserved1 : 5;

		/**
                 * [bits 10:8] pa1.
                 */
		uint64 pa1 : 3;
#define ia32_pat_pa1_bit 8
#define ia32_pat_pa1_flag 0x700
#define ia32_pat_pa1_mask 0x07
#define ia32_pat_pa1(_) (((_) >> 8) & 0x07)
		uint64 reserved2 : 5;

		/**
                 * [bits 18:16] pa2.
                 */
		uint64 pa2 : 3;
#define ia32_pat_pa2_bit 16
#define ia32_pat_pa2_flag 0x70000
#define ia32_pat_pa2_mask 0x07
#define ia32_pat_pa2(_) (((_) >> 16) & 0x07)
		uint64 reserved3 : 5;

		/**
                 * [bits 26:24] pa3.
                 */
		uint64 pa3 : 3;
#define ia32_pat_pa3_bit 24
#define ia32_pat_pa3_flag 0x7000000
#define ia32_pat_pa3_mask 0x07
#define ia32_pat_pa3(_) (((_) >> 24) & 0x07)
		uint64 reserved4 : 5;

		/**
                 * [bits 34:32] pa4.
                 */
		uint64 pa4 : 3;
#define ia32_pat_pa4_bit 32
#define ia32_pat_pa4_flag 0x700000000
#define ia32_pat_pa4_mask 0x07
#define ia32_pat_pa4(_) (((_) >> 32) & 0x07)
		uint64 reserved5 : 5;

		/**
                 * [bits 42:40] pa5.
                 */
		uint64 pa5 : 3;
#define ia32_pat_pa5_bit 40
#define ia32_pat_pa5_flag 0x70000000000
#define ia32_pat_pa5_mask 0x07
#define ia32_pat_pa5(_) (((_) >> 40) & 0x07)
		uint64 reserved6 : 5;

		/**
                 * [bits 50:48] pa6.
                 */
		uint64 pa6 : 3;
#define ia32_pat_pa6_bit 48
#define ia32_pat_pa6_flag 0x7000000000000
#define ia32_pat_pa6_mask 0x07
#define ia32_pat_pa6(_) (((_) >> 48) & 0x07)
		uint64 reserved7 : 5;

		/**
                 * [bits 58:56] pa7.
                 */
		uint64 pa7 : 3;
#define ia32_pat_pa7_bit 56
#define ia32_pat_pa7_flag 0x700000000000000
#define ia32_pat_pa7_mask 0x07
#define ia32_pat_pa7(_) (((_) >> 56) & 0x07)
		uint64 reserved8 : 5;
	};

	uint64 flags;
} ia32_pat_register;

/**
 * @defgroup ia32_mc_ctl2 \
 *           ia32_mc(i)_ctl2
 *
 * msr to enable/disable cmci capability for bank n.
 *
 * @remarks if ia32_mcg_cap[10] = 1 && ia32_mcg_cap[7:0] > n
 * @see vol3b[15.3.2.5(ia32_mci_ctl2 msrs)]
 * @{
 */
#define ia32_mc0_ctl2 0x00000280
#define ia32_mc1_ctl2 0x00000281
#define ia32_mc2_ctl2 0x00000282
#define ia32_mc3_ctl2 0x00000283
#define ia32_mc4_ctl2 0x00000284
#define ia32_mc5_ctl2 0x00000285
#define ia32_mc6_ctl2 0x00000286
#define ia32_mc7_ctl2 0x00000287
#define ia32_mc8_ctl2 0x00000288
#define ia32_mc9_ctl2 0x00000289
#define ia32_mc10_ctl2 0x0000028a
#define ia32_mc11_ctl2 0x0000028b
#define ia32_mc12_ctl2 0x0000028c
#define ia32_mc13_ctl2 0x0000028d
#define ia32_mc14_ctl2 0x0000028e
#define ia32_mc15_ctl2 0x0000028f
#define ia32_mc16_ctl2 0x00000290
#define ia32_mc17_ctl2 0x00000291
#define ia32_mc18_ctl2 0x00000292
#define ia32_mc19_ctl2 0x00000293
#define ia32_mc20_ctl2 0x00000294
#define ia32_mc21_ctl2 0x00000295
#define ia32_mc22_ctl2 0x00000296
#define ia32_mc23_ctl2 0x00000297
#define ia32_mc24_ctl2 0x00000298
#define ia32_mc25_ctl2 0x00000299
#define ia32_mc26_ctl2 0x0000029a
#define ia32_mc27_ctl2 0x0000029b
#define ia32_mc28_ctl2 0x0000029c
#define ia32_mc29_ctl2 0x0000029d
#define ia32_mc30_ctl2 0x0000029e
#define ia32_mc31_ctl2 0x0000029f
typedef union {
	struct {
		/**
                 * [bits 14:0] corrected error count threshold.
                 */
		uint64 correctederrorcountthreshold : 15;
#define ia32_mc_ctl2_corrected_error_count_threshold_bit 0
#define ia32_mc_ctl2_corrected_error_count_threshold_flag 0x7fff
#define ia32_mc_ctl2_corrected_error_count_threshold_mask 0x7fff
#define ia32_mc_ctl2_corrected_error_count_threshold(_) (((_) >> 0) & 0x7fff)
		uint64 reserved1 : 15;

		/**
                 * [bit 30] cmci_en.
                 */
		uint64 cmcien : 1;
#define ia32_mc_ctl2_cmci_en_bit 30
#define ia32_mc_ctl2_cmci_en_flag 0x40000000
#define ia32_mc_ctl2_cmci_en_mask 0x01
#define ia32_mc_ctl2_cmci_en(_) (((_) >> 30) & 0x01)
		uint64 reserved2 : 33;
	};

	uint64 flags;
} ia32_mc_ctl2_register;

/**
 * @}
 */

/**
 * ia32_mtrr_def_type.
 *
 * @remarks if cpuid.01h: edx.mtrr[12] = 1
 */
#define ia32_mtrr_def_type 0x000002ff
typedef union {
	struct {
		/**
                 * [bits 2:0] default memory type.
                 */
		uint64 defaultmemorytype : 3;
#define ia32_mtrr_def_type_default_memory_type_bit 0
#define ia32_mtrr_def_type_default_memory_type_flag 0x07
#define ia32_mtrr_def_type_default_memory_type_mask 0x07
#define ia32_mtrr_def_type_default_memory_type(_) (((_) >> 0) & 0x07)
		uint64 reserved1 : 7;

		/**
                 * [bit 10] fixed range mtrr enable.
                 */
		uint64 fixedrangemtrrenable : 1;
#define ia32_mtrr_def_type_fixed_range_mtrr_enable_bit 10
#define ia32_mtrr_def_type_fixed_range_mtrr_enable_flag 0x400
#define ia32_mtrr_def_type_fixed_range_mtrr_enable_mask 0x01
#define ia32_mtrr_def_type_fixed_range_mtrr_enable(_) (((_) >> 10) & 0x01)

		/**
                 * [bit 11] mtrr enable.
                 */
		uint64 mtrrenable : 1;
#define ia32_mtrr_def_type_mtrr_enable_bit 11
#define ia32_mtrr_def_type_mtrr_enable_flag 0x800
#define ia32_mtrr_def_type_mtrr_enable_mask 0x01
#define ia32_mtrr_def_type_mtrr_enable(_) (((_) >> 11) & 0x01)
		uint64 reserved2 : 52;
	};

	uint64 flags;
} ia32_mtrr_def_type_register;

/**
 * @defgroup ia32_fixed_ctr \
 *           ia32_fixed_ctr(n)
 *
 * fixed-function performance counter n.
 *
 * @remarks if cpuid.0ah: edx[4:0] > n
 * @{
 */
/**
 * counts instr_retired.any.
 */
#define ia32_fixed_ctr0 0x00000309

/**
 * counts cpu_clk_unhalted.core
 */
#define ia32_fixed_ctr1 0x0000030a

/**
 * counts cpu_clk_unhalted.ref
 */
#define ia32_fixed_ctr2 0x0000030b
/**
 * @}
 */

/**
 * read only msr that enumerates the existence of performance monitoring features.
 *
 * @remarks if cpuid.01h: ecx[15] = 1
 */
#define ia32_perf_capabilities 0x00000345
typedef union {
	struct {
		/**
                 * [bits 5:0] lbr format.
                 */
		uint64 lbrformat : 6;
#define ia32_perf_capabilities_lbr_format_bit 0
#define ia32_perf_capabilities_lbr_format_flag 0x3f
#define ia32_perf_capabilities_lbr_format_mask 0x3f
#define ia32_perf_capabilities_lbr_format(_) (((_) >> 0) & 0x3f)

		/**
                 * [bit 6] pebs trap.
                 */
		uint64 pebstrap : 1;
#define ia32_perf_capabilities_pebs_trap_bit 6
#define ia32_perf_capabilities_pebs_trap_flag 0x40
#define ia32_perf_capabilities_pebs_trap_mask 0x01
#define ia32_perf_capabilities_pebs_trap(_) (((_) >> 6) & 0x01)

		/**
                 * [bit 7] pebssavearchregs.
                 */
		uint64 pebssavearchregs : 1;
#define ia32_perf_capabilities_pebs_save_arch_regs_bit 7
#define ia32_perf_capabilities_pebs_save_arch_regs_flag 0x80
#define ia32_perf_capabilities_pebs_save_arch_regs_mask 0x01
#define ia32_perf_capabilities_pebs_save_arch_regs(_) (((_) >> 7) & 0x01)

		/**
                 * [bits 11:8] pebs record format.
                 */
		uint64 pebsrecordformat : 4;
#define ia32_perf_capabilities_pebs_record_format_bit 8
#define ia32_perf_capabilities_pebs_record_format_flag 0xf00
#define ia32_perf_capabilities_pebs_record_format_mask 0x0f
#define ia32_perf_capabilities_pebs_record_format(_) (((_) >> 8) & 0x0f)

		/**
                 * [bit 12] freeze while smm is supported.
                 */
		uint64 freezewhilesmmissupported : 1;
#define ia32_perf_capabilities_freeze_while_smm_is_supported_bit 12
#define ia32_perf_capabilities_freeze_while_smm_is_supported_flag 0x1000
#define ia32_perf_capabilities_freeze_while_smm_is_supported_mask 0x01
#define ia32_perf_capabilities_freeze_while_smm_is_supported(_) \
	(((_) >> 12) & 0x01)

		/**
                 * [bit 13] full width of counter writable via ia32_a_pmcx.
                 */
		uint64 fullwidthcounterwrite : 1;
#define ia32_perf_capabilities_full_width_counter_write_bit 13
#define ia32_perf_capabilities_full_width_counter_write_flag 0x2000
#define ia32_perf_capabilities_full_width_counter_write_mask 0x01
#define ia32_perf_capabilities_full_width_counter_write(_) (((_) >> 13) & 0x01)
		uint64 reserved1 : 50;
	};

	uint64 flags;
} ia32_perf_capabilities_register;

/**
 * @brief fixed-function performance counter control <b>(r/w)</b>
 *
 * fixed-function performance counter control. counter increments while the results of anding respective enable bit in
 * ia32_perf_global_ctrl with the corresponding os or usr bits in this msr is true.
 *
 * @remarks if cpuid.0ah: eax[7:0] > 1
 */
#define ia32_fixed_ctr_ctrl 0x0000038d
typedef union {
	struct {
		/**
                 * [bit 0] en0_os: enable fixed counter 0 to count while cpl = 0.
                 */
		uint64 en0os : 1;
#define ia32_fixed_ctr_ctrl_en0_os_bit 0
#define ia32_fixed_ctr_ctrl_en0_os_flag 0x01
#define ia32_fixed_ctr_ctrl_en0_os_mask 0x01
#define ia32_fixed_ctr_ctrl_en0_os(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] en0_usr: enable fixed counter 0 to count while cpl > 0.
                 */
		uint64 en0usr : 1;
#define ia32_fixed_ctr_ctrl_en0_usr_bit 1
#define ia32_fixed_ctr_ctrl_en0_usr_flag 0x02
#define ia32_fixed_ctr_ctrl_en0_usr_mask 0x01
#define ia32_fixed_ctr_ctrl_en0_usr(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] anythread: when set to 1, it enables counting the associated event conditions occurring across all logical
                 * processors sharing a processor core. when set to 0, the counter only increments the associated event conditions
                 * occurring in the logical processor which programmed the msr.
                 */
		uint64 anythread0 : 1;
#define ia32_fixed_ctr_ctrl_any_thread0_bit 2
#define ia32_fixed_ctr_ctrl_any_thread0_flag 0x04
#define ia32_fixed_ctr_ctrl_any_thread0_mask 0x01
#define ia32_fixed_ctr_ctrl_any_thread0(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] en0_pmi: enable pmi when fixed counter 0 overflows.
                 */
		uint64 en0pmi : 1;
#define ia32_fixed_ctr_ctrl_en0_pmi_bit 3
#define ia32_fixed_ctr_ctrl_en0_pmi_flag 0x08
#define ia32_fixed_ctr_ctrl_en0_pmi_mask 0x01
#define ia32_fixed_ctr_ctrl_en0_pmi(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] en1_os: enable fixed counter 1 to count while cpl = 0.
                 */
		uint64 en1os : 1;
#define ia32_fixed_ctr_ctrl_en1_os_bit 4
#define ia32_fixed_ctr_ctrl_en1_os_flag 0x10
#define ia32_fixed_ctr_ctrl_en1_os_mask 0x01
#define ia32_fixed_ctr_ctrl_en1_os(_) (((_) >> 4) & 0x01)

		/**
                 * [bit 5] en1_usr: enable fixed counter 1 to count while cpl > 0.
                 */
		uint64 en1usr : 1;
#define ia32_fixed_ctr_ctrl_en1_usr_bit 5
#define ia32_fixed_ctr_ctrl_en1_usr_flag 0x20
#define ia32_fixed_ctr_ctrl_en1_usr_mask 0x01
#define ia32_fixed_ctr_ctrl_en1_usr(_) (((_) >> 5) & 0x01)

		/**
                 * [bit 6] anythread: when set to 1, it enables counting the associated event conditions occurring across all logical
                 * processors sharing a processor core. when set to 0, the counter only increments the associated event conditions
                 * occurring in the logical processor which programmed the msr.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 2
                 */
		uint64 anythread1 : 1;
#define ia32_fixed_ctr_ctrl_any_thread1_bit 6
#define ia32_fixed_ctr_ctrl_any_thread1_flag 0x40
#define ia32_fixed_ctr_ctrl_any_thread1_mask 0x01
#define ia32_fixed_ctr_ctrl_any_thread1(_) (((_) >> 6) & 0x01)

		/**
                 * [bit 7] en1_pmi: enable pmi when fixed counter 1 overflows.
                 */
		uint64 en1pmi : 1;
#define ia32_fixed_ctr_ctrl_en1_pmi_bit 7
#define ia32_fixed_ctr_ctrl_en1_pmi_flag 0x80
#define ia32_fixed_ctr_ctrl_en1_pmi_mask 0x01
#define ia32_fixed_ctr_ctrl_en1_pmi(_) (((_) >> 7) & 0x01)

		/**
                 * [bit 8] en2_os: enable fixed counter 2 to count while cpl = 0.
                 */
		uint64 en2os : 1;
#define ia32_fixed_ctr_ctrl_en2_os_bit 8
#define ia32_fixed_ctr_ctrl_en2_os_flag 0x100
#define ia32_fixed_ctr_ctrl_en2_os_mask 0x01
#define ia32_fixed_ctr_ctrl_en2_os(_) (((_) >> 8) & 0x01)

		/**
                 * [bit 9] en2_usr: enable fixed counter 2 to count while cpl > 0.
                 */
		uint64 en2usr : 1;
#define ia32_fixed_ctr_ctrl_en2_usr_bit 9
#define ia32_fixed_ctr_ctrl_en2_usr_flag 0x200
#define ia32_fixed_ctr_ctrl_en2_usr_mask 0x01
#define ia32_fixed_ctr_ctrl_en2_usr(_) (((_) >> 9) & 0x01)

		/**
                 * [bit 10] anythread: when set to 1, it enables counting the associated event conditions occurring across all logical
                 * processors sharing a processor core. when set to 0, the counter only increments the associated event conditions
                 * occurring in the logical processor which programmed the msr.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 2
                 */
		uint64 anythread2 : 1;
#define ia32_fixed_ctr_ctrl_any_thread2_bit 10
#define ia32_fixed_ctr_ctrl_any_thread2_flag 0x400
#define ia32_fixed_ctr_ctrl_any_thread2_mask 0x01
#define ia32_fixed_ctr_ctrl_any_thread2(_) (((_) >> 10) & 0x01)

		/**
                 * [bit 11] en2_pmi: enable pmi when fixed counter 2 overflows.
                 */
		uint64 en2pmi : 1;
#define ia32_fixed_ctr_ctrl_en2_pmi_bit 11
#define ia32_fixed_ctr_ctrl_en2_pmi_flag 0x800
#define ia32_fixed_ctr_ctrl_en2_pmi_mask 0x01
#define ia32_fixed_ctr_ctrl_en2_pmi(_) (((_) >> 11) & 0x01)
		uint64 reserved1 : 52;
	};

	uint64 flags;
} ia32_fixed_ctr_ctrl_register;

/**
 * global performance counter status.
 *
 * @remarks if cpuid.0ah: eax[7:0] > 0
 */
#define ia32_perf_global_status 0x0000038e
typedef union {
	struct {
		/**
                 * [bit 0] ovf_pmc0: overflow status of ia32_pmc0.
                 *
                 * @remarks if cpuid.0ah: eax[15:8] > 0
                 */
		uint64 ovfpmc0 : 1;
#define ia32_perf_global_status_ovf_pmc0_bit 0
#define ia32_perf_global_status_ovf_pmc0_flag 0x01
#define ia32_perf_global_status_ovf_pmc0_mask 0x01
#define ia32_perf_global_status_ovf_pmc0(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] ovf_pmc1: overflow status of ia32_pmc1.
                 *
                 * @remarks if cpuid.0ah: eax[15:8] > 1
                 */
		uint64 ovfpmc1 : 1;
#define ia32_perf_global_status_ovf_pmc1_bit 1
#define ia32_perf_global_status_ovf_pmc1_flag 0x02
#define ia32_perf_global_status_ovf_pmc1_mask 0x01
#define ia32_perf_global_status_ovf_pmc1(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] ovf_pmc2: overflow status of ia32_pmc2.
                 *
                 * @remarks if cpuid.0ah: eax[15:8] > 2
                 */
		uint64 ovfpmc2 : 1;
#define ia32_perf_global_status_ovf_pmc2_bit 2
#define ia32_perf_global_status_ovf_pmc2_flag 0x04
#define ia32_perf_global_status_ovf_pmc2_mask 0x01
#define ia32_perf_global_status_ovf_pmc2(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] ovf_pmc3: overflow status of ia32_pmc3.
                 *
                 * @remarks if cpuid.0ah: eax[15:8] > 3
                 */
		uint64 ovfpmc3 : 1;
#define ia32_perf_global_status_ovf_pmc3_bit 3
#define ia32_perf_global_status_ovf_pmc3_flag 0x08
#define ia32_perf_global_status_ovf_pmc3_mask 0x01
#define ia32_perf_global_status_ovf_pmc3(_) (((_) >> 3) & 0x01)
		uint64 reserved1 : 28;

		/**
                 * [bit 32] ovf_fixedctr0: overflow status of ia32_fixed_ctr0.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 1
                 */
		uint64 ovffixedctr0 : 1;
#define ia32_perf_global_status_ovf_fixedctr0_bit 32
#define ia32_perf_global_status_ovf_fixedctr0_flag 0x100000000
#define ia32_perf_global_status_ovf_fixedctr0_mask 0x01
#define ia32_perf_global_status_ovf_fixedctr0(_) (((_) >> 32) & 0x01)

		/**
                 * [bit 33] ovf_fixedctr1: overflow status of ia32_fixed_ctr1.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 1
                 */
		uint64 ovffixedctr1 : 1;
#define ia32_perf_global_status_ovf_fixedctr1_bit 33
#define ia32_perf_global_status_ovf_fixedctr1_flag 0x200000000
#define ia32_perf_global_status_ovf_fixedctr1_mask 0x01
#define ia32_perf_global_status_ovf_fixedctr1(_) (((_) >> 33) & 0x01)

		/**
                 * [bit 34] ovf_fixedctr2: overflow status of ia32_fixed_ctr2.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 1
                 */
		uint64 ovffixedctr2 : 1;
#define ia32_perf_global_status_ovf_fixedctr2_bit 34
#define ia32_perf_global_status_ovf_fixedctr2_flag 0x400000000
#define ia32_perf_global_status_ovf_fixedctr2_mask 0x01
#define ia32_perf_global_status_ovf_fixedctr2(_) (((_) >> 34) & 0x01)
		uint64 reserved2 : 20;

		/**
                 * [bit 55] trace_topa_pmi: a pmi occurred due to a topa entry memory buffer that was completely filled.
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=0):ebx[25] = 1) && ia32_rtit_ctl.topa = 1
                 */
		uint64 tracetopapmi : 1;
#define ia32_perf_global_status_trace_topa_pmi_bit 55
#define ia32_perf_global_status_trace_topa_pmi_flag 0x80000000000000
#define ia32_perf_global_status_trace_topa_pmi_mask 0x01
#define ia32_perf_global_status_trace_topa_pmi(_) (((_) >> 55) & 0x01)
		uint64 reserved3 : 2;

		/**
                 * [bit 58] lbr_frz. lbrs are frozen due to:
                 * * ia32_debugctl.freeze_lbr_on_pmi=1.
                 * * the lbr stack overflowed.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 3
                 */
		uint64 lbrfrz : 1;
#define ia32_perf_global_status_lbr_frz_bit 58
#define ia32_perf_global_status_lbr_frz_flag 0x400000000000000
#define ia32_perf_global_status_lbr_frz_mask 0x01
#define ia32_perf_global_status_lbr_frz(_) (((_) >> 58) & 0x01)

		/**
                 * [bit 59] ctr_frz. performance counters in the core pmu are frozen due to:
                 * * ia32_debugctl.freeze_perfmon_on_pmi=1.
                 * * one or more core pmu counters overflowed.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 3
                 */
		uint64 ctrfrz : 1;
#define ia32_perf_global_status_ctr_frz_bit 59
#define ia32_perf_global_status_ctr_frz_flag 0x800000000000000
#define ia32_perf_global_status_ctr_frz_mask 0x01
#define ia32_perf_global_status_ctr_frz(_) (((_) >> 59) & 0x01)

		/**
                 * [bit 60] asci: data in the performance counters in the core pmu may include contributions from the direct or indirect
                 * operation intel sgx to protect an enclave.
                 *
                 * @remarks if cpuid.(eax=07h, ecx=0):ebx[2] = 1
                 */
		uint64 asci : 1;
#define ia32_perf_global_status_asci_bit 60
#define ia32_perf_global_status_asci_flag 0x1000000000000000
#define ia32_perf_global_status_asci_mask 0x01
#define ia32_perf_global_status_asci(_) (((_) >> 60) & 0x01)

		/**
                 * [bit 61] uncore counter overflow status.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 2
                 */
		uint64 ovfuncore : 1;
#define ia32_perf_global_status_ovf_uncore_bit 61
#define ia32_perf_global_status_ovf_uncore_flag 0x2000000000000000
#define ia32_perf_global_status_ovf_uncore_mask 0x01
#define ia32_perf_global_status_ovf_uncore(_) (((_) >> 61) & 0x01)

		/**
                 * [bit 62] ovfbuf: ds save area buffer overflow status.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 0
                 */
		uint64 ovfbuf : 1;
#define ia32_perf_global_status_ovf_buf_bit 62
#define ia32_perf_global_status_ovf_buf_flag 0x4000000000000000
#define ia32_perf_global_status_ovf_buf_mask 0x01
#define ia32_perf_global_status_ovf_buf(_) (((_) >> 62) & 0x01)

		/**
                 * [bit 63] condchgd: status bits of this register have changed.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 0
                 */
		uint64 condchgd : 1;
#define ia32_perf_global_status_cond_chgd_bit 63
#define ia32_perf_global_status_cond_chgd_flag 0x8000000000000000
#define ia32_perf_global_status_cond_chgd_mask 0x01
#define ia32_perf_global_status_cond_chgd(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} ia32_perf_global_status_register;

/**
 * @brief global performance counter control <b>(r/w)</b>
 *
 * global performance counter control. counter increments while the result of anding the respective enable bit in this msr
 * with the corresponding os or usr bits in the general-purpose or fixed counter control msr is true.
 *
 * @remarks if cpuid.0ah: eax[7:0] > 0
 */
#define ia32_perf_global_ctrl 0x0000038f
typedef struct {
	/**
         * en_pmc(n). enable bitmask. only the first n-1 bits are valid. bits 31:n are reserved.
         *
         * @remarks if cpuid.0ah: eax[15:8] > n
         */
	uint32 enpmcn;

	/**
         * en_fixed_ctr(n). enable bitmask. only the first n-1 bits are valid. bits 31:n are reserved.
         *
         * @remarks if cpuid.0ah: edx[4:0] > n
         */
	uint32 enfixedctrn;
} ia32_perf_global_ctrl_register;

/**
 * global performance counter overflow reset control.
 *
 * @remarks if cpuid.0ah: eax[7:0] > 3
 */
#define ia32_perf_global_status_reset 0x00000390
typedef union {
	struct {
		/**
                 * [bits 31:0] set 1 to clear ovf_pmc(n) bit. clear bitmask. only the first n-1 bits are valid. bits 31:n are reserved.
                 *
                 * @remarks if cpuid.0ah: eax[15:8] > n
                 */
		uint64 clearovfpmcn : 32;
#define ia32_perf_global_status_reset_clear_ovf_pmcn_bit 0
#define ia32_perf_global_status_reset_clear_ovf_pmcn_flag 0xffffffff
#define ia32_perf_global_status_reset_clear_ovf_pmcn_mask 0xffffffff
#define ia32_perf_global_status_reset_clear_ovf_pmcn(_) \
	(((_) >> 0) & 0xffffffff)

		/**
                 * [bits 34:32] set 1 to clear ovf_fixed_ctr(n) bit. clear bitmask. only the first n-1 bits are valid. bits 31:n are
                 * reserved.
                 *
                 * @remarks if cpuid.0ah: edx[4:0] > n
                 */
		uint64 clearovffixedctrn : 3;
#define ia32_perf_global_status_reset_clear_ovf_fixed_ctrn_bit 32
#define ia32_perf_global_status_reset_clear_ovf_fixed_ctrn_flag 0x700000000
#define ia32_perf_global_status_reset_clear_ovf_fixed_ctrn_mask 0x07
#define ia32_perf_global_status_reset_clear_ovf_fixed_ctrn(_) \
	(((_) >> 32) & 0x07)
		uint64 reserved1 : 20;

		/**
                 * [bit 55] set 1 to clear trace_topa_pmi bit.
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=0):ebx[25] = 1) && ia32_rtit_ctl.topa = 1
                 */
		uint64 cleartracetopapmi : 1;
#define ia32_perf_global_status_reset_clear_trace_topa_pmi_bit 55
#define ia32_perf_global_status_reset_clear_trace_topa_pmi_flag 0x80000000000000
#define ia32_perf_global_status_reset_clear_trace_topa_pmi_mask 0x01
#define ia32_perf_global_status_reset_clear_trace_topa_pmi(_) \
	(((_) >> 55) & 0x01)
		uint64 reserved2 : 2;

		/**
                 * [bit 58] set 1 to clear lbr_frz bit.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 3
                 */
		uint64 clearlbrfrz : 1;
#define ia32_perf_global_status_reset_clear_lbr_frz_bit 58
#define ia32_perf_global_status_reset_clear_lbr_frz_flag 0x400000000000000
#define ia32_perf_global_status_reset_clear_lbr_frz_mask 0x01
#define ia32_perf_global_status_reset_clear_lbr_frz(_) (((_) >> 58) & 0x01)

		/**
                 * [bit 59] set 1 to clear ctr_frz bit.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 3
                 */
		uint64 clearctrfrz : 1;
#define ia32_perf_global_status_reset_clear_ctr_frz_bit 59
#define ia32_perf_global_status_reset_clear_ctr_frz_flag 0x800000000000000
#define ia32_perf_global_status_reset_clear_ctr_frz_mask 0x01
#define ia32_perf_global_status_reset_clear_ctr_frz(_) (((_) >> 59) & 0x01)

		/**
                 * [bit 60] set 1 to clear asci bit.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 3
                 */
		uint64 clearasci : 1;
#define ia32_perf_global_status_reset_clear_asci_bit 60
#define ia32_perf_global_status_reset_clear_asci_flag 0x1000000000000000
#define ia32_perf_global_status_reset_clear_asci_mask 0x01
#define ia32_perf_global_status_reset_clear_asci(_) (((_) >> 60) & 0x01)

		/**
                 * [bit 61] set 1 to clear ovf_uncore bit.
                 *
                 * @remarks 06_2eh
                 */
		uint64 clearovfuncore : 1;
#define ia32_perf_global_status_reset_clear_ovf_uncore_bit 61
#define ia32_perf_global_status_reset_clear_ovf_uncore_flag 0x2000000000000000
#define ia32_perf_global_status_reset_clear_ovf_uncore_mask 0x01
#define ia32_perf_global_status_reset_clear_ovf_uncore(_) (((_) >> 61) & 0x01)

		/**
                 * [bit 62] set 1 to clear ovfbuf bit.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 0
                 */
		uint64 clearovfbuf : 1;
#define ia32_perf_global_status_reset_clear_ovf_buf_bit 62
#define ia32_perf_global_status_reset_clear_ovf_buf_flag 0x4000000000000000
#define ia32_perf_global_status_reset_clear_ovf_buf_mask 0x01
#define ia32_perf_global_status_reset_clear_ovf_buf(_) (((_) >> 62) & 0x01)

		/**
                 * [bit 63] set 1 to clear condchgd bit.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 0
                 */
		uint64 clearcondchgd : 1;
#define ia32_perf_global_status_reset_clear_cond_chgd_bit 63
#define ia32_perf_global_status_reset_clear_cond_chgd_flag 0x8000000000000000
#define ia32_perf_global_status_reset_clear_cond_chgd_mask 0x01
#define ia32_perf_global_status_reset_clear_cond_chgd(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} ia32_perf_global_status_reset_register;

/**
 * global performance counter overflow set control.
 *
 * @remarks if cpuid.0ah: eax[7:0] > 3
 */
#define ia32_perf_global_status_set 0x00000391
typedef union {
	struct {
		/**
                 * [bits 31:0] set 1 to cause ovf_pmc(n) = 1. set bitmask. only the first n-1 bits are valid. bits 31:n are reserved.
                 *
                 * @remarks if cpuid.0ah: eax[15:8] > n
                 */
		uint64 ovfpmcn : 32;
#define ia32_perf_global_status_set_ovf_pmcn_bit 0
#define ia32_perf_global_status_set_ovf_pmcn_flag 0xffffffff
#define ia32_perf_global_status_set_ovf_pmcn_mask 0xffffffff
#define ia32_perf_global_status_set_ovf_pmcn(_) (((_) >> 0) & 0xffffffff)

		/**
                 * [bits 34:32] set 1 to cause ovf_fixed_ctr(n) = 1. set bitmask. only the first n-1 bits are valid. bits 31:n are
                 * reserved.
                 *
                 * @remarks if cpuid.0ah: edx[4:0] > n
                 */
		uint64 ovffixedctrn : 3;
#define ia32_perf_global_status_set_ovf_fixed_ctrn_bit 32
#define ia32_perf_global_status_set_ovf_fixed_ctrn_flag 0x700000000
#define ia32_perf_global_status_set_ovf_fixed_ctrn_mask 0x07
#define ia32_perf_global_status_set_ovf_fixed_ctrn(_) (((_) >> 32) & 0x07)
		uint64 reserved1 : 20;

		/**
                 * [bit 55] set 1 to cause trace_topa_pmi = 1.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 3
                 */
		uint64 tracetopapmi : 1;
#define ia32_perf_global_status_set_trace_topa_pmi_bit 55
#define ia32_perf_global_status_set_trace_topa_pmi_flag 0x80000000000000
#define ia32_perf_global_status_set_trace_topa_pmi_mask 0x01
#define ia32_perf_global_status_set_trace_topa_pmi(_) (((_) >> 55) & 0x01)
		uint64 reserved2 : 2;

		/**
                 * [bit 58] set 1 to cause lbr_frz = 1.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 3
                 */
		uint64 lbrfrz : 1;
#define ia32_perf_global_status_set_lbr_frz_bit 58
#define ia32_perf_global_status_set_lbr_frz_flag 0x400000000000000
#define ia32_perf_global_status_set_lbr_frz_mask 0x01
#define ia32_perf_global_status_set_lbr_frz(_) (((_) >> 58) & 0x01)

		/**
                 * [bit 59] set 1 to cause ctr_frz = 1.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 3
                 */
		uint64 ctrfrz : 1;
#define ia32_perf_global_status_set_ctr_frz_bit 59
#define ia32_perf_global_status_set_ctr_frz_flag 0x800000000000000
#define ia32_perf_global_status_set_ctr_frz_mask 0x01
#define ia32_perf_global_status_set_ctr_frz(_) (((_) >> 59) & 0x01)

		/**
                 * [bit 60] set 1 to cause asci = 1.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 3
                 */
		uint64 asci : 1;
#define ia32_perf_global_status_set_asci_bit 60
#define ia32_perf_global_status_set_asci_flag 0x1000000000000000
#define ia32_perf_global_status_set_asci_mask 0x01
#define ia32_perf_global_status_set_asci(_) (((_) >> 60) & 0x01)

		/**
                 * [bit 61] set 1 to cause ovf_uncore = 1.
                 *
                 * @remarks 06_2eh
                 */
		uint64 ovfuncore : 1;
#define ia32_perf_global_status_set_ovf_uncore_bit 61
#define ia32_perf_global_status_set_ovf_uncore_flag 0x2000000000000000
#define ia32_perf_global_status_set_ovf_uncore_mask 0x01
#define ia32_perf_global_status_set_ovf_uncore(_) (((_) >> 61) & 0x01)

		/**
                 * [bit 62] set 1 to cause ovfbuf = 1.
                 *
                 * @remarks if cpuid.0ah: eax[7:0] > 3
                 */
		uint64 ovfbuf : 1;
#define ia32_perf_global_status_set_ovf_buf_bit 62
#define ia32_perf_global_status_set_ovf_buf_flag 0x4000000000000000
#define ia32_perf_global_status_set_ovf_buf_mask 0x01
#define ia32_perf_global_status_set_ovf_buf(_) (((_) >> 62) & 0x01)
		uint64 reserved3 : 1;
	};

	uint64 flags;
} ia32_perf_global_status_set_register;

/**
 * indicator that core perfmon interface is in use.
 *
 * @remarks if cpuid.0ah: eax[7:0] > 3
 */
#define ia32_perf_global_inuse 0x00000392
typedef union {
	struct {
		/**
                 * [bits 31:0] ia32_perfevtsel(n) in use. status bitmask. only the first n-1 bits are valid. bits 31:n are reserved.
                 *
                 * @remarks if cpuid.0ah: eax[15:8] > n
                 */
		uint64 ia32perfevtselninuse : 32;
#define ia32_perf_global_inuse_ia32_perfevtseln_in_use_bit 0
#define ia32_perf_global_inuse_ia32_perfevtseln_in_use_flag 0xffffffff
#define ia32_perf_global_inuse_ia32_perfevtseln_in_use_mask 0xffffffff
#define ia32_perf_global_inuse_ia32_perfevtseln_in_use(_) \
	(((_) >> 0) & 0xffffffff)

		/**
                 * [bits 34:32] ia32_fixed_ctr(n) in use. status bitmask. only the first n-1 bits are valid. bits 31:n are reserved.
                 */
		uint64 ia32fixedctrninuse : 3;
#define ia32_perf_global_inuse_ia32_fixed_ctrn_in_use_bit 32
#define ia32_perf_global_inuse_ia32_fixed_ctrn_in_use_flag 0x700000000
#define ia32_perf_global_inuse_ia32_fixed_ctrn_in_use_mask 0x07
#define ia32_perf_global_inuse_ia32_fixed_ctrn_in_use(_) (((_) >> 32) & 0x07)
		uint64 reserved1 : 28;

		/**
                 * [bit 63] pmi in use.
                 */
		uint64 pmiinuse : 1;
#define ia32_perf_global_inuse_pmi_in_use_bit 63
#define ia32_perf_global_inuse_pmi_in_use_flag 0x8000000000000000
#define ia32_perf_global_inuse_pmi_in_use_mask 0x01
#define ia32_perf_global_inuse_pmi_in_use(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} ia32_perf_global_inuse_register;

/**
 * pebs control.
 *
 * @remarks if cpuid.0ah: eax[7:0] > 3
 */
#define ia32_pebs_enable 0x000003f1
typedef union {
	struct {
		/**
                 * [bit 0] enable pebs on ia32_pmc0.
                 *
                 * @remarks 06_0fh
                 */
		uint64 enablepebs : 1;
#define ia32_pebs_enable_enable_pebs_bit 0
#define ia32_pebs_enable_enable_pebs_flag 0x01
#define ia32_pebs_enable_enable_pebs_mask 0x01
#define ia32_pebs_enable_enable_pebs(_) (((_) >> 0) & 0x01)

		/**
                 * [bits 3:1] reserved or model specific.
                 */
		uint64 reservedormodelspecific1 : 3;
#define ia32_pebs_enable_reservedormodelspecific1_bit 1
#define ia32_pebs_enable_reservedormodelspecific1_flag 0x0e
#define ia32_pebs_enable_reservedormodelspecific1_mask 0x07
#define ia32_pebs_enable_reservedormodelspecific1(_) (((_) >> 1) & 0x07)
		uint64 reserved1 : 28;

		/**
                 * [bits 35:32] reserved or model specific.
                 */
		uint64 reservedormodelspecific2 : 4;
#define ia32_pebs_enable_reservedormodelspecific2_bit 32
#define ia32_pebs_enable_reservedormodelspecific2_flag 0xf00000000
#define ia32_pebs_enable_reservedormodelspecific2_mask 0x0f
#define ia32_pebs_enable_reservedormodelspecific2(_) (((_) >> 32) & 0x0f)
		uint64 reserved2 : 28;
	};

	uint64 flags;
} ia32_pebs_enable_register;

/**
 * @defgroup ia32_mc_ctl \
 *           ia32_mc(i)_ctl
 *
 * ia32_mc(0-28)_ctl.
 *
 * @remarks if ia32_mcg_cap.cnt > n
 * @{
 */
#define ia32_mc0_ctl 0x00000400
#define ia32_mc1_ctl 0x00000404
#define ia32_mc2_ctl 0x00000408
#define ia32_mc3_ctl 0x0000040c
#define ia32_mc4_ctl 0x00000410
#define ia32_mc5_ctl 0x00000414
#define ia32_mc6_ctl 0x00000418
#define ia32_mc7_ctl 0x0000041c
#define ia32_mc8_ctl 0x00000420
#define ia32_mc9_ctl 0x00000424
#define ia32_mc10_ctl 0x00000428
#define ia32_mc11_ctl 0x0000042c
#define ia32_mc12_ctl 0x00000430
#define ia32_mc13_ctl 0x00000434
#define ia32_mc14_ctl 0x00000438
#define ia32_mc15_ctl 0x0000043c
#define ia32_mc16_ctl 0x00000440
#define ia32_mc17_ctl 0x00000444
#define ia32_mc18_ctl 0x00000448
#define ia32_mc19_ctl 0x0000044c
#define ia32_mc20_ctl 0x00000450
#define ia32_mc21_ctl 0x00000454
#define ia32_mc22_ctl 0x00000458
#define ia32_mc23_ctl 0x0000045c
#define ia32_mc24_ctl 0x00000460
#define ia32_mc25_ctl 0x00000464
#define ia32_mc26_ctl 0x00000468
#define ia32_mc27_ctl 0x0000046c
#define ia32_mc28_ctl 0x00000470
/**
 * @}
 */

/**
 * @defgroup ia32_mc_status \
 *           ia32_mc(i)_status
 *
 * ia32_mc(0-28)_status.
 *
 * @remarks if ia32_mcg_cap.cnt > n
 * @{
 */
#define ia32_mc0_status 0x00000401
#define ia32_mc1_status 0x00000405
#define ia32_mc2_status 0x00000409
#define ia32_mc3_status 0x0000040d
#define ia32_mc4_status 0x00000411
#define ia32_mc5_status 0x00000415
#define ia32_mc6_status 0x00000419
#define ia32_mc7_status 0x0000041d
#define ia32_mc8_status 0x00000421
#define ia32_mc9_status 0x00000425
#define ia32_mc10_status 0x00000429
#define ia32_mc11_status 0x0000042d
#define ia32_mc12_status 0x00000431
#define ia32_mc13_status 0x00000435
#define ia32_mc14_status 0x00000439
#define ia32_mc15_status 0x0000043d
#define ia32_mc16_status 0x00000441
#define ia32_mc17_status 0x00000445
#define ia32_mc18_status 0x00000449
#define ia32_mc19_status 0x0000044d
#define ia32_mc20_status 0x00000451
#define ia32_mc21_status 0x00000455
#define ia32_mc22_status 0x00000459
#define ia32_mc23_status 0x0000045d
#define ia32_mc24_status 0x00000461
#define ia32_mc25_status 0x00000465
#define ia32_mc26_status 0x00000469
#define ia32_mc27_status 0x0000046d
#define ia32_mc28_status 0x00000471
/**
 * @}
 */

/**
 * @defgroup ia32_mc_addr \
 *           ia32_mc(i)_addr
 *
 * ia32_mc(0-28)_addr.
 *
 * @remarks if ia32_mcg_cap.cnt > n
 * @{
 */
#define ia32_mc0_addr 0x00000402
#define ia32_mc1_addr 0x00000406
#define ia32_mc2_addr 0x0000040a
#define ia32_mc3_addr 0x0000040e
#define ia32_mc4_addr 0x00000412
#define ia32_mc5_addr 0x00000416
#define ia32_mc6_addr 0x0000041a
#define ia32_mc7_addr 0x0000041e
#define ia32_mc8_addr 0x00000422
#define ia32_mc9_addr 0x00000426
#define ia32_mc10_addr 0x0000042a
#define ia32_mc11_addr 0x0000042e
#define ia32_mc12_addr 0x00000432
#define ia32_mc13_addr 0x00000436
#define ia32_mc14_addr 0x0000043a
#define ia32_mc15_addr 0x0000043e
#define ia32_mc16_addr 0x00000442
#define ia32_mc17_addr 0x00000446
#define ia32_mc18_addr 0x0000044a
#define ia32_mc19_addr 0x0000044e
#define ia32_mc20_addr 0x00000452
#define ia32_mc21_addr 0x00000456
#define ia32_mc22_addr 0x0000045a
#define ia32_mc23_addr 0x0000045e
#define ia32_mc24_addr 0x00000462
#define ia32_mc25_addr 0x00000466
#define ia32_mc26_addr 0x0000046a
#define ia32_mc27_addr 0x0000046e
#define ia32_mc28_addr 0x00000472
/**
 * @}
 */

/**
 * @defgroup ia32_mc_misc \
 *           ia32_mc(i)_misc
 *
 * ia32_mc(0-28)_misc.
 *
 * @remarks if ia32_mcg_cap.cnt > n
 * @{
 */
#define ia32_mc0_misc 0x00000403
#define ia32_mc1_misc 0x00000407
#define ia32_mc2_misc 0x0000040b
#define ia32_mc3_misc 0x0000040f
#define ia32_mc4_misc 0x00000413
#define ia32_mc5_misc 0x00000417
#define ia32_mc6_misc 0x0000041b
#define ia32_mc7_misc 0x0000041f
#define ia32_mc8_misc 0x00000423
#define ia32_mc9_misc 0x00000427
#define ia32_mc10_misc 0x0000042b
#define ia32_mc11_misc 0x0000042f
#define ia32_mc12_misc 0x00000433
#define ia32_mc13_misc 0x00000437
#define ia32_mc14_misc 0x0000043b
#define ia32_mc15_misc 0x0000043f
#define ia32_mc16_misc 0x00000443
#define ia32_mc17_misc 0x00000447
#define ia32_mc18_misc 0x0000044b
#define ia32_mc19_misc 0x0000044f
#define ia32_mc20_misc 0x00000453
#define ia32_mc21_misc 0x00000457
#define ia32_mc22_misc 0x0000045b
#define ia32_mc23_misc 0x0000045f
#define ia32_mc24_misc 0x00000463
#define ia32_mc25_misc 0x00000467
#define ia32_mc26_misc 0x0000046b
#define ia32_mc27_misc 0x0000046f
#define ia32_mc28_misc 0x00000473
/**
 * @}
 */

/**
 * reporting register of basic vmx capabilities.
 *
 * @remarks if cpuid.01h:ecx.[5] = 1
 * @see vol3d[a.1(basic vmx information)]
 * @see vol3d[a.1(basic vmx information)] (reference)
 */
#define ia32_vmx_basic 0x00000480
typedef union {
	struct {
		/**
                 * @brief vmcs revision identifier used by the processor
                 *
                 * [bits 30:0] 31-bit vmcs revision identifier used by the processor. processors that use the same vmcs revision identifier
                 * use the same size for vmcs regions.
                 */
		uint64 vmcsrevisionid : 31;
#define ia32_vmx_basic_vmcs_revision_id_bit 0
#define ia32_vmx_basic_vmcs_revision_id_flag 0x7fffffff
#define ia32_vmx_basic_vmcs_revision_id_mask 0x7fffffff
#define ia32_vmx_basic_vmcs_revision_id(_) (((_) >> 0) & 0x7fffffff)

		/**
                 * [bit 31] bit 31 is always 0.
                 */
		uint64 mustbezero : 1;
#define ia32_vmx_basic_must_be_zero_bit 31
#define ia32_vmx_basic_must_be_zero_flag 0x80000000
#define ia32_vmx_basic_must_be_zero_mask 0x01
#define ia32_vmx_basic_must_be_zero(_) (((_) >> 31) & 0x01)

		/**
                 * @brief size of the vmcs
                 *
                 * [bits 44:32] report the number of bytes that software should allocate for the vmxon region and any vmcs region. it is a
                 * value greater than 0 and at most 4096 (bit 44 is set if and only if bits 43:32 are clear).
                 */
		uint64 vmcssizeinbytes : 13;
#define ia32_vmx_basic_vmcs_size_in_bytes_bit 32
#define ia32_vmx_basic_vmcs_size_in_bytes_flag 0x1fff00000000
#define ia32_vmx_basic_vmcs_size_in_bytes_mask 0x1fff
#define ia32_vmx_basic_vmcs_size_in_bytes(_) (((_) >> 32) & 0x1fff)
		uint64 reserved1 : 3;

		/**
                 * @brief width of physical address used for the vmcs
                 *        - 0 -> limited to the available amount of physical ram
                 *        - 1 -> within the first 4 gb
                 *
                 * [bit 48] indicates the width of the physical addresses that may be used for the vmxon region, each vmcs, and data
                 * structures referenced by pointers in a vmcs (i/o bitmaps, virtual-apic page, msr areas for vmx transitions). if the bit
                 * is 0, these addresses are limited to the processor's physical-address width.2 if the bit is 1, these addresses are
                 * limited to 32 bits. this bit is always 0 for processors that support intel 64 architecture.
                 */
		uint64 vmcsphysicaladdresswidth : 1;
#define ia32_vmx_basic_vmcs_physical_address_width_bit 48
#define ia32_vmx_basic_vmcs_physical_address_width_flag 0x1000000000000
#define ia32_vmx_basic_vmcs_physical_address_width_mask 0x01
#define ia32_vmx_basic_vmcs_physical_address_width(_) (((_) >> 48) & 0x01)

		/**
                 * @brief whether the processor supports the dual-monitor treatment of system-management interrupts and system-management
                 *        code (always 1)
                 *
                 * [bit 49] read as 1, the logical processor supports the dual-monitor treatment of system-management interrupts and
                 * system-management mode.
                 *
                 * @see vol3c[34.15(dual-monitor treatment of smis and smm)]
                 */
		uint64 dualmonitorsupport : 1;
#define ia32_vmx_basic_dual_monitor_support_bit 49
#define ia32_vmx_basic_dual_monitor_support_flag 0x2000000000000
#define ia32_vmx_basic_dual_monitor_support_mask 0x01
#define ia32_vmx_basic_dual_monitor_support(_) (((_) >> 49) & 0x01)

		/**
                 * @brief memory type that must be used for the vmcs
                 *
                 * [bits 53:50] report the memory type that should be used for the vmcs, for data structures referenced by pointers in the
                 * vmcs (i/o bitmaps, virtual-apic page, msr areas for vmx transitions), and for the mseg header. if software needs to
                 * access these data structures (e.g., to modify the contents of the msr bitmaps), it can configure the paging structures
                 * to map them into the linear-address space. if it does so, it should establish mappings that use the memory type reported
                 * bits 53:50 in this msr.
                 * as of this writing, all processors that support vmx operation indicate the write-back type.
                 */
		uint64 memorytype : 4;
#define ia32_vmx_basic_memory_type_bit 50
#define ia32_vmx_basic_memory_type_flag 0x3c000000000000
#define ia32_vmx_basic_memory_type_mask 0x0f
#define ia32_vmx_basic_memory_type(_) (((_) >> 50) & 0x0f)

		/**
                 * @brief whether the processor provides additional information for exits due to ins/outs
                 *
                 * [bit 54] when set to 1, the processor reports information in the vm-exit instruction-information field on vm exits due
                 * to execution of the ins and outs instructions. this reporting is done only if this bit is read as 1.
                 *
                 * @see vol3c[27.2.4(information for vm exits due to instruction execution)]
                 */
		uint64 insoutsreporting : 1;
#define ia32_vmx_basic_ins_outs_reporting_bit 54
#define ia32_vmx_basic_ins_outs_reporting_flag 0x40000000000000
#define ia32_vmx_basic_ins_outs_reporting_mask 0x01
#define ia32_vmx_basic_ins_outs_reporting(_) (((_) >> 54) & 0x01)

		/**
                 * @brief whether default 1 bits in control msrs (pin/proc/exit/entry) may be cleared to 0 and that 'true' control msrs are
                 *        supported
                 *
                 * [bit 55] is read as 1 if any vmx controls that default to 1 may be cleared to 0. it also reports support for the vmx
                 * capability msrs ia32_vmx_true_pinbased_ctls, ia32_vmx_true_procbased_ctls, ia32_vmx_true_exit_ctls, and
                 * ia32_vmx_true_entry_ctls.
                 *
                 * @see vol3d[a.2(reserved controls and default settings)]
                 * @see vol3d[a.3.1(pin-based vm-execution controls)]
                 * @see vol3d[a.3.2(primary processor-based vm-execution controls)]
                 * @see vol3d[a.4(vm-exit controls)]
                 * @see vol3d[a.5(vm-entry controls)]
                 */
		uint64 vmxcontrols : 1;
#define ia32_vmx_basic_vmx_controls_bit 55
#define ia32_vmx_basic_vmx_controls_flag 0x80000000000000
#define ia32_vmx_basic_vmx_controls_mask 0x01
#define ia32_vmx_basic_vmx_controls(_) (((_) >> 55) & 0x01)
		uint64 reserved2 : 8;
	};

	uint64 flags;
} ia32_vmx_basic_register;

/**
 * capability reporting register of pin-based vm-execution controls.
 *
 * @remarks if cpuid.01h:ecx.[5] = 1
 * @see vol3d[a.3.1(pin-based vm-execution controls)]
 * @see vol3c[24.6.1(pin-based vm-execution controls)] (reference)
 */
#define ia32_vmx_pinbased_ctls 0x00000481
typedef union {
	struct {
		/**
                 * @brief external interrupts cause vm-exits if set; otherwise dispatched through the guest's idt
                 *
                 * [bit 0] if this control is 1, external interrupts cause vm exits. otherwise, they are delivered normally through the
                 * guest interrupt-descriptor table (idt). if this control is 1, the value of rflags.if does not affect interrupt blocking.
                 */
		uint64 externalinterruptexiting : 1;
#define ia32_vmx_pinbased_ctls_external_interrupt_exiting_bit 0
#define ia32_vmx_pinbased_ctls_external_interrupt_exiting_flag 0x01
#define ia32_vmx_pinbased_ctls_external_interrupt_exiting_mask 0x01
#define ia32_vmx_pinbased_ctls_external_interrupt_exiting(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 2;

		/**
                 * @brief non-maskable interrupts cause vm-exits if set; otherwise dispatched through the guest's idt
                 *
                 * [bit 3] if this control is 1, non-maskable interrupts (nmis) cause vm exits. otherwise, they are delivered normally
                 * using descriptor 2 of the idt. this control also determines interactions between iret and blocking by nmi.
                 *
                 * @see vol3c[25.3(changes to instruction behavior in vmx non-root operation)]
                 */
		uint64 nmiexiting : 1;
#define ia32_vmx_pinbased_ctls_nmi_exiting_bit 3
#define ia32_vmx_pinbased_ctls_nmi_exiting_flag 0x08
#define ia32_vmx_pinbased_ctls_nmi_exiting_mask 0x01
#define ia32_vmx_pinbased_ctls_nmi_exiting(_) (((_) >> 3) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * @brief virtual nmis
                 *
                 * [bit 5] if this control is 1, nmis are never blocked and the "blocking by nmi" bit (bit 3) in the interruptibility-state
                 * field indicates "virtual-nmi blocking". this control also interacts with the "nmi-window exiting" vm-execution control.
                 *
                 * @see vol3c[24.6.2(processor-based vm-execution controls)]
                 */
		uint64 virtualnmi : 1;
#define ia32_vmx_pinbased_ctls_virtual_nmi_bit 5
#define ia32_vmx_pinbased_ctls_virtual_nmi_flag 0x20
#define ia32_vmx_pinbased_ctls_virtual_nmi_mask 0x01
#define ia32_vmx_pinbased_ctls_virtual_nmi(_) (((_) >> 5) & 0x01)

		/**
                 * @brief activate vmx preemption timer
                 *
                 * [bit 6] if this control is 1, the vmx-preemption timer counts down in vmx non-root operation. a vm exit occurs when the
                 * timer counts down to zero.
                 *
                 * @see vol3c[25.5.1(vmx-preemption timer)]
                 * @see vol3c[25.2(other causes of vm exits)]
                 */
		uint64 activatevmxpreemptiontimer : 1;
#define ia32_vmx_pinbased_ctls_activate_vmx_preemption_timer_bit 6
#define ia32_vmx_pinbased_ctls_activate_vmx_preemption_timer_flag 0x40
#define ia32_vmx_pinbased_ctls_activate_vmx_preemption_timer_mask 0x01
#define ia32_vmx_pinbased_ctls_activate_vmx_preemption_timer(_) \
	(((_) >> 6) & 0x01)

		/**
                 * @brief process interrupts with the posted-interrupt notification list
                 *
                 * [bit 7] if this control is 1, the processor treats interrupts with the posted-interrupt notification list specially,
                 * updating the virtual-apic page with posted-interrupt requests.
                 *
                 * @see vol3c[24.6.8(controls for apic virtualization)]
                 * @see vol3c[29.6(posted-interrupt processing)]
                 */
		uint64 processpostedinterrupts : 1;
#define ia32_vmx_pinbased_ctls_process_posted_interrupts_bit 7
#define ia32_vmx_pinbased_ctls_process_posted_interrupts_flag 0x80
#define ia32_vmx_pinbased_ctls_process_posted_interrupts_mask 0x01
#define ia32_vmx_pinbased_ctls_process_posted_interrupts(_) (((_) >> 7) & 0x01)
		uint64 reserved3 : 56;
	};

	uint64 flags;
} ia32_vmx_pinbased_ctls_register;

/**
 * capability reporting register of primary processor-based vm-execution controls.
 *
 * @remarks if cpuid.01h:ecx.[5] = 1
 * @see vol3d[a.3.2(primary processor-based vm-execution controls)]
 * @see vol3c[24.6.2(processor-based vm-execution controls)] (reference)
 */
#define ia32_vmx_procbased_ctls 0x00000482
typedef union {
	struct {
		uint64 reserved1 : 2;

		/**
                 * @brief vm-exit as soon as rflags.if=1 and no blocking is active
                 *
                 * [bit 2] if this control is 1, a vm exit occurs at the beginning of any instruction if rflags.if = 1 and there are no
                 * other blocking of interrupts.
                 *
                 * @see vol3c[24.4.2(guest non-register state)]
                 */
		uint64 interruptwindowexiting : 1;
#define ia32_vmx_procbased_ctls_interrupt_window_exiting_bit 2
#define ia32_vmx_procbased_ctls_interrupt_window_exiting_flag 0x04
#define ia32_vmx_procbased_ctls_interrupt_window_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_interrupt_window_exiting(_) (((_) >> 2) & 0x01)

		/**
                 * @brief use timestamp counter offset
                 *
                 * [bit 3] this control determines whether executions of rdtsc, executions of rdtscp, and executions of rdmsr that read
                 * from the ia32_time_stamp_counter msr return a value modified by the tsc offset field.
                 *
                 * @see vol3c[24.6.5(time-stamp counter offset and multiplier)]
                 * @see vol3c[25.3(changes to instruction behavior in vmx non-root operation)]
                 */
		uint64 usetscoffsetting : 1;
#define ia32_vmx_procbased_ctls_use_tsc_offsetting_bit 3
#define ia32_vmx_procbased_ctls_use_tsc_offsetting_flag 0x08
#define ia32_vmx_procbased_ctls_use_tsc_offsetting_mask 0x01
#define ia32_vmx_procbased_ctls_use_tsc_offsetting(_) (((_) >> 3) & 0x01)
		uint64 reserved2 : 3;

		/**
                 * @brief vm-exit when executing the hlt instruction
                 *
                 * [bit 7] this control determines whether executions of hlt cause vm exits.
                 */
		uint64 hltexiting : 1;
#define ia32_vmx_procbased_ctls_hlt_exiting_bit 7
#define ia32_vmx_procbased_ctls_hlt_exiting_flag 0x80
#define ia32_vmx_procbased_ctls_hlt_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_hlt_exiting(_) (((_) >> 7) & 0x01)
		uint64 reserved3 : 1;

		/**
                 * @brief vm-exit when executing the invlpg instruction
                 *
                 * [bit 9] this control determines whether executions of invlpg cause vm exits.
                 */
		uint64 invlpgexiting : 1;
#define ia32_vmx_procbased_ctls_invlpg_exiting_bit 9
#define ia32_vmx_procbased_ctls_invlpg_exiting_flag 0x200
#define ia32_vmx_procbased_ctls_invlpg_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_invlpg_exiting(_) (((_) >> 9) & 0x01)

		/**
                 * @brief vm-exit when executing the mwait instruction
                 *
                 * [bit 10] this control determines whether executions of mwait cause vm exits.
                 */
		uint64 mwaitexiting : 1;
#define ia32_vmx_procbased_ctls_mwait_exiting_bit 10
#define ia32_vmx_procbased_ctls_mwait_exiting_flag 0x400
#define ia32_vmx_procbased_ctls_mwait_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_mwait_exiting(_) (((_) >> 10) & 0x01)

		/**
                 * @brief vm-exit when executing the rdpmc instruction
                 *
                 * [bit 11] this control determines whether executions of rdpmc cause vm exits.
                 */
		uint64 rdpmcexiting : 1;
#define ia32_vmx_procbased_ctls_rdpmc_exiting_bit 11
#define ia32_vmx_procbased_ctls_rdpmc_exiting_flag 0x800
#define ia32_vmx_procbased_ctls_rdpmc_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_rdpmc_exiting(_) (((_) >> 11) & 0x01)

		/**
                 * @brief vm-exit when executing the rdtsc/rdtscp instruction
                 *
                 * [bit 12] this control determines whether executions of rdtsc and rdtscp cause vm exits.
                 */
		uint64 rdtscexiting : 1;
#define ia32_vmx_procbased_ctls_rdtsc_exiting_bit 12
#define ia32_vmx_procbased_ctls_rdtsc_exiting_flag 0x1000
#define ia32_vmx_procbased_ctls_rdtsc_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_rdtsc_exiting(_) (((_) >> 12) & 0x01)
		uint64 reserved4 : 2;

		/**
                 * @brief vm-exit when executing the mov to cr3 instruction (forced to 1 on the 'first' vt-x capable cpus; this actually
                 *        includes the newest nehalem cpus)
                 *
                 * [bit 15] in conjunction with the cr3-target controls, this control determines whether executions of mov to cr3 cause vm
                 * exits. the first processors to support the virtual-machine extensions supported only the 1-setting of this control.
                 *
                 * @see vol3c[24.6.7(cr3-target controls)]
                 * @see vol3c[25.1.3(instructions that cause vm exits conditionally)]
                 */
		uint64 cr3loadexiting : 1;
#define ia32_vmx_procbased_ctls_cr3_load_exiting_bit 15
#define ia32_vmx_procbased_ctls_cr3_load_exiting_flag 0x8000
#define ia32_vmx_procbased_ctls_cr3_load_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_cr3_load_exiting(_) (((_) >> 15) & 0x01)

		/**
                 * @brief vm-exit when executing the mov from cr3 instruction (forced to 1 on the 'first' vt-x capable cpus; this actually
                 *        includes the newest nehalem cpus)
                 *
                 * [bit 16] this control determines whether executions of mov from cr3 cause vm exits. the first processors to support the
                 * virtual-machine extensions supported only the 1-setting of this control.
                 */
		uint64 cr3storeexiting : 1;
#define ia32_vmx_procbased_ctls_cr3_store_exiting_bit 16
#define ia32_vmx_procbased_ctls_cr3_store_exiting_flag 0x10000
#define ia32_vmx_procbased_ctls_cr3_store_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_cr3_store_exiting(_) (((_) >> 16) & 0x01)
		uint64 reserved5 : 2;

		/**
                 * @brief vm-exit on cr8 loads
                 *
                 * [bit 19] this control determines whether executions of mov to cr8 cause vm exits.
                 */
		uint64 cr8loadexiting : 1;
#define ia32_vmx_procbased_ctls_cr8_load_exiting_bit 19
#define ia32_vmx_procbased_ctls_cr8_load_exiting_flag 0x80000
#define ia32_vmx_procbased_ctls_cr8_load_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_cr8_load_exiting(_) (((_) >> 19) & 0x01)

		/**
                 * @brief vm-exit on cr8 stores
                 *
                 * [bit 20] this control determines whether executions of mov from cr8 cause vm exits.
                 */
		uint64 cr8storeexiting : 1;
#define ia32_vmx_procbased_ctls_cr8_store_exiting_bit 20
#define ia32_vmx_procbased_ctls_cr8_store_exiting_flag 0x100000
#define ia32_vmx_procbased_ctls_cr8_store_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_cr8_store_exiting(_) (((_) >> 20) & 0x01)

		/**
                 * @brief use tpr shadow
                 *
                 * [bit 21] setting this control to 1 enables tpr virtualization and other apic-virtualization features.
                 *
                 * @see vol3c[29(apic virtualization and virtual interrupts)]
                 */
		uint64 usetprshadow : 1;
#define ia32_vmx_procbased_ctls_use_tpr_shadow_bit 21
#define ia32_vmx_procbased_ctls_use_tpr_shadow_flag 0x200000
#define ia32_vmx_procbased_ctls_use_tpr_shadow_mask 0x01
#define ia32_vmx_procbased_ctls_use_tpr_shadow(_) (((_) >> 21) & 0x01)

		/**
                 * @brief vm-exit when virtual nmi blocking is disabled
                 *
                 * [bit 22] if this control is 1, a vm exit occurs at the beginning of any instruction if there is no virtual-nmi blocking.
                 *
                 * @see vol3c[24.4.2(guest non-register state)]
                 */
		uint64 nmiwindowexiting : 1;
#define ia32_vmx_procbased_ctls_nmi_window_exiting_bit 22
#define ia32_vmx_procbased_ctls_nmi_window_exiting_flag 0x400000
#define ia32_vmx_procbased_ctls_nmi_window_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_nmi_window_exiting(_) (((_) >> 22) & 0x01)

		/**
                 * @brief vm-exit when executing a mov drx instruction
                 *
                 * [bit 23] this control determines whether executions of mov dr cause vm exits.
                 */
		uint64 movdrexiting : 1;
#define ia32_vmx_procbased_ctls_mov_dr_exiting_bit 23
#define ia32_vmx_procbased_ctls_mov_dr_exiting_flag 0x800000
#define ia32_vmx_procbased_ctls_mov_dr_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_mov_dr_exiting(_) (((_) >> 23) & 0x01)

		/**
                 * @brief vm-exit when executing io instructions
                 *
                 * [bit 24] this control determines whether executions of i/o instructions (in, ins/insb/insw/insd, out, and
                 * outs/outsb/outsw/outsd) cause vm exits.
                 */
		uint64 unconditionalioexiting : 1;
#define ia32_vmx_procbased_ctls_unconditional_io_exiting_bit 24
#define ia32_vmx_procbased_ctls_unconditional_io_exiting_flag 0x1000000
#define ia32_vmx_procbased_ctls_unconditional_io_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_unconditional_io_exiting(_) (((_) >> 24) & 0x01)

		/**
                 * @brief use io bitmaps
                 *
                 * [bit 25] this control determines whether i/o bitmaps are used to restrict executions of i/o instructions for this
                 * control, "0" means "do not use i/o bitmaps" and "1" means "use i/o bitmaps." if the i/o bitmaps are used, the setting of
                 * the "unconditional i/o exiting" control is ignored.
                 *
                 * @see vol3c[24.6.4(i/o-bitmap addresses)]
                 * @see vol3c[25.1.3(instructions that cause vm exits conditionally)]
                 */
		uint64 useiobitmaps : 1;
#define ia32_vmx_procbased_ctls_use_io_bitmaps_bit 25
#define ia32_vmx_procbased_ctls_use_io_bitmaps_flag 0x2000000
#define ia32_vmx_procbased_ctls_use_io_bitmaps_mask 0x01
#define ia32_vmx_procbased_ctls_use_io_bitmaps(_) (((_) >> 25) & 0x01)
		uint64 reserved6 : 1;

		/**
                 * @brief monitor trap flag
                 *
                 * [bit 27] if this control is 1, the monitor trap flag debugging feature is enabled.
                 *
                 * @see vol3c[25.5.2(monitor trap flag)]
                 */
		uint64 monitortrapflag : 1;
#define ia32_vmx_procbased_ctls_monitor_trap_flag_bit 27
#define ia32_vmx_procbased_ctls_monitor_trap_flag_flag 0x8000000
#define ia32_vmx_procbased_ctls_monitor_trap_flag_mask 0x01
#define ia32_vmx_procbased_ctls_monitor_trap_flag(_) (((_) >> 27) & 0x01)

		/**
                 * @brief use msr bitmaps
                 *
                 * [bit 28] this control determines whether msr bitmaps are used to control execution of the rdmsr and wrmsr instructions.
                 * for this control, "0" means "do not use msr bitmaps" and "1" means "use msr bitmaps." if the msr bitmaps are not used,
                 * all executions of the rdmsr and wrmsr instructions cause vm exits.
                 *
                 * @see vol3c[24.6.9(msr-bitmap address)]
                 * @see vol3c[25.1.3(instructions that cause vm exits conditionally)]
                 */
		uint64 usemsrbitmaps : 1;
#define ia32_vmx_procbased_ctls_use_msr_bitmaps_bit 28
#define ia32_vmx_procbased_ctls_use_msr_bitmaps_flag 0x10000000
#define ia32_vmx_procbased_ctls_use_msr_bitmaps_mask 0x01
#define ia32_vmx_procbased_ctls_use_msr_bitmaps(_) (((_) >> 28) & 0x01)

		/**
                 * @brief vm-exit when executing the monitor instruction
                 *
                 * [bit 29] this control determines whether executions of monitor cause vm exits.
                 */
		uint64 monitorexiting : 1;
#define ia32_vmx_procbased_ctls_monitor_exiting_bit 29
#define ia32_vmx_procbased_ctls_monitor_exiting_flag 0x20000000
#define ia32_vmx_procbased_ctls_monitor_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_monitor_exiting(_) (((_) >> 29) & 0x01)

		/**
                 * @brief vm-exit when executing the pause instruction
                 *
                 * [bit 30] this control determines whether executions of pause cause vm exits.
                 */
		uint64 pauseexiting : 1;
#define ia32_vmx_procbased_ctls_pause_exiting_bit 30
#define ia32_vmx_procbased_ctls_pause_exiting_flag 0x40000000
#define ia32_vmx_procbased_ctls_pause_exiting_mask 0x01
#define ia32_vmx_procbased_ctls_pause_exiting(_) (((_) >> 30) & 0x01)

		/**
                 * @brief determines whether the secondary processor based vm-execution controls are used
                 *
                 * [bit 31] this control determines whether the secondary processor-based vm-execution controls are used. if this control
                 * is 0, the logical processor operates as if all the secondary processor-based vm-execution controls were also 0.
                 */
		uint64 activatesecondarycontrols : 1;
#define ia32_vmx_procbased_ctls_activate_secondary_controls_bit 31
#define ia32_vmx_procbased_ctls_activate_secondary_controls_flag 0x80000000
#define ia32_vmx_procbased_ctls_activate_secondary_controls_mask 0x01
#define ia32_vmx_procbased_ctls_activate_secondary_controls(_) \
	(((_) >> 31) & 0x01)
		uint64 reserved7 : 32;
	};

	uint64 flags;
} ia32_vmx_procbased_ctls_register;

/**
 * capability reporting register of vm-exit controls.
 *
 * @remarks if cpuid.01h:ecx.[5] = 1
 * @see vol3d[a.4(vm-exit controls)]
 * @see vol3c[24.7.1(vm-exit controls)] (reference)
 */
#define ia32_vmx_exit_ctls 0x00000483
typedef union {
	struct {
		uint64 reserved1 : 2;

		/**
                 * @brief save guest debug controls (dr7 & ia32_debugctl_msr) (forced to 1 on the 'first' vt-x capable cpus; this actually
                 *        includes the newest nehalem cpus)
                 *
                 * [bit 2] this control determines whether dr7 and the ia32_debugctl msr are saved on vm exit. the first processors to
                 * support the virtual-machine extensions supported only the 1-setting of this control.
                 */
		uint64 savedebugcontrols : 1;
#define ia32_vmx_exit_ctls_save_debug_controls_bit 2
#define ia32_vmx_exit_ctls_save_debug_controls_flag 0x04
#define ia32_vmx_exit_ctls_save_debug_controls_mask 0x01
#define ia32_vmx_exit_ctls_save_debug_controls(_) (((_) >> 2) & 0x01)
		uint64 reserved2 : 6;

		/**
                 * @brief return to long mode after a vm-exit
                 *
                 * [bit 9] on processors that support intel 64 architecture, this control determines whether a logical processor is in
                 * 64-bit mode after the next vm exit. its value is loaded into cs.l, ia32_efer.lme, and ia32_efer.lma on every vm exit.1
                 * this control must be 0 on processors that do not support intel 64 architecture.
                 */
		uint64 hostaddressspacesize : 1;
#define ia32_vmx_exit_ctls_host_address_space_size_bit 9
#define ia32_vmx_exit_ctls_host_address_space_size_flag 0x200
#define ia32_vmx_exit_ctls_host_address_space_size_mask 0x01
#define ia32_vmx_exit_ctls_host_address_space_size(_) (((_) >> 9) & 0x01)
		uint64 reserved3 : 2;

		/**
                 * @brief whether the ia32_perf_global_ctrl msr is loaded on vm-exit
                 *
                 * [bit 12] this control determines whether the ia32_perf_global_ctrl msr is loaded on vm exit.
                 */
		uint64 loadia32perfglobalctrl : 1;
#define ia32_vmx_exit_ctls_load_ia32_perf_global_ctrl_bit 12
#define ia32_vmx_exit_ctls_load_ia32_perf_global_ctrl_flag 0x1000
#define ia32_vmx_exit_ctls_load_ia32_perf_global_ctrl_mask 0x01
#define ia32_vmx_exit_ctls_load_ia32_perf_global_ctrl(_) (((_) >> 12) & 0x01)
		uint64 reserved4 : 2;

		/**
                 * @brief acknowledge external interrupts with the irq controller if one caused a vm-exit
                 *
                 * [bit 15] this control affects vm exits due to external interrupts:
                 * - if such a vm exit occurs and this control is 1, the logical processor acknowledges the interrupt controller, acquiring
                 * the interrupt's list. the list is stored in the vm-exit interruption-information field, which is marked valid.
                 * - if such a vm exit occurs and this control is 0, the interrupt is not acknowledged and the vm-exit
                 * interruption-information field is marked invalid.
                 */
		uint64 acknowledgeinterruptonexit : 1;
#define ia32_vmx_exit_ctls_acknowledge_interrupt_on_exit_bit 15
#define ia32_vmx_exit_ctls_acknowledge_interrupt_on_exit_flag 0x8000
#define ia32_vmx_exit_ctls_acknowledge_interrupt_on_exit_mask 0x01
#define ia32_vmx_exit_ctls_acknowledge_interrupt_on_exit(_) (((_) >> 15) & 0x01)
		uint64 reserved5 : 2;

		/**
                 * @brief whether the guest ia32_pat msr is saved on vm-exit
                 *
                 * [bit 18] this control determines whether the ia32_pat msr is saved on vm exit.
                 */
		uint64 saveia32pat : 1;
#define ia32_vmx_exit_ctls_save_ia32_pat_bit 18
#define ia32_vmx_exit_ctls_save_ia32_pat_flag 0x40000
#define ia32_vmx_exit_ctls_save_ia32_pat_mask 0x01
#define ia32_vmx_exit_ctls_save_ia32_pat(_) (((_) >> 18) & 0x01)

		/**
                 * @brief whether the host ia32_pat msr is loaded on vm-exit
                 *
                 * [bit 19] this control determines whether the ia32_pat msr is loaded on vm exit.
                 */
		uint64 loadia32pat : 1;
#define ia32_vmx_exit_ctls_load_ia32_pat_bit 19
#define ia32_vmx_exit_ctls_load_ia32_pat_flag 0x80000
#define ia32_vmx_exit_ctls_load_ia32_pat_mask 0x01
#define ia32_vmx_exit_ctls_load_ia32_pat(_) (((_) >> 19) & 0x01)

		/**
                 * @brief whether the guest ia32_efer msr is saved on vm-exit
                 *
                 * [bit 20] this control determines whether the ia32_efer msr is saved on vm exit.
                 */
		uint64 saveia32efer : 1;
#define ia32_vmx_exit_ctls_save_ia32_efer_bit 20
#define ia32_vmx_exit_ctls_save_ia32_efer_flag 0x100000
#define ia32_vmx_exit_ctls_save_ia32_efer_mask 0x01
#define ia32_vmx_exit_ctls_save_ia32_efer(_) (((_) >> 20) & 0x01)

		/**
                 * @brief whether the host ia32_efer msr is loaded on vm-exit
                 *
                 * [bit 21] this control determines whether the ia32_efer msr is loaded on vm exit.
                 */
		uint64 loadia32efer : 1;
#define ia32_vmx_exit_ctls_load_ia32_efer_bit 21
#define ia32_vmx_exit_ctls_load_ia32_efer_flag 0x200000
#define ia32_vmx_exit_ctls_load_ia32_efer_mask 0x01
#define ia32_vmx_exit_ctls_load_ia32_efer(_) (((_) >> 21) & 0x01)

		/**
                 * @brief whether the value of the vmx preemption timer is saved on every vm-exit
                 *
                 * [bit 22] this control determines whether the value of the vmx-preemption timer is saved on vm exit.
                 */
		uint64 savevmxpreemptiontimervalue : 1;
#define ia32_vmx_exit_ctls_save_vmx_preemption_timer_value_bit 22
#define ia32_vmx_exit_ctls_save_vmx_preemption_timer_value_flag 0x400000
#define ia32_vmx_exit_ctls_save_vmx_preemption_timer_value_mask 0x01
#define ia32_vmx_exit_ctls_save_vmx_preemption_timer_value(_) \
	(((_) >> 22) & 0x01)

		/**
                 * [bit 23] this control determines whether the ia32_bndcfgs msr is cleared on vm exit.
                 */
		uint64 clearia32bndcfgs : 1;
#define ia32_vmx_exit_ctls_clear_ia32_bndcfgs_bit 23
#define ia32_vmx_exit_ctls_clear_ia32_bndcfgs_flag 0x800000
#define ia32_vmx_exit_ctls_clear_ia32_bndcfgs_mask 0x01
#define ia32_vmx_exit_ctls_clear_ia32_bndcfgs(_) (((_) >> 23) & 0x01)

		/**
                 * [bit 24] if this control is 1, intel processor trace does not produce a paging information packet (pip) on a vm exit or
                 * a vmcs packet on an smm vm exit.
                 *
                 * @see vol3c[35(intel(r) processor trace)]
                 */
		uint64 concealvmxfrompt : 1;
#define ia32_vmx_exit_ctls_conceal_vmx_from_pt_bit 24
#define ia32_vmx_exit_ctls_conceal_vmx_from_pt_flag 0x1000000
#define ia32_vmx_exit_ctls_conceal_vmx_from_pt_mask 0x01
#define ia32_vmx_exit_ctls_conceal_vmx_from_pt(_) (((_) >> 24) & 0x01)
		uint64 reserved6 : 39;
	};

	uint64 flags;
} ia32_vmx_exit_ctls_register;

/**
 * capability reporting register of vm-entry controls.
 *
 * @remarks if cpuid.01h:ecx.[5] = 1
 * @see vol3d[a.5(vm-entry controls)]
 * @see vol3d[24.8.1(vm-entry controls)] (reference)
 */
#define ia32_vmx_entry_ctls 0x00000484
typedef union {
	struct {
		uint64 reserved1 : 2;

		/**
                 * @brief load guest debug controls (dr7 & ia32_debugctl_msr) (forced to 1 on the 'first' vt-x capable cpus; this actually
                 *        includes the newest nehalem cpus)
                 *
                 * [bit 2] this control determines whether dr7 and the ia32_debugctl msr are loaded on vm entry. the first processors to
                 * support the virtual-machine extensions supported only the 1-setting of this control.
                 */
		uint64 loaddebugcontrols : 1;
#define ia32_vmx_entry_ctls_load_debug_controls_bit 2
#define ia32_vmx_entry_ctls_load_debug_controls_flag 0x04
#define ia32_vmx_entry_ctls_load_debug_controls_mask 0x01
#define ia32_vmx_entry_ctls_load_debug_controls(_) (((_) >> 2) & 0x01)
		uint64 reserved2 : 6;

		/**
                 * @brief 64 bits guest mode. must be 0 for cpus that don't support amd64
                 *
                 * [bit 9] on processors that support intel 64 architecture, this control determines whether the logical processor is in
                 * ia-32e mode after vm entry. its value is loaded into ia32_efer.lma as part of vm entry. this control must be 0 on
                 * processors that do not support intel 64 architecture.
                 */
		uint64 ia32emodeguest : 1;
#define ia32_vmx_entry_ctls_ia32e_mode_guest_bit 9
#define ia32_vmx_entry_ctls_ia32e_mode_guest_flag 0x200
#define ia32_vmx_entry_ctls_ia32e_mode_guest_mask 0x01
#define ia32_vmx_entry_ctls_ia32e_mode_guest(_) (((_) >> 9) & 0x01)

		/**
                 * @brief in smm mode after vm-entry
                 *
                 * [bit 10] this control determines whether the logical processor is in system-management mode (smm) after vm entry. this
                 * control must be 0 for any vm entry from outside smm.
                 */
		uint64 entrytosmm : 1;
#define ia32_vmx_entry_ctls_entry_to_smm_bit 10
#define ia32_vmx_entry_ctls_entry_to_smm_flag 0x400
#define ia32_vmx_entry_ctls_entry_to_smm_mask 0x01
#define ia32_vmx_entry_ctls_entry_to_smm(_) (((_) >> 10) & 0x01)

		/**
                 * @brief disable dual treatment of smi and smm; must be zero for vm-entry outside of smm
                 *
                 * [bit 11] if set to 1, the default treatment of smis and smm is in effect after the vm entry. this control must be 0 for
                 * any vm entry from outside smm
                 *
                 * @see vol3c[34.15.7(deactivating the dual-monitor treatment)]
                 */
		uint64 deactivatedualmonitortreatment : 1;
#define ia32_vmx_entry_ctls_deactivate_dual_monitor_treatment_bit 11
#define ia32_vmx_entry_ctls_deactivate_dual_monitor_treatment_flag 0x800
#define ia32_vmx_entry_ctls_deactivate_dual_monitor_treatment_mask 0x01
#define ia32_vmx_entry_ctls_deactivate_dual_monitor_treatment(_) \
	(((_) >> 11) & 0x01)
		uint64 reserved3 : 1;

		/**
                 * @brief whether the guest ia32_perf_global_ctrl msr is loaded on vm-entry
                 *
                 * [bit 13] this control determines whether the ia32_perf_global_ctrl msr is loaded on vm entry.
                 */
		uint64 loadia32perfglobalctrl : 1;
#define ia32_vmx_entry_ctls_load_ia32_perf_global_ctrl_bit 13
#define ia32_vmx_entry_ctls_load_ia32_perf_global_ctrl_flag 0x2000
#define ia32_vmx_entry_ctls_load_ia32_perf_global_ctrl_mask 0x01
#define ia32_vmx_entry_ctls_load_ia32_perf_global_ctrl(_) (((_) >> 13) & 0x01)

		/**
                 * @brief whether the guest ia32_pat msr is loaded on vm-entry
                 *
                 * [bit 14] this control determines whether the ia32_pat msr is loaded on vm entry.
                 */
		uint64 loadia32pat : 1;
#define ia32_vmx_entry_ctls_load_ia32_pat_bit 14
#define ia32_vmx_entry_ctls_load_ia32_pat_flag 0x4000
#define ia32_vmx_entry_ctls_load_ia32_pat_mask 0x01
#define ia32_vmx_entry_ctls_load_ia32_pat(_) (((_) >> 14) & 0x01)

		/**
                 * @brief whether the guest ia32_efer msr is loaded on vm-entry
                 *
                 * [bit 15] this control determines whether the ia32_efer msr is loaded on vm entry.
                 */
		uint64 loadia32efer : 1;
#define ia32_vmx_entry_ctls_load_ia32_efer_bit 15
#define ia32_vmx_entry_ctls_load_ia32_efer_flag 0x8000
#define ia32_vmx_entry_ctls_load_ia32_efer_mask 0x01
#define ia32_vmx_entry_ctls_load_ia32_efer(_) (((_) >> 15) & 0x01)

		/**
                 * [bit 16] this control determines whether the ia32_bndcfgs msr is loaded on vm entry.
                 */
		uint64 loadia32bndcfgs : 1;
#define ia32_vmx_entry_ctls_load_ia32_bndcfgs_bit 16
#define ia32_vmx_entry_ctls_load_ia32_bndcfgs_flag 0x10000
#define ia32_vmx_entry_ctls_load_ia32_bndcfgs_mask 0x01
#define ia32_vmx_entry_ctls_load_ia32_bndcfgs(_) (((_) >> 16) & 0x01)

		/**
                 * [bit 17] if this control is 1, intel processor trace does not produce a paging information packet (pip) on a vm entry or
                 * a vmcs packet on a vm entry that returns from smm.
                 *
                 * @see vol3c[35(intel(r) processor trace)]
                 */
		uint64 concealvmxfrompt : 1;
#define ia32_vmx_entry_ctls_conceal_vmx_from_pt_bit 17
#define ia32_vmx_entry_ctls_conceal_vmx_from_pt_flag 0x20000
#define ia32_vmx_entry_ctls_conceal_vmx_from_pt_mask 0x01
#define ia32_vmx_entry_ctls_conceal_vmx_from_pt(_) (((_) >> 17) & 0x01)

		/**
                 * [bit 18] this control determines whether the ia32_rtit_ctl msr is loaded on vm entry.
                 */
		uint64 loadia32rtitctl : 1;
#define ia32_vmx_entry_ctls_load_ia32_rtit_ctl_bit 18
#define ia32_vmx_entry_ctls_load_ia32_rtit_ctl_flag 0x40000
#define ia32_vmx_entry_ctls_load_ia32_rtit_ctl_mask 0x01
#define ia32_vmx_entry_ctls_load_ia32_rtit_ctl(_) (((_) >> 18) & 0x01)
		uint64 reserved4 : 1;

		/**
                 * [bit 20] this control determines whether cet-related msrs and spp are loaded on vm entry.
                 */
		uint64 loadcetstate : 1;
#define ia32_vmx_entry_ctls_load_cet_state_bit 20
#define ia32_vmx_entry_ctls_load_cet_state_flag 0x100000
#define ia32_vmx_entry_ctls_load_cet_state_mask 0x01
#define ia32_vmx_entry_ctls_load_cet_state(_) (((_) >> 20) & 0x01)
		uint64 reserved5 : 43;
	};

	uint64 flags;
} ia32_vmx_entry_ctls_register;

/**
 * reporting register of miscellaneous vmx capabilities.
 *
 * @remarks if cpuid.01h:ecx.[5] = 1
 * @see vol3d[a.6(miscellaneous data)]
 * @see vol3d[a.6(miscellaneous data)] (reference)
 */
#define ia32_vmx_misc 0x00000485
typedef union {
	struct {
		/**
                 * @brief relationship between the preemption timer and tsc; count down every time bit x of the tsc changes
                 *
                 * [bits 4:0] report a value x that specifies the relationship between the rate of the vmx-preemption timer and that of the
                 * timestamp counter (tsc). specifically, the vmx-preemption timer (if it is active) counts down by 1 every time bit x in
                 * the tsc changes due to a tsc increment.
                 */
		uint64 preemptiontimertscrelationship : 5;
#define ia32_vmx_misc_preemption_timer_tsc_relationship_bit 0
#define ia32_vmx_misc_preemption_timer_tsc_relationship_flag 0x1f
#define ia32_vmx_misc_preemption_timer_tsc_relationship_mask 0x1f
#define ia32_vmx_misc_preemption_timer_tsc_relationship(_) (((_) >> 0) & 0x1f)

		/**
                 * @brief whether vm-exit stores efer.lma into the "ia32e mode guest" field
                 *
                 * [bit 5] when set to 1, vm exits store the value of ia32_efer.lma into the "ia-32e mode guest" vm-entry control. this bit
                 * is read as 1 on any logical processor that supports the 1-setting of the "unrestricted guest" vm-execution control.
                 *
                 * @see vol3c[27.2(recording vm-exit information and updating vm-entry control fields)]
                 */
		uint64 storeeferlmaonvmexit : 1;
#define ia32_vmx_misc_store_efer_lma_on_vmexit_bit 5
#define ia32_vmx_misc_store_efer_lma_on_vmexit_flag 0x20
#define ia32_vmx_misc_store_efer_lma_on_vmexit_mask 0x01
#define ia32_vmx_misc_store_efer_lma_on_vmexit(_) (((_) >> 5) & 0x01)

		/**
                 * @brief activity states supported by the implementation
                 *
                 * [bits 8:6] report, as a bitmap, the activity states supported by the implementation:
                 * - bit 6 reports (if set) the support for activity state 1 (hlt).
                 * - bit 7 reports (if set) the support for activity state 2 (shutdown).
                 * - bit 8 reports (if set) the support for activity state 3 (wait-for-sipi).
                 * if an activity state is not supported, the implementation causes a vm entry to fail if it attempts to establish that
                 * activity state. all implementations support vm entry to activity state 0 (active).
                 */
		uint64 activitystates : 3;
#define ia32_vmx_misc_activity_states_bit 6
#define ia32_vmx_misc_activity_states_flag 0x1c0
#define ia32_vmx_misc_activity_states_mask 0x07
#define ia32_vmx_misc_activity_states(_) (((_) >> 6) & 0x07)
		uint64 reserved1 : 5;

		/**
                 * @brief intel processor trace (intel pt) can be used in vmx operation
                 *
                 * [bit 14] when set to 1, intel(r) processor trace (intel pt) can be used in vmx operation. if the processor supports intel
                 * pt but does not allow it to be used in vmx operation, execution of vmxon clears ia32_rtit_ctl.traceen; any attempt to
                 * write ia32_rtit_ctl while in vmx operation (including vmx root operation) causes a general-protection exception.
                 *
                 * @see vol3c[30.3(vmx instructions | vmxon-enter vmx operation)]
                 */
		uint64 intelptavailableinvmx : 1;
#define ia32_vmx_misc_intel_pt_available_in_vmx_bit 14
#define ia32_vmx_misc_intel_pt_available_in_vmx_flag 0x4000
#define ia32_vmx_misc_intel_pt_available_in_vmx_mask 0x01
#define ia32_vmx_misc_intel_pt_available_in_vmx(_) (((_) >> 14) & 0x01)

		/**
                 * @brief whether rdmsr can be used to read ia32_smbase_msr in smm
                 *
                 * [bit 15] when set to 1, the rdmsr instruction can be used in system-management mode (smm) to read the ia32_smbase msr
                 * (msr address 9eh).
                 *
                 * @see vol3c[34.15.6.3(saving guest state)]
                 */
		uint64 rdmsrcanreadia32smbasemsrinsmm : 1;
#define ia32_vmx_misc_rdmsr_can_read_ia32_smbase_msr_in_smm_bit 15
#define ia32_vmx_misc_rdmsr_can_read_ia32_smbase_msr_in_smm_flag 0x8000
#define ia32_vmx_misc_rdmsr_can_read_ia32_smbase_msr_in_smm_mask 0x01
#define ia32_vmx_misc_rdmsr_can_read_ia32_smbase_msr_in_smm(_) \
	(((_) >> 15) & 0x01)

		/**
                 * @brief number of cr3 target values supported by the processor (0-256)
                 *
                 * [bits 24:16] indicate the number of cr3-target values supported by the processor. this number is a value between 0 and
                 * 256, inclusive (bit 24 is set if and only if bits 23:16 are clear).
                 */
		uint64 cr3targetcount : 9;
#define ia32_vmx_misc_cr3_target_count_bit 16
#define ia32_vmx_misc_cr3_target_count_flag 0x1ff0000
#define ia32_vmx_misc_cr3_target_count_mask 0x1ff
#define ia32_vmx_misc_cr3_target_count(_) (((_) >> 16) & 0x1ff)

		/**
                 * @brief maximum number of msrs in the vmcs. (n+1)*512
                 *
                 * [bits 27:25] used to compute the recommended maximum number of msrs that should appear in the vm-exit msr-store list,
                 * the vm-exit msr-load list, or the vm-entry msr-load list. specifically, if the value bits 27:25 of ia32_vmx_misc is n,
                 * then 512 * (n + 1) is the recommended maximum number of msrs to be included in each list. if the limit is exceeded,
                 * undefined processor behavior may result (including a machine check during the vmx transition).
                 */
		uint64 maxnumberofmsr : 3;
#define ia32_vmx_misc_max_number_of_msr_bit 25
#define ia32_vmx_misc_max_number_of_msr_flag 0xe000000
#define ia32_vmx_misc_max_number_of_msr_mask 0x07
#define ia32_vmx_misc_max_number_of_msr(_) (((_) >> 25) & 0x07)

		/**
                 * @brief whether bit 2 of ia32_smm_monitor_ctl can be set to 1
                 *
                 * [bit 28] when set to 1, bit 2 of the ia32_smm_monitor_ctl can be set to 1. vmxoff unblocks smis unless
                 * ia32_smm_monitor_ctl[bit 2] is 1.
                 *
                 * @see vol3c[34.14.4(vmxoff and smi unblocking)]
                 */
		uint64 smmmonitorctlb2 : 1;
#define ia32_vmx_misc_smm_monitor_ctl_b2_bit 28
#define ia32_vmx_misc_smm_monitor_ctl_b2_flag 0x10000000
#define ia32_vmx_misc_smm_monitor_ctl_b2_mask 0x01
#define ia32_vmx_misc_smm_monitor_ctl_b2(_) (((_) >> 28) & 0x01)

		/**
                 * @brief whether vmwrite can be used to write vm-exit information fields
                 *
                 * [bit 29] when set to 1, software can use vmwrite to write to any supported field in the vmcs; otherwise, vmwrite cannot
                 * be used to modify vm-exit information fields.
                 */
		uint64 vmwritevmexitinfo : 1;
#define ia32_vmx_misc_vmwrite_vmexit_info_bit 29
#define ia32_vmx_misc_vmwrite_vmexit_info_flag 0x20000000
#define ia32_vmx_misc_vmwrite_vmexit_info_mask 0x01
#define ia32_vmx_misc_vmwrite_vmexit_info(_) (((_) >> 29) & 0x01)

		/**
                 * [bit 30] when set to 1, vm entry allows injection of a software interrupt, software exception, or privileged software
                 * exception with an instruction length of 0.
                 */
		uint64 zerolengthinstructionvmentryinjection : 1;
#define ia32_vmx_misc_zero_length_instruction_vmentry_injection_bit 30
#define ia32_vmx_misc_zero_length_instruction_vmentry_injection_flag 0x40000000
#define ia32_vmx_misc_zero_length_instruction_vmentry_injection_mask 0x01
#define ia32_vmx_misc_zero_length_instruction_vmentry_injection(_) \
	(((_) >> 30) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * @brief mseg revision identifier used by the processor
                 *
                 * [bits 63:32] report the 32-bit mseg revision identifier used by the processor.
                 */
		uint64 msegid : 32;
#define ia32_vmx_misc_mseg_id_bit 32
#define ia32_vmx_misc_mseg_id_flag 0xffffffff00000000
#define ia32_vmx_misc_mseg_id_mask 0xffffffff
#define ia32_vmx_misc_mseg_id(_) (((_) >> 32) & 0xffffffff)
	};

	uint64 flags;
} ia32_vmx_misc_register;

/**
 * capability reporting register of cr0 bits fixed to 0.
 *
 * @remarks if cpuid.01h:ecx.[5] = 1
 * @see vol3d[a.7(vmx-fixed bits in cr0)]
 * @see vol3d[a.7(vmx-fixed bits in cr0)] (reference)
 */
#define ia32_vmx_cr0_fixed0 0x00000486

/**
 * capability reporting register of cr0 bits fixed to 1.
 *
 * @remarks if cpuid.01h:ecx.[5] = 1
 * @see vol3d[a.7(vmx-fixed bits in cr0)]
 * @see vol3d[a.7(vmx-fixed bits in cr0)] (reference)
 */
#define ia32_vmx_cr0_fixed1 0x00000487

/**
 * capability reporting register of cr4 bits fixed to 0.
 *
 * @remarks if cpuid.01h:ecx.[5] = 1
 * @see vol3d[a.8(vmx-fixed bits in cr4)]
 * @see vol3d[a.8(vmx-fixed bits in cr4)] (reference)
 */
#define ia32_vmx_cr4_fixed0 0x00000488

/**
 * capability reporting register of cr4 bits fixed to 1.
 *
 * @remarks if cpuid.01h:ecx.[5] = 1
 * @see vol3d[a.8(vmx-fixed bits in cr4)]
 * @see vol3d[a.8(vmx-fixed bits in cr4)] (reference)
 */
#define ia32_vmx_cr4_fixed1 0x00000489

/**
 * capability reporting register of vmcs field enumeration.
 *
 * @remarks if cpuid.01h:ecx.[5] = 1
 * @see vol3d[a.9(vmcs enumeration)]
 * @see vol3d[a.9(vmcs enumeration)] (reference)
 */
#define ia32_vmx_vmcs_enum 0x0000048a
typedef union {
	struct {
		/**
                 * [bit 0] indicates access type.
                 */
		uint64 accesstype : 1;
#define ia32_vmx_vmcs_enum_access_type_bit 0
#define ia32_vmx_vmcs_enum_access_type_flag 0x01
#define ia32_vmx_vmcs_enum_access_type_mask 0x01
#define ia32_vmx_vmcs_enum_access_type(_) (((_) >> 0) & 0x01)

		/**
                 * [bits 9:1] highest index value used for any vmcs encoding.
                 */
		uint64 highestindexvalue : 9;
#define ia32_vmx_vmcs_enum_highest_index_value_bit 1
#define ia32_vmx_vmcs_enum_highest_index_value_flag 0x3fe
#define ia32_vmx_vmcs_enum_highest_index_value_mask 0x1ff
#define ia32_vmx_vmcs_enum_highest_index_value(_) (((_) >> 1) & 0x1ff)

		/**
                 * [bits 11:10] indicate the field's type.
                 */
		uint64 fieldtype : 2;
#define ia32_vmx_vmcs_enum_field_type_bit 10
#define ia32_vmx_vmcs_enum_field_type_flag 0xc00
#define ia32_vmx_vmcs_enum_field_type_mask 0x03
#define ia32_vmx_vmcs_enum_field_type(_) (((_) >> 10) & 0x03)
		uint64 reserved1 : 1;

		/**
                 * [bits 14:13] indicate the field's width.
                 */
		uint64 fieldwidth : 2;
#define ia32_vmx_vmcs_enum_field_width_bit 13
#define ia32_vmx_vmcs_enum_field_width_flag 0x6000
#define ia32_vmx_vmcs_enum_field_width_mask 0x03
#define ia32_vmx_vmcs_enum_field_width(_) (((_) >> 13) & 0x03)
		uint64 reserved2 : 49;
	};

	uint64 flags;
} ia32_vmx_vmcs_enum_register;

/**
 * capability reporting register of secondary processor-based vm-execution controls.
 *
 * @remarks if ( cpuid.01h:ecx.[5] && ia32_vmx_procbased_ctls[63] )
 * @see vol3d[a.3.3(secondary processor-based vm-execution controls)]
 * @see vol3d[24.6.2(processor-based vm-execution controls)] (reference)
 */
#define ia32_vmx_procbased_ctls2 0x0000048b
typedef union {
	struct {
		/**
                 * @brief virtualize apic access
                 *
                 * [bit 0] if this control is 1, the logical processor treats specially accesses to the page with the apicaccess address.
                 *
                 * @see vol3c[29.4(virtualizing memory-mapped apic accesses)]
                 */
		uint64 virtualizeapicaccesses : 1;
#define ia32_vmx_procbased_ctls2_virtualize_apic_accesses_bit 0
#define ia32_vmx_procbased_ctls2_virtualize_apic_accesses_flag 0x01
#define ia32_vmx_procbased_ctls2_virtualize_apic_accesses_mask 0x01
#define ia32_vmx_procbased_ctls2_virtualize_apic_accesses(_) (((_) >> 0) & 0x01)

		/**
                 * @brief ept supported/enabled
                 *
                 * [bit 1] if this control is 1, extended page tables (ept) are enabled.
                 *
                 * @see vol3c[28.2(the extended page table mechanism (ept))]
                 */
		uint64 enableept : 1;
#define ia32_vmx_procbased_ctls2_enable_ept_bit 1
#define ia32_vmx_procbased_ctls2_enable_ept_flag 0x02
#define ia32_vmx_procbased_ctls2_enable_ept_mask 0x01
#define ia32_vmx_procbased_ctls2_enable_ept(_) (((_) >> 1) & 0x01)

		/**
                 * @brief descriptor table instructions cause vm-exits
                 *
                 * [bit 2] this control determines whether executions of lgdt, lidt, lldt, ltr, sgdt, sidt, sldt, and str cause vm exits.
                 */
		uint64 descriptortableexiting : 1;
#define ia32_vmx_procbased_ctls2_descriptor_table_exiting_bit 2
#define ia32_vmx_procbased_ctls2_descriptor_table_exiting_flag 0x04
#define ia32_vmx_procbased_ctls2_descriptor_table_exiting_mask 0x01
#define ia32_vmx_procbased_ctls2_descriptor_table_exiting(_) (((_) >> 2) & 0x01)

		/**
                 * @brief rdtscp supported/enabled
                 *
                 * [bit 3] if this control is 0, any execution of rdtscp causes an invalid-opcode exception (\#ud).
                 */
		uint64 enablerdtscp : 1;
#define ia32_vmx_procbased_ctls2_enable_rdtscp_bit 3
#define ia32_vmx_procbased_ctls2_enable_rdtscp_flag 0x08
#define ia32_vmx_procbased_ctls2_enable_rdtscp_mask 0x01
#define ia32_vmx_procbased_ctls2_enable_rdtscp(_) (((_) >> 3) & 0x01)

		/**
                 * @brief virtualize x2apic mode
                 *
                 * [bit 4] if this control is 1, the logical processor treats specially rdmsr and wrmsr to apic msrs (in the range
                 * 800h-8ffh).
                 *
                 * @see vol3c[29.5(virtualizing msr-based apic accesses)]
                 */
		uint64 virtualizex2apicmode : 1;
#define ia32_vmx_procbased_ctls2_virtualize_x2apic_mode_bit 4
#define ia32_vmx_procbased_ctls2_virtualize_x2apic_mode_flag 0x10
#define ia32_vmx_procbased_ctls2_virtualize_x2apic_mode_mask 0x01
#define ia32_vmx_procbased_ctls2_virtualize_x2apic_mode(_) (((_) >> 4) & 0x01)

		/**
                 * @brief vpid supported/enabled
                 *
                 * [bit 5] if this control is 1, cached translations of linear addresses are associated with a virtualprocessor identifier
                 * (vpid).
                 *
                 * @see vol3c[28.1(virtual processor identifiers (vpids))]
                 */
		uint64 enablevpid : 1;
#define ia32_vmx_procbased_ctls2_enable_vpid_bit 5
#define ia32_vmx_procbased_ctls2_enable_vpid_flag 0x20
#define ia32_vmx_procbased_ctls2_enable_vpid_mask 0x01
#define ia32_vmx_procbased_ctls2_enable_vpid(_) (((_) >> 5) & 0x01)

		/**
                 * @brief vm-exit when executing the wbinvd instruction
                 *
                 * [bit 6] this control determines whether executions of wbinvd cause vm exits.
                 */
		uint64 wbinvdexiting : 1;
#define ia32_vmx_procbased_ctls2_wbinvd_exiting_bit 6
#define ia32_vmx_procbased_ctls2_wbinvd_exiting_flag 0x40
#define ia32_vmx_procbased_ctls2_wbinvd_exiting_mask 0x01
#define ia32_vmx_procbased_ctls2_wbinvd_exiting(_) (((_) >> 6) & 0x01)

		/**
                 * @brief unrestricted guest execution
                 *
                 * [bit 7] this control determines whether guest software may run in unpaged protected mode or in realaddress mode.
                 */
		uint64 unrestrictedguest : 1;
#define ia32_vmx_procbased_ctls2_unrestricted_guest_bit 7
#define ia32_vmx_procbased_ctls2_unrestricted_guest_flag 0x80
#define ia32_vmx_procbased_ctls2_unrestricted_guest_mask 0x01
#define ia32_vmx_procbased_ctls2_unrestricted_guest(_) (((_) >> 7) & 0x01)

		/**
                 * @brief apic register virtualization
                 *
                 * [bit 8] if this control is 1, the logical processor virtualizes certain apic accesses.
                 *
                 * @see vol3c[29.4(virtualizing memory-mapped apic accesses)]
                 * @see vol3c[29.5(virtualizing msr-based apic accesses)]
                 */
		uint64 apicregistervirtualization : 1;
#define ia32_vmx_procbased_ctls2_apic_register_virtualization_bit 8
#define ia32_vmx_procbased_ctls2_apic_register_virtualization_flag 0x100
#define ia32_vmx_procbased_ctls2_apic_register_virtualization_mask 0x01
#define ia32_vmx_procbased_ctls2_apic_register_virtualization(_) \
	(((_) >> 8) & 0x01)

		/**
                 * @brief virtual-interrupt delivery
                 *
                 * [bit 9] this controls enables the evaluation and delivery of pending virtual interrupts as well as the emulation of
                 * writes to the apic registers that control interrupt prioritization.
                 */
		uint64 virtualinterruptdelivery : 1;
#define ia32_vmx_procbased_ctls2_virtual_interrupt_delivery_bit 9
#define ia32_vmx_procbased_ctls2_virtual_interrupt_delivery_flag 0x200
#define ia32_vmx_procbased_ctls2_virtual_interrupt_delivery_mask 0x01
#define ia32_vmx_procbased_ctls2_virtual_interrupt_delivery(_) \
	(((_) >> 9) & 0x01)

		/**
                 * @brief a specified number of pause loops cause a vm-exit
                 *
                 * [bit 10] this control determines whether a series of executions of pause can cause a vm exit.
                 *
                 * @see vol3c[24.6.13(controls for pause-loop exiting)]
                 * @see vol3c[25.1.3(instructions that cause vm exits conditionally)]
                 */
		uint64 pauseloopexiting : 1;
#define ia32_vmx_procbased_ctls2_pause_loop_exiting_bit 10
#define ia32_vmx_procbased_ctls2_pause_loop_exiting_flag 0x400
#define ia32_vmx_procbased_ctls2_pause_loop_exiting_mask 0x01
#define ia32_vmx_procbased_ctls2_pause_loop_exiting(_) (((_) >> 10) & 0x01)

		/**
                 * @brief vm-exit when executing rdrand instructions
                 *
                 * [bit 11] this control determines whether executions of rdrand cause vm exits.
                 */
		uint64 rdrandexiting : 1;
#define ia32_vmx_procbased_ctls2_rdrand_exiting_bit 11
#define ia32_vmx_procbased_ctls2_rdrand_exiting_flag 0x800
#define ia32_vmx_procbased_ctls2_rdrand_exiting_mask 0x01
#define ia32_vmx_procbased_ctls2_rdrand_exiting(_) (((_) >> 11) & 0x01)

		/**
                 * @brief enables invpcid instructions
                 *
                 * [bit 12] if this control is 0, any execution of invpcid causes a \#ud.
                 */
		uint64 enableinvpcid : 1;
#define ia32_vmx_procbased_ctls2_enable_invpcid_bit 12
#define ia32_vmx_procbased_ctls2_enable_invpcid_flag 0x1000
#define ia32_vmx_procbased_ctls2_enable_invpcid_mask 0x01
#define ia32_vmx_procbased_ctls2_enable_invpcid(_) (((_) >> 12) & 0x01)

		/**
                 * @brief enables vmfunc instructions
                 *
                 * [bit 13] setting this control to 1 enables use of the vmfunc instruction in vmx non-root operation.
                 *
                 * @see vol3c[25.5.5(vm functions)]
                 */
		uint64 enablevmfunctions : 1;
#define ia32_vmx_procbased_ctls2_enable_vm_functions_bit 13
#define ia32_vmx_procbased_ctls2_enable_vm_functions_flag 0x2000
#define ia32_vmx_procbased_ctls2_enable_vm_functions_mask 0x01
#define ia32_vmx_procbased_ctls2_enable_vm_functions(_) (((_) >> 13) & 0x01)

		/**
                 * @brief enables vmcs shadowing
                 *
                 * [bit 14] if this control is 1, executions of vmread and vmwrite in vmx non-root operation may access a shadow vmcs
                 * (instead of causing vm exits).
                 *
                 * @see {'vol3c[24.10(vmcs types': 'ordinary and shadow)]'}
                 * @see vol3c[30.3(vmx instructions)]
                 */
		uint64 vmcsshadowing : 1;
#define ia32_vmx_procbased_ctls2_vmcs_shadowing_bit 14
#define ia32_vmx_procbased_ctls2_vmcs_shadowing_flag 0x4000
#define ia32_vmx_procbased_ctls2_vmcs_shadowing_mask 0x01
#define ia32_vmx_procbased_ctls2_vmcs_shadowing(_) (((_) >> 14) & 0x01)

		/**
                 * @brief enables encls vm-exits
                 *
                 * [bit 15] if this control is 1, executions of encls consult the encls-exiting bitmap to determine whether the instruction
                 * causes a vm exit.
                 *
                 * @see vol3c[24.6.16(encls-exiting bitmap)]
                 * @see vol3c[25.1.3(instructions that cause vm exits conditionally)]
                 */
		uint64 enableenclsexiting : 1;
#define ia32_vmx_procbased_ctls2_enable_encls_exiting_bit 15
#define ia32_vmx_procbased_ctls2_enable_encls_exiting_flag 0x8000
#define ia32_vmx_procbased_ctls2_enable_encls_exiting_mask 0x01
#define ia32_vmx_procbased_ctls2_enable_encls_exiting(_) (((_) >> 15) & 0x01)

		/**
                 * @brief vm-exit when executing rdseed
                 *
                 * [bit 16] this control determines whether executions of rdseed cause vm exits.
                 */
		uint64 rdseedexiting : 1;
#define ia32_vmx_procbased_ctls2_rdseed_exiting_bit 16
#define ia32_vmx_procbased_ctls2_rdseed_exiting_flag 0x10000
#define ia32_vmx_procbased_ctls2_rdseed_exiting_mask 0x01
#define ia32_vmx_procbased_ctls2_rdseed_exiting(_) (((_) >> 16) & 0x01)

		/**
                 * @brief enables page-modification logging
                 *
                 * [bit 17] if this control is 1, an access to a guest-physical address that sets an ept dirty bit first adds an entry to
                 * the page-modification log.
                 *
                 * @see vol3c[28.2.5(page-modification logging)]
                 */
		uint64 enablepml : 1;
#define ia32_vmx_procbased_ctls2_enable_pml_bit 17
#define ia32_vmx_procbased_ctls2_enable_pml_flag 0x20000
#define ia32_vmx_procbased_ctls2_enable_pml_mask 0x01
#define ia32_vmx_procbased_ctls2_enable_pml(_) (((_) >> 17) & 0x01)

		/**
                 * @brief controls whether ept-violations may cause
                 *
                 * [bit 18] if this control is 1, ept violations may cause virtualization exceptions (\#ve) instead of vm exits.
                 *
                 * @see vol3c[25.5.6(virtualization exceptions)]
                 */
		uint64 eptviolation : 1;
#define ia32_vmx_procbased_ctls2_ept_violation_bit 18
#define ia32_vmx_procbased_ctls2_ept_violation_flag 0x40000
#define ia32_vmx_procbased_ctls2_ept_violation_mask 0x01
#define ia32_vmx_procbased_ctls2_ept_violation(_) (((_) >> 18) & 0x01)

		/**
                 * @brief conceal vmx non-root operation from intel processor trace (pt)
                 *
                 * [bit 19] if this control is 1, intel processor trace suppresses from pips an indication that the processor was in vmx
                 * non-root operation and omits a vmcs packet from any psb+ produced in vmx nonroot operation.
                 *
                 * @see vol3c[35(intel(r) processor trace)]
                 */
		uint64 concealvmxfrompt : 1;
#define ia32_vmx_procbased_ctls2_conceal_vmx_from_pt_bit 19
#define ia32_vmx_procbased_ctls2_conceal_vmx_from_pt_flag 0x80000
#define ia32_vmx_procbased_ctls2_conceal_vmx_from_pt_mask 0x01
#define ia32_vmx_procbased_ctls2_conceal_vmx_from_pt(_) (((_) >> 19) & 0x01)

		/**
                 * @brief enables xsaves/xrstors instructions
                 *
                 * [bit 20] if this control is 0, any execution of xsaves or xrstors causes a \#ud.
                 */
		uint64 enablexsaves : 1;
#define ia32_vmx_procbased_ctls2_enable_xsaves_bit 20
#define ia32_vmx_procbased_ctls2_enable_xsaves_flag 0x100000
#define ia32_vmx_procbased_ctls2_enable_xsaves_mask 0x01
#define ia32_vmx_procbased_ctls2_enable_xsaves(_) (((_) >> 20) & 0x01)
		uint64 reserved1 : 1;

		/**
                 * [bit 22] if this control is 1, ept execute permissions are based on whether the linear address being accessed is
                 * supervisor mode or user mode.
                 *
                 * @see vol3c[28(vmx support for address translation)]
                 */
		uint64 modebasedexecutecontrolforept : 1;
#define ia32_vmx_procbased_ctls2_mode_based_execute_control_for_ept_bit 22
#define ia32_vmx_procbased_ctls2_mode_based_execute_control_for_ept_flag \
	0x400000
#define ia32_vmx_procbased_ctls2_mode_based_execute_control_for_ept_mask 0x01
#define ia32_vmx_procbased_ctls2_mode_based_execute_control_for_ept(_) \
	(((_) >> 22) & 0x01)
		uint64 reserved2 : 2;

		/**
                 * @brief use tsc scaling
                 *
                 * [bit 25] this control determines whether executions of rdtsc, executions of rdtscp, and executions of rdmsr that read
                 * from the ia32_time_stamp_counter msr return a value modified by the tsc multiplier field.
                 *
                 * @see vol3c[24.6.5(time-stamp counter offset and multiplier)]
                 * @see vol3c[25.3(changes to instruction behavior in vmx non-root operation)]
                 */
		uint64 usetscscaling : 1;
#define ia32_vmx_procbased_ctls2_use_tsc_scaling_bit 25
#define ia32_vmx_procbased_ctls2_use_tsc_scaling_flag 0x2000000
#define ia32_vmx_procbased_ctls2_use_tsc_scaling_mask 0x01
#define ia32_vmx_procbased_ctls2_use_tsc_scaling(_) (((_) >> 25) & 0x01)
		uint64 reserved3 : 38;
	};

	uint64 flags;
} ia32_vmx_procbased_ctls2_register;

/**
 * capability reporting register of ept and vpid.
 *
 * @remarks if ( cpuid.01h:ecx.[5] && ia32_vmx_procbased_ctls[63] && (ia32_vmx_procbased_ctls2[33] ||
 *          ia32_vmx_procbased_ctls2[37]) )
 * @see vol3d[a.10(vpid and ept capabilities)]
 * @see vol3d[a.10(vpid and ept capabilities)] (reference)
 */
#define ia32_vmx_ept_vpid_cap 0x0000048c
typedef union {
	struct {
		/**
                 * [bit 0] when set to 1, the processor supports execute-only translations by ept. this support allows software to
                 * configure ept paging-structure entries in which bits 1:0 are clear (indicating that data accesses are not allowed) and
                 * bit 2 is set (indicating that instruction fetches are allowed).
                 */
		uint64 executeonlypages : 1;
#define ia32_vmx_ept_vpid_cap_execute_only_pages_bit 0
#define ia32_vmx_ept_vpid_cap_execute_only_pages_flag 0x01
#define ia32_vmx_ept_vpid_cap_execute_only_pages_mask 0x01
#define ia32_vmx_ept_vpid_cap_execute_only_pages(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 5;

		/**
                 * [bit 6] indicates support for a page-walk length of 4.
                 */
		uint64 pagewalklength4 : 1;
#define ia32_vmx_ept_vpid_cap_page_walk_length_4_bit 6
#define ia32_vmx_ept_vpid_cap_page_walk_length_4_flag 0x40
#define ia32_vmx_ept_vpid_cap_page_walk_length_4_mask 0x01
#define ia32_vmx_ept_vpid_cap_page_walk_length_4(_) (((_) >> 6) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * [bit 8] when set to 1, the logical processor allows software to configure the ept paging-structure memory type to be
                 * uncacheable (uc).
                 *
                 * @see vol3c[24.6.11(extended-page-table pointer (eptp))]
                 */
		uint64 memorytypeuncacheable : 1;
#define ia32_vmx_ept_vpid_cap_memory_type_uncacheable_bit 8
#define ia32_vmx_ept_vpid_cap_memory_type_uncacheable_flag 0x100
#define ia32_vmx_ept_vpid_cap_memory_type_uncacheable_mask 0x01
#define ia32_vmx_ept_vpid_cap_memory_type_uncacheable(_) (((_) >> 8) & 0x01)
		uint64 reserved3 : 5;

		/**
                 * [bit 14] when set to 1, the logical processor allows software to configure the ept paging-structure memory type to be
                 * write-back (wb).
                 */
		uint64 memorytypewriteback : 1;
#define ia32_vmx_ept_vpid_cap_memory_type_write_back_bit 14
#define ia32_vmx_ept_vpid_cap_memory_type_write_back_flag 0x4000
#define ia32_vmx_ept_vpid_cap_memory_type_write_back_mask 0x01
#define ia32_vmx_ept_vpid_cap_memory_type_write_back(_) (((_) >> 14) & 0x01)
		uint64 reserved4 : 1;

		/**
                 * [bit 16] when set to 1, the logical processor allows software to configure a ept pde to map a 2-mbyte page (by setting
                 * bit 7 in the ept pde).
                 */
		uint64 pde2mbpages : 1;
#define ia32_vmx_ept_vpid_cap_pde_2mb_pages_bit 16
#define ia32_vmx_ept_vpid_cap_pde_2mb_pages_flag 0x10000
#define ia32_vmx_ept_vpid_cap_pde_2mb_pages_mask 0x01
#define ia32_vmx_ept_vpid_cap_pde_2mb_pages(_) (((_) >> 16) & 0x01)

		/**
                 * [bit 17] when set to 1, the logical processor allows software to configure a ept pdpte to map a 1-gbyte page (by setting
                 * bit 7 in the ept pdpte).
                 */
		uint64 pdpte1gbpages : 1;
#define ia32_vmx_ept_vpid_cap_pdpte_1gb_pages_bit 17
#define ia32_vmx_ept_vpid_cap_pdpte_1gb_pages_flag 0x20000
#define ia32_vmx_ept_vpid_cap_pdpte_1gb_pages_mask 0x01
#define ia32_vmx_ept_vpid_cap_pdpte_1gb_pages(_) (((_) >> 17) & 0x01)
		uint64 reserved5 : 2;

		/**
                 * [bit 20] if bit 20 is read as 1, the invept instruction is supported.
                 *
                 * @see vol3c[30(vmx instruction reference)]
                 * @see vol3c[28.3.3.1(operations that invalidate cached mappings)]
                 */
		uint64 invept : 1;
#define ia32_vmx_ept_vpid_cap_invept_bit 20
#define ia32_vmx_ept_vpid_cap_invept_flag 0x100000
#define ia32_vmx_ept_vpid_cap_invept_mask 0x01
#define ia32_vmx_ept_vpid_cap_invept(_) (((_) >> 20) & 0x01)

		/**
                 * [bit 21] when set to 1, accessed and dirty flags for ept are supported.
                 *
                 * @see vol3c[28.2.4(accessed and dirty flags for ept)]
                 */
		uint64 eptaccessedanddirtyflags : 1;
#define ia32_vmx_ept_vpid_cap_ept_accessed_and_dirty_flags_bit 21
#define ia32_vmx_ept_vpid_cap_ept_accessed_and_dirty_flags_flag 0x200000
#define ia32_vmx_ept_vpid_cap_ept_accessed_and_dirty_flags_mask 0x01
#define ia32_vmx_ept_vpid_cap_ept_accessed_and_dirty_flags(_) \
	(((_) >> 21) & 0x01)

		/**
                 * [bit 22] when set to 1, the processor reports advanced vm-exit information for ept violations. this reporting is done
                 * only if this bit is read as 1.
                 *
                 * @see vol3c[27.2.1(basic vm-exit information)]
                 */
		uint64 advancedvmexiteptviolationsinformation : 1;
#define ia32_vmx_ept_vpid_cap_advanced_vmexit_ept_violations_information_bit 22
#define ia32_vmx_ept_vpid_cap_advanced_vmexit_ept_violations_information_flag \
	0x400000
#define ia32_vmx_ept_vpid_cap_advanced_vmexit_ept_violations_information_mask \
	0x01
#define ia32_vmx_ept_vpid_cap_advanced_vmexit_ept_violations_information(_) \
	(((_) >> 22) & 0x01)
		uint64 reserved6 : 2;

		/**
                 * [bit 25] when set to 1, the single-context invept type is supported.
                 *
                 * @see vol3c[30(vmx instruction reference)]
                 * @see vol3c[28.3.3.1(operations that invalidate cached mappings)]
                 */
		uint64 inveptsinglecontext : 1;
#define ia32_vmx_ept_vpid_cap_invept_single_context_bit 25
#define ia32_vmx_ept_vpid_cap_invept_single_context_flag 0x2000000
#define ia32_vmx_ept_vpid_cap_invept_single_context_mask 0x01
#define ia32_vmx_ept_vpid_cap_invept_single_context(_) (((_) >> 25) & 0x01)

		/**
                 * [bit 26] when set to 1, the all-context invept type is supported.
                 *
                 * @see vol3c[30(vmx instruction reference)]
                 * @see vol3c[28.3.3.1(operations that invalidate cached mappings)]
                 */
		uint64 inveptallcontexts : 1;
#define ia32_vmx_ept_vpid_cap_invept_all_contexts_bit 26
#define ia32_vmx_ept_vpid_cap_invept_all_contexts_flag 0x4000000
#define ia32_vmx_ept_vpid_cap_invept_all_contexts_mask 0x01
#define ia32_vmx_ept_vpid_cap_invept_all_contexts(_) (((_) >> 26) & 0x01)
		uint64 reserved7 : 5;

		/**
                 * [bit 32] when set to 1, the invvpid instruction is supported.
                 */
		uint64 invvpid : 1;
#define ia32_vmx_ept_vpid_cap_invvpid_bit 32
#define ia32_vmx_ept_vpid_cap_invvpid_flag 0x100000000
#define ia32_vmx_ept_vpid_cap_invvpid_mask 0x01
#define ia32_vmx_ept_vpid_cap_invvpid(_) (((_) >> 32) & 0x01)
		uint64 reserved8 : 7;

		/**
                 * [bit 40] when set to 1, the individual-address invvpid type is supported.
                 */
		uint64 invvpidindividualaddress : 1;
#define ia32_vmx_ept_vpid_cap_invvpid_individual_address_bit 40
#define ia32_vmx_ept_vpid_cap_invvpid_individual_address_flag 0x10000000000
#define ia32_vmx_ept_vpid_cap_invvpid_individual_address_mask 0x01
#define ia32_vmx_ept_vpid_cap_invvpid_individual_address(_) (((_) >> 40) & 0x01)

		/**
                 * [bit 41] when set to 1, the single-context invvpid type is supported.
                 */
		uint64 invvpidsinglecontext : 1;
#define ia32_vmx_ept_vpid_cap_invvpid_single_context_bit 41
#define ia32_vmx_ept_vpid_cap_invvpid_single_context_flag 0x20000000000
#define ia32_vmx_ept_vpid_cap_invvpid_single_context_mask 0x01
#define ia32_vmx_ept_vpid_cap_invvpid_single_context(_) (((_) >> 41) & 0x01)

		/**
                 * [bit 42] when set to 1, the all-context invvpid type is supported.
                 */
		uint64 invvpidallcontexts : 1;
#define ia32_vmx_ept_vpid_cap_invvpid_all_contexts_bit 42
#define ia32_vmx_ept_vpid_cap_invvpid_all_contexts_flag 0x40000000000
#define ia32_vmx_ept_vpid_cap_invvpid_all_contexts_mask 0x01
#define ia32_vmx_ept_vpid_cap_invvpid_all_contexts(_) (((_) >> 42) & 0x01)

		/**
                 * [bit 43] when set to 1, the single-context-retaining-globals invvpid type is supported.
                 */
		uint64 invvpidsinglecontextretainglobals : 1;
#define ia32_vmx_ept_vpid_cap_invvpid_single_context_retain_globals_bit 43
#define ia32_vmx_ept_vpid_cap_invvpid_single_context_retain_globals_flag \
	0x80000000000
#define ia32_vmx_ept_vpid_cap_invvpid_single_context_retain_globals_mask 0x01
#define ia32_vmx_ept_vpid_cap_invvpid_single_context_retain_globals(_) \
	(((_) >> 43) & 0x01)
		uint64 reserved9 : 20;
	};

	uint64 flags;
} ia32_vmx_ept_vpid_cap_register;

/**
 * @defgroup ia32_vmx_true_ctls \
 *           ia32_vmx_true_(x)_ctls
 *
 * capability reporting register of pin-based vm-execution flex controls, primary processor-based vm-execution flex
 * controls, vm-exit flex controls and vm-entry flex controls.
 *
 * @remarks if ( cpuid.01h:ecx.[5] = 1 && ia32_vmx_basic[55] )
 * @see vol3d[a.3.1(pin-based vm-execution controls)]
 * @see vol3d[a.3.2(primary processor-based vm-execution controls)]
 * @see vol3d[a.4(vm-exit controls)]
 * @see vol3d[a.5(vm-entry controls)]
 * @see vol3d[a.3.1(pin-based vmexecution controls)] (reference)
 * @see vol3d[a.3.2(primary processor-based vm-execution controls)] (reference)
 * @see vol3d[a.4(vm-exit controls)] (reference)
 * @see vol3d[a.5(vm-entry controls)] (reference)
 * @{
 */
#define ia32_vmx_true_pinbased_ctls 0x0000048d
#define ia32_vmx_true_procbased_ctls 0x0000048e
#define ia32_vmx_true_exit_ctls 0x0000048f
#define ia32_vmx_true_entry_ctls 0x00000490
typedef union {
	struct {
		/**
                 * [bits 31:0] indicate the allowed 0-settings of these controls. vm entry allows control x to be 0 if bit x in the msr is
                 * cleared to 0; if bit x in the msr is set to 1, vm entry fails if control x is 0.
                 */
		uint64 allowed0settings : 32;
#define ia32_vmx_true_ctls_allowed_0_settings_bit 0
#define ia32_vmx_true_ctls_allowed_0_settings_flag 0xffffffff
#define ia32_vmx_true_ctls_allowed_0_settings_mask 0xffffffff
#define ia32_vmx_true_ctls_allowed_0_settings(_) (((_) >> 0) & 0xffffffff)

		/**
                 * [bits 63:32] indicate the allowed 1-settings of these controls. vm entry allows control x to be 1 if bit 32+x in the msr
                 * is set to 1; if bit 32+x in the msr is cleared to 0, vm entry fails if control x is 1.
                 */
		uint64 allowed1settings : 32;
#define ia32_vmx_true_ctls_allowed_1_settings_bit 32
#define ia32_vmx_true_ctls_allowed_1_settings_flag 0xffffffff00000000
#define ia32_vmx_true_ctls_allowed_1_settings_mask 0xffffffff
#define ia32_vmx_true_ctls_allowed_1_settings(_) (((_) >> 32) & 0xffffffff)
	};

	uint64 flags;
} ia32_vmx_true_ctls_register;

/**
 * @}
 */

/**
 * capability reporting register of vmfunction controls.
 *
 * @remarks if ( cpuid.01h:ecx.[5] = 1 && ia32_vmx_basic[55] )
 * @see vol3d[a.11(vm functions)]
 * @see vol3d[24.6.14(vm-function controls)] (reference)
 */
#define ia32_vmx_vmfunc 0x00000491
typedef union {
	struct {
		/**
                 * [bit 0] the eptp-switching vm function changes the ept pointer to a value chosen from the eptp list.
                 *
                 * @see vol3c[25.5.5.3(eptp switching)]
                 */
		uint64 eptpswitching : 1;
#define ia32_vmx_vmfunc_eptp_switching_bit 0
#define ia32_vmx_vmfunc_eptp_switching_flag 0x01
#define ia32_vmx_vmfunc_eptp_switching_mask 0x01
#define ia32_vmx_vmfunc_eptp_switching(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 63;
	};

	uint64 flags;
} ia32_vmx_vmfunc_register;

/**
 * @defgroup ia32_a_pmc \
 *           ia32_a_pmc(n)
 *
 * full width writable ia32_pmc(n) alias.
 *
 * @remarks (if cpuid.0ah: eax[15:8] > 0) && ia32_perf_capabilities[13] = 1
 * @{
 */
#define ia32_a_pmc0 0x000004c1
#define ia32_a_pmc1 0x000004c2
#define ia32_a_pmc2 0x000004c3
#define ia32_a_pmc3 0x000004c4
#define ia32_a_pmc4 0x000004c5
#define ia32_a_pmc5 0x000004c6
#define ia32_a_pmc6 0x000004c7
#define ia32_a_pmc7 0x000004c8
/**
 * @}
 */

/**
 * allows software to signal some mces to only a single logical processor in the system.
 *
 * @remarks if ia32_mcg_cap.lmce_p = 1
 * @see vol3b[15.3.1.4(ia32_mcg_ext_ctl msr)]
 */
#define ia32_mcg_ext_ctl 0x000004d0
typedef union {
	struct {
		uint64 lmceen : 1;
#define ia32_mcg_ext_ctl_lmce_en_bit 0
#define ia32_mcg_ext_ctl_lmce_en_flag 0x01
#define ia32_mcg_ext_ctl_lmce_en_mask 0x01
#define ia32_mcg_ext_ctl_lmce_en(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 63;
	};

	uint64 flags;
} ia32_mcg_ext_ctl_register;

/**
 * @brief status and svn threshold of sgx support for acm <b>(ro)</b>
 *
 * intel sgx only allows launching acms with an intel sgx svn that is at the same level or higher than the expected intel
 * sgx svn. the expected intel sgx svn is specified by bios and locked down by the processor on the first successful
 * execution of an intel sgx instruction that doesn't return an error code. intel sgx provides interfaces for system
 * software to discover whether a non faulting intel sgx instruction has been executed, and evaluate the suitability of the
 * intel sgx svn value of any acm that is expected to be launched by the os or the vmm.
 *
 * @remarks if cpuid.(eax=07h, ecx=0h): ebx[2] = 1
 * @see vol3d[41.11.3(interactions with authenticated code modules (acms))] (reference)
 */
#define ia32_sgx_svn_status 0x00000500
typedef union {
	struct {
		/**
                 * [bit 0] - if 1, indicates that a non-faulting intel sgx instruction has been executed, consequently, launching a
                 * properly signed acm but with intel sgx svn value less than the bios specified intel sgx svn threshold would lead to an
                 * txt shutdown.
                 * - if 0, indicates that the processor will allow a properly signed acm to launch irrespective of the intel sgx svn value
                 * of the acm.
                 *
                 * @see vol3d[41.11.3(interactions with authenticated code modules (acms))]
                 */
		uint64 lock : 1;
#define ia32_sgx_svn_status_lock_bit 0
#define ia32_sgx_svn_status_lock_flag 0x01
#define ia32_sgx_svn_status_lock_mask 0x01
#define ia32_sgx_svn_status_lock(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 15;

		/**
                 * @brief reflects the expected threshold of intel sgx svn for the sinit acm
                 *
                 * [bits 23:16] - if cpuid.01h:ecx.smx = 1, this field reflects the expected threshold of intel sgx svn for the sinit acm.
                 * - if cpuid.01h:ecx.smx = 0, this field is reserved (0).
                 *
                 * @see vol3d[41.11.3(interactions with authenticated code modules (acms))]
                 */
		uint64 sgxsvnsinit : 8;
#define ia32_sgx_svn_status_sgx_svn_sinit_bit 16
#define ia32_sgx_svn_status_sgx_svn_sinit_flag 0xff0000
#define ia32_sgx_svn_status_sgx_svn_sinit_mask 0xff
#define ia32_sgx_svn_status_sgx_svn_sinit(_) (((_) >> 16) & 0xff)
		uint64 reserved2 : 40;
	};

	uint64 flags;
} ia32_sgx_svn_status_register;

/**
 * trace output base register.
 *
 * @remarks if ( (cpuid.(eax=07h, ecx=0):ebx[25] = 1) && ( (cpuid.(eax=14h,ecx=0): ecx[0] = 1) ||
 *          (cpuid.(eax=14h,ecx=0):ecx[2] = 1) ) )
 * @see vol3c[35.2.7.7(ia32_rtit_output_base msr)] (reference)
 */
#define ia32_rtit_output_base 0x00000560
typedef union {
	struct {
		uint64 reserved1 : 7;

		/**
                 * @brief base physical address
                 *
                 * [bits 47:7] the base physical address. how this address is used depends on the value of ia32_rtit_ctl.topa:
                 * - 0: this is the base physical address of a single, contiguous physical output region. this could be mapped to dram or
                 * to mmio, depending on the value. the base address should be aligned with the size of the region, such that none of the
                 * 1s in the mask value overlap with 1s in the base address. if the base is not aligned, an operational error will result.
                 * - 1: the base physical address of the current topa table. the address must be 4k aligned. writing an address in which
                 * bits 11:7 are non-zero will not cause a \#gp, but an operational error will be signaled once traceen is set.
                 *
                 * @see vol3c[35.2.7.8(ia32_rtit_output_mask_ptrs msr)]
                 * @see vol3c[35.3.9(operational errors)]
                 * @see vol3c[35.2.6.2(table of physical addresses (topa))]
                 */
		uint64 basephysicaladdress : 41;
#define ia32_rtit_output_base_base_physical_address_bit 7
#define ia32_rtit_output_base_base_physical_address_flag 0xffffffffff80
#define ia32_rtit_output_base_base_physical_address_mask 0x1ffffffffff
#define ia32_rtit_output_base_base_physical_address(_) \
	(((_) >> 7) & 0x1ffffffffff)
		uint64 reserved2 : 16;
	};

	uint64 flags;
} ia32_rtit_output_base_register;

/**
 * trace output mask pointers register.
 *
 * @remarks if ( (cpuid.(eax=07h, ecx=0):ebx[25] = 1) && ( (cpuid.(eax=14h,ecx=0):ecx[0] = 1) ||
 *          (cpuid.(eax=14h,ecx=0):ecx[2] = 1) ) )
 * @see vol3c[35.2.7.8(ia32_rtit_output_mask_ptrs msr)] (reference)
 */
#define ia32_rtit_output_mask_ptrs 0x00000561
typedef union {
	struct {
		/**
                 * [bits 6:0] forced to 1, writes are ignored.
                 */
		uint64 lowermask : 7;
#define ia32_rtit_output_mask_ptrs_lower_mask_bit 0
#define ia32_rtit_output_mask_ptrs_lower_mask_flag 0x7f
#define ia32_rtit_output_mask_ptrs_lower_mask_mask 0x7f
#define ia32_rtit_output_mask_ptrs_lower_mask(_) (((_) >> 0) & 0x7f)

		/**
                 * @brief maskortableoffset
                 *
                 * [bits 31:7] the use of this field depends on the value of ia32_rtit_ctl.topa:
                 * - 0: this field holds bits 31:7 of the mask value for the single, contiguous physical output region. the size of this
                 * field indicates that regions can be of size 128b up to 4gb. this value (combined with the lower 7 bits, which are
                 * reserved to 1) will be anded with the outputoffset field to determine the next write address. all 1s in this field
                 * should be consecutive and starting at bit 7, otherwise the region will not be contiguous, and an operational error will
                 * be signaled when traceen is set.
                 * - 1: this field holds bits 27:3 of the offset pointer into the current topa table. this value can be added to the
                 * ia32_rtit_output_base value to produce a pointer to the current topa table entry, which itself is a pointer to the
                 * current output region. in this scenario, the lower 7 reserved bits are ignored. this field supports tables up to 256
                 * mbytes in size.
                 *
                 * @see vol3c[35.3.9(operational errors)]
                 */
		uint64 maskortableoffset : 25;
#define ia32_rtit_output_mask_ptrs_mask_or_table_offset_bit 7
#define ia32_rtit_output_mask_ptrs_mask_or_table_offset_flag 0xffffff80
#define ia32_rtit_output_mask_ptrs_mask_or_table_offset_mask 0x1ffffff
#define ia32_rtit_output_mask_ptrs_mask_or_table_offset(_) \
	(((_) >> 7) & 0x1ffffff)

		/**
                 * @brief output offset
                 *
                 * [bits 63:32] the use of this field depends on the value of ia32_rtit_ctl.topa:
                 * - 0: this is bits 31:0 of the offset pointer into the single, contiguous physical output region. this value will be
                 * added to the ia32_rtit_output_base value to form the physical address at which the next byte of packet output data will
                 * be written. this value must be less than or equal to the maskortableoffset field, otherwise an operational error will be
                 * signaled when traceen is set.
                 * - 1: this field holds bits 31:0 of the offset pointer into the current topa output region. this value will be added to
                 * the output region base field, found in the current topa table entry, to form the physical address at which the next byte
                 * of trace output data will be written. this value must be less than the topa entry size, otherwise an operational error
                 * will be signaled when traceen is set.
                 *
                 * @see vol3c[35.3.9(operational errors)]
                 */
		uint64 outputoffset : 32;
#define ia32_rtit_output_mask_ptrs_output_offset_bit 32
#define ia32_rtit_output_mask_ptrs_output_offset_flag 0xffffffff00000000
#define ia32_rtit_output_mask_ptrs_output_offset_mask 0xffffffff
#define ia32_rtit_output_mask_ptrs_output_offset(_) (((_) >> 32) & 0xffffffff)
	};

	uint64 flags;
} ia32_rtit_output_mask_ptrs_register;

/**
 * trace control register.
 *
 * @remarks if (cpuid.(eax=07h, ecx=0):ebx[25] = 1)
 * @see vol3c[35.2.7.2(ia32_rtit_ctl msr)] (reference)
 */
#define ia32_rtit_ctl 0x00000570
typedef union {
	struct {
		/**
                 * @brief traceen
                 *
                 * [bit 0] if 1, enables tracing; else tracing is disabled.
                 * when this bit transitions from 1 to 0, all buffered packets are flushed out of internal buffers. a further store, fence,
                 * or architecturally serializing instruction may be required to ensure that packet data can be observed at the trace
                 * endpoint.
                 * note that the processor will clear this bit on \#smi (section) and warm reset. other msr bits of ia32_rtit_ctl (and
                 * other trace configuration msrs) are not impacted by these events.
                 *
                 * @see vol3c[35.2.7.3(enabling and disabling packet generation with traceen)]
                 */
		uint64 traceenabled : 1;
#define ia32_rtit_ctl_trace_enabled_bit 0
#define ia32_rtit_ctl_trace_enabled_flag 0x01
#define ia32_rtit_ctl_trace_enabled_mask 0x01
#define ia32_rtit_ctl_trace_enabled(_) (((_) >> 0) & 0x01)

		/**
                 * @brief cycen
                 *
                 * [bit 1] - 0: disables cyc packet.
                 * - 1: enables cyc packet.
                 *
                 * @remarks if cpuid.(eax=14h, ecx=0):ebx.cpsb_cam[bit 1] = 0
                 * @see vol3c[35.4.2.14(cycle count (cyc) packet)]
                 */
		uint64 cycenabled : 1;
#define ia32_rtit_ctl_cyc_enabled_bit 1
#define ia32_rtit_ctl_cyc_enabled_flag 0x02
#define ia32_rtit_ctl_cyc_enabled_mask 0x01
#define ia32_rtit_ctl_cyc_enabled(_) (((_) >> 1) & 0x01)

		/**
                 * @brief os
                 *
                 * [bit 2] - 0: packet generation is disabled when cpl = 0.
                 * - 1: packet generation may be enabled when cpl = 0.
                 */
		uint64 os : 1;
#define ia32_rtit_ctl_os_bit 2
#define ia32_rtit_ctl_os_flag 0x04
#define ia32_rtit_ctl_os_mask 0x01
#define ia32_rtit_ctl_os(_) (((_) >> 2) & 0x01)

		/**
                 * @brief user
                 *
                 * [bit 3] - 0: packet generation is disabled when cpl > 0.
                 * - 1: packet generation may be enabled when cpl > 0.
                 */
		uint64 user : 1;
#define ia32_rtit_ctl_user_bit 3
#define ia32_rtit_ctl_user_flag 0x08
#define ia32_rtit_ctl_user_mask 0x01
#define ia32_rtit_ctl_user(_) (((_) >> 3) & 0x01)

		/**
                 * @brief pwrevten
                 *
                 * [bit 4] - 0: power event trace packets are disabled.
                 * - 1: power event trace packets are enabled.
                 *
                 * @see vol3c[35.2.3(power event tracing)]
                 */
		uint64 powereventtraceenabled : 1;
#define ia32_rtit_ctl_power_event_trace_enabled_bit 4
#define ia32_rtit_ctl_power_event_trace_enabled_flag 0x10
#define ia32_rtit_ctl_power_event_trace_enabled_mask 0x01
#define ia32_rtit_ctl_power_event_trace_enabled(_) (((_) >> 4) & 0x01)

		/**
                 * @brief fuponptw
                 *
                 * [bit 5] - 0: ptw packets are not followed by fups.
                 * - 1: ptw packets are followed by fups.
                 */
		uint64 fuponptw : 1;
#define ia32_rtit_ctl_fup_on_ptw_bit 5
#define ia32_rtit_ctl_fup_on_ptw_flag 0x20
#define ia32_rtit_ctl_fup_on_ptw_mask 0x01
#define ia32_rtit_ctl_fup_on_ptw(_) (((_) >> 5) & 0x01)

		/**
                 * @brief fabricen
                 *
                 * [bit 6] - 0: trace output is directed to the memory subsystem, mechanism depends on ia32_rtit_ctl.topa.
                 * - 1: trace output is directed to the trace transport subsystem, ia32_rtit_ctl.topa is ignored.
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=0):ecx[3] = 1) reserved if cpuid.(eax=14h, ecx=0):ecx[bit 3] = 0
                 */
		uint64 fabricenabled : 1;
#define ia32_rtit_ctl_fabric_enabled_bit 6
#define ia32_rtit_ctl_fabric_enabled_flag 0x40
#define ia32_rtit_ctl_fabric_enabled_mask 0x01
#define ia32_rtit_ctl_fabric_enabled(_) (((_) >> 6) & 0x01)

		/**
                 * @brief cr3 filter
                 *
                 * [bit 7] - 0: disables cr3 filtering.
                 * - 1: enables cr3 filtering.
                 */
		uint64 cr3filter : 1;
#define ia32_rtit_ctl_cr3_filter_bit 7
#define ia32_rtit_ctl_cr3_filter_flag 0x80
#define ia32_rtit_ctl_cr3_filter_mask 0x01
#define ia32_rtit_ctl_cr3_filter(_) (((_) >> 7) & 0x01)

		/**
                 * @brief topa
                 *
                 * [bit 8] - 0: single-range output scheme enabled.
                 * - 1: topa output scheme enabled.
                 *
                 * @remarks 0: if cpuid.(eax=14h, ecx=0):ecx.snglrgnout[bit 2] = 1 and ia32_rtit_ctl.fabricen=0 1: if cpuid.(eax=14h,
                 *          ecx=0):ecx.topa[bit 0] = 1, and ia32_rtit_ctl.fabricen=0
                 *          wrmsr to ia32_rtit_ctl that sets traceen but clears this bit and fabricen would cause \#gp: if cpuid.(eax=14h,
                 *          ecx=0):ecx.snglrgnout[bit 2] = 0 wrmsr to ia32_rtit_ctl that sets this bit causes \#gp: if cpuid.(eax=14h,
                 *          ecx=0):ecx.topa[bit 0] = 0
                 * @see vol3c[35.2.6.2(table of physical addresses (topa))]
                 */
		uint64 topa : 1;
#define ia32_rtit_ctl_topa_bit 8
#define ia32_rtit_ctl_topa_flag 0x100
#define ia32_rtit_ctl_topa_mask 0x01
#define ia32_rtit_ctl_topa(_) (((_) >> 8) & 0x01)

		/**
                 * @brief mtcen
                 *
                 * [bit 9] - 0: disables mtc packet.
                 * - 1: enables mtc packet.
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=0):ebx[3] = 1) reserved if cpuid.(eax=14h, ecx=0):ebx.mtc[bit 3] = 0
                 * @see vol3c[35.4.2.16(overflow (ovf) packet)]
                 */
		uint64 mtcenabled : 1;
#define ia32_rtit_ctl_mtc_enabled_bit 9
#define ia32_rtit_ctl_mtc_enabled_flag 0x200
#define ia32_rtit_ctl_mtc_enabled_mask 0x01
#define ia32_rtit_ctl_mtc_enabled(_) (((_) >> 9) & 0x01)

		/**
                 * @brief tscen
                 *
                 * [bit 10] - 0: disable tsc packets.
                 * - 1: enable tsc packets.
                 *
                 * @see vol3c[35.4.2.11(timestamp counter (tsc) packet)]
                 */
		uint64 tscenabled : 1;
#define ia32_rtit_ctl_tsc_enabled_bit 10
#define ia32_rtit_ctl_tsc_enabled_flag 0x400
#define ia32_rtit_ctl_tsc_enabled_mask 0x01
#define ia32_rtit_ctl_tsc_enabled(_) (((_) >> 10) & 0x01)

		/**
                 * @brief disretc
                 *
                 * [bit 11] - 0: enable ret compression.
                 * - 1: disable ret compression.
                 *
                 * @see vol3c[35.2.1.2(indirect transfer cofi)]
                 */
		uint64 retcompressiondisabled : 1;
#define ia32_rtit_ctl_ret_compression_disabled_bit 11
#define ia32_rtit_ctl_ret_compression_disabled_flag 0x800
#define ia32_rtit_ctl_ret_compression_disabled_mask 0x01
#define ia32_rtit_ctl_ret_compression_disabled(_) (((_) >> 11) & 0x01)

		/**
                 * @brief ptwen
                 *
                 * [bit 12] - 0: ptwrite packet generation disabled.
                 * - 1: ptwrite packet generation enabled.
                 */
		uint64 ptwenabled : 1;
#define ia32_rtit_ctl_ptw_enabled_bit 12
#define ia32_rtit_ctl_ptw_enabled_flag 0x1000
#define ia32_rtit_ctl_ptw_enabled_mask 0x01
#define ia32_rtit_ctl_ptw_enabled(_) (((_) >> 12) & 0x01)

		/**
                 * @brief branchen
                 *
                 * [bit 13] - 0: disable cofi-based packets.
                 * - 1: enable cofi-based packets: fup, tip, tip.pge, tip.pgd, tnt, mode.exec, mode.tsx.
                 *
                 * @see vol3c[35.2.5.4(branch enable (branchen))]
                 */
		uint64 branchenabled : 1;
#define ia32_rtit_ctl_branch_enabled_bit 13
#define ia32_rtit_ctl_branch_enabled_flag 0x2000
#define ia32_rtit_ctl_branch_enabled_mask 0x01
#define ia32_rtit_ctl_branch_enabled(_) (((_) >> 13) & 0x01)

		/**
                 * @brief mtcfreq
                 *
                 * [bits 17:14] defines mtc packet frequency, which is based on the core crystal clock, or always running timer (art). mtc
                 * will be sent each time the selected art bit toggles. the following encodings are defined:
                 * 0: art(0), 1: art(1), 2: art(2), 3: art(3), 4: art(4), 5: art(5), 6: art(6), 7: art(7), 8: art(8), 9: art(9), 10:
                 * art(10), 11: art(11), 12: art(12), 13: art(13), 14: art(14), 15: art(15)
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=0):ebx[3] = 1) reserved if cpuid.(eax=14h, ecx=0):ebx.mtc[bit 3] = 0
                 * @see vol3c[35.3.1(detection of intel processor trace and capability enumeration)]
                 */
		uint64 mtcfrequency : 4;
#define ia32_rtit_ctl_mtc_frequency_bit 14
#define ia32_rtit_ctl_mtc_frequency_flag 0x3c000
#define ia32_rtit_ctl_mtc_frequency_mask 0x0f
#define ia32_rtit_ctl_mtc_frequency(_) (((_) >> 14) & 0x0f)
		uint64 reserved1 : 1;

		/**
                 * @brief cycthresh
                 *
                 * [bits 22:19] cyc packet threshold. cyc packets will be sent with the first eligible packet after n cycles have passed
                 * since the last cyc packet. if cycthresh is 0 then n=0, otherwise n is defined as 2(cycthresh-1). the following encodings
                 * are defined:
                 * 0: 0, 1: 1, 2: 2, 3: 4, 4: 8, 5: 16, 6: 32, 7: 64, 8: 128, 9: 256, 10: 512, 11: 1024, 12: 2048, 13: 4096, 14: 8192, 15:
                 * 16384
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=0):ebx[1] = 1) reserved if cpuid.(eax=14h, ecx=0):ebx.cpsb_cam[bit 1] = 0
                 * @see vol3c[35.3.6(cycle-accurate mode)]
                 * @see vol3c[35.3.1(detection of intel processor trace and capability enumeration)]
                 */
		uint64 cycthreshold : 4;
#define ia32_rtit_ctl_cyc_threshold_bit 19
#define ia32_rtit_ctl_cyc_threshold_flag 0x780000
#define ia32_rtit_ctl_cyc_threshold_mask 0x0f
#define ia32_rtit_ctl_cyc_threshold(_) (((_) >> 19) & 0x0f)
		uint64 reserved2 : 1;

		/**
                 * @brief psbfreq
                 *
                 * [bits 27:24] indicates the frequency of psb packets. psb packet frequency is based on the number of intel pt packet
                 * bytes output, so this field allows the user to determine the increment of ia32_ia32_rtit_status.packetbytecnt that
                 * should cause a psb to be generated. note that psb insertion is not precise, but the average output bytes per psb should
                 * approximate the sw selected period. the following encodings are defined:
                 * 0: 2k, 1: 4k, 2: 8k, 3: 16k, 4: 32k, 5: 64k, 6: 128k, 7: 256k, 8: 512k, 9: 1m, 10: 2m, 11: 4m, 12: 8m, 13: 16m, 14: 32m,
                 * 15: 64m
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=0):ebx[1] = 1) reserved if cpuid.(eax=14h, ecx=0):ebx.cpsb_cam[bit 1] = 0
                 * @see vol3c[35.3.1(detection of intel processor trace and capability enumeration)]
                 */
		uint64 psbfrequency : 4;
#define ia32_rtit_ctl_psb_frequency_bit 24
#define ia32_rtit_ctl_psb_frequency_flag 0xf000000
#define ia32_rtit_ctl_psb_frequency_mask 0x0f
#define ia32_rtit_ctl_psb_frequency(_) (((_) >> 24) & 0x0f)
		uint64 reserved3 : 4;

		/**
                 * @brief addr0_cfg
                 *
                 * [bits 35:32] configures the base/limit register pair ia32_rtit_addr0_a/b based on the following encodings:
                 * - 0: addr0 range unused.
                 * - 1: the [ia32_rtit_addr0_a..ia32_rtit_addr0_b] range defines a filteren range. filteren will only be set when the ip is
                 * within this range, though other filteren ranges can additionally be used.
                 * - 2: the [ia32_rtit_addr0_a..ia32_rtit_addr0_b] range defines a tracestop range. tracestop will be asserted if code
                 * branches into this range.
                 * - 3..15: reserved (\#gp).
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=1):eax[2:0] > 0) reserved if cpuid.(eax=14h, ecx=1):ebx.rangecnt[2:0] >= 0
                 * @see vol3c[35.2.4.3(filtering by ip)]
                 * @see vol3c[35.4.2.10(core:bus ratio (cbr) packet)]
                 */
		uint64 addr0cfg : 4;
#define ia32_rtit_ctl_addr0_cfg_bit 32
#define ia32_rtit_ctl_addr0_cfg_flag 0xf00000000
#define ia32_rtit_ctl_addr0_cfg_mask 0x0f
#define ia32_rtit_ctl_addr0_cfg(_) (((_) >> 32) & 0x0f)

		/**
                 * @brief addr1_cfg
                 *
                 * [bits 39:36] configures the base/limit register pair ia32_rtit_addr1_a/b based on the following encodings:
                 * - 0: addr1 range unused.
                 * - 1: the [ia32_rtit_addr1_a..ia32_rtit_addr1_b] range defines a filteren range. filteren will only be set when the ip is
                 * within this range, though other filteren ranges can additionally be used.
                 * - 2: the [ia32_rtit_addr1_a..ia32_rtit_addr1_b] range defines a tracestop range. tracestop will be asserted if code
                 * branches into this range.
                 * - 3..15: reserved (\#gp).
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=1):eax[2:0] > 1) reserved if cpuid.(eax=14h, ecx=1):ebx.rangecnt[2:0] < 2
                 * @see vol3c[35.2.4.3(filtering by ip)]
                 * @see vol3c[35.4.2.10(core:bus ratio (cbr) packet)]
                 */
		uint64 addr1cfg : 4;
#define ia32_rtit_ctl_addr1_cfg_bit 36
#define ia32_rtit_ctl_addr1_cfg_flag 0xf000000000
#define ia32_rtit_ctl_addr1_cfg_mask 0x0f
#define ia32_rtit_ctl_addr1_cfg(_) (((_) >> 36) & 0x0f)

		/**
                 * @brief addr2_cfg
                 *
                 * [bits 43:40] configures the base/limit register pair ia32_rtit_addr2_a/b based on the following encodings:
                 * - 0: addr2 range unused.
                 * - 1: the [ia32_rtit_addr2_a..ia32_rtit_addr2_b] range defines a filteren range. filteren will only be set when the ip is
                 * within this range, though other filteren ranges can additionally be used.
                 * - 2: the [ia32_rtit_addr2_a..ia32_rtit_addr2_b] range defines a tracestop range. tracestop will be asserted if code
                 * branches into this range.
                 * - 3..15: reserved (\#gp).
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=1):eax[2:0] > 2) reserved if cpuid.(eax=14h, ecx=1):ebx.rangecnt[2:0] < 3
                 * @see vol3c[35.2.4.3(filtering by ip)]
                 * @see vol3c[35.4.2.10(core:bus ratio (cbr) packet)]
                 */
		uint64 addr2cfg : 4;
#define ia32_rtit_ctl_addr2_cfg_bit 40
#define ia32_rtit_ctl_addr2_cfg_flag 0xf0000000000
#define ia32_rtit_ctl_addr2_cfg_mask 0x0f
#define ia32_rtit_ctl_addr2_cfg(_) (((_) >> 40) & 0x0f)

		/**
                 * @brief addr3_cfg
                 *
                 * [bits 47:44] configures the base/limit register pair ia32_rtit_addr3_a/b based on the following encodings:
                 * - 0: addr3 range unused.
                 * - 1: the [ia32_rtit_addr3_a..ia32_rtit_addr3_b] range defines a filteren range. filteren will only be set when the ip is
                 * within this range, though other filteren ranges can additionally be used.
                 * - 2: the [ia32_rtit_addr3_a..ia32_rtit_addr3_b] range defines a tracestop range. tracestop will be asserted if code
                 * branches into this range.
                 * - 3..15: reserved (\#gp).
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=1):eax[2:0] > 3) reserved if cpuid.(eax=14h, ecx=1):ebx.rangecnt[2:0] < 4
                 * @see vol3c[35.2.4.3(filtering by ip)]
                 * @see vol3c[35.4.2.10(core:bus ratio (cbr) packet)]
                 */
		uint64 addr3cfg : 4;
#define ia32_rtit_ctl_addr3_cfg_bit 44
#define ia32_rtit_ctl_addr3_cfg_flag 0xf00000000000
#define ia32_rtit_ctl_addr3_cfg_mask 0x0f
#define ia32_rtit_ctl_addr3_cfg(_) (((_) >> 44) & 0x0f)
		uint64 reserved4 : 8;

		/**
                 * @brief injectpsbpmionenable
                 *
                 * [bit 56] - 1: enables use of ia32_rtit_status bits pendpsb[6] and pendtopapmi[7].
                 * - 0: ia32_rtit_status bits 6 and 7 are ignored.
                 *
                 * @remarks reserved if cpuid.(eax=14h, ecx=0):ebx.injectpsbpmi[6] = 0
                 * @see vol3c[35.2.7.4(ia32_rtit_status msr)]
                 */
		uint64 injectpsbpmionenable : 1;
#define ia32_rtit_ctl_inject_psb_pmi_on_enable_bit 56
#define ia32_rtit_ctl_inject_psb_pmi_on_enable_flag 0x100000000000000
#define ia32_rtit_ctl_inject_psb_pmi_on_enable_mask 0x01
#define ia32_rtit_ctl_inject_psb_pmi_on_enable(_) (((_) >> 56) & 0x01)
		uint64 reserved5 : 7;
	};

	uint64 flags;
} ia32_rtit_ctl_register;

/**
 * tracing status register.
 *
 * @remarks if (cpuid.(eax=07h, ecx=0):ebx[25] = 1)
 */
#define ia32_rtit_status 0x00000571
typedef union {
	struct {
		/**
                 * @brief filteren (writes ignored)
                 *
                 * [bit 0] this bit is written by the processor, and indicates that tracing is allowed for the current ip. writes are
                 * ignored.
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=0):ebx[2] = 1)
                 * @see vol3c[35.2.5.5(filter enable (filteren))]
                 */
		uint64 filterenabled : 1;
#define ia32_rtit_status_filter_enabled_bit 0
#define ia32_rtit_status_filter_enabled_flag 0x01
#define ia32_rtit_status_filter_enabled_mask 0x01
#define ia32_rtit_status_filter_enabled(_) (((_) >> 0) & 0x01)

		/**
                 * @brief contexen (writes ignored)
                 *
                 * [bit 1] the processor sets this bit to indicate that tracing is allowed for the current context. writes are ignored.
                 *
                 * @see vol3c[35.2.5.3(context enable (contexten))]
                 */
		uint64 contextenabled : 1;
#define ia32_rtit_status_context_enabled_bit 1
#define ia32_rtit_status_context_enabled_flag 0x02
#define ia32_rtit_status_context_enabled_mask 0x01
#define ia32_rtit_status_context_enabled(_) (((_) >> 1) & 0x01)

		/**
                 * @brief triggeren (writes ignored)
                 *
                 * [bit 2] the processor sets this bit to indicate that tracing is enabled. writes are ignored.
                 *
                 * @see vol3c[35.2.5.2(trigger enable (triggeren))]
                 */
		uint64 triggerenabled : 1;
#define ia32_rtit_status_trigger_enabled_bit 2
#define ia32_rtit_status_trigger_enabled_flag 0x04
#define ia32_rtit_status_trigger_enabled_mask 0x01
#define ia32_rtit_status_trigger_enabled(_) (((_) >> 2) & 0x01)
		uint64 reserved1 : 1;

		/**
                 * @brief error
                 *
                 * [bit 4] the processor sets this bit to indicate that an operational error has been encountered. when this bit is set,
                 * triggeren is cleared to 0 and packet generation is disabled.
                 * when traceen is cleared, software can write this bit. once it is set, only software can clear it. it is not recommended
                 * that software ever set this bit, except in cases where it is restoring a prior saved state.
                 *
                 * @see vol3c[35.2.6.2(table of physical addresses (topa) | topa errors)]
                 */
		uint64 error : 1;
#define ia32_rtit_status_error_bit 4
#define ia32_rtit_status_error_flag 0x10
#define ia32_rtit_status_error_mask 0x01
#define ia32_rtit_status_error(_) (((_) >> 4) & 0x01)

		/**
                 * @brief stopped
                 *
                 * [bit 5] the processor sets this bit to indicate that a topa stop condition has been encountered. when this bit is set,
                 * triggeren is cleared to 0 and packet generation is disabled.
                 * when traceen is cleared, software can write this bit. once it is set, only software can clear it. it is not recommended
                 * that software ever set this bit, except in cases where it is restoring a prior saved state.
                 *
                 * @see vol3c[35.2.6.2(table of physical addresses (topa) | topa stop)]
                 */
		uint64 stopped : 1;
#define ia32_rtit_status_stopped_bit 5
#define ia32_rtit_status_stopped_flag 0x20
#define ia32_rtit_status_stopped_mask 0x01
#define ia32_rtit_status_stopped(_) (((_) >> 5) & 0x01)

		/**
                 * @brief pend psb
                 *
                 * [bit 6] if ia32_rtit_ctl.injectpsbpmionenable[56] = 1, the processor sets this bit when the threshold for a psb+ to be
                 * inserted has been reached. the processor will clear this bit when the psb+ has been inserted into the trace. if pendpsb
                 * = 1 and injectpsbpmionenable = 1 when ia32_rtit_ctl.traceen[0] transitions from 0 to 1, a psb+ will be inserted into the
                 * trace.
                 *
                 * @remarks if cpuid.(eax=14h, ecx=0):ebx.injectpsbpmi[6] = 1
                 */
		uint64 pendpsb : 1;
#define ia32_rtit_status_pend_psb_bit 6
#define ia32_rtit_status_pend_psb_flag 0x40
#define ia32_rtit_status_pend_psb_mask 0x01
#define ia32_rtit_status_pend_psb(_) (((_) >> 6) & 0x01)

		/**
                 * @brief pend topa pmi
                 *
                 * [bit 7] if ia32_rtit_ctl.injectpsbpmionenable[56] = 1, the processor sets this bit when the threshold for a topa pmi to
                 * be inserted has been reached. software should clear this bit once the topa pmi has been handled. if pendtopapmi = 1 and
                 * injectpsbpmionenable = 1 when ia32_rtit_ctl.traceen[0] transitions from 0 to 1, a pmi will be pended.
                 *
                 * @remarks if cpuid.(eax=14h, ecx=0):ebx.injectpsbpmi[6] = 1
                 * @see vol3c[35.2.6.2(table of physical addresses (topa) | topa pmi)]
                 */
		uint64 pendtopapmi : 1;
#define ia32_rtit_status_pend_topa_pmi_bit 7
#define ia32_rtit_status_pend_topa_pmi_flag 0x80
#define ia32_rtit_status_pend_topa_pmi_mask 0x01
#define ia32_rtit_status_pend_topa_pmi(_) (((_) >> 7) & 0x01)
		uint64 reserved2 : 24;

		/**
                 * @brief packetbytecnt
                 *
                 * [bits 48:32] this field is written by the processor, and holds a count of packet bytes that have been sent out. the
                 * processor also uses this field to determine when the next psb packet should be inserted. note that the processor may
                 * clear or modify this field at any time while ia32_rtit_ctl.traceen=1. it will have a stable value when
                 * ia32_rtit_ctl.traceen=0.
                 *
                 * @remarks if (cpuid.(eax=07h, ecx=0):ebx[1] > 3)
                 * @see vol3c[35.4.2.17(packet stream boundary (psb) packet)]
                 */
		uint64 packetbytecount : 17;
#define ia32_rtit_status_packet_byte_count_bit 32
#define ia32_rtit_status_packet_byte_count_flag 0x1ffff00000000
#define ia32_rtit_status_packet_byte_count_mask 0x1ffff
#define ia32_rtit_status_packet_byte_count(_) (((_) >> 32) & 0x1ffff)
		uint64 reserved3 : 15;
	};

	uint64 flags;
} ia32_rtit_status_register;

/**
 * @brief trace filter cr3 match register <b>(r/w)</b>
 *
 * the ia32_rtit_cr3_match register is compared against cr3 when ia32_rtit_ctl.cr3filter is 1. bits 63:5 hold the cr3
 * address value to match, bits 4:0 are reserved to 0.
 *
 * @remarks if (cpuid.(eax=07h, ecx=0):ebx[25] = 1)
 * @see vol3c[35.2.4.2(filtering by cr3)]
 * @see vol3c[35.2.7.6(ia32_rtit_cr3_match msr)] (reference)
 */
#define ia32_rtit_cr3_match 0x00000572
typedef union {
	struct {
		uint64 reserved1 : 5;

		/**
                 * [bits 63:5] cr3[63:5] value to match.
                 */
		uint64 cr3valuetomatch : 59;
#define ia32_rtit_cr3_match_cr3_value_to_match_bit 5
#define ia32_rtit_cr3_match_cr3_value_to_match_flag 0xffffffffffffffe0
#define ia32_rtit_cr3_match_cr3_value_to_match_mask 0x7ffffffffffffff
#define ia32_rtit_cr3_match_cr3_value_to_match(_) \
	(((_) >> 5) & 0x7ffffffffffffff)
	};

	uint64 flags;
} ia32_rtit_cr3_match_register;

/**
 * @defgroup ia32_rtit_addr \
 *           ia32_rtit_addr(x)
 *
 * the role of the ia32_rtit_addrn_a/b register pairs, for each n, is determined by the corresponding addrn_cfg fields in
 * ia32_rtit_ctl. the number of these register pairs is enumerated by cpuid.(eax=14h, ecx=1):eax.rangecnt[2:0].
 *
 * @remarks if (cpuid.(eax=07h, ecx=1):eax[2:0] > n)
 * @see vol3c[35.2.7.2(ia32_rtit_ctl msr)]
 * @see vol3c[35.2.7.5(ia32_rtit_addrn_a and ia32_rtit_addrn_b msrs)] (reference)
 * @{
 */
/**
 * @defgroup ia32_rtit_addr_a \
 *           ia32_rtit_addr(n)_a
 *
 * region n start address.
 *
 * @remarks if (cpuid.(eax=07h, ecx=1):eax[2:0] > n)
 * @{
 */
#define ia32_rtit_addr0_a 0x00000580
#define ia32_rtit_addr1_a 0x00000582
#define ia32_rtit_addr2_a 0x00000584
#define ia32_rtit_addr3_a 0x00000586
/**
 * @}
 */

/**
 * @defgroup ia32_rtit_addr_b \
 *           ia32_rtit_addr(n)_b
 *
 * region n end address.
 *
 * @remarks if (cpuid.(eax=07h, ecx=1):eax[2:0] > n)
 * @{
 */
#define ia32_rtit_addr0_b 0x00000581
#define ia32_rtit_addr1_b 0x00000583
#define ia32_rtit_addr2_b 0x00000585
#define ia32_rtit_addr3_b 0x00000587
/**
 * @}
 */

typedef union {
	struct {
		/**
                 * [bits 47:0] virtual address.
                 */
		uint64 virtualaddress : 48;
#define ia32_rtit_addr_virtual_address_bit 0
#define ia32_rtit_addr_virtual_address_flag 0xffffffffffff
#define ia32_rtit_addr_virtual_address_mask 0xffffffffffff
#define ia32_rtit_addr_virtual_address(_) (((_) >> 0) & 0xffffffffffff)

		/**
                 * [bits 63:48] signext_va.
                 */
		uint64 signextva : 16;
#define ia32_rtit_addr_sign_ext_va_bit 48
#define ia32_rtit_addr_sign_ext_va_flag 0xffff000000000000
#define ia32_rtit_addr_sign_ext_va_mask 0xffff
#define ia32_rtit_addr_sign_ext_va(_) (((_) >> 48) & 0xffff)
	};

	uint64 flags;
} ia32_rtit_addr_register;

/**
 * @}
 */

/**
 * ds save area. points to the linear address of the first byte of the ds buffer management area, which is used to manage
 * the bts and pebs buffers.
 * returns:
 * - [63:0] the linear address of the first byte of the ds buffer management area, if ia-32e mode is active.
 * - [31:0] the linear address of the first byte of the ds buffer management area, if not in ia-32e mode.
 * - [63:32] reserved if not in ia-32e mode.
 *
 * @remarks if cpuid.01h:edx.ds[21] = 1
 * @see vol3b[18.6.3.4(debug store (ds) mechanism)]
 */
#define ia32_ds_area 0x00000600

/**
 * tsc target of local apic's tsc deadline mode.
 *
 * @remarks if cpuid.01h:ecx.[24] = 1
 */
#define ia32_tsc_deadline 0x000006e0

/**
 * enable/disable hwp.
 *
 * @remarks if cpuid.06h:eax.[7] = 1
 */
#define ia32_pm_enable 0x00000770
typedef union {
	struct {
		/**
                 * [bit 0] hwp_enable.
                 *
                 * @remarks if cpuid.06h:eax.[7] = 1
                 * @see vol3b[14.4.2(enabling hwp)]
                 */
		uint64 hwpenable : 1;
#define ia32_pm_enable_hwp_enable_bit 0
#define ia32_pm_enable_hwp_enable_flag 0x01
#define ia32_pm_enable_hwp_enable_mask 0x01
#define ia32_pm_enable_hwp_enable(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 63;
	};

	uint64 flags;
} ia32_pm_enable_register;

/**
 * hwp performance range enumeration.
 *
 * @remarks if cpuid.06h:eax.[7] = 1
 */
#define ia32_hwp_capabilities 0x00000771
typedef union {
	struct {
		/**
                 * [bits 7:0] highest_performance.
                 *
                 * @remarks if cpuid.06h:eax.[7] = 1
                 * @see vol3b[14.4.3(hwp performance range and dynamic capabilities)]
                 */
		uint64 highestperformance : 8;
#define ia32_hwp_capabilities_highest_performance_bit 0
#define ia32_hwp_capabilities_highest_performance_flag 0xff
#define ia32_hwp_capabilities_highest_performance_mask 0xff
#define ia32_hwp_capabilities_highest_performance(_) (((_) >> 0) & 0xff)

		/**
                 * [bits 15:8] guaranteed_performance.
                 *
                 * @remarks if cpuid.06h:eax.[7] = 1
                 * @see vol3b[14.4.3(hwp performance range and dynamic capabilities)]
                 */
		uint64 guaranteedperformance : 8;
#define ia32_hwp_capabilities_guaranteed_performance_bit 8
#define ia32_hwp_capabilities_guaranteed_performance_flag 0xff00
#define ia32_hwp_capabilities_guaranteed_performance_mask 0xff
#define ia32_hwp_capabilities_guaranteed_performance(_) (((_) >> 8) & 0xff)

		/**
                 * [bits 23:16] most_efficient_performance.
                 *
                 * @remarks if cpuid.06h:eax.[7] = 1
                 * @see vol3b[14.4.3(hwp performance range and dynamic capabilities)]
                 */
		uint64 mostefficientperformance : 8;
#define ia32_hwp_capabilities_most_efficient_performance_bit 16
#define ia32_hwp_capabilities_most_efficient_performance_flag 0xff0000
#define ia32_hwp_capabilities_most_efficient_performance_mask 0xff
#define ia32_hwp_capabilities_most_efficient_performance(_) (((_) >> 16) & 0xff)

		/**
                 * [bits 31:24] lowest_performance.
                 *
                 * @remarks if cpuid.06h:eax.[7] = 1
                 * @see vol3b[14.4.3(hwp performance range and dynamic capabilities)]
                 */
		uint64 lowestperformance : 8;
#define ia32_hwp_capabilities_lowest_performance_bit 24
#define ia32_hwp_capabilities_lowest_performance_flag 0xff000000
#define ia32_hwp_capabilities_lowest_performance_mask 0xff
#define ia32_hwp_capabilities_lowest_performance(_) (((_) >> 24) & 0xff)
		uint64 reserved1 : 32;
	};

	uint64 flags;
} ia32_hwp_capabilities_register;

/**
 * power management control hints for all logical processors in a package.
 *
 * @remarks if cpuid.06h:eax.[11] = 1
 */
#define ia32_hwp_request_pkg 0x00000772
typedef union {
	struct {
		/**
                 * [bits 7:0] minimum_performance.
                 *
                 * @remarks if cpuid.06h:eax.[11] = 1
                 * @see vol3b[14.4.4(managing hwp)]
                 */
		uint64 minimumperformance : 8;
#define ia32_hwp_request_pkg_minimum_performance_bit 0
#define ia32_hwp_request_pkg_minimum_performance_flag 0xff
#define ia32_hwp_request_pkg_minimum_performance_mask 0xff
#define ia32_hwp_request_pkg_minimum_performance(_) (((_) >> 0) & 0xff)

		/**
                 * [bits 15:8] maximum_performance.
                 *
                 * @remarks if cpuid.06h:eax.[11] = 1
                 * @see vol3b[14.4.4(managing hwp)]
                 */
		uint64 maximumperformance : 8;
#define ia32_hwp_request_pkg_maximum_performance_bit 8
#define ia32_hwp_request_pkg_maximum_performance_flag 0xff00
#define ia32_hwp_request_pkg_maximum_performance_mask 0xff
#define ia32_hwp_request_pkg_maximum_performance(_) (((_) >> 8) & 0xff)

		/**
                 * [bits 23:16] desired_performance.
                 *
                 * @remarks if cpuid.06h:eax.[11] = 1
                 * @see vol3b[14.4.4(managing hwp)]
                 */
		uint64 desiredperformance : 8;
#define ia32_hwp_request_pkg_desired_performance_bit 16
#define ia32_hwp_request_pkg_desired_performance_flag 0xff0000
#define ia32_hwp_request_pkg_desired_performance_mask 0xff
#define ia32_hwp_request_pkg_desired_performance(_) (((_) >> 16) & 0xff)

		/**
                 * [bits 31:24] energy_performance_preference.
                 *
                 * @remarks if cpuid.06h:eax.[11] = 1 && cpuid.06h:eax.[10] = 1
                 * @see vol3b[14.4.4(managing hwp)]
                 */
		uint64 energyperformancepreference : 8;
#define ia32_hwp_request_pkg_energy_performance_preference_bit 24
#define ia32_hwp_request_pkg_energy_performance_preference_flag 0xff000000
#define ia32_hwp_request_pkg_energy_performance_preference_mask 0xff
#define ia32_hwp_request_pkg_energy_performance_preference(_) \
	(((_) >> 24) & 0xff)

		/**
                 * [bits 41:32] activity_window.
                 *
                 * @remarks if cpuid.06h:eax.[11] = 1 && cpuid.06h:eax.[9] = 1
                 * @see vol3b[14.4.4(managing hwp)]
                 */
		uint64 activitywindow : 10;
#define ia32_hwp_request_pkg_activity_window_bit 32
#define ia32_hwp_request_pkg_activity_window_flag 0x3ff00000000
#define ia32_hwp_request_pkg_activity_window_mask 0x3ff
#define ia32_hwp_request_pkg_activity_window(_) (((_) >> 32) & 0x3ff)
		uint64 reserved1 : 22;
	};

	uint64 flags;
} ia32_hwp_request_pkg_register;

/**
 * control hwp native interrupts.
 *
 * @remarks if cpuid.06h:eax.[8] = 1
 */
#define ia32_hwp_interrupt 0x00000773
typedef union {
	struct {
		/**
                 * [bit 0] en_guaranteed_performance_change.
                 *
                 * @remarks if cpuid.06h:eax.[8] = 1
                 * @see vol3b[14.4.6(hwp notifications)]
                 */
		uint64 enguaranteedperformancechange : 1;
#define ia32_hwp_interrupt_en_guaranteed_performance_change_bit 0
#define ia32_hwp_interrupt_en_guaranteed_performance_change_flag 0x01
#define ia32_hwp_interrupt_en_guaranteed_performance_change_mask 0x01
#define ia32_hwp_interrupt_en_guaranteed_performance_change(_) \
	(((_) >> 0) & 0x01)

		/**
                 * [bit 1] en_excursion_minimum.
                 *
                 * @remarks if cpuid.06h:eax.[8] = 1
                 * @see vol3b[14.4.6(hwp notifications)]
                 */
		uint64 enexcursionminimum : 1;
#define ia32_hwp_interrupt_en_excursion_minimum_bit 1
#define ia32_hwp_interrupt_en_excursion_minimum_flag 0x02
#define ia32_hwp_interrupt_en_excursion_minimum_mask 0x01
#define ia32_hwp_interrupt_en_excursion_minimum(_) (((_) >> 1) & 0x01)
		uint64 reserved1 : 62;
	};

	uint64 flags;
} ia32_hwp_interrupt_register;

/**
 * power management control hints to a logical processor.
 *
 * @remarks if cpuid.06h:eax.[7] = 1
 */
#define ia32_hwp_request 0x00000774
typedef union {
	struct {
		/**
                 * [bits 7:0] minimum_performance.
                 *
                 * @remarks if cpuid.06h:eax.[7] = 1
                 * @see vol3b[14.4.4(managing hwp)]
                 */
		uint64 minimumperformance : 8;
#define ia32_hwp_request_minimum_performance_bit 0
#define ia32_hwp_request_minimum_performance_flag 0xff
#define ia32_hwp_request_minimum_performance_mask 0xff
#define ia32_hwp_request_minimum_performance(_) (((_) >> 0) & 0xff)

		/**
                 * [bits 15:8] maximum_performance.
                 *
                 * @remarks if cpuid.06h:eax.[7] = 1
                 * @see vol3b[14.4.4(managing hwp)]
                 */
		uint64 maximumperformance : 8;
#define ia32_hwp_request_maximum_performance_bit 8
#define ia32_hwp_request_maximum_performance_flag 0xff00
#define ia32_hwp_request_maximum_performance_mask 0xff
#define ia32_hwp_request_maximum_performance(_) (((_) >> 8) & 0xff)

		/**
                 * [bits 23:16] desired_performance.
                 *
                 * @remarks if cpuid.06h:eax.[7] = 1
                 * @see vol3b[14.4.4(managing hwp)]
                 */
		uint64 desiredperformance : 8;
#define ia32_hwp_request_desired_performance_bit 16
#define ia32_hwp_request_desired_performance_flag 0xff0000
#define ia32_hwp_request_desired_performance_mask 0xff
#define ia32_hwp_request_desired_performance(_) (((_) >> 16) & 0xff)

		/**
                 * [bits 31:24] energy_performance_preference.
                 *
                 * @remarks if cpuid.06h:eax.[7] = 1 && cpuid.06h:eax.[10] = 1
                 * @see vol3b[14.4.4(managing hwp)]
                 */
		uint64 energyperformancepreference : 8;
#define ia32_hwp_request_energy_performance_preference_bit 24
#define ia32_hwp_request_energy_performance_preference_flag 0xff000000
#define ia32_hwp_request_energy_performance_preference_mask 0xff
#define ia32_hwp_request_energy_performance_preference(_) (((_) >> 24) & 0xff)

		/**
                 * [bits 41:32] activity_window.
                 *
                 * @remarks if cpuid.06h:eax.[7] = 1 && cpuid.06h:eax.[9] = 1
                 * @see vol3b[14.4.4(managing hwp)]
                 */
		uint64 activitywindow : 10;
#define ia32_hwp_request_activity_window_bit 32
#define ia32_hwp_request_activity_window_flag 0x3ff00000000
#define ia32_hwp_request_activity_window_mask 0x3ff
#define ia32_hwp_request_activity_window(_) (((_) >> 32) & 0x3ff)

		/**
                 * [bit 42] package_control.
                 *
                 * @remarks if cpuid.06h:eax.[7] = 1 && cpuid.06h:eax.[11] = 1
                 * @see vol3b[14.4.4(managing hwp)]
                 */
		uint64 packagecontrol : 1;
#define ia32_hwp_request_package_control_bit 42
#define ia32_hwp_request_package_control_flag 0x40000000000
#define ia32_hwp_request_package_control_mask 0x01
#define ia32_hwp_request_package_control(_) (((_) >> 42) & 0x01)
		uint64 reserved1 : 21;
	};

	uint64 flags;
} ia32_hwp_request_register;

/**
 * log bits indicating changes to guaranteed & excursions to minimum.
 *
 * @remarks if cpuid.06h:eax.[7] = 1
 */
#define ia32_hwp_status 0x00000777
typedef union {
	struct {
		/**
                 * [bit 0] guaranteed_performance_change.
                 *
                 * @remarks if cpuid.06h:eax.[7] = 1
                 * @see vol3b[14.4.5(hwp feedback)]
                 */
		uint64 guaranteedperformancechange : 1;
#define ia32_hwp_status_guaranteed_performance_change_bit 0
#define ia32_hwp_status_guaranteed_performance_change_flag 0x01
#define ia32_hwp_status_guaranteed_performance_change_mask 0x01
#define ia32_hwp_status_guaranteed_performance_change(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 1;

		/**
                 * [bit 2] excursion_to_minimum.
                 *
                 * @remarks if cpuid.06h:eax.[7] = 1
                 * @see vol3b[14.4.5(hwp feedback)]
                 */
		uint64 excursiontominimum : 1;
#define ia32_hwp_status_excursion_to_minimum_bit 2
#define ia32_hwp_status_excursion_to_minimum_flag 0x04
#define ia32_hwp_status_excursion_to_minimum_mask 0x01
#define ia32_hwp_status_excursion_to_minimum(_) (((_) >> 2) & 0x01)
		uint64 reserved2 : 61;
	};

	uint64 flags;
} ia32_hwp_status_register;

/**
 * x2apic id register.
 *
 * @remarks if cpuid.01h:ecx[21] = 1 && ia32_apic_base.[10] = 1
 * @see vol3a[10.12(extended xapic (x2apic))]
 */
#define ia32_x2apic_apicid 0x00000802

/**
 * x2apic version register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_version 0x00000803

/**
 * x2apic task priority register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_tpr 0x00000808

/**
 * x2apic processor priority register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_ppr 0x0000080a

/**
 * x2apic eoi register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_eoi 0x0000080b

/**
 * x2apic logical destination register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_ldr 0x0000080d

/**
 * x2apic spurious interrupt list register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_sivr 0x0000080f
/**
 * @defgroup ia32_x2apic_isr \
 *           ia32_x2apic_isr(n)
 *
 * x2apic in-service register bits (n * 32 + 31):(n * 32).
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 * @{
 */
#define ia32_x2apic_isr0 0x00000810
#define ia32_x2apic_isr1 0x00000811
#define ia32_x2apic_isr2 0x00000812
#define ia32_x2apic_isr3 0x00000813
#define ia32_x2apic_isr4 0x00000814
#define ia32_x2apic_isr5 0x00000815
#define ia32_x2apic_isr6 0x00000816
#define ia32_x2apic_isr7 0x00000817
/**
 * @}
 */

/**
 * @defgroup ia32_x2apic_tmr \
 *           ia32_x2apic_tmr(n)
 *
 * x2apic trigger mode register bits (n * 32 + 31):(n * 32).
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 * @{
 */
#define ia32_x2apic_tmr0 0x00000818
#define ia32_x2apic_tmr1 0x00000819
#define ia32_x2apic_tmr2 0x0000081a
#define ia32_x2apic_tmr3 0x0000081b
#define ia32_x2apic_tmr4 0x0000081c
#define ia32_x2apic_tmr5 0x0000081d
#define ia32_x2apic_tmr6 0x0000081e
#define ia32_x2apic_tmr7 0x0000081f
/**
 * @}
 */

/**
 * @defgroup ia32_x2apic_irr \
 *           ia32_x2apic_irr(n)
 *
 * x2apic interrupt request register bits (n * 32 + 31):(n * 32).
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 * @{
 */
#define ia32_x2apic_irr0 0x00000820
#define ia32_x2apic_irr1 0x00000821
#define ia32_x2apic_irr2 0x00000822
#define ia32_x2apic_irr3 0x00000823
#define ia32_x2apic_irr4 0x00000824
#define ia32_x2apic_irr5 0x00000825
#define ia32_x2apic_irr6 0x00000826
#define ia32_x2apic_irr7 0x00000827
/**
 * @}
 */

/**
 * x2apic error status register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_esr 0x00000828

/**
 * x2apic lvt corrected machine check interrupt register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_lvt_cmci 0x0000082f

/**
 * x2apic interrupt command register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_icr 0x00000830

/**
 * x2apic lvt timer interrupt register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_lvt_timer 0x00000832

/**
 * x2apic lvt thermal sensor interrupt register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_lvt_thermal 0x00000833

/**
 * x2apic lvt performance monitor interrupt register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_lvt_pmi 0x00000834

/**
 * x2apic lvt lint0 register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_lvt_lint0 0x00000835

/**
 * x2apic lvt lint1 register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_lvt_lint1 0x00000836

/**
 * x2apic lvt error register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_lvt_error 0x00000837

/**
 * x2apic initial count register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_init_count 0x00000838

/**
 * x2apic current count register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_cur_count 0x00000839

/**
 * x2apic divide configuration register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_div_conf 0x0000083e

/**
 * x2apic self ipi register.
 *
 * @remarks if cpuid.01h:ecx.[21] = 1 && ia32_apic_base.[10] = 1
 */
#define ia32_x2apic_self_ipi 0x0000083f

/**
 * silicon debug feature control.
 *
 * @remarks if cpuid.01h:ecx.[11] = 1
 */
#define ia32_debug_interface 0x00000c80
typedef union {
	struct {
		/**
                 * @brief enable <b>(r/w)</b>
                 *
                 * [bit 0] bios set 1 to enable silicon debug features. default is 0.
                 *
                 * @remarks if cpuid.01h:ecx.[11] = 1
                 */
		uint64 enable : 1;
#define ia32_debug_interface_enable_bit 0
#define ia32_debug_interface_enable_flag 0x01
#define ia32_debug_interface_enable_mask 0x01
#define ia32_debug_interface_enable(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 29;

		/**
                 * @brief lock <b>(r/w)</b>
                 *
                 * [bit 30] if 1, locks any further change to the msr. the lock bit is set automatically on the first smi assertion even if
                 * not explicitly set by bios. default is 0.
                 *
                 * @remarks if cpuid.01h:ecx.[11] = 1
                 */
		uint64 lock : 1;
#define ia32_debug_interface_lock_bit 30
#define ia32_debug_interface_lock_flag 0x40000000
#define ia32_debug_interface_lock_mask 0x01
#define ia32_debug_interface_lock(_) (((_) >> 30) & 0x01)

		/**
                 * @brief debug occurred <b>(r/o)</b>
                 *
                 * [bit 31] this "sticky bit" is set by hardware to indicate the status of bit 0. default is 0.
                 *
                 * @remarks if cpuid.01h:ecx.[11] = 1
                 */
		uint64 debugoccurred : 1;
#define ia32_debug_interface_debug_occurred_bit 31
#define ia32_debug_interface_debug_occurred_flag 0x80000000
#define ia32_debug_interface_debug_occurred_mask 0x01
#define ia32_debug_interface_debug_occurred(_) (((_) >> 31) & 0x01)
		uint64 reserved2 : 32;
	};

	uint64 flags;
} ia32_debug_interface_register;

/**
 * l3 qos configuration.
 *
 * @remarks if ( cpuid.(eax=10h, ecx=1):ecx.[2] = 1 )
 */
#define ia32_l3_qos_cfg 0x00000c81
typedef union {
	struct {
		/**
                 * @brief enable <b>(r/w)</b>
                 *
                 * [bit 0] set 1 to enable l3 cat masks and cos to operate in code and data prioritization (cdp) mode.
                 */
		uint64 enable : 1;
#define ia32_l3_qos_cfg_enable_bit 0
#define ia32_l3_qos_cfg_enable_flag 0x01
#define ia32_l3_qos_cfg_enable_mask 0x01
#define ia32_l3_qos_cfg_enable(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 63;
	};

	uint64 flags;
} ia32_l3_qos_cfg_register;

/**
 * l2 qos configuration.
 *
 * @remarks if ( cpuid.(eax=10h, ecx=2):ecx.[2] = 1 )
 */
#define ia32_l2_qos_cfg 0x00000c82
typedef union {
	struct {
		/**
                 * @brief enable <b>(r/w)</b>
                 *
                 * [bit 0] set 1 to enable l2 cat masks and cos to operate in code and data prioritization (cdp) mode.
                 */
		uint64 enable : 1;
#define ia32_l2_qos_cfg_enable_bit 0
#define ia32_l2_qos_cfg_enable_flag 0x01
#define ia32_l2_qos_cfg_enable_mask 0x01
#define ia32_l2_qos_cfg_enable(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 63;
	};

	uint64 flags;
} ia32_l2_qos_cfg_register;

/**
 * monitoring event select register.
 *
 * @remarks if ( cpuid.(eax=07h, ecx=0):ebx.[12] = 1 )
 */
#define ia32_qm_evtsel 0x00000c8d
typedef union {
	struct {
		/**
                 * @brief event id
                 *
                 * [bits 7:0] id of a supported monitoring event to report via ia32_qm_ctr.
                 */
		uint64 eventid : 8;
#define ia32_qm_evtsel_event_id_bit 0
#define ia32_qm_evtsel_event_id_flag 0xff
#define ia32_qm_evtsel_event_id_mask 0xff
#define ia32_qm_evtsel_event_id(_) (((_) >> 0) & 0xff)
		uint64 reserved1 : 24;

		/**
                 * @brief resource monitoring id
                 *
                 * [bits 63:32] id for monitoring hardware to report monitored data via ia32_qm_ctr.
                 *
                 * @remarks bits [n+31:32] n = ceil (log2 (cpuid.(eax= 0fh,ecx=0h).ebx[31:0] + 1))
                 */
		uint64 resourcemonitoringid : 32;
#define ia32_qm_evtsel_resource_monitoring_id_bit 32
#define ia32_qm_evtsel_resource_monitoring_id_flag 0xffffffff00000000
#define ia32_qm_evtsel_resource_monitoring_id_mask 0xffffffff
#define ia32_qm_evtsel_resource_monitoring_id(_) (((_) >> 32) & 0xffffffff)
	};

	uint64 flags;
} ia32_qm_evtsel_register;

/**
 * monitoring counter register.
 *
 * @remarks if ( cpuid.(eax=07h, ecx=0):ebx.[12] = 1 )
 */
#define ia32_qm_ctr 0x00000c8e
typedef union {
	struct {
		/**
                 * [bits 61:0] resource monitored data.
                 */
		uint64 resourcemonitoreddata : 62;
#define ia32_qm_ctr_resource_monitored_data_bit 0
#define ia32_qm_ctr_resource_monitored_data_flag 0x3fffffffffffffff
#define ia32_qm_ctr_resource_monitored_data_mask 0x3fffffffffffffff
#define ia32_qm_ctr_resource_monitored_data(_) (((_) >> 0) & 0x3fffffffffffffff)

		/**
                 * @brief unavailable
                 *
                 * [bit 62] if 1, indicates data for this rmid is not available or not monitored for this resource or rmid.
                 */
		uint64 unavailable : 1;
#define ia32_qm_ctr_unavailable_bit 62
#define ia32_qm_ctr_unavailable_flag 0x4000000000000000
#define ia32_qm_ctr_unavailable_mask 0x01
#define ia32_qm_ctr_unavailable(_) (((_) >> 62) & 0x01)

		/**
                 * @brief error
                 *
                 * [bit 63] if 1, indicates an unsupported rmid or event type was written to ia32_pqr_qm_evtsel.
                 */
		uint64 error : 1;
#define ia32_qm_ctr_error_bit 63
#define ia32_qm_ctr_error_flag 0x8000000000000000
#define ia32_qm_ctr_error_mask 0x01
#define ia32_qm_ctr_error(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} ia32_qm_ctr_register;

/**
 * resource association register.
 *
 * @remarks if ( (cpuid.(eax=07h, ecx=0):ebx[12] = 1) or (cpuid.(eax=07h, ecx=0):ebx[15] = 1 ) )
 */
#define ia32_pqr_assoc 0x00000c8f
typedef union {
	struct {
		/**
                 * @brief resource monitoring id <b>(r/w)</b>
                 *
                 * [bits 31:0] id for monitoring hardware to track internal operation, e.g., memory access.
                 *
                 * @remarks bits [n-1:0] n = ceil (log2 (cpuid.(eax= 0fh, ecx=0h).ebx[31:0] +1)) 31:n reserved
                 */
		uint64 resourcemonitoringid : 32;
#define ia32_pqr_assoc_resource_monitoring_id_bit 0
#define ia32_pqr_assoc_resource_monitoring_id_flag 0xffffffff
#define ia32_pqr_assoc_resource_monitoring_id_mask 0xffffffff
#define ia32_pqr_assoc_resource_monitoring_id(_) (((_) >> 0) & 0xffffffff)

		/**
                 * @brief cos <b>(r/w)</b>
                 *
                 * [bits 63:32] the class of service (cos) to enforce (on writes); returns the current cos when read.
                 *
                 * @remarks if ( cpuid.(eax=07h, ecx=0):ebx.[15] = 1 )
                 */
		uint64 cos : 32;
#define ia32_pqr_assoc_cos_bit 32
#define ia32_pqr_assoc_cos_flag 0xffffffff00000000
#define ia32_pqr_assoc_cos_mask 0xffffffff
#define ia32_pqr_assoc_cos(_) (((_) >> 32) & 0xffffffff)
	};

	uint64 flags;
} ia32_pqr_assoc_register;

/**
 * supervisor state of mpx configuration.
 *
 * @remarks if (cpuid.(eax=07h, ecx=0h):ebx[14] = 1)
 */
#define ia32_bndcfgs 0x00000d90
typedef union {
	struct {
		/**
                 * [bit 0] enable intel mpx in supervisor mode.
                 */
		uint64 enable : 1;
#define ia32_bndcfgs_enable_bit 0
#define ia32_bndcfgs_enable_flag 0x01
#define ia32_bndcfgs_enable_mask 0x01
#define ia32_bndcfgs_enable(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] preserve the bounds registers for near branch instructions in the absence of the bnd prefix.
                 */
		uint64 bndpreserve : 1;
#define ia32_bndcfgs_bnd_preserve_bit 1
#define ia32_bndcfgs_bnd_preserve_flag 0x02
#define ia32_bndcfgs_bnd_preserve_mask 0x01
#define ia32_bndcfgs_bnd_preserve(_) (((_) >> 1) & 0x01)
		uint64 reserved1 : 10;

		/**
                 * [bits 63:12] base address of bound directory.
                 */
		uint64 bounddirectorybaseaddress : 52;
#define ia32_bndcfgs_bound_directory_base_address_bit 12
#define ia32_bndcfgs_bound_directory_base_address_flag 0xfffffffffffff000
#define ia32_bndcfgs_bound_directory_base_address_mask 0xfffffffffffff
#define ia32_bndcfgs_bound_directory_base_address(_) \
	(((_) >> 12) & 0xfffffffffffff)
	};

	uint64 flags;
} ia32_bndcfgs_register;

/**
 * extended supervisor state mask.
 *
 * @remarks if ( cpuid.(0dh, 1):eax.[3] = 1
 */
#define ia32_xss 0x00000da0
typedef union {
	struct {
		uint64 reserved1 : 8;

		/**
                 * [bit 8] trace packet configuration state.
                 */
		uint64 tracepacketconfigurationstate : 1;
#define ia32_xss_trace_packet_configuration_state_bit 8
#define ia32_xss_trace_packet_configuration_state_flag 0x100
#define ia32_xss_trace_packet_configuration_state_mask 0x01
#define ia32_xss_trace_packet_configuration_state(_) (((_) >> 8) & 0x01)
		uint64 reserved2 : 55;
	};

	uint64 flags;
} ia32_xss_register;

/**
 * package level enable/disable hdc.
 *
 * @remarks if cpuid.06h:eax.[13] = 1
 */
#define ia32_pkg_hdc_ctl 0x00000db0
typedef union {
	struct {
		/**
                 * @brief hdc_pkg_enable <b>(r/w)</b>
                 *
                 * [bit 0] force hdc idling or wake up hdc-idled logical processors in the package.
                 *
                 * @remarks if cpuid.06h:eax.[13] = 1
                 * @see vol3b[14.5.2(package level enabling hdc)]
                 */
		uint64 hdcpkgenable : 1;
#define ia32_pkg_hdc_ctl_hdc_pkg_enable_bit 0
#define ia32_pkg_hdc_ctl_hdc_pkg_enable_flag 0x01
#define ia32_pkg_hdc_ctl_hdc_pkg_enable_mask 0x01
#define ia32_pkg_hdc_ctl_hdc_pkg_enable(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 63;
	};

	uint64 flags;
} ia32_pkg_hdc_ctl_register;

/**
 * enable/disable hwp.
 *
 * @remarks if cpuid.06h:eax.[13] = 1
 */
#define ia32_pm_ctl1 0x00000db1
typedef union {
	struct {
		/**
                 * @brief hdc_allow_block <b>(r/w)</b>
                 *
                 * [bit 0] allow/block this logical processor for package level hdc control.
                 *
                 * @remarks if cpuid.06h:eax.[13] = 1
                 * @see vol3b[14.5.3(logical-processor level hdc control)]
                 */
		uint64 hdcallowblock : 1;
#define ia32_pm_ctl1_hdc_allow_block_bit 0
#define ia32_pm_ctl1_hdc_allow_block_flag 0x01
#define ia32_pm_ctl1_hdc_allow_block_mask 0x01
#define ia32_pm_ctl1_hdc_allow_block(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 63;
	};

	uint64 flags;
} ia32_pm_ctl1_register;

/**
 * per-logical_processor hdc idle residency.
 *
 * @remarks if cpuid.06h:eax.[13] = 1
 */
#define ia32_thread_stall 0x00000db2
typedef struct {
	/**
         * @brief stall_cycle_cnt <b>(r/w)</b>
         *
         * stalled cycles due to hdc forced idle on this logical processor.
         *
         * @remarks if cpuid.06h:eax.[13] = 1
         * @see vol3b[14.5.4.1(ia32_thread_stall)]
         */
	uint64 stallcyclecount;
} ia32_thread_stall_register;

/**
 * extended feature enables.
 *
 * @remarks if cpuid.06h:eax.[13] = 1
 */
#define ia32_efer 0xc0000080
typedef union {
	struct {
		/**
                 * @brief syscall enable <b>(r/w)</b>
                 *
                 * [bit 0] enables syscall/sysret instructions in 64-bit mode.
                 */
		uint64 syscallenable : 1;
#define ia32_efer_syscall_enable_bit 0
#define ia32_efer_syscall_enable_flag 0x01
#define ia32_efer_syscall_enable_mask 0x01
#define ia32_efer_syscall_enable(_) (((_) >> 0) & 0x01)
		uint64 reserved1 : 7;

		/**
                 * @brief ia-32e mode enable <b>(r/w)</b>
                 *
                 * [bit 8] enables ia-32e mode operation.
                 */
		uint64 ia32emodeenable : 1;
#define ia32_efer_ia32e_mode_enable_bit 8
#define ia32_efer_ia32e_mode_enable_flag 0x100
#define ia32_efer_ia32e_mode_enable_mask 0x01
#define ia32_efer_ia32e_mode_enable(_) (((_) >> 8) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * @brief ia-32e mode active <b>(r)</b>
                 *
                 * [bit 10] indicates ia-32e mode is active when set.
                 */
		uint64 ia32emodeactive : 1;
#define ia32_efer_ia32e_mode_active_bit 10
#define ia32_efer_ia32e_mode_active_flag 0x400
#define ia32_efer_ia32e_mode_active_mask 0x01
#define ia32_efer_ia32e_mode_active(_) (((_) >> 10) & 0x01)

		/**
                 * [bit 11] execute disable bit enable.
                 */
		uint64 executedisablebitenable : 1;
#define ia32_efer_execute_disable_bit_enable_bit 11
#define ia32_efer_execute_disable_bit_enable_flag 0x800
#define ia32_efer_execute_disable_bit_enable_mask 0x01
#define ia32_efer_execute_disable_bit_enable(_) (((_) >> 11) & 0x01)
		uint64 reserved3 : 52;
	};

	uint64 flags;
} ia32_efer_register;

/**
 * system call target address.
 *
 * @remarks if cpuid.80000001:edx.[29] = 1
 */
#define ia32_star 0xc0000081

/**
 * @brief ia-32e mode system call target address <b>(r/w)</b>
 *
 * target rip for the called procedure when syscall is executed in 64-bit mode.
 *
 * @remarks if cpuid.80000001:edx.[29] = 1
 */
#define ia32_lstar 0xc0000082

/**
 * @brief ia-32e mode system call target address <b>(r/w)</b>
 *
 * not used, as the syscall instruction is not recognized in compatibility mode.
 *
 * @remarks if cpuid.80000001:edx.[29] = 1
 */
#define ia32_cstar 0xc0000083

/**
 * system call flag mask.
 *
 * @remarks if cpuid.80000001:edx.[29] = 1
 */
#define ia32_fmask 0xc0000084

/**
 * map of base address of fs.
 *
 * @remarks if cpuid.80000001:edx.[29] = 1
 */
#define ia32_fs_base 0xc0000100

/**
 * map of base address of gs.
 *
 * @remarks if cpuid.80000001:edx.[29] = 1
 */
#define ia32_gs_base 0xc0000101

/**
 * swap target of base address of gs.
 *
 * @remarks if cpuid.80000001:edx.[29] = 1
 */
#define ia32_kernel_gs_base 0xc0000102

/**
 * auxiliary tsc.
 *
 * @remarks if cpuid.80000001h: edx[27] = 1 or cpuid.(eax=7,ecx=0):ecx[bit 22] = 1
 */
#define ia32_tsc_aux 0xc0000103
typedef union {
	struct {
		/**
                 * [bits 31:0] aux. auxiliary signature of tsc.
                 */
		uint64 tscauxiliarysignature : 32;
#define ia32_tsc_aux_tsc_auxiliary_signature_bit 0
#define ia32_tsc_aux_tsc_auxiliary_signature_flag 0xffffffff
#define ia32_tsc_aux_tsc_auxiliary_signature_mask 0xffffffff
#define ia32_tsc_aux_tsc_auxiliary_signature(_) (((_) >> 0) & 0xffffffff)
		uint64 reserved1 : 32;
	};

	uint64 flags;
} ia32_tsc_aux_register;

/**
 * @}
 */

/**
 * @defgroup paging \
 *           paging
 * @{
 */
/**
 * @defgroup paging_32 \
 *           32-bit paging
 *
 * a logical processor uses 32-bit paging if cr0.pg = 1 and cr4.pae = 0. 32-bit paging translates 32-bit linear addresses
 * to 40-bit physical addresses. although 40 bits corresponds to 1 tbyte, linear addresses are limited to 32 bits; at most
 * 4 gbytes of linear-address space may be accessed at any given time.
 * 32-bit paging uses a hierarchy of paging structures to produce a translation for a linear address. cr3 is used to locate
 * the first paging-structure, the page directory. 32-bit paging may map linear addresses to either 4-kbyte pages or
 * 4-mbyte pages.
 *
 * @see vol3a[4.5(4-level paging)] (reference)
 * @{
 */
/**
 * @brief format of a 32-bit page-directory entry that maps a 4-mbyte page
 */
typedef union {
	struct {
		/**
                 * [bit 0] present; must be 1 to map a 4-mbyte page.
                 */
		uint32 present : 1;
#define pde_4mb_32_present_bit 0
#define pde_4mb_32_present_flag 0x01
#define pde_4mb_32_present_mask 0x01
#define pde_4mb_32_present(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] read/write; if 0, writes may not be allowed to the 4-mbyte page referenced by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint32 write : 1;
#define pde_4mb_32_write_bit 1
#define pde_4mb_32_write_flag 0x02
#define pde_4mb_32_write_mask 0x01
#define pde_4mb_32_write(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] user/supervisor; if 0, user-mode accesses are not allowed to the 4-mbyte page referenced by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint32 supervisor : 1;
#define pde_4mb_32_supervisor_bit 2
#define pde_4mb_32_supervisor_flag 0x04
#define pde_4mb_32_supervisor_mask 0x01
#define pde_4mb_32_supervisor(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] page-level write-through; indirectly determines the memory type used to access the 4-mbyte page referenced by
                 * this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint32 pagelevelwritethrough : 1;
#define pde_4mb_32_page_level_write_through_bit 3
#define pde_4mb_32_page_level_write_through_flag 0x08
#define pde_4mb_32_page_level_write_through_mask 0x01
#define pde_4mb_32_page_level_write_through(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] page-level cache disable; indirectly determines the memory type used to access the 4-mbyte page referenced by
                 * this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint32 pagelevelcachedisable : 1;
#define pde_4mb_32_page_level_cache_disable_bit 4
#define pde_4mb_32_page_level_cache_disable_flag 0x10
#define pde_4mb_32_page_level_cache_disable_mask 0x01
#define pde_4mb_32_page_level_cache_disable(_) (((_) >> 4) & 0x01)

		/**
                 * [bit 5] accessed; indicates whether software has accessed the 4-mbyte page referenced by this entry.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint32 accessed : 1;
#define pde_4mb_32_accessed_bit 5
#define pde_4mb_32_accessed_flag 0x20
#define pde_4mb_32_accessed_mask 0x01
#define pde_4mb_32_accessed(_) (((_) >> 5) & 0x01)

		/**
                 * [bit 6] dirty; indicates whether software has written to the 4-mbyte page referenced by this entry.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint32 dirty : 1;
#define pde_4mb_32_dirty_bit 6
#define pde_4mb_32_dirty_flag 0x40
#define pde_4mb_32_dirty_mask 0x01
#define pde_4mb_32_dirty(_) (((_) >> 6) & 0x01)

		/**
                 * [bit 7] page size; must be 1 (otherwise, this entry references a page table).
                 */
		uint32 largepage : 1;
#define pde_4mb_32_large_page_bit 7
#define pde_4mb_32_large_page_flag 0x80
#define pde_4mb_32_large_page_mask 0x01
#define pde_4mb_32_large_page(_) (((_) >> 7) & 0x01)

		/**
                 * [bit 8] global; if cr4.pge = 1, determines whether the translation is global; ignored otherwise.
                 *
                 * @see vol3a[4.10(caching translation information)]
                 */
		uint32 global : 1;
#define pde_4mb_32_global_bit 8
#define pde_4mb_32_global_flag 0x100
#define pde_4mb_32_global_mask 0x01
#define pde_4mb_32_global(_) (((_) >> 8) & 0x01)

		/**
                 * [bits 11:9] ignored.
                 */
		uint32 ignored1 : 3;
#define pde_4mb_32_ignored_1_bit 9
#define pde_4mb_32_ignored_1_flag 0xe00
#define pde_4mb_32_ignored_1_mask 0x07
#define pde_4mb_32_ignored_1(_) (((_) >> 9) & 0x07)

		/**
                 * [bit 12] indirectly determines the memory type used to access the 4-mbyte page referenced by this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint32 pat : 1;
#define pde_4mb_32_pat_bit 12
#define pde_4mb_32_pat_flag 0x1000
#define pde_4mb_32_pat_mask 0x01
#define pde_4mb_32_pat(_) (((_) >> 12) & 0x01)

		/**
                 * [bits 20:13] bits (m-1):32 of physical address of the 4-mbyte page referenced by this entry.
                 */
		uint32 pageframenumberlow : 8;
#define pde_4mb_32_page_frame_number_low_bit 13
#define pde_4mb_32_page_frame_number_low_flag 0x1fe000
#define pde_4mb_32_page_frame_number_low_mask 0xff
#define pde_4mb_32_page_frame_number_low(_) (((_) >> 13) & 0xff)
		uint32 reserved1 : 1;

		/**
                 * [bits 31:22] bits 31:22 of physical address of the 4-mbyte page referenced by this entry.
                 */
		uint32 pageframenumberhigh : 10;
#define pde_4mb_32_page_frame_number_high_bit 22
#define pde_4mb_32_page_frame_number_high_flag 0xffc00000
#define pde_4mb_32_page_frame_number_high_mask 0x3ff
#define pde_4mb_32_page_frame_number_high(_) (((_) >> 22) & 0x3ff)
	};

	uint32 flags;
} pde_4mb_32;

/**
 * @brief format of a 32-bit page-directory entry that references a page table
 */
typedef union {
	struct {
		/**
                 * [bit 0] present; must be 1 to reference a page table.
                 */
		uint32 present : 1;
#define pde_32_present_bit 0
#define pde_32_present_flag 0x01
#define pde_32_present_mask 0x01
#define pde_32_present(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] read/write; if 0, writes may not be allowed to the 4-mbyte region controlled by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint32 write : 1;
#define pde_32_write_bit 1
#define pde_32_write_flag 0x02
#define pde_32_write_mask 0x01
#define pde_32_write(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] user/supervisor; if 0, user-mode accesses are not allowed to the 4-mbyte region controlled by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint32 supervisor : 1;
#define pde_32_supervisor_bit 2
#define pde_32_supervisor_flag 0x04
#define pde_32_supervisor_mask 0x01
#define pde_32_supervisor(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] page-level write-through; indirectly determines the memory type used to access the page table referenced by this
                 * entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint32 pagelevelwritethrough : 1;
#define pde_32_page_level_write_through_bit 3
#define pde_32_page_level_write_through_flag 0x08
#define pde_32_page_level_write_through_mask 0x01
#define pde_32_page_level_write_through(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] page-level cache disable; indirectly determines the memory type used to access the page table referenced by this
                 * entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint32 pagelevelcachedisable : 1;
#define pde_32_page_level_cache_disable_bit 4
#define pde_32_page_level_cache_disable_flag 0x10
#define pde_32_page_level_cache_disable_mask 0x01
#define pde_32_page_level_cache_disable(_) (((_) >> 4) & 0x01)

		/**
                 * [bit 5] accessed; indicates whether this entry has been used for linear-address translation.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint32 accessed : 1;
#define pde_32_accessed_bit 5
#define pde_32_accessed_flag 0x20
#define pde_32_accessed_mask 0x01
#define pde_32_accessed(_) (((_) >> 5) & 0x01)

		/**
                 * [bit 6] ignored.
                 */
		uint32 ignored1 : 1;
#define pde_32_ignored_1_bit 6
#define pde_32_ignored_1_flag 0x40
#define pde_32_ignored_1_mask 0x01
#define pde_32_ignored_1(_) (((_) >> 6) & 0x01)

		/**
                 * [bit 7] if cr4.pse = 1, must be 0 (otherwise, this entry maps a 4-mbyte page); otherwise, ignored.
                 */
		uint32 largepage : 1;
#define pde_32_large_page_bit 7
#define pde_32_large_page_flag 0x80
#define pde_32_large_page_mask 0x01
#define pde_32_large_page(_) (((_) >> 7) & 0x01)

		/**
                 * [bits 11:8] ignored.
                 */
		uint32 ignored2 : 4;
#define pde_32_ignored_2_bit 8
#define pde_32_ignored_2_flag 0xf00
#define pde_32_ignored_2_mask 0x0f
#define pde_32_ignored_2(_) (((_) >> 8) & 0x0f)

		/**
                 * [bits 31:12] physical address of 4-kbyte aligned page table referenced by this entry.
                 */
		uint32 pageframenumber : 20;
#define pde_32_page_frame_number_bit 12
#define pde_32_page_frame_number_flag 0xfffff000
#define pde_32_page_frame_number_mask 0xfffff
#define pde_32_page_frame_number(_) (((_) >> 12) & 0xfffff)
	};

	uint32 flags;
} pde_32;

/**
 * @brief format of a 32-bit page-table entry that maps a 4-kbyte page
 */
typedef union {
	struct {
		/**
                 * [bit 0] present; must be 1 to map a 4-kbyte page.
                 */
		uint32 present : 1;
#define pte_32_present_bit 0
#define pte_32_present_flag 0x01
#define pte_32_present_mask 0x01
#define pte_32_present(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] read/write; if 0, writes may not be allowed to the 4-kbyte page referenced by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint32 write : 1;
#define pte_32_write_bit 1
#define pte_32_write_flag 0x02
#define pte_32_write_mask 0x01
#define pte_32_write(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] user/supervisor; if 0, user-mode accesses are not allowed to the 4-kbyte page referenced by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint32 supervisor : 1;
#define pte_32_supervisor_bit 2
#define pte_32_supervisor_flag 0x04
#define pte_32_supervisor_mask 0x01
#define pte_32_supervisor(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] page-level write-through; indirectly determines the memory type used to access the 4-kbyte page referenced by
                 * this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint32 pagelevelwritethrough : 1;
#define pte_32_page_level_write_through_bit 3
#define pte_32_page_level_write_through_flag 0x08
#define pte_32_page_level_write_through_mask 0x01
#define pte_32_page_level_write_through(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] page-level cache disable; indirectly determines the memory type used to access the 4-kbyte page referenced by
                 * this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint32 pagelevelcachedisable : 1;
#define pte_32_page_level_cache_disable_bit 4
#define pte_32_page_level_cache_disable_flag 0x10
#define pte_32_page_level_cache_disable_mask 0x01
#define pte_32_page_level_cache_disable(_) (((_) >> 4) & 0x01)

		/**
                 * [bit 5] accessed; indicates whether software has accessed the 4-kbyte page referenced by this entry.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint32 accessed : 1;
#define pte_32_accessed_bit 5
#define pte_32_accessed_flag 0x20
#define pte_32_accessed_mask 0x01
#define pte_32_accessed(_) (((_) >> 5) & 0x01)

		/**
                 * [bit 6] dirty; indicates whether software has written to the 4-kbyte page referenced by this entry.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint32 dirty : 1;
#define pte_32_dirty_bit 6
#define pte_32_dirty_flag 0x40
#define pte_32_dirty_mask 0x01
#define pte_32_dirty(_) (((_) >> 6) & 0x01)

		/**
                 * [bit 7] indirectly determines the memory type used to access the 4-kbyte page referenced by this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint32 pat : 1;
#define pte_32_pat_bit 7
#define pte_32_pat_flag 0x80
#define pte_32_pat_mask 0x01
#define pte_32_pat(_) (((_) >> 7) & 0x01)

		/**
                 * [bit 8] global; if cr4.pge = 1, determines whether the translation is global; ignored otherwise.
                 *
                 * @see vol3a[4.10(caching translation information)]
                 */
		uint32 global : 1;
#define pte_32_global_bit 8
#define pte_32_global_flag 0x100
#define pte_32_global_mask 0x01
#define pte_32_global(_) (((_) >> 8) & 0x01)

		/**
                 * [bits 11:9] ignored.
                 */
		uint32 ignored1 : 3;
#define pte_32_ignored_1_bit 9
#define pte_32_ignored_1_flag 0xe00
#define pte_32_ignored_1_mask 0x07
#define pte_32_ignored_1(_) (((_) >> 9) & 0x07)

		/**
                 * [bits 31:12] physical address of 4-kbyte aligned page table referenced by this entry.
                 */
		uint32 pageframenumber : 20;
#define pte_32_page_frame_number_bit 12
#define pte_32_page_frame_number_flag 0xfffff000
#define pte_32_page_frame_number_mask 0xfffff
#define pte_32_page_frame_number(_) (((_) >> 12) & 0xfffff)
	};

	uint32 flags;
} pte_32;

/**
 * @brief format of a common page-table entry
 */
typedef union {
	struct {
		uint32 present : 1;
#define pt_entry_32_present_bit 0
#define pt_entry_32_present_flag 0x01
#define pt_entry_32_present_mask 0x01
#define pt_entry_32_present(_) (((_) >> 0) & 0x01)
		uint32 write : 1;
#define pt_entry_32_write_bit 1
#define pt_entry_32_write_flag 0x02
#define pt_entry_32_write_mask 0x01
#define pt_entry_32_write(_) (((_) >> 1) & 0x01)
		uint32 supervisor : 1;
#define pt_entry_32_supervisor_bit 2
#define pt_entry_32_supervisor_flag 0x04
#define pt_entry_32_supervisor_mask 0x01
#define pt_entry_32_supervisor(_) (((_) >> 2) & 0x01)
		uint32 pagelevelwritethrough : 1;
#define pt_entry_32_page_level_write_through_bit 3
#define pt_entry_32_page_level_write_through_flag 0x08
#define pt_entry_32_page_level_write_through_mask 0x01
#define pt_entry_32_page_level_write_through(_) (((_) >> 3) & 0x01)
		uint32 pagelevelcachedisable : 1;
#define pt_entry_32_page_level_cache_disable_bit 4
#define pt_entry_32_page_level_cache_disable_flag 0x10
#define pt_entry_32_page_level_cache_disable_mask 0x01
#define pt_entry_32_page_level_cache_disable(_) (((_) >> 4) & 0x01)
		uint32 accessed : 1;
#define pt_entry_32_accessed_bit 5
#define pt_entry_32_accessed_flag 0x20
#define pt_entry_32_accessed_mask 0x01
#define pt_entry_32_accessed(_) (((_) >> 5) & 0x01)
		uint32 dirty : 1;
#define pt_entry_32_dirty_bit 6
#define pt_entry_32_dirty_flag 0x40
#define pt_entry_32_dirty_mask 0x01
#define pt_entry_32_dirty(_) (((_) >> 6) & 0x01)
		uint32 largepage : 1;
#define pt_entry_32_large_page_bit 7
#define pt_entry_32_large_page_flag 0x80
#define pt_entry_32_large_page_mask 0x01
#define pt_entry_32_large_page(_) (((_) >> 7) & 0x01)
		uint32 global : 1;
#define pt_entry_32_global_bit 8
#define pt_entry_32_global_flag 0x100
#define pt_entry_32_global_mask 0x01
#define pt_entry_32_global(_) (((_) >> 8) & 0x01)

		/**
                 * [bits 11:9] ignored.
                 */
		uint32 ignored1 : 3;
#define pt_entry_32_ignored_1_bit 9
#define pt_entry_32_ignored_1_flag 0xe00
#define pt_entry_32_ignored_1_mask 0x07
#define pt_entry_32_ignored_1(_) (((_) >> 9) & 0x07)

		/**
                 * [bits 31:12] physical address of the 4-kbyte page referenced by this entry.
                 */
		uint32 pageframenumber : 20;
#define pt_entry_32_page_frame_number_bit 12
#define pt_entry_32_page_frame_number_flag 0xfffff000
#define pt_entry_32_page_frame_number_mask 0xfffff
#define pt_entry_32_page_frame_number(_) (((_) >> 12) & 0xfffff)
	};

	uint32 flags;
} pt_entry_32;

/**
 * @defgroup paging_structures_entry_count_32 \
 *           paging structures entry counts
 *
 * paging structures entry counts.
 * @{
 */
#define pde_entry_count_32 0x00000400
#define pte_entry_count_32 0x00000400
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup paging_64 \
 *           64-bit (4-level) paging
 *
 * a logical processor uses 4-level paging if cr0.pg = 1, cr4.pae = 1, and ia32_efer.lme = 1. with 4-level paging, linear
 * address are translated using a hierarchy of in-memory paging structures located using the contents of cr3. 4-level
 * paging translates 48-bit linear addresses to 52-bit physical addresses. although 52 bits corresponds to 4 pbytes, linear
 * addresses are limited to 48 bits; at most 256 tbytes of linear-address space may be accessed at any given time.
 * 4-level paging uses a hierarchy of paging structures to produce a translation for a linear address. cr3 is used to
 * locate the first paging-structure, the pml4 table. use of cr3 with 4-level paging depends on whether processcontext
 * identifiers (pcids) have been enabled by setting cr4.pcide.
 *
 * @see vol3a[4.5(4-level paging)] (reference)
 * @{
 */
/**
 * @brief format of a 4-level pml4 entry (pml4e) that references a page-directory-pointer table
 */
typedef union {
	struct {
		/**
                 * [bit 0] present; must be 1 to reference a page-directory-pointer table.
                 */
		uint64 present : 1;
#define pml4e_64_present_bit 0
#define pml4e_64_present_flag 0x01
#define pml4e_64_present_mask 0x01
#define pml4e_64_present(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] read/write; if 0, writes may not be allowed to the 512-gbyte region controlled by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 write : 1;
#define pml4e_64_write_bit 1
#define pml4e_64_write_flag 0x02
#define pml4e_64_write_mask 0x01
#define pml4e_64_write(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] user/supervisor; if 0, user-mode accesses are not allowed to the 512-gbyte region controlled by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 supervisor : 1;
#define pml4e_64_supervisor_bit 2
#define pml4e_64_supervisor_flag 0x04
#define pml4e_64_supervisor_mask 0x01
#define pml4e_64_supervisor(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] page-level write-through; indirectly determines the memory type used to access the page-directory-pointer table
                 * referenced by this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pagelevelwritethrough : 1;
#define pml4e_64_page_level_write_through_bit 3
#define pml4e_64_page_level_write_through_flag 0x08
#define pml4e_64_page_level_write_through_mask 0x01
#define pml4e_64_page_level_write_through(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] page-level cache disable; indirectly determines the memory type used to access the page-directory-pointer table
                 * referenced by this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pagelevelcachedisable : 1;
#define pml4e_64_page_level_cache_disable_bit 4
#define pml4e_64_page_level_cache_disable_flag 0x10
#define pml4e_64_page_level_cache_disable_mask 0x01
#define pml4e_64_page_level_cache_disable(_) (((_) >> 4) & 0x01)

		/**
                 * [bit 5] accessed; indicates whether this entry has been used for linear-address translation.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint64 accessed : 1;
#define pml4e_64_accessed_bit 5
#define pml4e_64_accessed_flag 0x20
#define pml4e_64_accessed_mask 0x01
#define pml4e_64_accessed(_) (((_) >> 5) & 0x01)
		uint64 reserved1 : 1;

		/**
                 * [bit 7] reserved (must be 0).
                 */
		uint64 mustbezero : 1;
#define pml4e_64_must_be_zero_bit 7
#define pml4e_64_must_be_zero_flag 0x80
#define pml4e_64_must_be_zero_mask 0x01
#define pml4e_64_must_be_zero(_) (((_) >> 7) & 0x01)

		/**
                 * [bits 11:8] ignored.
                 */
		uint64 ignored1 : 4;
#define pml4e_64_ignored_1_bit 8
#define pml4e_64_ignored_1_flag 0xf00
#define pml4e_64_ignored_1_mask 0x0f
#define pml4e_64_ignored_1(_) (((_) >> 8) & 0x0f)

		/**
                 * [bits 47:12] physical address of 4-kbyte aligned page-directory-pointer table referenced by this entry.
                 */
		uint64 pageframenumber : 40;
#define pml4e_64_page_frame_number_bit 12
#define pml4e_64_page_frame_number_flag 0xfffffffff000
#define pml4e_64_page_frame_number_mask 0xfffffffff
#define pml4e_64_page_frame_number(_) (((_) >> 12) & 0xfffffffff)

		/**
                 * [bits 62:52] ignored.
                 */
		uint64 ignored2 : 11;
#define pml4e_64_ignored_2_bit 52
#define pml4e_64_ignored_2_flag 0x7ff0000000000000
#define pml4e_64_ignored_2_mask 0x7ff
#define pml4e_64_ignored_2(_) (((_) >> 52) & 0x7ff)

		/**
                 * [bit 63] if ia32_efer.nxe = 1, execute-disable (if 1, instruction fetches are not allowed from the 512-gbyte region
                 * controlled by this entry); otherwise, reserved (must be 0).
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 executedisable : 1;
#define pml4e_64_execute_disable_bit 63
#define pml4e_64_execute_disable_flag 0x8000000000000000
#define pml4e_64_execute_disable_mask 0x01
#define pml4e_64_execute_disable(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} pml4e_64;

/**
 * @brief format of a 4-level page-directory-pointer-table entry (pdpte) that maps a 1-gbyte page
 */
typedef union {
	struct {
		/**
                 * [bit 0] present; must be 1 to map a 1-gbyte page.
                 */
		uint64 present : 1;
#define pdpte_1gb_64_present_bit 0
#define pdpte_1gb_64_present_flag 0x01
#define pdpte_1gb_64_present_mask 0x01
#define pdpte_1gb_64_present(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] read/write; if 0, writes may not be allowed to the 1-gbyte page referenced by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 write : 1;
#define pdpte_1gb_64_write_bit 1
#define pdpte_1gb_64_write_flag 0x02
#define pdpte_1gb_64_write_mask 0x01
#define pdpte_1gb_64_write(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] user/supervisor; if 0, user-mode accesses are not allowed to the 1-gbyte page referenced by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 supervisor : 1;
#define pdpte_1gb_64_supervisor_bit 2
#define pdpte_1gb_64_supervisor_flag 0x04
#define pdpte_1gb_64_supervisor_mask 0x01
#define pdpte_1gb_64_supervisor(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] page-level write-through; indirectly determines the memory type used to access the 1-gbyte page referenced by
                 * this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pagelevelwritethrough : 1;
#define pdpte_1gb_64_page_level_write_through_bit 3
#define pdpte_1gb_64_page_level_write_through_flag 0x08
#define pdpte_1gb_64_page_level_write_through_mask 0x01
#define pdpte_1gb_64_page_level_write_through(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] page-level cache disable; indirectly determines the memory type used to access the 1-gbyte page referenced by
                 * this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pagelevelcachedisable : 1;
#define pdpte_1gb_64_page_level_cache_disable_bit 4
#define pdpte_1gb_64_page_level_cache_disable_flag 0x10
#define pdpte_1gb_64_page_level_cache_disable_mask 0x01
#define pdpte_1gb_64_page_level_cache_disable(_) (((_) >> 4) & 0x01)

		/**
                 * [bit 5] accessed; indicates whether software has accessed the 1-gbyte page referenced by this entry.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint64 accessed : 1;
#define pdpte_1gb_64_accessed_bit 5
#define pdpte_1gb_64_accessed_flag 0x20
#define pdpte_1gb_64_accessed_mask 0x01
#define pdpte_1gb_64_accessed(_) (((_) >> 5) & 0x01)

		/**
                 * [bit 6] dirty; indicates whether software has written to the 1-gbyte page referenced by this entry.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint64 dirty : 1;
#define pdpte_1gb_64_dirty_bit 6
#define pdpte_1gb_64_dirty_flag 0x40
#define pdpte_1gb_64_dirty_mask 0x01
#define pdpte_1gb_64_dirty(_) (((_) >> 6) & 0x01)

		/**
                 * [bit 7] page size; must be 1 (otherwise, this entry references a page directory).
                 */
		uint64 largepage : 1;
#define pdpte_1gb_64_large_page_bit 7
#define pdpte_1gb_64_large_page_flag 0x80
#define pdpte_1gb_64_large_page_mask 0x01
#define pdpte_1gb_64_large_page(_) (((_) >> 7) & 0x01)

		/**
                 * [bit 8] global; if cr4.pge = 1, determines whether the translation is global; ignored otherwise.
                 *
                 * @see vol3a[4.10(caching translation information)]
                 */
		uint64 global : 1;
#define pdpte_1gb_64_global_bit 8
#define pdpte_1gb_64_global_flag 0x100
#define pdpte_1gb_64_global_mask 0x01
#define pdpte_1gb_64_global(_) (((_) >> 8) & 0x01)

		/**
                 * [bits 11:9] ignored.
                 */
		uint64 ignored1 : 3;
#define pdpte_1gb_64_ignored_1_bit 9
#define pdpte_1gb_64_ignored_1_flag 0xe00
#define pdpte_1gb_64_ignored_1_mask 0x07
#define pdpte_1gb_64_ignored_1(_) (((_) >> 9) & 0x07)

		/**
                 * [bit 12] indirectly determines the memory type used to access the 1-gbyte page referenced by this entry.
                 *
                 * @note the pat is supported on all processors that support 4-level paging.
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pat : 1;
#define pdpte_1gb_64_pat_bit 12
#define pdpte_1gb_64_pat_flag 0x1000
#define pdpte_1gb_64_pat_mask 0x01
#define pdpte_1gb_64_pat(_) (((_) >> 12) & 0x01)
		uint64 reserved1 : 17;

		/**
                 * [bits 51:30] physical address of the 1-gbyte page referenced by this entry.
                 */
		uint64 pageframenumber : 22;
#define pdpte_1gb_64_page_frame_number_bit 30
#define pdpte_1gb_64_page_frame_number_flag 0xffffc0000000
#define pdpte_1gb_64_page_frame_number_mask 0x3ffff
#define pdpte_1gb_64_page_frame_number(_) (((_) >> 30) & 0x3ffff)

		/**
                 * [bits 58:52] ignored.
                 */
		uint64 ignored2 : 7;
#define pdpte_1gb_64_ignored_2_bit 52
#define pdpte_1gb_64_ignored_2_flag 0x7f0000000000000
#define pdpte_1gb_64_ignored_2_mask 0x7f
#define pdpte_1gb_64_ignored_2(_) (((_) >> 52) & 0x7f)

		/**
                 * [bits 62:59] protection key; if cr4.pke = 1, determines the protection key of the page; ignored otherwise.
                 *
                 * @see vol3a[4.6.2(protection keys)]
                 */
		uint64 protectionkey : 4;
#define pdpte_1gb_64_protection_key_bit 59
#define pdpte_1gb_64_protection_key_flag 0x7800000000000000
#define pdpte_1gb_64_protection_key_mask 0x0f
#define pdpte_1gb_64_protection_key(_) (((_) >> 59) & 0x0f)

		/**
                 * [bit 63] if ia32_efer.nxe = 1, execute-disable (if 1, instruction fetches are not allowed from the 1-gbyte page
                 * controlled by this entry); otherwise, reserved (must be 0).
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 executedisable : 1;
#define pdpte_1gb_64_execute_disable_bit 63
#define pdpte_1gb_64_execute_disable_flag 0x8000000000000000
#define pdpte_1gb_64_execute_disable_mask 0x01
#define pdpte_1gb_64_execute_disable(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} pdpte_1gb_64;

/**
 * @brief format of a 4-level page-directory-pointer-table entry (pdpte) that references a page directory
 */
typedef union {
	struct {
		/**
                 * [bit 0] present; must be 1 to reference a page directory.
                 */
		uint64 present : 1;
#define pdpte_64_present_bit 0
#define pdpte_64_present_flag 0x01
#define pdpte_64_present_mask 0x01
#define pdpte_64_present(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] read/write; if 0, writes may not be allowed to the 1-gbyte region controlled by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 write : 1;
#define pdpte_64_write_bit 1
#define pdpte_64_write_flag 0x02
#define pdpte_64_write_mask 0x01
#define pdpte_64_write(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] user/supervisor; if 0, user-mode accesses are not allowed to the 1-gbyte region controlled by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 supervisor : 1;
#define pdpte_64_supervisor_bit 2
#define pdpte_64_supervisor_flag 0x04
#define pdpte_64_supervisor_mask 0x01
#define pdpte_64_supervisor(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] page-level write-through; indirectly determines the memory type used to access the page directory referenced by
                 * this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pagelevelwritethrough : 1;
#define pdpte_64_page_level_write_through_bit 3
#define pdpte_64_page_level_write_through_flag 0x08
#define pdpte_64_page_level_write_through_mask 0x01
#define pdpte_64_page_level_write_through(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] page-level cache disable; indirectly determines the memory type used to access the page directory referenced by
                 * this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pagelevelcachedisable : 1;
#define pdpte_64_page_level_cache_disable_bit 4
#define pdpte_64_page_level_cache_disable_flag 0x10
#define pdpte_64_page_level_cache_disable_mask 0x01
#define pdpte_64_page_level_cache_disable(_) (((_) >> 4) & 0x01)

		/**
                 * [bit 5] accessed; indicates whether this entry has been used for linear-address translation.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint64 accessed : 1;
#define pdpte_64_accessed_bit 5
#define pdpte_64_accessed_flag 0x20
#define pdpte_64_accessed_mask 0x01
#define pdpte_64_accessed(_) (((_) >> 5) & 0x01)
		uint64 reserved1 : 1;

		/**
                 * [bit 7] page size; must be 0 (otherwise, this entry maps a 1-gbyte page).
                 */
		uint64 largepage : 1;
#define pdpte_64_large_page_bit 7
#define pdpte_64_large_page_flag 0x80
#define pdpte_64_large_page_mask 0x01
#define pdpte_64_large_page(_) (((_) >> 7) & 0x01)

		/**
                 * [bits 11:8] ignored.
                 */
		uint64 ignored1 : 4;
#define pdpte_64_ignored_1_bit 8
#define pdpte_64_ignored_1_flag 0xf00
#define pdpte_64_ignored_1_mask 0x0f
#define pdpte_64_ignored_1(_) (((_) >> 8) & 0x0f)

		/**
                 * [bits 51:12] physical address of 4-kbyte aligned page directory referenced by this entry.
                 */
		uint64 pageframenumber : 40;
#define pdpte_64_page_frame_number_bit 12
#define pdpte_64_page_frame_number_flag 0xfffffffff000
#define pdpte_64_page_frame_number_mask 0xfffffffff
#define pdpte_64_page_frame_number(_) (((_) >> 12) & 0xfffffffff)

		/**
                 * [bits 62:52] ignored.
                 */
		uint64 ignored2 : 11;
#define pdpte_64_ignored_2_bit 52
#define pdpte_64_ignored_2_flag 0x7ff0000000000000
#define pdpte_64_ignored_2_mask 0x7ff
#define pdpte_64_ignored_2(_) (((_) >> 52) & 0x7ff)

		/**
                 * [bit 63] if ia32_efer.nxe = 1, execute-disable (if 1, instruction fetches are not allowed from the 1-gbyte region
                 * controlled by this entry); otherwise, reserved (must be 0).
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 executedisable : 1;
#define pdpte_64_execute_disable_bit 63
#define pdpte_64_execute_disable_flag 0x8000000000000000
#define pdpte_64_execute_disable_mask 0x01
#define pdpte_64_execute_disable(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} pdpte_64;

/**
 * @brief format of a 4-level page-directory entry that maps a 2-mbyte page
 */
typedef union {
	struct {
		/**
                 * [bit 0] present; must be 1 to map a 2-mbyte page.
                 */
		uint64 present : 1;
#define pde_2mb_64_present_bit 0
#define pde_2mb_64_present_flag 0x01
#define pde_2mb_64_present_mask 0x01
#define pde_2mb_64_present(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] read/write; if 0, writes may not be allowed to the 2-mbyte page referenced by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 write : 1;
#define pde_2mb_64_write_bit 1
#define pde_2mb_64_write_flag 0x02
#define pde_2mb_64_write_mask 0x01
#define pde_2mb_64_write(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] user/supervisor; if 0, user-mode accesses are not allowed to the 2-mbyte page referenced by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 supervisor : 1;
#define pde_2mb_64_supervisor_bit 2
#define pde_2mb_64_supervisor_flag 0x04
#define pde_2mb_64_supervisor_mask 0x01
#define pde_2mb_64_supervisor(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] page-level write-through; indirectly determines the memory type used to access the 2-mbyte page referenced by
                 * this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pagelevelwritethrough : 1;
#define pde_2mb_64_page_level_write_through_bit 3
#define pde_2mb_64_page_level_write_through_flag 0x08
#define pde_2mb_64_page_level_write_through_mask 0x01
#define pde_2mb_64_page_level_write_through(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] page-level cache disable; indirectly determines the memory type used to access the 2-mbyte page referenced by
                 * this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pagelevelcachedisable : 1;
#define pde_2mb_64_page_level_cache_disable_bit 4
#define pde_2mb_64_page_level_cache_disable_flag 0x10
#define pde_2mb_64_page_level_cache_disable_mask 0x01
#define pde_2mb_64_page_level_cache_disable(_) (((_) >> 4) & 0x01)

		/**
                 * [bit 5] accessed; indicates whether software has accessed the 2-mbyte page referenced by this entry.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint64 accessed : 1;
#define pde_2mb_64_accessed_bit 5
#define pde_2mb_64_accessed_flag 0x20
#define pde_2mb_64_accessed_mask 0x01
#define pde_2mb_64_accessed(_) (((_) >> 5) & 0x01)

		/**
                 * [bit 6] dirty; indicates whether software has written to the 2-mbyte page referenced by this entry.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint64 dirty : 1;
#define pde_2mb_64_dirty_bit 6
#define pde_2mb_64_dirty_flag 0x40
#define pde_2mb_64_dirty_mask 0x01
#define pde_2mb_64_dirty(_) (((_) >> 6) & 0x01)

		/**
                 * [bit 7] page size; must be 1 (otherwise, this entry references a page directory).
                 */
		uint64 largepage : 1;
#define pde_2mb_64_large_page_bit 7
#define pde_2mb_64_large_page_flag 0x80
#define pde_2mb_64_large_page_mask 0x01
#define pde_2mb_64_large_page(_) (((_) >> 7) & 0x01)

		/**
                 * [bit 8] global; if cr4.pge = 1, determines whether the translation is global; ignored otherwise.
                 *
                 * @see vol3a[4.10(caching translation information)]
                 */
		uint64 global : 1;
#define pde_2mb_64_global_bit 8
#define pde_2mb_64_global_flag 0x100
#define pde_2mb_64_global_mask 0x01
#define pde_2mb_64_global(_) (((_) >> 8) & 0x01)

		/**
                 * [bits 11:9] ignored.
                 */
		uint64 ignored1 : 3;
#define pde_2mb_64_ignored_1_bit 9
#define pde_2mb_64_ignored_1_flag 0xe00
#define pde_2mb_64_ignored_1_mask 0x07
#define pde_2mb_64_ignored_1(_) (((_) >> 9) & 0x07)

		/**
                 * [bit 12] indirectly determines the memory type used to access the 2-mbyte page referenced by this entry.
                 *
                 * @note the pat is supported on all processors that support 4-level paging.
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pat : 1;
#define pde_2mb_64_pat_bit 12
#define pde_2mb_64_pat_flag 0x1000
#define pde_2mb_64_pat_mask 0x01
#define pde_2mb_64_pat(_) (((_) >> 12) & 0x01)
		uint64 reserved1 : 8;

		/**
                 * [bits 51:21] physical address of the 2-mbyte page referenced by this entry.
                 */
		uint64 pageframenumber : 31;
#define pde_2mb_64_page_frame_number_bit 21
#define pde_2mb_64_page_frame_number_flag 0xffffffe00000
#define pde_2mb_64_page_frame_number_mask 0x7ffffff
#define pde_2mb_64_page_frame_number(_) (((_) >> 21) & 0x7ffffff)

		/**
                 * [bits 58:52] ignored.
                 */
		uint64 ignored2 : 7;
#define pde_2mb_64_ignored_2_bit 52
#define pde_2mb_64_ignored_2_flag 0x7f0000000000000
#define pde_2mb_64_ignored_2_mask 0x7f
#define pde_2mb_64_ignored_2(_) (((_) >> 52) & 0x7f)

		/**
                 * [bits 62:59] protection key; if cr4.pke = 1, determines the protection key of the page; ignored otherwise.
                 *
                 * @see vol3a[4.6.2(protection keys)]
                 */
		uint64 protectionkey : 4;
#define pde_2mb_64_protection_key_bit 59
#define pde_2mb_64_protection_key_flag 0x7800000000000000
#define pde_2mb_64_protection_key_mask 0x0f
#define pde_2mb_64_protection_key(_) (((_) >> 59) & 0x0f)

		/**
                 * [bit 63] if ia32_efer.nxe = 1, execute-disable (if 1, instruction fetches are not allowed from the 2-mbyte page
                 * controlled by this entry); otherwise, reserved (must be 0).
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 executedisable : 1;
#define pde_2mb_64_execute_disable_bit 63
#define pde_2mb_64_execute_disable_flag 0x8000000000000000
#define pde_2mb_64_execute_disable_mask 0x01
#define pde_2mb_64_execute_disable(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} pde_2mb_64;

/**
 * @brief format of a 4-level page-directory entry that references a page table
 */
typedef union {
	struct {
		/**
                 * [bit 0] present; must be 1 to reference a page table.
                 */
		uint64 present : 1;
#define pde_64_present_bit 0
#define pde_64_present_flag 0x01
#define pde_64_present_mask 0x01
#define pde_64_present(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] read/write; if 0, writes may not be allowed to the 2-mbyte region controlled by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 write : 1;
#define pde_64_write_bit 1
#define pde_64_write_flag 0x02
#define pde_64_write_mask 0x01
#define pde_64_write(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] user/supervisor; if 0, user-mode accesses are not allowed to the 2-mbyte region controlled by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 supervisor : 1;
#define pde_64_supervisor_bit 2
#define pde_64_supervisor_flag 0x04
#define pde_64_supervisor_mask 0x01
#define pde_64_supervisor(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] page-level write-through; indirectly determines the memory type used to access the page table referenced by this
                 * entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pagelevelwritethrough : 1;
#define pde_64_page_level_write_through_bit 3
#define pde_64_page_level_write_through_flag 0x08
#define pde_64_page_level_write_through_mask 0x01
#define pde_64_page_level_write_through(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] page-level cache disable; indirectly determines the memory type used to access the page table referenced by this
                 * entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pagelevelcachedisable : 1;
#define pde_64_page_level_cache_disable_bit 4
#define pde_64_page_level_cache_disable_flag 0x10
#define pde_64_page_level_cache_disable_mask 0x01
#define pde_64_page_level_cache_disable(_) (((_) >> 4) & 0x01)

		/**
                 * [bit 5] accessed; indicates whether this entry has been used for linear-address translation.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint64 accessed : 1;
#define pde_64_accessed_bit 5
#define pde_64_accessed_flag 0x20
#define pde_64_accessed_mask 0x01
#define pde_64_accessed(_) (((_) >> 5) & 0x01)
		uint64 reserved1 : 1;

		/**
                 * [bit 7] page size; must be 0 (otherwise, this entry maps a 2-mbyte page).
                 */
		uint64 largepage : 1;
#define pde_64_large_page_bit 7
#define pde_64_large_page_flag 0x80
#define pde_64_large_page_mask 0x01
#define pde_64_large_page(_) (((_) >> 7) & 0x01)

		/**
                 * [bits 11:8] ignored.
                 */
		uint64 ignored1 : 4;
#define pde_64_ignored_1_bit 8
#define pde_64_ignored_1_flag 0xf00
#define pde_64_ignored_1_mask 0x0f
#define pde_64_ignored_1(_) (((_) >> 8) & 0x0f)

		/**
                 * [bits 51:12] physical address of 4-kbyte aligned page table referenced by this entry.
                 */
		uint64 pageframenumber : 40;
#define pde_64_page_frame_number_bit 12
#define pde_64_page_frame_number_flag 0xfffffffff000
#define pde_64_page_frame_number_mask 0xfffffffff
#define pde_64_page_frame_number(_) (((_) >> 12) & 0xfffffffff)

		/**
                 * [bits 62:52] ignored.
                 */
		uint64 ignored2 : 11;
#define pde_64_ignored_2_bit 52
#define pde_64_ignored_2_flag 0x7ff0000000000000
#define pde_64_ignored_2_mask 0x7ff
#define pde_64_ignored_2(_) (((_) >> 52) & 0x7ff)

		/**
                 * [bit 63] if ia32_efer.nxe = 1, execute-disable (if 1, instruction fetches are not allowed from the 2-mbyte region
                 * controlled by this entry); otherwise, reserved (must be 0).
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 executedisable : 1;
#define pde_64_execute_disable_bit 63
#define pde_64_execute_disable_flag 0x8000000000000000
#define pde_64_execute_disable_mask 0x01
#define pde_64_execute_disable(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} pde_64;

/**
 * @brief format of a 4-level page-table entry that maps a 4-kbyte page
 */
typedef union {
	struct {
		/**
                 * [bit 0] present; must be 1 to map a 4-kbyte page.
                 */
		uint64 present : 1;
#define pte_64_present_bit 0
#define pte_64_present_flag 0x01
#define pte_64_present_mask 0x01
#define pte_64_present(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] read/write; if 0, writes may not be allowed to the 4-kbyte page referenced by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 write : 1;
#define pte_64_write_bit 1
#define pte_64_write_flag 0x02
#define pte_64_write_mask 0x01
#define pte_64_write(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] user/supervisor; if 0, user-mode accesses are not allowed to the 4-kbyte page referenced by this entry.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 supervisor : 1;
#define pte_64_supervisor_bit 2
#define pte_64_supervisor_flag 0x04
#define pte_64_supervisor_mask 0x01
#define pte_64_supervisor(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] page-level write-through; indirectly determines the memory type used to access the 4-kbyte page referenced by
                 * this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pagelevelwritethrough : 1;
#define pte_64_page_level_write_through_bit 3
#define pte_64_page_level_write_through_flag 0x08
#define pte_64_page_level_write_through_mask 0x01
#define pte_64_page_level_write_through(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] page-level cache disable; indirectly determines the memory type used to access the 4-kbyte page referenced by
                 * this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pagelevelcachedisable : 1;
#define pte_64_page_level_cache_disable_bit 4
#define pte_64_page_level_cache_disable_flag 0x10
#define pte_64_page_level_cache_disable_mask 0x01
#define pte_64_page_level_cache_disable(_) (((_) >> 4) & 0x01)

		/**
                 * [bit 5] accessed; indicates whether software has accessed the 4-kbyte page referenced by this entry.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint64 accessed : 1;
#define pte_64_accessed_bit 5
#define pte_64_accessed_flag 0x20
#define pte_64_accessed_mask 0x01
#define pte_64_accessed(_) (((_) >> 5) & 0x01)

		/**
                 * [bit 6] dirty; indicates whether software has written to the 4-kbyte page referenced by this entry.
                 *
                 * @see vol3a[4.8(accessed and dirty flags)]
                 */
		uint64 dirty : 1;
#define pte_64_dirty_bit 6
#define pte_64_dirty_flag 0x40
#define pte_64_dirty_mask 0x01
#define pte_64_dirty(_) (((_) >> 6) & 0x01)

		/**
                 * [bit 7] indirectly determines the memory type used to access the 4-kbyte page referenced by this entry.
                 *
                 * @see vol3a[4.9.2(paging and memory typing when the pat is supported (pentium iii and more recent processor families))]
                 */
		uint64 pat : 1;
#define pte_64_pat_bit 7
#define pte_64_pat_flag 0x80
#define pte_64_pat_mask 0x01
#define pte_64_pat(_) (((_) >> 7) & 0x01)

		/**
                 * [bit 8] global; if cr4.pge = 1, determines whether the translation is global; ignored otherwise.
                 *
                 * @see vol3a[4.10(caching translation information)]
                 */
		uint64 global : 1;
#define pte_64_global_bit 8
#define pte_64_global_flag 0x100
#define pte_64_global_mask 0x01
#define pte_64_global(_) (((_) >> 8) & 0x01)

		/**
                 * [bits 11:9] ignored.
                 */
		uint64 ignored1 : 3;
#define pte_64_ignored_1_bit 9
#define pte_64_ignored_1_flag 0xe00
#define pte_64_ignored_1_mask 0x07
#define pte_64_ignored_1(_) (((_) >> 9) & 0x07)

		/**
                 * [bits 51:12] physical address of the 4-kbyte page referenced by this entry.
                 */
		uint64 pageframenumber : 40;
#define pte_64_page_frame_number_bit 12
#define pte_64_page_frame_number_flag 0xfffffffff000
#define pte_64_page_frame_number_mask 0xfffffffff
#define pte_64_page_frame_number(_) (((_) >> 12) & 0xfffffffff)

		/**
                 * [bits 58:52] ignored.
                 */
		uint64 ignored2 : 7;
#define pte_64_ignored_2_bit 52
#define pte_64_ignored_2_flag 0x7f0000000000000
#define pte_64_ignored_2_mask 0x7f
#define pte_64_ignored_2(_) (((_) >> 52) & 0x7f)

		/**
                 * [bits 62:59] protection key; if cr4.pke = 1, determines the protection key of the page; ignored otherwise.
                 *
                 * @see vol3a[4.6.2(protection keys)]
                 */
		uint64 protectionkey : 4;
#define pte_64_protection_key_bit 59
#define pte_64_protection_key_flag 0x7800000000000000
#define pte_64_protection_key_mask 0x0f
#define pte_64_protection_key(_) (((_) >> 59) & 0x0f)

		/**
                 * [bit 63] if ia32_efer.nxe = 1, execute-disable (if 1, instruction fetches are not allowed from the 1-gbyte page
                 * controlled by this entry); otherwise, reserved (must be 0).
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 executedisable : 1;
#define pte_64_execute_disable_bit 63
#define pte_64_execute_disable_flag 0x8000000000000000
#define pte_64_execute_disable_mask 0x01
#define pte_64_execute_disable(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} pte_64;

/**
 * @brief format of a common page-table entry
 */
typedef union {
	struct {
		uint64 present : 1;
#define pt_entry_64_present_bit 0
#define pt_entry_64_present_flag 0x01
#define pt_entry_64_present_mask 0x01
#define pt_entry_64_present(_) (((_) >> 0) & 0x01)
		uint64 write : 1;
#define pt_entry_64_write_bit 1
#define pt_entry_64_write_flag 0x02
#define pt_entry_64_write_mask 0x01
#define pt_entry_64_write(_) (((_) >> 1) & 0x01)
		uint64 supervisor : 1;
#define pt_entry_64_supervisor_bit 2
#define pt_entry_64_supervisor_flag 0x04
#define pt_entry_64_supervisor_mask 0x01
#define pt_entry_64_supervisor(_) (((_) >> 2) & 0x01)
		uint64 pagelevelwritethrough : 1;
#define pt_entry_64_page_level_write_through_bit 3
#define pt_entry_64_page_level_write_through_flag 0x08
#define pt_entry_64_page_level_write_through_mask 0x01
#define pt_entry_64_page_level_write_through(_) (((_) >> 3) & 0x01)
		uint64 pagelevelcachedisable : 1;
#define pt_entry_64_page_level_cache_disable_bit 4
#define pt_entry_64_page_level_cache_disable_flag 0x10
#define pt_entry_64_page_level_cache_disable_mask 0x01
#define pt_entry_64_page_level_cache_disable(_) (((_) >> 4) & 0x01)
		uint64 accessed : 1;
#define pt_entry_64_accessed_bit 5
#define pt_entry_64_accessed_flag 0x20
#define pt_entry_64_accessed_mask 0x01
#define pt_entry_64_accessed(_) (((_) >> 5) & 0x01)
		uint64 dirty : 1;
#define pt_entry_64_dirty_bit 6
#define pt_entry_64_dirty_flag 0x40
#define pt_entry_64_dirty_mask 0x01
#define pt_entry_64_dirty(_) (((_) >> 6) & 0x01)
		uint64 largepage : 1;
#define pt_entry_64_large_page_bit 7
#define pt_entry_64_large_page_flag 0x80
#define pt_entry_64_large_page_mask 0x01
#define pt_entry_64_large_page(_) (((_) >> 7) & 0x01)
		uint64 global : 1;
#define pt_entry_64_global_bit 8
#define pt_entry_64_global_flag 0x100
#define pt_entry_64_global_mask 0x01
#define pt_entry_64_global(_) (((_) >> 8) & 0x01)

		/**
                 * [bits 11:9] ignored.
                 */
		uint64 ignored1 : 3;
#define pt_entry_64_ignored_1_bit 9
#define pt_entry_64_ignored_1_flag 0xe00
#define pt_entry_64_ignored_1_mask 0x07
#define pt_entry_64_ignored_1(_) (((_) >> 9) & 0x07)

		/**
                 * [bits 51:12] physical address of the 4-kbyte page referenced by this entry.
                 */
		uint64 pageframenumber : 40;
#define pt_entry_64_page_frame_number_bit 12
#define pt_entry_64_page_frame_number_flag 0xfffffffff000
#define pt_entry_64_page_frame_number_mask 0xfffffffff
#define pt_entry_64_page_frame_number(_) (((_) >> 12) & 0xfffffffff)

		/**
                 * [bits 58:52] ignored.
                 */
		uint64 ignored2 : 7;
#define pt_entry_64_ignored_2_bit 52
#define pt_entry_64_ignored_2_flag 0x7f0000000000000
#define pt_entry_64_ignored_2_mask 0x7f
#define pt_entry_64_ignored_2(_) (((_) >> 52) & 0x7f)
		uint64 protectionkey : 4;
#define pt_entry_64_protection_key_bit 59
#define pt_entry_64_protection_key_flag 0x7800000000000000
#define pt_entry_64_protection_key_mask 0x0f
#define pt_entry_64_protection_key(_) (((_) >> 59) & 0x0f)
		uint64 executedisable : 1;
#define pt_entry_64_execute_disable_bit 63
#define pt_entry_64_execute_disable_flag 0x8000000000000000
#define pt_entry_64_execute_disable_mask 0x01
#define pt_entry_64_execute_disable(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} pt_entry_64;

/**
 * @defgroup paging_structures_entry_count_64 \
 *           paging structures entry counts
 *
 * paging structures entry counts.
 * @{
 */
#define pml4e_entry_count_64 0x00000200
#define pdpte_entry_count_64 0x00000200
#define pde_entry_count_64 0x00000200
#define pte_entry_count_64 0x00000200
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup segment_descriptors \
 *           segment descriptors
 * @{
 */
/**
 * @brief pseudo-descriptor format (32-bit)
 *
 * @see vol3a[3.5.1(segment descriptor tables)] (reference)
 */
#pragma pack(push, 1)
typedef struct {
	/**
         * limit.
         */
	uint16 limit;

	/**
         * base address.
         */
	uint32 baseaddress;
} segment_descriptor_register_32;
#pragma pack(pop)

/**
 * @brief pseudo-descriptor format (64-bit)
 *
 * @see vol3a[3.5.1(segment descriptor tables)] (reference)
 */
#pragma pack(push, 1)
typedef struct {
	/**
         * limit.
         */
	uint16 limit;

	/**
         * base address.
         */
	uint64 baseaddress;
} segment_descriptor_register_64;
#pragma pack(pop)

/**
 * @brief segment access rights
 *
 * @see vol2a[3.2(instructions (a-l) | lar-load access rights byte)] (reference)
 */
typedef union {
	struct {
		uint32 reserved1 : 8;

		/**
                 * @brief type field
                 *
                 * [bits 11:8] indicates the segment or gate type and specifies the kinds of access that can be made to the segment and the
                 * direction of growth. the interpretation of this field depends on whether the descriptor type flag specifies an
                 * application (code or data) descriptor or a system descriptor. the encoding of the type field is different for code,
                 * data, and system descriptors.
                 *
                 * @see vol3a[3.4.5.1(code- and data-segment descriptor types)]
                 */
		uint32 type : 4;
#define segment_access_rights_type_bit 8
#define segment_access_rights_type_flag 0xf00
#define segment_access_rights_type_mask 0x0f
#define segment_access_rights_type(_) (((_) >> 8) & 0x0f)

		/**
                 * @brief s (descriptor type) flag
                 *
                 * [bit 12] specifies whether the segment descriptor is for a system segment (s flag is clear) or a code or data segment (s
                 * flag is set).
                 */
		uint32 descriptortype : 1;
#define segment_access_rights_descriptor_type_bit 12
#define segment_access_rights_descriptor_type_flag 0x1000
#define segment_access_rights_descriptor_type_mask 0x01
#define segment_access_rights_descriptor_type(_) (((_) >> 12) & 0x01)

		/**
                 * @brief dpl (descriptor privilege level) field
                 *
                 * [bits 14:13] specifies the privilege level of the segment. the privilege level can range from 0 to 3, with 0 being the
                 * most privileged level. the dpl is used to control access to the segment. see section 5.5, "privilege levels", for a
                 * description of the relationship of the dpl to the cpl of the executing code segment and the rpl of a segment selector.
                 */
		uint32 descriptorprivilegelevel : 2;
#define segment_access_rights_descriptor_privilege_level_bit 13
#define segment_access_rights_descriptor_privilege_level_flag 0x6000
#define segment_access_rights_descriptor_privilege_level_mask 0x03
#define segment_access_rights_descriptor_privilege_level(_) (((_) >> 13) & 0x03)

		/**
                 * @brief p (segment-present) flag
                 *
                 * [bit 15] indicates whether the segment is present in memory (set) or not present (clear). if this flag is clear, the
                 * processor generates a segment-not-present exception (\#np) when a segment selector that points to the segment descriptor
                 * is loaded into a segment register. memory management software can use this flag to control which segments are actually
                 * loaded into physical memory at a given time. it offers a control in addition to paging for managing virtual memory.
                 */
		uint32 present : 1;
#define segment_access_rights_present_bit 15
#define segment_access_rights_present_flag 0x8000
#define segment_access_rights_present_mask 0x01
#define segment_access_rights_present(_) (((_) >> 15) & 0x01)
		uint32 reserved2 : 4;

		/**
                 * @brief available bit
                 *
                 * [bit 20] bit 20 of the second doubleword of the segment descriptor is available for use by system software.
                 */
		uint32 system : 1;
#define segment_access_rights_system_bit 20
#define segment_access_rights_system_flag 0x100000
#define segment_access_rights_system_mask 0x01
#define segment_access_rights_system(_) (((_) >> 20) & 0x01)

		/**
                 * @brief l (64-bit code segment) flag
                 *
                 * [bit 21] in ia-32e mode, bit 21 of the second doubleword of the segment descriptor indicates whether a code segment
                 * contains native 64-bit code. a value of 1 indicates instructions in this code segment are executed in 64-bit mode. a
                 * value of 0 indicates the instructions in this code segment are executed in compatibility mode. if l-bit is set, then
                 * d-bit must be cleared. when not in ia-32e mode or for non-code segments, bit 21 is reserved and should always be set to
                 * 0.
                 */
		uint32 longmode : 1;
#define segment_access_rights_long_mode_bit 21
#define segment_access_rights_long_mode_flag 0x200000
#define segment_access_rights_long_mode_mask 0x01
#define segment_access_rights_long_mode(_) (((_) >> 21) & 0x01)

		/**
                 * @brief d/b (default operation size/default stack pointer size and/or upper bound) flag
                 *
                 * [bit 22] performs different functions depending on whether the segment descriptor is an executable code segment, an
                 * expand-down data segment, or a stack segment. (this flag should always be set to 1 for 32-bit code and data segments and
                 * to 0 for 16-bit code and data segments.)
                 * - executable code segment. the flag is called the d flag and it indicates the default length for effective addresses and
                 * operands referenced by instructions in the segment. if the flag is set, 32-bit addresses and 32-bit or 8-bit operands
                 * are assumed; if it is clear, 16-bit addresses and 16-bit or 8-bit operands are assumed. the instruction prefix 66h can
                 * be used to select an operand size other than the default, and the prefix 67h can be used select an address size other
                 * than the default.
                 * - stack segment (data segment pointed to by the ss register). the flag is called the b (big) flag and it specifies the
                 * size of the stack pointer used for implicit stack operations (such as pushes, pops, and calls). if the flag is set, a
                 * 32-bit stack pointer is used, which is stored in the 32-bit esp register; if the flag is clear, a 16-bit stack pointer
                 * is used, which is stored in the 16- bit sp register. if the stack segment is set up to be an expand-down data segment
                 * (described in the next paragraph), the b flag also specifies the upper bound of the stack segment.
                 * - expand-down data segment. the flag is called the b flag and it specifies the upper bound of the segment. if the flag
                 * is set, the upper bound is ffffffffh (4 gbytes); if the flag is clear, the upper bound is ffffh (64 kbytes).
                 */
		uint32 defaultbig : 1;
#define segment_access_rights_default_big_bit 22
#define segment_access_rights_default_big_flag 0x400000
#define segment_access_rights_default_big_mask 0x01
#define segment_access_rights_default_big(_) (((_) >> 22) & 0x01)

		/**
                 * @brief g (granularity) flag
                 *
                 * [bit 23] determines the scaling of the segment limit field. when the granularity flag is clear, the segment limit is
                 * interpreted in byte units; when flag is set, the segment limit is interpreted in 4-kbyte units. (this flag does not
                 * affect the granularity of the base address; it is always byte granular.) when the granularity flag is set, the twelve
                 * least significant bits of an offset are not tested when checking the offset against the segment limit. for example, when
                 * the granularity flag is set, a limit of 0 results in valid offsets from 0 to 4095.
                 */
		uint32 granularity : 1;
#define segment_access_rights_granularity_bit 23
#define segment_access_rights_granularity_flag 0x800000
#define segment_access_rights_granularity_mask 0x01
#define segment_access_rights_granularity(_) (((_) >> 23) & 0x01)
		uint32 reserved3 : 8;
	};

	uint32 flags;
} segment_access_rights;

/**
 * @brief general segment descriptor (32-bit)
 *
 * a segment descriptor is a data structure in a gdt or ldt that provides the processor with the size and location of a
 * segment, as well as access control and status information. segment descriptors are typically created by compilers,
 * linkers, loaders, or the operating system or executive, but not application programs.
 *
 * @see vol3a[5.2(fields and flags used for segment-level and page-level protection)]
 * @see vol3a[5.2.1(code-segment descriptor in 64-bit mode)]
 * @see vol3a[5.8.3(call gates)]
 * @see vol3a[6.11(idt descriptors)]
 * @see vol3a[6.14.1(64-bit mode idt)]
 * @see vol3a[7.2.2(tss descriptor)]
 * @see vol3a[7.2.3(tss descriptor in 64-bit mode)]
 * @see vol3a[7.2.5(task-gate descriptor)]
 * @see vol3a[3.4.5(segment descriptors)] (reference)
 */
typedef struct {
	/**
         * @brief segment limit field (15:00)
         *
         * specifies the size of the segment. the processor puts together the two segment limit fields to form a 20-bit value. the
         * processor interprets the segment limit in one of two ways, depending on the setting of the g (granularity) flag:
         * - if the granularity flag is clear, the segment size can range from 1 byte to 1 mbyte, in byte increments.
         * - if the granularity flag is set, the segment size can range from 4 kbytes to 4 gbytes, in 4-kbyte increments.
         * the processor uses the segment limit in two different ways, depending on whether the segment is an expand-up or an
         * expand-down segment. for expand-up segments, the offset in a logical address can range from 0 to the segment limit.
         * offsets greater than the segment limit generate general-protection exceptions (\#gp, for all segments other than ss) or
         * stack-fault exceptions (\#ss for the ss segment). for expand-down segments, the segment limit has the reverse function;
         * the offset can range from the segment limit plus 1 to ffffffffh or ffffh, depending on the setting of the b flag.
         * offsets less than or equal to the segment limit generate general-protection exceptions or stack-fault exceptions.
         * decreasing the value in the segment limit field for an expanddown segment allocates new memory at the bottom of the
         * segment's address space, rather than at the top. ia-32 architecture stacks always grow downwards, making this mechanism
         * convenient for expandable stacks.
         *
         * @see vol3a[3.4.5.1(code- and data-segment descriptor types)]
         */
	uint16 segmentlimitlow;

	/**
         * @brief base address field (15:00)
         *
         * defines the location of byte 0 of the segment within the 4-gbyte linear address space. the processor puts together the
         * three base address fields to form a single 32-bit value. segment base addresses should be aligned to 16-byte boundaries.
         * although 16-byte alignment is not required, this alignment allows programs to maximize performance by aligning code and
         * data on 16-byte boundaries.
         */
	uint16 baseaddresslow;
	/**
         * @brief segment descriptor fields
         */
	union {
		struct {
			/**
                         * [bits 7:0] base address field (23:16); see description of $base_low for more details.
                         */
			uint32 baseaddressmiddle : 8;
#define segment__base_address_middle_bit 0
#define segment__base_address_middle_flag 0xff
#define segment__base_address_middle_mask 0xff
#define segment__base_address_middle(_) (((_) >> 0) & 0xff)

			/**
                         * @brief type field
                         *
                         * [bits 11:8] indicates the segment or gate type and specifies the kinds of access that can be made to the segment and the
                         * direction of growth. the interpretation of this field depends on whether the descriptor type flag specifies an
                         * application (code or data) descriptor or a system descriptor. the encoding of the type field is different for code,
                         * data, and system descriptors.
                         *
                         * @see vol3a[3.4.5.1(code- and data-segment descriptor types)]
                         */
			uint32 type : 4;
#define segment__type_bit 8
#define segment__type_flag 0xf00
#define segment__type_mask 0x0f
#define segment__type(_) (((_) >> 8) & 0x0f)

			/**
                         * @brief s (descriptor type) flag
                         *
                         * [bit 12] specifies whether the segment descriptor is for a system segment (s flag is clear) or a code or data segment (s
                         * flag is set).
                         */
			uint32 descriptortype : 1;
#define segment__descriptor_type_bit 12
#define segment__descriptor_type_flag 0x1000
#define segment__descriptor_type_mask 0x01
#define segment__descriptor_type(_) (((_) >> 12) & 0x01)

			/**
                         * @brief dpl (descriptor privilege level) field
                         *
                         * [bits 14:13] specifies the privilege level of the segment. the privilege level can range from 0 to 3, with 0 being the
                         * most privileged level. the dpl is used to control access to the segment. see section 5.5, "privilege levels", for a
                         * description of the relationship of the dpl to the cpl of the executing code segment and the rpl of a segment selector.
                         */
			uint32 descriptorprivilegelevel : 2;
#define segment__descriptor_privilege_level_bit 13
#define segment__descriptor_privilege_level_flag 0x6000
#define segment__descriptor_privilege_level_mask 0x03
#define segment__descriptor_privilege_level(_) (((_) >> 13) & 0x03)

			/**
                         * @brief p (segment-present) flag
                         *
                         * [bit 15] indicates whether the segment is present in memory (set) or not present (clear). if this flag is clear, the
                         * processor generates a segment-not-present exception (\#np) when a segment selector that points to the segment descriptor
                         * is loaded into a segment register. memory management software can use this flag to control which segments are actually
                         * loaded into physical memory at a given time. it offers a control in addition to paging for managing virtual memory.
                         */
			uint32 present : 1;
#define segment__present_bit 15
#define segment__present_flag 0x8000
#define segment__present_mask 0x01
#define segment__present(_) (((_) >> 15) & 0x01)

			/**
                         * [bits 19:16] segment limit field (19:16); see description of $limit_low for more details.
                         */
			uint32 segmentlimithigh : 4;
#define segment__segment_limit_high_bit 16
#define segment__segment_limit_high_flag 0xf0000
#define segment__segment_limit_high_mask 0x0f
#define segment__segment_limit_high(_) (((_) >> 16) & 0x0f)

			/**
                         * @brief available bit
                         *
                         * [bit 20] bit 20 of the second doubleword of the segment descriptor is available for use by system software.
                         */
			uint32 system : 1;
#define segment__system_bit 20
#define segment__system_flag 0x100000
#define segment__system_mask 0x01
#define segment__system(_) (((_) >> 20) & 0x01)

			/**
                         * @brief l (64-bit code segment) flag
                         *
                         * [bit 21] in ia-32e mode, bit 21 of the second doubleword of the segment descriptor indicates whether a code segment
                         * contains native 64-bit code. a value of 1 indicates instructions in this code segment are executed in 64-bit mode. a
                         * value of 0 indicates the instructions in this code segment are executed in compatibility mode. if l-bit is set, then
                         * d-bit must be cleared. when not in ia-32e mode or for non-code segments, bit 21 is reserved and should always be set to
                         * 0.
                         */
			uint32 longmode : 1;
#define segment__long_mode_bit 21
#define segment__long_mode_flag 0x200000
#define segment__long_mode_mask 0x01
#define segment__long_mode(_) (((_) >> 21) & 0x01)

			/**
                         * @brief d/b (default operation size/default stack pointer size and/or upper bound) flag
                         *
                         * [bit 22] performs different functions depending on whether the segment descriptor is an executable code segment, an
                         * expand-down data segment, or a stack segment. (this flag should always be set to 1 for 32-bit code and data segments and
                         * to 0 for 16-bit code and data segments.)
                         * - executable code segment. the flag is called the d flag and it indicates the default length for effective addresses and
                         * operands referenced by instructions in the segment. if the flag is set, 32-bit addresses and 32-bit or 8-bit operands
                         * are assumed; if it is clear, 16-bit addresses and 16-bit or 8-bit operands are assumed. the instruction prefix 66h can
                         * be used to select an operand size other than the default, and the prefix 67h can be used select an address size other
                         * than the default.
                         * - stack segment (data segment pointed to by the ss register). the flag is called the b (big) flag and it specifies the
                         * size of the stack pointer used for implicit stack operations (such as pushes, pops, and calls). if the flag is set, a
                         * 32-bit stack pointer is used, which is stored in the 32-bit esp register; if the flag is clear, a 16-bit stack pointer
                         * is used, which is stored in the 16- bit sp register. if the stack segment is set up to be an expand-down data segment
                         * (described in the next paragraph), the b flag also specifies the upper bound of the stack segment.
                         * - expand-down data segment. the flag is called the b flag and it specifies the upper bound of the segment. if the flag
                         * is set, the upper bound is ffffffffh (4 gbytes); if the flag is clear, the upper bound is ffffh (64 kbytes).
                         */
			uint32 defaultbig : 1;
#define segment__default_big_bit 22
#define segment__default_big_flag 0x400000
#define segment__default_big_mask 0x01
#define segment__default_big(_) (((_) >> 22) & 0x01)

			/**
                         * @brief g (granularity) flag
                         *
                         * [bit 23] determines the scaling of the segment limit field. when the granularity flag is clear, the segment limit is
                         * interpreted in byte units; when flag is set, the segment limit is interpreted in 4-kbyte units. (this flag does not
                         * affect the granularity of the base address; it is always byte granular.) when the granularity flag is set, the twelve
                         * least significant bits of an offset are not tested when checking the offset against the segment limit. for example, when
                         * the granularity flag is set, a limit of 0 results in valid offsets from 0 to 4095.
                         */
			uint32 granularity : 1;
#define segment__granularity_bit 23
#define segment__granularity_flag 0x800000
#define segment__granularity_mask 0x01
#define segment__granularity(_) (((_) >> 23) & 0x01)

			/**
                         * [bits 31:24] base address field (31:24); see description of $base_low for more details.
                         */
			uint32 baseaddresshigh : 8;
#define segment__base_address_high_bit 24
#define segment__base_address_high_flag 0xff000000
#define segment__base_address_high_mask 0xff
#define segment__base_address_high(_) (((_) >> 24) & 0xff)
		};

		uint32 flags;
	};

} segment_descriptor_32;

/**
 * @brief general segment descriptor (64-bit)
 *
 * a segment descriptor is a data structure in a gdt or ldt that provides the processor with the size and location of a
 * segment, as well as access control and status information. segment descriptors are typically created by compilers,
 * linkers, loaders, or the operating system or executive, but not application programs.
 *
 * @see vol3a[3.4.5(segment descriptors)] (reference)
 */
typedef struct {
	/**
         * @brief segment limit field (15:00)
         *
         * specifies the size of the segment. the processor puts together the two segment limit fields to form a 20-bit value. the
         * processor interprets the segment limit in one of two ways, depending on the setting of the g (granularity) flag:
         * - if the granularity flag is clear, the segment size can range from 1 byte to 1 mbyte, in byte increments.
         * - if the granularity flag is set, the segment size can range from 4 kbytes to 4 gbytes, in 4-kbyte increments.
         * the processor uses the segment limit in two different ways, depending on whether the segment is an expand-up or an
         * expand-down segment. for expand-up segments, the offset in a logical address can range from 0 to the segment limit.
         * offsets greater than the segment limit generate general-protection exceptions (\#gp, for all segments other than ss) or
         * stack-fault exceptions (\#ss for the ss segment). for expand-down segments, the segment limit has the reverse function;
         * the offset can range from the segment limit plus 1 to ffffffffh or ffffh, depending on the setting of the b flag.
         * offsets less than or equal to the segment limit generate general-protection exceptions or stack-fault exceptions.
         * decreasing the value in the segment limit field for an expanddown segment allocates new memory at the bottom of the
         * segment's address space, rather than at the top. ia-32 architecture stacks always grow downwards, making this mechanism
         * convenient for expandable stacks.
         *
         * @see vol3a[3.4.5.1(code- and data-segment descriptor types)]
         */
	uint16 segmentlimitlow;

	/**
         * @brief base address field (15:00)
         *
         * defines the location of byte 0 of the segment within the 4-gbyte linear address space. the processor puts together the
         * three base address fields to form a single 32-bit value. segment base addresses should be aligned to 16-byte boundaries.
         * although 16-byte alignment is not required, this alignment allows programs to maximize performance by aligning code and
         * data on 16-byte boundaries.
         */
	uint16 baseaddresslow;
	/**
         * @brief segment descriptor fields
         */
	union {
		struct {
			/**
                         * [bits 7:0] base address field (23:16); see description of $base_low for more details.
                         */
			uint32 baseaddressmiddle : 8;
#define segment__base_address_middle_bit 0
#define segment__base_address_middle_flag 0xff
#define segment__base_address_middle_mask 0xff
#define segment__base_address_middle(_) (((_) >> 0) & 0xff)

			/**
                         * @brief type field
                         *
                         * [bits 11:8] indicates the segment or gate type and specifies the kinds of access that can be made to the segment and the
                         * direction of growth. the interpretation of this field depends on whether the descriptor type flag specifies an
                         * application (code or data) descriptor or a system descriptor. the encoding of the type field is different for code,
                         * data, and system descriptors.
                         *
                         * @see vol3a[3.4.5.1(code- and data-segment descriptor types)]
                         */
			uint32 type : 4;
#define segment__type_bit 8
#define segment__type_flag 0xf00
#define segment__type_mask 0x0f
#define segment__type(_) (((_) >> 8) & 0x0f)

			/**
                         * @brief s (descriptor type) flag
                         *
                         * [bit 12] specifies whether the segment descriptor is for a system segment (s flag is clear) or a code or data segment (s
                         * flag is set).
                         */
			uint32 descriptortype : 1;
#define segment__descriptor_type_bit 12
#define segment__descriptor_type_flag 0x1000
#define segment__descriptor_type_mask 0x01
#define segment__descriptor_type(_) (((_) >> 12) & 0x01)

			/**
                         * @brief dpl (descriptor privilege level) field
                         *
                         * [bits 14:13] specifies the privilege level of the segment. the privilege level can range from 0 to 3, with 0 being the
                         * most privileged level. the dpl is used to control access to the segment. see section 5.5, "privilege levels", for a
                         * description of the relationship of the dpl to the cpl of the executing code segment and the rpl of a segment selector.
                         */
			uint32 descriptorprivilegelevel : 2;
#define segment__descriptor_privilege_level_bit 13
#define segment__descriptor_privilege_level_flag 0x6000
#define segment__descriptor_privilege_level_mask 0x03
#define segment__descriptor_privilege_level(_) (((_) >> 13) & 0x03)

			/**
                         * @brief p (segment-present) flag
                         *
                         * [bit 15] indicates whether the segment is present in memory (set) or not present (clear). if this flag is clear, the
                         * processor generates a segment-not-present exception (\#np) when a segment selector that points to the segment descriptor
                         * is loaded into a segment register. memory management software can use this flag to control which segments are actually
                         * loaded into physical memory at a given time. it offers a control in addition to paging for managing virtual memory.
                         */
			uint32 present : 1;
#define segment__present_bit 15
#define segment__present_flag 0x8000
#define segment__present_mask 0x01
#define segment__present(_) (((_) >> 15) & 0x01)

			/**
                         * [bits 19:16] segment limit field (19:16); see description of $limit_low for more details.
                         */
			uint32 segmentlimithigh : 4;
#define segment__segment_limit_high_bit 16
#define segment__segment_limit_high_flag 0xf0000
#define segment__segment_limit_high_mask 0x0f
#define segment__segment_limit_high(_) (((_) >> 16) & 0x0f)

			/**
                         * @brief available bit
                         *
                         * [bit 20] bit 20 of the second doubleword of the segment descriptor is available for use by system software.
                         */
			uint32 system : 1;
#define segment__system_bit 20
#define segment__system_flag 0x100000
#define segment__system_mask 0x01
#define segment__system(_) (((_) >> 20) & 0x01)

			/**
                         * @brief l (64-bit code segment) flag
                         *
                         * [bit 21] in ia-32e mode, bit 21 of the second doubleword of the segment descriptor indicates whether a code segment
                         * contains native 64-bit code. a value of 1 indicates instructions in this code segment are executed in 64-bit mode. a
                         * value of 0 indicates the instructions in this code segment are executed in compatibility mode. if l-bit is set, then
                         * d-bit must be cleared. when not in ia-32e mode or for non-code segments, bit 21 is reserved and should always be set to
                         * 0.
                         */
			uint32 longmode : 1;
#define segment__long_mode_bit 21
#define segment__long_mode_flag 0x200000
#define segment__long_mode_mask 0x01
#define segment__long_mode(_) (((_) >> 21) & 0x01)

			/**
                         * @brief d/b (default operation size/default stack pointer size and/or upper bound) flag
                         *
                         * [bit 22] performs different functions depending on whether the segment descriptor is an executable code segment, an
                         * expand-down data segment, or a stack segment. (this flag should always be set to 1 for 32-bit code and data segments and
                         * to 0 for 16-bit code and data segments.)
                         * - executable code segment. the flag is called the d flag and it indicates the default length for effective addresses and
                         * operands referenced by instructions in the segment. if the flag is set, 32-bit addresses and 32-bit or 8-bit operands
                         * are assumed; if it is clear, 16-bit addresses and 16-bit or 8-bit operands are assumed. the instruction prefix 66h can
                         * be used to select an operand size other than the default, and the prefix 67h can be used select an address size other
                         * than the default.
                         * - stack segment (data segment pointed to by the ss register). the flag is called the b (big) flag and it specifies the
                         * size of the stack pointer used for implicit stack operations (such as pushes, pops, and calls). if the flag is set, a
                         * 32-bit stack pointer is used, which is stored in the 32-bit esp register; if the flag is clear, a 16-bit stack pointer
                         * is used, which is stored in the 16- bit sp register. if the stack segment is set up to be an expand-down data segment
                         * (described in the next paragraph), the b flag also specifies the upper bound of the stack segment.
                         * - expand-down data segment. the flag is called the b flag and it specifies the upper bound of the segment. if the flag
                         * is set, the upper bound is ffffffffh (4 gbytes); if the flag is clear, the upper bound is ffffh (64 kbytes).
                         */
			uint32 defaultbig : 1;
#define segment__default_big_bit 22
#define segment__default_big_flag 0x400000
#define segment__default_big_mask 0x01
#define segment__default_big(_) (((_) >> 22) & 0x01)

			/**
                         * @brief g (granularity) flag
                         *
                         * [bit 23] determines the scaling of the segment limit field. when the granularity flag is clear, the segment limit is
                         * interpreted in byte units; when flag is set, the segment limit is interpreted in 4-kbyte units. (this flag does not
                         * affect the granularity of the base address; it is always byte granular.) when the granularity flag is set, the twelve
                         * least significant bits of an offset are not tested when checking the offset against the segment limit. for example, when
                         * the granularity flag is set, a limit of 0 results in valid offsets from 0 to 4095.
                         */
			uint32 granularity : 1;
#define segment__granularity_bit 23
#define segment__granularity_flag 0x800000
#define segment__granularity_mask 0x01
#define segment__granularity(_) (((_) >> 23) & 0x01)

			/**
                         * [bits 31:24] base address field (31:24); see description of $base_low for more details.
                         */
			uint32 baseaddresshigh : 8;
#define segment__base_address_high_bit 24
#define segment__base_address_high_flag 0xff000000
#define segment__base_address_high_mask 0xff
#define segment__base_address_high(_) (((_) >> 24) & 0xff)
		};

		uint32 flags;
	};

	/**
         * base address field (32:63); see description of $base_low for more details.
         */
	uint32 baseaddressupper;

	/**
         * base address field (32:63); see description of $base_low for more details.
         */
	uint32 mustbezero;
} segment_descriptor_64;

#define segment_descriptor_type_system 0x00000000
#define segment_descriptor_type_code_or_data 0x00000001
/**
 * @defgroup segment_descriptor_code_and_data_type \
 *           code- and data-segment descriptor types
 *
 * when the s (descriptor type) flag in a segment descriptor is set, the descriptor is for either a code or a data segment.
 * the highest order bit of the type field (bit 11 of the second double word of the segment descriptor) then determines
 * whether the descriptor is for a data segment (clear) or a code segment (set). for data segments, the three low-order
 * bits of the type field (bits 8, 9, and 10) are interpreted as accessed (a), write-enable (w), and expansion-direction
 * (e). see table 3-1 for a description of the encoding of the bits in the type field for code and data segments. data
 * segments can be read-only or read/write segments, depending on the setting of the write-enable bit.
 *
 * @see vol3a[3.4.5.1(code- and data-segment descriptor types)] (reference)
 * @{
 */
/**
 * read-only.
 */
#define segment_descriptor_type_data_read_only 0x00000000

/**
 * data read-only, accessed.
 */
#define segment_descriptor_type_data_read_only_accessed 0x00000001

/**
 * data read/write.
 */
#define segment_descriptor_type_data_read_write 0x00000002

/**
 * data read/write, accessed.
 */
#define segment_descriptor_type_data_read_write_accessed 0x00000003

/**
 * data read-only, expand-down.
 */
#define segment_descriptor_type_data_read_only_expand_down 0x00000004

/**
 * data read-only, expand-down, accessed.
 */
#define segment_descriptor_type_data_read_only_expand_down_accessed 0x00000005

/**
 * data read/write, expand-down.
 */
#define segment_descriptor_type_data_read_write_expand_down 0x00000006

/**
 * data read/write, expand-down, accessed.
 */
#define segment_descriptor_type_data_read_write_expand_down_accessed 0x00000007

/**
 * code execute-only.
 */
#define segment_descriptor_type_code_execute_only 0x00000008

/**
 * code execute-only, accessed.
 */
#define segment_descriptor_type_code_execute_only_accessed 0x00000009

/**
 * code execute/read.
 */
#define segment_descriptor_type_code_execute_read 0x0000000a

/**
 * code execute/read, accessed.
 */
#define segment_descriptor_type_code_execute_read_accessed 0x0000000b

/**
 * code execute-only, conforming.
 */
#define segment_descriptor_type_code_execute_only_conforming 0x0000000c

/**
 * code execute-only, conforming, accessed.
 */
#define segment_descriptor_type_code_execute_only_conforming_accessed 0x0000000d

/**
 * code execute/read, conforming.
 */
#define segment_descriptor_type_code_execute_read_conforming 0x0000000e

/**
 * code execute/read, conforming, accessed.
 */
#define segment_descriptor_type_code_execute_read_conforming_accessed 0x0000000f
/**
 * @}
 */

/**
 * @defgroup segment_descriptor_system_type \
 *           system descriptor types
 *
 * when the s (descriptor type) flag in a segment descriptor is clear, the descriptor type is a system descriptor. the
 * processor recognizes the following types of system descriptors:
 * - local descriptor-table (ldt) segment descriptor.
 * - task-state segment (tss) descriptor.
 * - call-gate descriptor.
 * - interrupt-gate descriptor.
 * - trap-gate descriptor.
 * - task-gate descriptor.
 * these descriptor types fall into two categories: system-segment descriptors and gate descriptors. systemsegment
 * descriptors point to system segments (ldt and tss segments). gate descriptors are in themselves "gates," which hold
 * pointers to procedure entry points in code segments (call, interrupt, and trap gates) or which hold segment selectors
 * for tss's (task gates).
 *
 * @see vol3a[3.5(system descriptor types)] (reference)
 * @{
 */
/**
 * - 32-bit mode: reserved
 * - ia-32e mode: reserved
 */
#define segment_descriptor_type_reserved_1 0x00000000

/**
 * - 32-bit mode: 16-bit tss (available)
 * - ia-32e mode: reserved
 */
#define segment_descriptor_type_tss_16_available 0x00000001

/**
 * - 32-bit mode: ldt
 * - ia-32e mode: ldt
 */
#define segment_descriptor_type_ldt 0x00000002

/**
 * - 32-bit mode: 16-bit tss (busy)
 * - ia-32e mode: reserved
 */
#define segment_descriptor_type_tss_16_busy 0x00000003

/**
 * - 32-bit mode: 16-bit call gate
 * - ia-32e mode: reserved
 */
#define segment_descriptor_type_call_gate_16 0x00000004

/**
 * - 32-bit mode: task gate
 * - ia-32e mode: reserved
 */
#define segment_descriptor_type_task_gate 0x00000005

/**
 * - 32-bit mode: 16-bit interrupt gate
 * - ia-32e mode: reserved
 */
#define segment_descriptor_type_interrupt_gate_16 0x00000006

/**
 * - 32-bit mode: 16-bit trap gate
 * - ia-32e mode: reserved
 */
#define segment_descriptor_type_trap_gate_16 0x00000007

/**
 * - 32-bit mode: reserved
 * - ia-32e mode: reserved
 */
#define segment_descriptor_type_reserved_2 0x00000008

/**
 * - 32-bit mode: 32-bit tss (available)
 * - ia-32e mode: 64-bit tss (available)
 */
#define segment_descriptor_type_tss_available 0x00000009

/**
 * - 32-bit mode: reserved
 * - ia-32e mode: reserved
 */
#define segment_descriptor_type_reserved_3 0x0000000a

/**
 * - 32-bit mode: 32-bit tss (busy)
 * - ia-32e mode: 64-bit tss (busy)
 */
#define segment_descriptor_type_tss_busy 0x0000000b

/**
 * - 32-bit mode: 32-bit call gate
 * - ia-32e mode: 64-bit call gate
 */
#define segment_descriptor_type_call_gate 0x0000000c

/**
 * - 32-bit mode: reserved
 * - ia-32e mode: reserved
 */
#define segment_descriptor_type_reserved_4 0x0000000d

/**
 * - 32-bit mode: 32-bit interrupt gate
 * - ia-32e mode: 64-bit interrupt gate
 */
#define segment_descriptor_type_interrupt_gate 0x0000000e

/**
 * - 32-bit mode: 32-bit trap gate
 * - ia-32e mode: 64-bit trap gate
 */
#define segment_descriptor_type_trap_gate 0x0000000f
/**
 * @}
 */

/**
 * @brief a segment selector is a 16-bit identifier for a segment. it does not point directly to the segment, but instead
 *        points to the segment descriptor that defines the segment
 *
 * @see vol3a[3.4.2(segment selectors)] (reference)
 */
typedef union {
	struct {
		/**
                 * [bits 1:0] specifies the privilege level of the selector. the privilege level can range from 0 to 3, with 0 being the
                 * most privileged level.
                 *
                 * @see vol3a[5.5(privilege levels)]
                 */
		uint16 requestprivilegelevel : 2;
#define segment_selector_request_privilege_level_bit 0
#define segment_selector_request_privilege_level_flag 0x03
#define segment_selector_request_privilege_level_mask 0x03
#define segment_selector_request_privilege_level(_) (((_) >> 0) & 0x03)

		/**
                 * [bit 2] specifies the descriptor table to use: clearing this flag selects the gdt; setting this flag selects the current
                 * ldt.
                 */
		uint16 table : 1;
#define segment_selector_table_bit 2
#define segment_selector_table_flag 0x04
#define segment_selector_table_mask 0x01
#define segment_selector_table(_) (((_) >> 2) & 0x01)

		/**
                 * [bits 15:3] selects one of 8192 descriptors in the gdt or ldt. the processor multiplies the index value by 8 (the number
                 * of bytes in a segment descriptor) and adds the result to the base address of the gdt or ldt (from the gdtr or ldtr
                 * register, respectively).
                 */
		uint16 index : 13;
#define segment_selector_index_bit 3
#define segment_selector_index_flag 0xfff8
#define segment_selector_index_mask 0x1fff
#define segment_selector_index(_) (((_) >> 3) & 0x1fff)
	};

	uint16 flags;
} segment_selector;

/**
 * @}
 */

/**
 * @defgroup vmx \
 *           vmx
 * @{
 */
/**
 * @{
 */
/**
 * @defgroup vmx_basic_exit_reasons \
 *           vmx basic exit reasons
 *
 * vmx basic exit reasons.
 *
 * @see vol3d[c(vmx basic exit reasons)] (reference)
 * @{
 */
/**
 * @brief exception or non-maskable interrupt (nmi)
 *
 * either:
 * -# guest software caused an exception and the bit in the exception bitmap associated with exception's list was 1. this
 * case includes executions of bound that cause \#br, executions of int1 (they cause \#db), executions of int3 (they cause
 * \#bp), executions of into that cause \#of, and executions of ud0, ud1, and ud2 (they cause \#ud).
 * -# an nmi was delivered to the logical processor and the "nmi exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_exception_or_nmi 0x00000000

/**
 * @brief external interrupt
 *
 * an external interrupt arrived and the "external-interrupt exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_external_interrupt 0x00000001

/**
 * @brief triple fault
 *
 * the logical processor encountered an exception while attempting to call the double-fault handler and that exception did
 * not itself cause a vm exit due to the exception bitmap.
 */
#define vmx_exit_reason_triple_fault 0x00000002

/**
 * @brief init signal
 *
 * an init signal arrived.
 */
#define vmx_exit_reason_init_signal 0x00000003

/**
 * @brief start-up ipi (sipi)
 *
 * a sipi arrived while the logical processor was in the "wait-for-sipi" state.
 */
#define vmx_exit_reason_startup_ipi 0x00000004

/**
 * @brief i/o system-management interrupt (smi)
 *
 * an smi arrived immediately after retirement of an i/o instruction and caused an smm vm exit.
 *
 * @see vol3c[34.15.2(smm vm exits)]
 */
#define vmx_exit_reason_io_smi 0x00000005

/**
 * @brief other smi
 *
 * an smi arrived and caused an smm vm exit but not immediately after retirement of an i/o instruction.
 *
 * @see vol3c[34.15.2(smm vm exits)]
 */
#define vmx_exit_reason_smi 0x00000006

/**
 * @brief interrupt window exiting
 *
 * at the beginning of an instruction, rflags.if was 1; events were not blocked by sti or by mov ss; and the
 * "interrupt-window exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_interrupt_window 0x00000007

/**
 * @brief nmi window exiting
 *
 * at the beginning of an instruction, there was no virtual-nmi blocking; events were not blocked by mov ss; and the
 * "nmi-window exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_nmi_window 0x00000008

/**
 * @brief task switch
 *
 * guest software attempted a task switch.
 */
#define vmx_exit_reason_task_switch 0x00000009

/**
 * @brief cpuid
 *
 * guest software attempted to execute cpuid.
 */
#define vmx_exit_reason_execute_cpuid 0x0000000a

/**
 * @brief getsec
 *
 * guest software attempted to execute getsec.
 */
#define vmx_exit_reason_execute_getsec 0x0000000b

/**
 * @brief hlt
 *
 * guest software attempted to execute hlt and the "hlt exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_execute_hlt 0x0000000c

/**
 * @brief invd
 *
 * guest software attempted to execute invd.
 */
#define vmx_exit_reason_execute_invd 0x0000000d

/**
 * @brief invlpg
 *
 * guest software attempted to execute invlpg and the "invlpg exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_execute_invlpg 0x0000000e

/**
 * @brief rdpmc
 *
 * guest software attempted to execute rdpmc and the "rdpmc exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_execute_rdpmc 0x0000000f

/**
 * @brief rdtsc
 *
 * guest software attempted to execute rdtsc and the "rdtsc exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_execute_rdtsc 0x00000010

/**
 * @brief rsm in smm
 *
 * guest software attempted to execute rsm in smm.
 */
#define vmx_exit_reason_execute_rsm_in_smm 0x00000011

/**
 * @brief vmcall
 *
 * vmcall was executed either by guest software (causing an ordinary vm exit) or by the executive monitor (causing an smm
 * vm exit).
 *
 * @see vol3c[34.15.2(smm vm exits)]
 */
#define vmx_exit_reason_execute_vmcall 0x00000012

/**
 * @brief vmclear
 *
 * guest software attempted to execute vmclear.
 */
#define vmx_exit_reason_execute_vmclear 0x00000013

/**
 * @brief vmlaunch
 *
 * guest software attempted to execute vmlaunch.
 */
#define vmx_exit_reason_execute_vmlaunch 0x00000014

/**
 * @brief vmptrld
 *
 * guest software attempted to execute vmptrld.
 */
#define vmx_exit_reason_execute_vmptrld 0x00000015

/**
 * @brief vmptrst
 *
 * guest software attempted to execute vmptrst.
 */
#define vmx_exit_reason_execute_vmptrst 0x00000016

/**
 * @brief vmread
 *
 * guest software attempted to execute vmread.
 */
#define vmx_exit_reason_execute_vmread 0x00000017

/**
 * @brief vmresume
 *
 * guest software attempted to execute vmresume.
 */
#define vmx_exit_reason_execute_vmresume 0x00000018

/**
 * @brief vmwrite
 *
 * guest software attempted to execute vmwrite.
 */
#define vmx_exit_reason_execute_vmwrite 0x00000019

/**
 * @brief vmxoff
 *
 * guest software attempted to execute vmxoff.
 */
#define vmx_exit_reason_execute_vmxoff 0x0000001a

/**
 * @brief vmxon
 *
 * guest software attempted to execute vmxon.
 */
#define vmx_exit_reason_execute_vmxon 0x0000001b

/**
 * @brief control-register accesses
 *
 * guest software attempted to access cr0, cr3, cr4, or cr8 using clts, lmsw, or mov cr and the vm-execution control fields
 * indicate that a vm exit should occur. this basic exit reason is not used for trap-like vm exits following executions of
 * the mov to cr8 instruction when the "use tpr shadow" vm-execution control is 1. such vm exits instead use basic exit
 * reason 43.
 *
 * @see vol3c[25.1(instructions that cause vm exits)]
 */
#define vmx_exit_reason_mov_cr 0x0000001c

/**
 * @brief debug-register accesses
 *
 * guest software attempted a mov to or from a debug register and the "mov-dr exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_mov_dr 0x0000001d

/**
 * @brief i/o instruction
 *
 * guest software attempted to execute an i/o instruction and either:
 * -# the "use i/o bitmaps" vm-execution control was 0 and the "unconditional i/o exiting" vm-execution control was 1.
 * -# the "use i/o bitmaps" vm-execution control was 1 and a bit in the i/o bitmap associated with one of the ports
 * accessed by the i/o instruction was 1.
 */
#define vmx_exit_reason_execute_io_instruction 0x0000001e

/**
 * @brief rdmsr
 *
 * guest software attempted to execute rdmsr and either:
 * -# the "use msr bitmaps" vm-execution control was 0.
 * -# the value of rcx is neither in the range 00000000h - 00001fffh nor in the range c0000000h - c0001fffh.
 * -# the value of rcx was in the range 00000000h - 00001fffh and the nth bit in read bitmap for low msrs is 1, where n was
 * the value of rcx.
 * -# the value of rcx is in the range c0000000h - c0001fffh and the nth bit in read bitmap for high msrs is 1, where n is
 * the value of rcx & 00001fffh.
 */
#define vmx_exit_reason_execute_rdmsr 0x0000001f

/**
 * @brief wrmsr
 *
 * guest software attempted to execute wrmsr and either:
 * -# the "use msr bitmaps" vm-execution control was 0.
 * -# the value of rcx is neither in the range 00000000h - 00001fffh nor in the range c0000000h - c0001fffh.
 * -# the value of rcx was in the range 00000000h - 00001fffh and the nth bit in write bitmap for low msrs is 1, where n
 * was the value of rcx.
 * -# the value of rcx is in the range c0000000h - c0001fffh and the nth bit in write bitmap for high msrs is 1, where n is
 * the value of rcx & 00001fffh.
 */
#define vmx_exit_reason_execute_wrmsr 0x00000020

/**
 * @brief vm-entry failure due to invalid guest state
 *
 * a vm entry failed one of the checks identified in section 26.3.1.
 */
#define vmx_exit_reason_error_invalid_guest_state 0x00000021

/**
 * @brief vm-entry failure due to msr loading
 *
 * a vm entry failed in an attempt to load msrs. see section 26.4.
 */
#define vmx_exit_reason_error_msr_load 0x00000022

/**
 * @brief guest software executed mwait
 *
 * guest software attempted to execute mwait and the "mwait exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_execute_mwait 0x00000024

/**
 * @brief vm-exit due to monitor trap flag
 *
 * a vm entry occurred due to the 1-setting of the "monitor trap flag" vm-execution control and injection of an mtf vm exit
 * as part of vm entry.
 *
 * @see vol3c[25.5.2(monitor trap flag)]
 */
#define vmx_exit_reason_monitor_trap_flag 0x00000025

/**
 * @brief guest software attempted to execute monitor
 *
 * guest software attempted to execute monitor and the "monitor exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_execute_monitor 0x00000027

/**
 * @brief guest software attempted to execute pause
 *
 * either guest software attempted to execute pause and the "pause exiting" vm-execution control was 1 or the "pause-loop
 * exiting" vm-execution control was 1 and guest software executed a pause loop with execution time exceeding ple_window.
 *
 * @see vol3c[25.1.3(instructions that cause vm exits conditionally)]
 */
#define vmx_exit_reason_execute_pause 0x00000028

/**
 * @brief vm-entry failure due to machine-check
 *
 * a machine-check event occurred during vm entry.
 *
 * @see vol3c[26.8(machine-check events during vm entry)]
 */
#define vmx_exit_reason_error_machine_check 0x00000029

/**
 * @brief tpr below threshold
 *
 * the logical processor determined that the value of bits 7:4 of the byte at offset 080h on the virtual-apic page was
 * below that of the tpr threshold vm-execution control field while the "use tpr shadow" vmexecution control was 1 either
 * as part of tpr virtualization or vm entry.
 *
 * @see vol3c[29.1.2(tpr virtualization)]
 * @see vol3c[26.6.7(vm exits induced by the tpr threshold)]
 */
#define vmx_exit_reason_tpr_below_threshold 0x0000002b

/**
 * @brief apic access
 *
 * guest software attempted to access memory at a physical address on the apic-access page and the "virtualize apic
 * accesses" vm-execution control was 1.
 *
 * @see vol3c[29.4(virtualizing memory-mapped apic accesses)]
 */
#define vmx_exit_reason_apic_access 0x0000002c

/**
 * @brief virtualized eoi
 *
 * eoi virtualization was performed for a virtual interrupt whose list indexed a bit set in the eoiexit bitmap.
 */
#define vmx_exit_reason_virtualized_eoi 0x0000002d

/**
 * @brief access to gdtr or idtr
 *
 * guest software attempted to execute lgdt, lidt, sgdt, or sidt and the "descriptor-table exiting" vm-execution control
 * was 1.
 */
#define vmx_exit_reason_gdtr_idtr_access 0x0000002e

/**
 * @brief access to ldtr or tr
 *
 * guest software attempted to execute lldt, ltr, sldt, or str and the "descriptor-table exiting" vm-execution control was
 * 1.
 */
#define vmx_exit_reason_ldtr_tr_access 0x0000002f

/**
 * @brief ept violation
 *
 * an attempt to access memory with a guest-physical address was disallowed by the configuration of the ept paging
 * structures.
 */
#define vmx_exit_reason_ept_violation 0x00000030

/**
 * @brief ept misconfiguration
 *
 * an attempt to access memory with a guest-physical address encountered a misconfigured ept paging-structure entry.
 */
#define vmx_exit_reason_ept_misconfiguration 0x00000031

/**
 * @brief invept
 *
 * guest software attempted to execute invept.
 */
#define vmx_exit_reason_execute_invept 0x00000032

/**
 * @brief rdtscp
 *
 * guest software attempted to execute rdtscp and the "enable rdtscp" and "rdtsc exiting" vm-execution controls were both
 * 1.
 */
#define vmx_exit_reason_execute_rdtscp 0x00000033

/**
 * @brief vmx-preemption timer expired
 *
 * the preemption timer counted down to zero.
 */
#define vmx_exit_reason_vmx_preemption_timer_expired 0x00000034

/**
 * @brief invvpid
 *
 * guest software attempted to execute invvpid.
 */
#define vmx_exit_reason_execute_invvpid 0x00000035

/**
 * @brief wbinvd
 *
 * guest software attempted to execute wbinvd and the "wbinvd exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_execute_wbinvd 0x00000036

/**
 * @brief xsetbv - guest software attempted to execute xsetbv
 *
 * guest software attempted to execute xsetbv.
 */
#define vmx_exit_reason_execute_xsetbv 0x00000037

/**
 * @brief apic write
 *
 * guest software completed a write to the virtual-apic page that must be virtualized by vmm software.
 *
 * @see vol3c[29.4.3.3(apic-write vm exits)]
 */
#define vmx_exit_reason_apic_write 0x00000038

/**
 * @brief rdrand
 *
 * guest software attempted to execute rdrand and the "rdrand exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_execute_rdrand 0x00000039

/**
 * @brief invpcid
 *
 * guest software attempted to execute invpcid and the "enable invpcid" and "invlpg exiting" vm-execution controls were
 * both 1.
 */
#define vmx_exit_reason_execute_invpcid 0x0000003a

/**
 * @brief vmfunc
 *
 * guest software invoked a vm function with the vmfunc instruction and the vm function either was not enabled or generated
 * a function-specific condition causing a vm exit.
 */
#define vmx_exit_reason_execute_vmfunc 0x0000003b

/**
 * @brief encls
 *
 * guest software attempted to execute encls and "enable encls exiting" vm-execution control was 1 and either:
 * -# eax < 63 and the corresponding bit in the encls-exiting bitmap is 1; or
 * -# eax >= 63 and bit 63 in the encls-exiting bitmap is 1.
 */
#define vmx_exit_reason_execute_encls 0x0000003c

/**
 * @brief rdseed
 *
 * guest software attempted to execute rdseed and the "rdseed exiting" vm-execution control was 1.
 */
#define vmx_exit_reason_execute_rdseed 0x0000003d

/**
 * @brief page-modification log full
 *
 * the processor attempted to create a page-modification log entry and the value of the pml index was not in the range
 * 0-511.
 */
#define vmx_exit_reason_page_modification_log_full 0x0000003e

/**
 * @brief xsaves
 *
 * guest software attempted to execute xsaves, the "enable xsaves/xrstors" was 1, and a bit was set in the logical-and of
 * the following three values: edx:eax, the ia32_xss msr, and the xss-exiting bitmap.
 */
#define vmx_exit_reason_execute_xsaves 0x0000003f

/**
 * @brief xrstors
 *
 * guest software attempted to execute xrstors, the "enable xsaves/xrstors" was 1, and a bit was set in the logical-and of
 * the following three values: edx:eax, the ia32_xss msr, and the xss-exiting bitmap.
 */
#define vmx_exit_reason_execute_xrstors 0x00000040
/**
 * @}
 */

/**
 * @defgroup vmx_instruction_error_numbers \
 *           vm-instruction error numbers
 *
 * vm-instruction error numbers.
 *
 * @see vol3c[30.4(vm instruction error numbers)] (reference)
 * @{
 */
/**
 * vmcall executed in vmx root operation.
 */
#define vmx_error_vmcall_in_vmx_root_operation 0x00000001

/**
 * vmclear with invalid physical address.
 */
#define vmx_error_vmclear_invalid_physical_address 0x00000002

/**
 * vmclear with vmxon pointer.
 */
#define vmx_error_vmclear_invalid_vmxon_pointer 0x00000003

/**
 * vmlaunch with non-clear vmcs.
 */
#define vmx_error_vmlauch_non_clear_vmcs 0x00000004

/**
 * vmresume with non-launched vmcs.
 */
#define vmx_error_vmresume_non_launched_vmcs 0x00000005

/**
 * vmresume after vmxoff (vmxoff and vmxon between vmlaunch and vmresume).
 */
#define vmx_error_vmresume_after_vmxoff 0x00000006

/**
 * vm entry with invalid control field(s).
 */
#define vmx_error_vmentry_invalid_control_fields 0x00000007

/**
 * vm entry with invalid host-state field(s).
 */
#define vmx_error_vmentry_invalid_host_state 0x00000008

/**
 * vmptrld with invalid physical address.
 */
#define vmx_error_vmptrld_invalid_physical_address 0x00000009

/**
 * vmptrld with vmxon pointer.
 */
#define vmx_error_vmptrld_vmxon_pointer 0x0000000a

/**
 * vmptrld with incorrect vmcs revision identifier.
 */
#define vmx_error_vmptrld_incorrect_vmcs_revision_id 0x0000000b

/**
 * vmread/vmwrite from/to unsupported vmcs component.
 */
#define vmx_error_vmread_vmwrite_invalid_component 0x0000000c

/**
 * vmwrite to read-only vmcs component.
 */
#define vmx_error_vmwrite_readonly_component 0x0000000d

/**
 * vmxon executed in vmx root operation.
 */
#define vmx_error_vmxon_in_vmx_root_op 0x0000000f

/**
 * vm entry with invalid executive-vmcs pointer.
 */
#define vmx_error_vmentry_invalid_vmcs_executive_pointer 0x00000010

/**
 * vm entry with non-launched executive vmcs.
 */
#define vmx_error_vmentry_non_launched_executive_vmcs 0x00000011

/**
 * vm entry with executive-vmcs pointer not vmxon pointer (when attempting to deactivate the dual-monitor treatment of smis
 * and smm).
 */
#define vmx_error_vmentry_executive_vmcs_ptr 0x00000012

/**
 * vmcall with non-clear vmcs (when attempting to activate the dual-monitor treatment of smis and smm).
 */
#define vmx_error_vmcall_non_clear_vmcs 0x00000013

/**
 * vmcall with invalid vm-exit control fields.
 */
#define vmx_error_vmcall_invalid_vmexit_fields 0x00000014

/**
 * vmcall with incorrect mseg revision identifier (when attempting to activate the dual-monitor treatment of smis and smm).
 */
#define vmx_error_vmcall_invalid_mseg_revision_id 0x00000016

/**
 * vmxoff under dual-monitor treatment of smis and smm.
 */
#define vmx_error_vmxoff_dual_monitor 0x00000017

/**
 * vmcall with invalid smm-monitor features (when attempting to activate the dual-monitor treatment of smis and smm).
 */
#define vmx_error_vmcall_invalid_smm_monitor 0x00000018

/**
 * vm entry with invalid vm-execution control fields in executive vmcs (when attempting to return from smm).
 */
#define vmx_error_vmentry_invalid_vm_execution_control 0x00000019

/**
 * vm entry with events blocked by mov ss.
 */
#define vmx_error_vmentry_mov_ss 0x0000001a

/**
 * invalid operand to invept/invvpid.
 */
#define vmx_error_invept_invvpid_invalid_operand 0x0000001c
/**
 * @}
 */

/**
 * @defgroup vmx_exceptions \
 *           virtualization exceptions
 *
 * virtualization exceptions.
 *
 * @see vol3c[25.5.6(virtualization exceptions)] (reference)
 * @{
 */
typedef struct {
	/**
         * the 32-bit value that would have been saved into the vmcs as an exit reason had a vm exit occurred instead of the
         * virtualization exception. for ept violations, this value is 48 (00000030h).
         */
	uint32 reason;

	/**
         * ffffffffh
         */
	uint32 exceptionmask;

	/**
         * the 64-bit value that would have been saved into the vmcs as an exit qualification had a vm exit occurred instead of the
         * virtualization exception.
         */
	uint64 exit;

	/**
         * the 64-bit value that would have been saved into the vmcs as a guest-linear address had a vm exit occurred instead of
         * the virtualization exception.
         */
	uint64 guestlinearaddress;

	/**
         * the 64-bit value that would have been saved into the vmcs as a guest-physical address had a vm exit occurred instead of
         * the virtualization exception.
         */
	uint64 guestphysicaladdress;

	/**
         * the current 16-bit value of the eptp index vm-execution control.
         *
         * @see vol3c[24.6.18(controls for virtualization exceptions)]
         * @see vol3c[25.5.5.3(eptp switching)]
         */
	uint16 currenteptpindex;
} vmx_virtualization_exception_information;

/**
 * @}
 */

/**
 * @defgroup vmx_basic_exit_information \
 *           basic vm-exit information
 *
 * basic vm-exit information.
 *
 * @see vol3c[27.2.1(basic vm-exit information)] (reference)
 * @{
 */
/**
 * @brief exit qualification for debug exceptions
 */
typedef union {
	struct {
		/**
                 * @brief b0 - b3
                 *
                 * [bits 3:0] when set, each of these bits indicates that the corresponding breakpoint condition was met. any of these bits
                 * may be set even if its corresponding enabling bit in dr7 is not set.
                 */
		uint64 breakpointcondition : 4;
#define vmx_exit_qualification_debug_exception_breakpoint_condition_bit 0
#define vmx_exit_qualification_debug_exception_breakpoint_condition_flag 0x0f
#define vmx_exit_qualification_debug_exception_breakpoint_condition_mask 0x0f
#define vmx_exit_qualification_debug_exception_breakpoint_condition(_) \
	(((_) >> 0) & 0x0f)
		uint64 reserved1 : 9;

		/**
                 * @brief bd
                 *
                 * [bit 13] when set, this bit indicates that the cause of the debug exception is "debug register access detected."
                 */
		uint64 debugregisteraccessdetected : 1;
#define vmx_exit_qualification_debug_exception_debug_register_access_detected_bit \
	13
#define vmx_exit_qualification_debug_exception_debug_register_access_detected_flag \
	0x2000
#define vmx_exit_qualification_debug_exception_debug_register_access_detected_mask \
	0x01
#define vmx_exit_qualification_debug_exception_debug_register_access_detected( \
	_)                                                                     \
	(((_) >> 13) & 0x01)

		/**
                 * @brief bs
                 *
                 * [bit 14] when set, this bit indicates that the cause of the debug exception is either the execution of a single
                 * instruction (if rflags.tf = 1 and ia32_debugctl.btf = 0) or a taken branch (if rflags.tf = debugctl.btf = 1).
                 */
		uint64 singleinstruction : 1;
#define vmx_exit_qualification_debug_exception_single_instruction_bit 14
#define vmx_exit_qualification_debug_exception_single_instruction_flag 0x4000
#define vmx_exit_qualification_debug_exception_single_instruction_mask 0x01
#define vmx_exit_qualification_debug_exception_single_instruction(_) \
	(((_) >> 14) & 0x01)
		uint64 reserved2 : 49;
	};

	uint64 flags;
} vmx_exit_qualification_debug_exception;

/**
 * @brief exit qualification for task switch
 */
typedef union {
	struct {
		/**
                 * [bits 15:0] selector of task-state segment (tss) to which the guest attempted to switch.
                 */
		uint64 selector : 16;
#define vmx_exit_qualification_task_switch_selector_bit 0
#define vmx_exit_qualification_task_switch_selector_flag 0xffff
#define vmx_exit_qualification_task_switch_selector_mask 0xffff
#define vmx_exit_qualification_task_switch_selector(_) (((_) >> 0) & 0xffff)
		uint64 reserved1 : 14;

		/**
                 * [bits 31:30] source of task switch initiation.
                 */
		uint64 source : 2;
#define vmx_exit_qualification_task_switch_source_bit 30
#define vmx_exit_qualification_task_switch_source_flag 0xc0000000
#define vmx_exit_qualification_task_switch_source_mask 0x03
#define vmx_exit_qualification_task_switch_source(_) (((_) >> 30) & 0x03)
#define vmx_exit_qualification_type_call_instruction 0x00000000
#define vmx_exit_qualification_type_iret_instruction 0x00000001
#define vmx_exit_qualification_type_jmp_instruction 0x00000002
#define vmx_exit_qualification_type_task_gate_in_idt 0x00000003
		uint64 reserved2 : 32;
	};

	uint64 flags;
} vmx_exit_qualification_task_switch;

/**
 * @brief exit qualification for control-register accesses
 */
typedef union {
	struct {
		/**
                 * [bits 3:0] number of control register (0 for clts and lmsw). bit 3 is always 0 on processors that do not support intel
                 * 64 architecture as they do not support cr8.
                 */
		uint64 controlregister : 4;
#define vmx_exit_qualification_mov_cr_control_register_bit 0
#define vmx_exit_qualification_mov_cr_control_register_flag 0x0f
#define vmx_exit_qualification_mov_cr_control_register_mask 0x0f
#define vmx_exit_qualification_mov_cr_control_register(_) (((_) >> 0) & 0x0f)
#define vmx_exit_qualification_register_cr0 0x00000000
#define vmx_exit_qualification_register_cr2 0x00000002
#define vmx_exit_qualification_register_cr3 0x00000003
#define vmx_exit_qualification_register_cr4 0x00000004
#define vmx_exit_qualification_register_cr8 0x00000008

		/**
                 * [bits 5:4] access type.
                 */
		uint64 accesstype : 2;
#define vmx_exit_qualification_mov_cr_access_type_bit 4
#define vmx_exit_qualification_mov_cr_access_type_flag 0x30
#define vmx_exit_qualification_mov_cr_access_type_mask 0x03
#define vmx_exit_qualification_mov_cr_access_type(_) (((_) >> 4) & 0x03)
#define vmx_exit_qualification_access_mov_to_cr 0x00000000
#define vmx_exit_qualification_access_mov_from_cr 0x00000001
#define vmx_exit_qualification_access_clts 0x00000002
#define vmx_exit_qualification_access_lmsw 0x00000003

		/**
                 * [bit 6] lmsw operand type. for clts and mov cr, cleared to 0.
                 */
		uint64 lmswoperandtype : 1;
#define vmx_exit_qualification_mov_cr_lmsw_operand_type_bit 6
#define vmx_exit_qualification_mov_cr_lmsw_operand_type_flag 0x40
#define vmx_exit_qualification_mov_cr_lmsw_operand_type_mask 0x01
#define vmx_exit_qualification_mov_cr_lmsw_operand_type(_) (((_) >> 6) & 0x01)
#define vmx_exit_qualification_lmsw_op_register 0x00000000
#define vmx_exit_qualification_lmsw_op_memory 0x00000001
		uint64 reserved1 : 1;

		/**
                 * [bits 11:8] for mov cr, the general-purpose register.
                 */
		uint64 generalpurposeregister : 4;
#define vmx_exit_qualification_mov_cr_general_purpose_register_bit 8
#define vmx_exit_qualification_mov_cr_general_purpose_register_flag 0xf00
#define vmx_exit_qualification_mov_cr_general_purpose_register_mask 0x0f
#define vmx_exit_qualification_mov_cr_general_purpose_register(_) \
	(((_) >> 8) & 0x0f)
#define vmx_exit_qualification_genreg_rax 0x00000000
#define vmx_exit_qualification_genreg_rcx 0x00000001
#define vmx_exit_qualification_genreg_rdx 0x00000002
#define vmx_exit_qualification_genreg_rbx 0x00000003
#define vmx_exit_qualification_genreg_rsp 0x00000004
#define vmx_exit_qualification_genreg_rbp 0x00000005
#define vmx_exit_qualification_genreg_rsi 0x00000006
#define vmx_exit_qualification_genreg_rdi 0x00000007
#define vmx_exit_qualification_genreg_r8 0x00000008
#define vmx_exit_qualification_genreg_r9 0x00000009
#define vmx_exit_qualification_genreg_r10 0x0000000a
#define vmx_exit_qualification_genreg_r11 0x0000000b
#define vmx_exit_qualification_genreg_r12 0x0000000c
#define vmx_exit_qualification_genreg_r13 0x0000000d
#define vmx_exit_qualification_genreg_r14 0x0000000e
#define vmx_exit_qualification_genreg_r15 0x0000000f
		uint64 reserved2 : 4;

		/**
                 * [bits 31:16] for lmsw, the lmsw source data. for clts and mov cr, cleared to 0.
                 */
		uint64 lmswsourcedata : 16;
#define vmx_exit_qualification_mov_cr_lmsw_source_data_bit 16
#define vmx_exit_qualification_mov_cr_lmsw_source_data_flag 0xffff0000
#define vmx_exit_qualification_mov_cr_lmsw_source_data_mask 0xffff
#define vmx_exit_qualification_mov_cr_lmsw_source_data(_) (((_) >> 16) & 0xffff)
		uint64 reserved3 : 32;
	};

	uint64 flags;
} vmx_exit_qualification_mov_cr;

/**
 * @brief exit qualification for mov dr
 */
typedef union {
	struct {
		/**
                 * [bits 2:0] number of debug register.
                 */
		uint64 debugregister : 3;
#define vmx_exit_qualification_mov_dr_debug_register_bit 0
#define vmx_exit_qualification_mov_dr_debug_register_flag 0x07
#define vmx_exit_qualification_mov_dr_debug_register_mask 0x07
#define vmx_exit_qualification_mov_dr_debug_register(_) (((_) >> 0) & 0x07)
#define vmx_exit_qualification_register_dr0 0x00000000
#define vmx_exit_qualification_register_dr1 0x00000001
#define vmx_exit_qualification_register_dr2 0x00000002
#define vmx_exit_qualification_register_dr3 0x00000003
#define vmx_exit_qualification_register_dr6 0x00000006
#define vmx_exit_qualification_register_dr7 0x00000007
		uint64 reserved1 : 1;

		/**
                 * [bit 4] direction of access (0 = mov to dr; 1 = mov from dr).
                 */
		uint64 directionofaccess : 1;
#define vmx_exit_qualification_mov_dr_direction_of_access_bit 4
#define vmx_exit_qualification_mov_dr_direction_of_access_flag 0x10
#define vmx_exit_qualification_mov_dr_direction_of_access_mask 0x01
#define vmx_exit_qualification_mov_dr_direction_of_access(_) (((_) >> 4) & 0x01)
#define vmx_exit_qualification_direction_mov_to_dr 0x00000000
#define vmx_exit_qualification_direction_mov_from_dr 0x00000001
		uint64 reserved2 : 3;

		/**
                 * [bits 11:8] general-purpose register.
                 */
		uint64 generalpurposeregister : 4;
#define vmx_exit_qualification_mov_dr_general_purpose_register_bit 8
#define vmx_exit_qualification_mov_dr_general_purpose_register_flag 0xf00
#define vmx_exit_qualification_mov_dr_general_purpose_register_mask 0x0f
#define vmx_exit_qualification_mov_dr_general_purpose_register(_) \
	(((_) >> 8) & 0x0f)
		uint64 reserved3 : 52;
	};

	uint64 flags;
} vmx_exit_qualification_mov_dr;

/**
 * @brief exit qualification for i/o instructions
 */
typedef union {
	struct {
		/**
                 * [bits 2:0] size of access.
                 */
		uint64 sizeofaccess : 3;
#define vmx_exit_qualification_io_instruction_size_of_access_bit 0
#define vmx_exit_qualification_io_instruction_size_of_access_flag 0x07
#define vmx_exit_qualification_io_instruction_size_of_access_mask 0x07
#define vmx_exit_qualification_io_instruction_size_of_access(_) \
	(((_) >> 0) & 0x07)
#define vmx_exit_qualification_width_1_byte 0x00000000
#define vmx_exit_qualification_width_2_byte 0x00000001
#define vmx_exit_qualification_width_4_byte 0x00000003

		/**
                 * [bit 3] direction of the attempted access (0 = out, 1 = in).
                 */
		uint64 directionofaccess : 1;
#define vmx_exit_qualification_io_instruction_direction_of_access_bit 3
#define vmx_exit_qualification_io_instruction_direction_of_access_flag 0x08
#define vmx_exit_qualification_io_instruction_direction_of_access_mask 0x01
#define vmx_exit_qualification_io_instruction_direction_of_access(_) \
	(((_) >> 3) & 0x01)
#define vmx_exit_qualification_direction_out 0x00000000
#define vmx_exit_qualification_direction_in 0x00000001

		/**
                 * [bit 4] string instruction (0 = not string; 1 = string).
                 */
		uint64 stringinstruction : 1;
#define vmx_exit_qualification_io_instruction_string_instruction_bit 4
#define vmx_exit_qualification_io_instruction_string_instruction_flag 0x10
#define vmx_exit_qualification_io_instruction_string_instruction_mask 0x01
#define vmx_exit_qualification_io_instruction_string_instruction(_) \
	(((_) >> 4) & 0x01)
#define vmx_exit_qualification_is_string_not_string 0x00000000
#define vmx_exit_qualification_is_string_string 0x00000001

		/**
                 * [bit 5] rep prefixed (0 = not rep; 1 = rep).
                 */
		uint64 repprefixed : 1;
#define vmx_exit_qualification_io_instruction_rep_prefixed_bit 5
#define vmx_exit_qualification_io_instruction_rep_prefixed_flag 0x20
#define vmx_exit_qualification_io_instruction_rep_prefixed_mask 0x01
#define vmx_exit_qualification_io_instruction_rep_prefixed(_) \
	(((_) >> 5) & 0x01)
#define vmx_exit_qualification_is_rep_not_rep 0x00000000
#define vmx_exit_qualification_is_rep_rep 0x00000001

		/**
                 * [bit 6] operand encoding (0 = dx, 1 = immediate).
                 */
		uint64 operandencoding : 1;
#define vmx_exit_qualification_io_instruction_operand_encoding_bit 6
#define vmx_exit_qualification_io_instruction_operand_encoding_flag 0x40
#define vmx_exit_qualification_io_instruction_operand_encoding_mask 0x01
#define vmx_exit_qualification_io_instruction_operand_encoding(_) \
	(((_) >> 6) & 0x01)
#define vmx_exit_qualification_encoding_dx 0x00000000
#define vmx_exit_qualification_encoding_immediate 0x00000001
		uint64 reserved1 : 9;

		/**
                 * [bits 31:16] port number (as specified in dx or in an immediate operand).
                 */
		uint64 portnumber : 16;
#define vmx_exit_qualification_io_instruction_port_number_bit 16
#define vmx_exit_qualification_io_instruction_port_number_flag 0xffff0000
#define vmx_exit_qualification_io_instruction_port_number_mask 0xffff
#define vmx_exit_qualification_io_instruction_port_number(_) \
	(((_) >> 16) & 0xffff)
		uint64 reserved2 : 32;
	};

	uint64 flags;
} vmx_exit_qualification_io_instruction;

/**
 * @brief exit qualification for apic-access vm exits from linear accesses and guest-physical accesses
 */
typedef union {
	struct {
		/**
                 * [bits 11:0] - if the apic-access vm exit is due to a linear access, the offset of access within the apic page.
                 * - undefined if the apic-access vm exit is due a guest-physical access.
                 */
		uint64 pageoffset : 12;
#define vmx_exit_qualification_apic_access_page_offset_bit 0
#define vmx_exit_qualification_apic_access_page_offset_flag 0xfff
#define vmx_exit_qualification_apic_access_page_offset_mask 0xfff
#define vmx_exit_qualification_apic_access_page_offset(_) (((_) >> 0) & 0xfff)

		/**
                 * [bits 15:12] access type.
                 */
		uint64 accesstype : 4;
#define vmx_exit_qualification_apic_access_access_type_bit 12
#define vmx_exit_qualification_apic_access_access_type_flag 0xf000
#define vmx_exit_qualification_apic_access_access_type_mask 0x0f
#define vmx_exit_qualification_apic_access_access_type(_) (((_) >> 12) & 0x0f)
		/**
                 * linear access for a data read during instruction execution.
                 */
#define vmx_exit_qualification_type_linear_read 0x00000000

		/**
                 * linear access for a data write during instruction execution.
                 */
#define vmx_exit_qualification_type_linear_write 0x00000001

		/**
                 * linear access for an instruction fetch.
                 */
#define vmx_exit_qualification_type_linear_instruction_fetch 0x00000002

		/**
                 * linear access (read or write) during event delivery.
                 */
#define vmx_exit_qualification_type_linear_event_delivery 0x00000003

		/**
                 * guest-physical access during event delivery.
                 */
#define vmx_exit_qualification_type_physical_event_delivery 0x0000000a

		/**
                 * guest-physical access for an instruction fetch or during instruction execution.
                 */
#define vmx_exit_qualification_type_physical_instruction_fetch 0x0000000f
		uint64 reserved1 : 48;
	};

	uint64 flags;
} vmx_exit_qualification_apic_access;

/**
 * @brief exit qualification for ept violations
 */
typedef union {
	struct {
		/**
                 * [bit 0] set if the access causing the ept violation was a data read.
                 */
		uint64 readaccess : 1;
#define vmx_exit_qualification_ept_violation_read_access_bit 0
#define vmx_exit_qualification_ept_violation_read_access_flag 0x01
#define vmx_exit_qualification_ept_violation_read_access_mask 0x01
#define vmx_exit_qualification_ept_violation_read_access(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] set if the access causing the ept violation was a data write.
                 */
		uint64 writeaccess : 1;
#define vmx_exit_qualification_ept_violation_write_access_bit 1
#define vmx_exit_qualification_ept_violation_write_access_flag 0x02
#define vmx_exit_qualification_ept_violation_write_access_mask 0x01
#define vmx_exit_qualification_ept_violation_write_access(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] set if the access causing the ept violation was an instruction fetch.
                 */
		uint64 executeaccess : 1;
#define vmx_exit_qualification_ept_violation_execute_access_bit 2
#define vmx_exit_qualification_ept_violation_execute_access_flag 0x04
#define vmx_exit_qualification_ept_violation_execute_access_mask 0x01
#define vmx_exit_qualification_ept_violation_execute_access(_) \
	(((_) >> 2) & 0x01)

		/**
                 * [bit 3] the logical-and of bit 0 in the ept paging-structure entries used to translate the guest-physical address of the
                 * access causing the ept violation (indicates whether the guest-physical address was readable).
                 */
		uint64 eptreadable : 1;
#define vmx_exit_qualification_ept_violation_ept_readable_bit 3
#define vmx_exit_qualification_ept_violation_ept_readable_flag 0x08
#define vmx_exit_qualification_ept_violation_ept_readable_mask 0x01
#define vmx_exit_qualification_ept_violation_ept_readable(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] the logical-and of bit 1 in the ept paging-structure entries used to translate the guest-physical address of the
                 * access causing the ept violation (indicates whether the guest-physical address was writeable).
                 */
		uint64 eptwriteable : 1;
#define vmx_exit_qualification_ept_violation_ept_writeable_bit 4
#define vmx_exit_qualification_ept_violation_ept_writeable_flag 0x10
#define vmx_exit_qualification_ept_violation_ept_writeable_mask 0x01
#define vmx_exit_qualification_ept_violation_ept_writeable(_) \
	(((_) >> 4) & 0x01)

		/**
                 * [bit 5] the logical-and of bit 2 in the ept paging-structure entries used to translate the guest-physical address of the
                 * access causing the ept violation.
                 * if the "mode-based execute control for ept" vm-execution control is 0, this indicates whether the guest-physical address
                 * was executable. if that control is 1, this indicates whether the guest-physical address was executable for
                 * supervisor-mode linear addresses.
                 */
		uint64 eptexecutable : 1;
#define vmx_exit_qualification_ept_violation_ept_executable_bit 5
#define vmx_exit_qualification_ept_violation_ept_executable_flag 0x20
#define vmx_exit_qualification_ept_violation_ept_executable_mask 0x01
#define vmx_exit_qualification_ept_violation_ept_executable(_) \
	(((_) >> 5) & 0x01)

		/**
                 * [bit 6] if the "mode-based execute control" vm-execution control is 0, the value of this bit is undefined. if that
                 * control is 1, this bit is the logical-and of bit 10 in the ept paging-structures entries used to translate the
                 * guest-physical address of the access causing the ept violation. in this case, it indicates whether the guest-physical
                 * address was executable for user-mode linear addresses.
                 */
		uint64 eptexecutableforusermode : 1;
#define vmx_exit_qualification_ept_violation_ept_executable_for_user_mode_bit 6
#define vmx_exit_qualification_ept_violation_ept_executable_for_user_mode_flag \
	0x40
#define vmx_exit_qualification_ept_violation_ept_executable_for_user_mode_mask \
	0x01
#define vmx_exit_qualification_ept_violation_ept_executable_for_user_mode(_) \
	(((_) >> 6) & 0x01)

		/**
                 * [bit 7] set if the guest linear-address field is valid. the guest linear-address field is valid for all ept violations
                 * except those resulting from an attempt to load the guest pdptes as part of the execution of the mov cr instruction.
                 */
		uint64 validguestlinearaddress : 1;
#define vmx_exit_qualification_ept_violation_valid_guest_linear_address_bit 7
#define vmx_exit_qualification_ept_violation_valid_guest_linear_address_flag \
	0x80
#define vmx_exit_qualification_ept_violation_valid_guest_linear_address_mask \
	0x01
#define vmx_exit_qualification_ept_violation_valid_guest_linear_address(_) \
	(((_) >> 7) & 0x01)

		/**
                 * [bit 8] if bit 7 is 1:
                 * - set if the access causing the ept violation is to a guest-physical address that is the translation of a linear
                 * address.
                 * - clear if the access causing the ept violation is to a paging-structure entry as part of a page walk or the update of
                 * an accessed or dirty bit.
                 * reserved if bit 7 is 0 (cleared to 0).
                 */
		uint64 causedbytranslation : 1;
#define vmx_exit_qualification_ept_violation_caused_by_translation_bit 8
#define vmx_exit_qualification_ept_violation_caused_by_translation_flag 0x100
#define vmx_exit_qualification_ept_violation_caused_by_translation_mask 0x01
#define vmx_exit_qualification_ept_violation_caused_by_translation(_) \
	(((_) >> 8) & 0x01)

		/**
                 * [bit 9] this bit is 0 if the linear address is a supervisor-mode linear address and 1 if it is a user-mode linear
                 * address. otherwise, this bit is undefined.
                 *
                 * @remarks if bit 7 is 1, bit 8 is 1, and the processor supports advanced vm-exit information for ept violations. (if
                 *          cr0.pg = 0, the translation of every linear address is a user-mode linear address and thus this bit will be 1.)
                 */
		uint64 usermodelinearaddress : 1;
#define vmx_exit_qualification_ept_violation_user_mode_linear_address_bit 9
#define vmx_exit_qualification_ept_violation_user_mode_linear_address_flag 0x200
#define vmx_exit_qualification_ept_violation_user_mode_linear_address_mask 0x01
#define vmx_exit_qualification_ept_violation_user_mode_linear_address(_) \
	(((_) >> 9) & 0x01)

		/**
                 * [bit 10] this bit is 0 if paging translates the linear address to a read-only page and 1 if it translates to a
                 * read/write page. otherwise, this bit is undefined
                 *
                 * @remarks if bit 7 is 1, bit 8 is 1, and the processor supports advanced vm-exit information for ept violations. (if
                 *          cr0.pg = 0, every linear address is read/write and thus this bit will be 1.)
                 */
		uint64 readablewritablepage : 1;
#define vmx_exit_qualification_ept_violation_readable_writable_page_bit 10
#define vmx_exit_qualification_ept_violation_readable_writable_page_flag 0x400
#define vmx_exit_qualification_ept_violation_readable_writable_page_mask 0x01
#define vmx_exit_qualification_ept_violation_readable_writable_page(_) \
	(((_) >> 10) & 0x01)

		/**
                 * [bit 11] this bit is 0 if paging translates the linear address to an executable page and 1 if it translates to an
                 * execute-disable page. otherwise, this bit is undefined.
                 *
                 * @remarks if bit 7 is 1, bit 8 is 1, and the processor supports advanced vm-exit information for ept violations. (if
                 *          cr0.pg = 0, cr4.pae = 0, or ia32_efer.nxe = 0, every linear address is executable and thus this bit will be 0.)
                 */
		uint64 executedisablepage : 1;
#define vmx_exit_qualification_ept_violation_execute_disable_page_bit 11
#define vmx_exit_qualification_ept_violation_execute_disable_page_flag 0x800
#define vmx_exit_qualification_ept_violation_execute_disable_page_mask 0x01
#define vmx_exit_qualification_ept_violation_execute_disable_page(_) \
	(((_) >> 11) & 0x01)

		/**
                 * [bit 12] nmi unblocking due to iret.
                 */
		uint64 nmiunblocking : 1;
#define vmx_exit_qualification_ept_violation_nmi_unblocking_bit 12
#define vmx_exit_qualification_ept_violation_nmi_unblocking_flag 0x1000
#define vmx_exit_qualification_ept_violation_nmi_unblocking_mask 0x01
#define vmx_exit_qualification_ept_violation_nmi_unblocking(_) \
	(((_) >> 12) & 0x01)
		uint64 reserved1 : 51;
	};

	uint64 flags;
} vmx_exit_qualification_ept_violation;

/**
 * @}
 */

/**
 * @defgroup vmx_vmexit_instruction_information \
 *           information for vm exits due to instruction execution
 *
 * information for vm exits due to instruction execution.
 *
 * @see vol3c[27.2.4(information for vm exits due to instruction execution)] (reference)
 * @{
 */
/**
 * @brief vm-exit instruction-information field as used for ins and outs
 */
typedef union {
	struct {
		uint64 reserved1 : 7;

		/**
                 * @brief address size
                 *
                 * [bits 9:7] 0: 16-bit
                 * 1: 32-bit
                 * 2: 64-bit (used only on processors that support intel 64 architecture)
                 * other values not used.
                 */
		uint64 addresssize : 3;
#define vmx_vmexit_instruction_info_ins_outs_address_size_bit 7
#define vmx_vmexit_instruction_info_ins_outs_address_size_flag 0x380
#define vmx_vmexit_instruction_info_ins_outs_address_size_mask 0x07
#define vmx_vmexit_instruction_info_ins_outs_address_size(_) (((_) >> 7) & 0x07)
		uint64 reserved2 : 5;

		/**
                 * @brief segment register
                 *
                 * [bits 17:15] 0: es
                 * 1: cs
                 * 2: ss
                 * 3: ds
                 * 4: fs
                 * 5: gs
                 * other values not used. undefined for vm exits due to execution of ins.
                 */
		uint64 segmentregister : 3;
#define vmx_vmexit_instruction_info_ins_outs_segment_register_bit 15
#define vmx_vmexit_instruction_info_ins_outs_segment_register_flag 0x38000
#define vmx_vmexit_instruction_info_ins_outs_segment_register_mask 0x07
#define vmx_vmexit_instruction_info_ins_outs_segment_register(_) \
	(((_) >> 15) & 0x07)
		uint64 reserved3 : 46;
	};

	uint64 flags;
} vmx_vmexit_instruction_info_ins_outs;

/**
 * @brief vm-exit instruction-information field as used for invept, invpcid, and invvpid
 */
typedef union {
	struct {
		/**
                 * @brief scaling
                 *
                 * [bits 1:0] 0: no scaling
                 * 1: scale by 2
                 * 2: scale by 4
                 * 3: scale by 8 (used only on processors that support intel 64 architecture)
                 * undefined for instructions with no index register (bit 22 is set).
                 */
		uint64 scaling : 2;
#define vmx_vmexit_instruction_info_invalidate_scaling_bit 0
#define vmx_vmexit_instruction_info_invalidate_scaling_flag 0x03
#define vmx_vmexit_instruction_info_invalidate_scaling_mask 0x03
#define vmx_vmexit_instruction_info_invalidate_scaling(_) (((_) >> 0) & 0x03)
		uint64 reserved1 : 5;

		/**
                 * @brief address size
                 *
                 * [bits 9:7] 0: 16-bit
                 * 1: 32-bit
                 * 2: 64-bit (used only on processors that support intel 64 architecture)
                 * other values not used.
                 */
		uint64 addresssize : 3;
#define vmx_vmexit_instruction_info_invalidate_address_size_bit 7
#define vmx_vmexit_instruction_info_invalidate_address_size_flag 0x380
#define vmx_vmexit_instruction_info_invalidate_address_size_mask 0x07
#define vmx_vmexit_instruction_info_invalidate_address_size(_) \
	(((_) >> 7) & 0x07)
		uint64 reserved2 : 5;

		/**
                 * @brief segment register
                 *
                 * [bits 17:15] 0: es
                 * 1: cs
                 * 2: ss
                 * 3: ds
                 * 4: fs
                 * 5: gs
                 * other values not used. undefined for vm exits due to execution of ins.
                 */
		uint64 segmentregister : 3;
#define vmx_vmexit_instruction_info_invalidate_segment_register_bit 15
#define vmx_vmexit_instruction_info_invalidate_segment_register_flag 0x38000
#define vmx_vmexit_instruction_info_invalidate_segment_register_mask 0x07
#define vmx_vmexit_instruction_info_invalidate_segment_register(_) \
	(((_) >> 15) & 0x07)

		/**
                 * [bits 21:18] general-purpose register. undefined for instructions with no index register (bit 22 is set).
                 */
		uint64 generalpurposeregister : 4;
#define vmx_vmexit_instruction_info_invalidate_general_purpose_register_bit 18
#define vmx_vmexit_instruction_info_invalidate_general_purpose_register_flag \
	0x3c0000
#define vmx_vmexit_instruction_info_invalidate_general_purpose_register_mask \
	0x0f
#define vmx_vmexit_instruction_info_invalidate_general_purpose_register(_) \
	(((_) >> 18) & 0x0f)

		/**
                 * [bit 22] indexreg invalid (0 = valid; 1 = invalid).
                 */
		uint64 generalpurposeregisterinvalid : 1;
#define vmx_vmexit_instruction_info_invalidate_general_purpose_register_invalid_bit \
	22
#define vmx_vmexit_instruction_info_invalidate_general_purpose_register_invalid_flag \
	0x400000
#define vmx_vmexit_instruction_info_invalidate_general_purpose_register_invalid_mask \
	0x01
#define vmx_vmexit_instruction_info_invalidate_general_purpose_register_invalid( \
	_)                                                                       \
	(((_) >> 22) & 0x01)

		/**
                 * [bits 26:23] basereg (encoded as indexreg above). undefined for memory instructions with no base register (bit 27 is
                 * set).
                 */
		uint64 baseregister : 4;
#define vmx_vmexit_instruction_info_invalidate_base_register_bit 23
#define vmx_vmexit_instruction_info_invalidate_base_register_flag 0x7800000
#define vmx_vmexit_instruction_info_invalidate_base_register_mask 0x0f
#define vmx_vmexit_instruction_info_invalidate_base_register(_) \
	(((_) >> 23) & 0x0f)

		/**
                 * [bit 27] basereg invalid (0 = valid; 1 = invalid).
                 */
		uint64 baseregisterinvalid : 1;
#define vmx_vmexit_instruction_info_invalidate_base_register_invalid_bit 27
#define vmx_vmexit_instruction_info_invalidate_base_register_invalid_flag \
	0x8000000
#define vmx_vmexit_instruction_info_invalidate_base_register_invalid_mask 0x01
#define vmx_vmexit_instruction_info_invalidate_base_register_invalid(_) \
	(((_) >> 27) & 0x01)

		/**
                 * [bits 31:28] reg2 (same encoding as indexreg above).
                 */
		uint64 register2 : 4;
#define vmx_vmexit_instruction_info_invalidate_register_2_bit 28
#define vmx_vmexit_instruction_info_invalidate_register_2_flag 0xf0000000
#define vmx_vmexit_instruction_info_invalidate_register_2_mask 0x0f
#define vmx_vmexit_instruction_info_invalidate_register_2(_) \
	(((_) >> 28) & 0x0f)
		uint64 reserved3 : 32;
	};

	uint64 flags;
} vmx_vmexit_instruction_info_invalidate;

/**
 * @brief vm-exit instruction-information field as used for lidt, lgdt, sidt, or sgdt
 */
typedef union {
	struct {
		/**
                 * @brief scaling
                 *
                 * [bits 1:0] 0: no scaling
                 * 1: scale by 2
                 * 2: scale by 4
                 * 3: scale by 8 (used only on processors that support intel 64 architecture)
                 * undefined for instructions with no index register (bit 22 is set).
                 */
		uint64 scaling : 2;
#define vmx_vmexit_instruction_info_gdtr_idtr_access_scaling_bit 0
#define vmx_vmexit_instruction_info_gdtr_idtr_access_scaling_flag 0x03
#define vmx_vmexit_instruction_info_gdtr_idtr_access_scaling_mask 0x03
#define vmx_vmexit_instruction_info_gdtr_idtr_access_scaling(_) \
	(((_) >> 0) & 0x03)
		uint64 reserved1 : 5;

		/**
                 * @brief address size
                 *
                 * [bits 9:7] 0: 16-bit
                 * 1: 32-bit
                 * 2: 64-bit (used only on processors that support intel 64 architecture)
                 * other values not used.
                 */
		uint64 addresssize : 3;
#define vmx_vmexit_instruction_info_gdtr_idtr_access_address_size_bit 7
#define vmx_vmexit_instruction_info_gdtr_idtr_access_address_size_flag 0x380
#define vmx_vmexit_instruction_info_gdtr_idtr_access_address_size_mask 0x07
#define vmx_vmexit_instruction_info_gdtr_idtr_access_address_size(_) \
	(((_) >> 7) & 0x07)
		uint64 reserved2 : 1;

		/**
                 * @brief operand size
                 *
                 * [bit 11] 0: 16-bit
                 * 1: 32-bit
                 * undefined for vm exits from 64-bit mode.
                 */
		uint64 operandsize : 1;
#define vmx_vmexit_instruction_info_gdtr_idtr_access_operand_size_bit 11
#define vmx_vmexit_instruction_info_gdtr_idtr_access_operand_size_flag 0x800
#define vmx_vmexit_instruction_info_gdtr_idtr_access_operand_size_mask 0x01
#define vmx_vmexit_instruction_info_gdtr_idtr_access_operand_size(_) \
	(((_) >> 11) & 0x01)
		uint64 reserved3 : 3;

		/**
                 * @brief segment register
                 *
                 * [bits 17:15] 0: es
                 * 1: cs
                 * 2: ss
                 * 3: ds
                 * 4: fs
                 * 5: gs
                 * other values not used.
                 */
		uint64 segmentregister : 3;
#define vmx_vmexit_instruction_info_gdtr_idtr_access_segment_register_bit 15
#define vmx_vmexit_instruction_info_gdtr_idtr_access_segment_register_flag \
	0x38000
#define vmx_vmexit_instruction_info_gdtr_idtr_access_segment_register_mask 0x07
#define vmx_vmexit_instruction_info_gdtr_idtr_access_segment_register(_) \
	(((_) >> 15) & 0x07)

		/**
                 * [bits 21:18] general-purpose register. undefined for instructions with no index register (bit 22 is set).
                 */
		uint64 generalpurposeregister : 4;
#define vmx_vmexit_instruction_info_gdtr_idtr_access_general_purpose_register_bit \
	18
#define vmx_vmexit_instruction_info_gdtr_idtr_access_general_purpose_register_flag \
	0x3c0000
#define vmx_vmexit_instruction_info_gdtr_idtr_access_general_purpose_register_mask \
	0x0f
#define vmx_vmexit_instruction_info_gdtr_idtr_access_general_purpose_register( \
	_)                                                                     \
	(((_) >> 18) & 0x0f)

		/**
                 * [bit 22] indexreg invalid (0 = valid; 1 = invalid).
                 */
		uint64 generalpurposeregisterinvalid : 1;
#define vmx_vmexit_instruction_info_gdtr_idtr_access_general_purpose_register_invalid_bit \
	22
#define vmx_vmexit_instruction_info_gdtr_idtr_access_general_purpose_register_invalid_flag \
	0x400000
#define vmx_vmexit_instruction_info_gdtr_idtr_access_general_purpose_register_invalid_mask \
	0x01
#define vmx_vmexit_instruction_info_gdtr_idtr_access_general_purpose_register_invalid( \
	_)                                                                             \
	(((_) >> 22) & 0x01)

		/**
                 * [bits 26:23] basereg (encoded as indexreg above). undefined for memory instructions with no base register (bit 27 is
                 * set).
                 */
		uint64 baseregister : 4;
#define vmx_vmexit_instruction_info_gdtr_idtr_access_base_register_bit 23
#define vmx_vmexit_instruction_info_gdtr_idtr_access_base_register_flag \
	0x7800000
#define vmx_vmexit_instruction_info_gdtr_idtr_access_base_register_mask 0x0f
#define vmx_vmexit_instruction_info_gdtr_idtr_access_base_register(_) \
	(((_) >> 23) & 0x0f)

		/**
                 * [bit 27] basereg invalid (0 = valid; 1 = invalid).
                 */
		uint64 baseregisterinvalid : 1;
#define vmx_vmexit_instruction_info_gdtr_idtr_access_base_register_invalid_bit \
	27
#define vmx_vmexit_instruction_info_gdtr_idtr_access_base_register_invalid_flag \
	0x8000000
#define vmx_vmexit_instruction_info_gdtr_idtr_access_base_register_invalid_mask \
	0x01
#define vmx_vmexit_instruction_info_gdtr_idtr_access_base_register_invalid(_) \
	(((_) >> 27) & 0x01)

		/**
                 * @brief instruction identity
                 *
                 * [bits 29:28] 0: sgdt
                 * 1: sidt
                 * 2: lgdt
                 * 3: lidt
                 */
		uint64 instruction : 2;
#define vmx_vmexit_instruction_info_gdtr_idtr_access_instruction_bit 28
#define vmx_vmexit_instruction_info_gdtr_idtr_access_instruction_flag 0x30000000
#define vmx_vmexit_instruction_info_gdtr_idtr_access_instruction_mask 0x03
#define vmx_vmexit_instruction_info_gdtr_idtr_access_instruction(_) \
	(((_) >> 28) & 0x03)
		uint64 reserved4 : 34;
	};

	uint64 flags;
} vmx_vmexit_instruction_info_gdtr_idtr_access;

/**
 * @brief vm-exit instruction-information field as used for lldt, ltr, sldt, and str
 */
typedef union {
	struct {
		/**
                 * @brief scaling
                 *
                 * [bits 1:0] 0: no scaling
                 * 1: scale by 2
                 * 2: scale by 4
                 * 3: scale by 8 (used only on processors that support intel 64 architecture)
                 * undefined for instructions with no index register (bit 22 is set).
                 */
		uint64 scaling : 2;
#define vmx_vmexit_instruction_info_ldtr_tr_access_scaling_bit 0
#define vmx_vmexit_instruction_info_ldtr_tr_access_scaling_flag 0x03
#define vmx_vmexit_instruction_info_ldtr_tr_access_scaling_mask 0x03
#define vmx_vmexit_instruction_info_ldtr_tr_access_scaling(_) \
	(((_) >> 0) & 0x03)
		uint64 reserved1 : 1;

		/**
                 * [bits 6:3] reg1. undefined for memory instructions (bit 10 is clear).
                 */
		uint64 reg1 : 4;
#define vmx_vmexit_instruction_info_ldtr_tr_access_reg_1_bit 3
#define vmx_vmexit_instruction_info_ldtr_tr_access_reg_1_flag 0x78
#define vmx_vmexit_instruction_info_ldtr_tr_access_reg_1_mask 0x0f
#define vmx_vmexit_instruction_info_ldtr_tr_access_reg_1(_) (((_) >> 3) & 0x0f)

		/**
                 * @brief address size
                 *
                 * [bits 9:7] 0: 16-bit
                 * 1: 32-bit
                 * 2: 64-bit (used only on processors that support intel 64 architecture)
                 * other values not used. undefined for register instructions (bit 10 is set).
                 */
		uint64 addresssize : 3;
#define vmx_vmexit_instruction_info_ldtr_tr_access_address_size_bit 7
#define vmx_vmexit_instruction_info_ldtr_tr_access_address_size_flag 0x380
#define vmx_vmexit_instruction_info_ldtr_tr_access_address_size_mask 0x07
#define vmx_vmexit_instruction_info_ldtr_tr_access_address_size(_) \
	(((_) >> 7) & 0x07)

		/**
                 * [bit 10] mem/reg (0 = memory; 1 = register).
                 */
		uint64 memoryregister : 1;
#define vmx_vmexit_instruction_info_ldtr_tr_access_memory_register_bit 10
#define vmx_vmexit_instruction_info_ldtr_tr_access_memory_register_flag 0x400
#define vmx_vmexit_instruction_info_ldtr_tr_access_memory_register_mask 0x01
#define vmx_vmexit_instruction_info_ldtr_tr_access_memory_register(_) \
	(((_) >> 10) & 0x01)
		uint64 reserved2 : 4;

		/**
                 * @brief segment register
                 *
                 * [bits 17:15] 0: es
                 * 1: cs
                 * 2: ss
                 * 3: ds
                 * 4: fs
                 * 5: gs
                 * other values not used. undefined for register instructions (bit 10 is set).
                 */
		uint64 segmentregister : 3;
#define vmx_vmexit_instruction_info_ldtr_tr_access_segment_register_bit 15
#define vmx_vmexit_instruction_info_ldtr_tr_access_segment_register_flag 0x38000
#define vmx_vmexit_instruction_info_ldtr_tr_access_segment_register_mask 0x07
#define vmx_vmexit_instruction_info_ldtr_tr_access_segment_register(_) \
	(((_) >> 15) & 0x07)

		/**
                 * [bits 21:18] general-purpose register. undefined for register instructions (bit 10 is set) and for memory instructions
                 * with no index register (bit 10 is clear and bit 22 is set).
                 */
		uint64 generalpurposeregister : 4;
#define vmx_vmexit_instruction_info_ldtr_tr_access_general_purpose_register_bit \
	18
#define vmx_vmexit_instruction_info_ldtr_tr_access_general_purpose_register_flag \
	0x3c0000
#define vmx_vmexit_instruction_info_ldtr_tr_access_general_purpose_register_mask \
	0x0f
#define vmx_vmexit_instruction_info_ldtr_tr_access_general_purpose_register(_) \
	(((_) >> 18) & 0x0f)

		/**
                 * [bit 22] indexreg invalid (0 = valid; 1 = invalid). undefined for register instructions (bit 10 is set).
                 */
		uint64 generalpurposeregisterinvalid : 1;
#define vmx_vmexit_instruction_info_ldtr_tr_access_general_purpose_register_invalid_bit \
	22
#define vmx_vmexit_instruction_info_ldtr_tr_access_general_purpose_register_invalid_flag \
	0x400000
#define vmx_vmexit_instruction_info_ldtr_tr_access_general_purpose_register_invalid_mask \
	0x01
#define vmx_vmexit_instruction_info_ldtr_tr_access_general_purpose_register_invalid( \
	_)                                                                           \
	(((_) >> 22) & 0x01)

		/**
                 * [bits 26:23] basereg (encoded as indexreg above). undefined for register instructions (bit 10 is set) and for memory
                 * instructions with no base register (bit 10 is clear and bit 27 is set).
                 */
		uint64 baseregister : 4;
#define vmx_vmexit_instruction_info_ldtr_tr_access_base_register_bit 23
#define vmx_vmexit_instruction_info_ldtr_tr_access_base_register_flag 0x7800000
#define vmx_vmexit_instruction_info_ldtr_tr_access_base_register_mask 0x0f
#define vmx_vmexit_instruction_info_ldtr_tr_access_base_register(_) \
	(((_) >> 23) & 0x0f)

		/**
                 * [bit 27] basereg invalid (0 = valid; 1 = invalid). undefined for register instructions (bit 10 is set).
                 */
		uint64 baseregisterinvalid : 1;
#define vmx_vmexit_instruction_info_ldtr_tr_access_base_register_invalid_bit 27
#define vmx_vmexit_instruction_info_ldtr_tr_access_base_register_invalid_flag \
	0x8000000
#define vmx_vmexit_instruction_info_ldtr_tr_access_base_register_invalid_mask \
	0x01
#define vmx_vmexit_instruction_info_ldtr_tr_access_base_register_invalid(_) \
	(((_) >> 27) & 0x01)

		/**
                 * @brief instruction identity
                 *
                 * [bits 29:28] 0: sldt
                 * 1: str
                 * 2: lldt
                 * 3: ltr
                 */
		uint64 instruction : 2;
#define vmx_vmexit_instruction_info_ldtr_tr_access_instruction_bit 28
#define vmx_vmexit_instruction_info_ldtr_tr_access_instruction_flag 0x30000000
#define vmx_vmexit_instruction_info_ldtr_tr_access_instruction_mask 0x03
#define vmx_vmexit_instruction_info_ldtr_tr_access_instruction(_) \
	(((_) >> 28) & 0x03)
		uint64 reserved3 : 34;
	};

	uint64 flags;
} vmx_vmexit_instruction_info_ldtr_tr_access;

/**
 * @brief vm-exit instruction-information field as used for rdrand and rdseed
 */
typedef union {
	struct {
		uint64 reserved1 : 3;

		/**
                 * [bits 6:3] destination register.
                 */
		uint64 destinationregister : 4;
#define vmx_vmexit_instruction_info_rdrand_rdseed_destination_register_bit 3
#define vmx_vmexit_instruction_info_rdrand_rdseed_destination_register_flag 0x78
#define vmx_vmexit_instruction_info_rdrand_rdseed_destination_register_mask 0x0f
#define vmx_vmexit_instruction_info_rdrand_rdseed_destination_register(_) \
	(((_) >> 3) & 0x0f)
		uint64 reserved2 : 4;

		/**
                 * @brief operand size
                 *
                 * [bits 12:11] 0: 16-bit
                 * 1: 32-bit
                 * 2: 64-bit
                 * the value 3 is not used.
                 */
		uint64 operandsize : 2;
#define vmx_vmexit_instruction_info_rdrand_rdseed_operand_size_bit 11
#define vmx_vmexit_instruction_info_rdrand_rdseed_operand_size_flag 0x1800
#define vmx_vmexit_instruction_info_rdrand_rdseed_operand_size_mask 0x03
#define vmx_vmexit_instruction_info_rdrand_rdseed_operand_size(_) \
	(((_) >> 11) & 0x03)
		uint64 reserved3 : 51;
	};

	uint64 flags;
} vmx_vmexit_instruction_info_rdrand_rdseed;

/**
 * @brief vm-exit instruction-information field as used for vmclear, vmptrld, vmptrst, vmxon, xrstors, and xsaves
 */
typedef union {
	struct {
		/**
                 * @brief scaling
                 *
                 * [bits 1:0] 0: no scaling
                 * 1: scale by 2
                 * 2: scale by 4
                 * 3: scale by 8 (used only on processors that support intel 64 architecture)
                 * undefined for instructions with no index register (bit 22 is set).
                 */
		uint64 scaling : 2;
#define vmx_vmexit_instruction_info_vmx_and_xsaves_scaling_bit 0
#define vmx_vmexit_instruction_info_vmx_and_xsaves_scaling_flag 0x03
#define vmx_vmexit_instruction_info_vmx_and_xsaves_scaling_mask 0x03
#define vmx_vmexit_instruction_info_vmx_and_xsaves_scaling(_) \
	(((_) >> 0) & 0x03)
		uint64 reserved1 : 5;

		/**
                 * @brief address size
                 *
                 * [bits 9:7] 0: 16-bit
                 * 1: 32-bit
                 * 2: 64-bit (used only on processors that support intel 64 architecture)
                 * other values not used.
                 */
		uint64 addresssize : 3;
#define vmx_vmexit_instruction_info_vmx_and_xsaves_address_size_bit 7
#define vmx_vmexit_instruction_info_vmx_and_xsaves_address_size_flag 0x380
#define vmx_vmexit_instruction_info_vmx_and_xsaves_address_size_mask 0x07
#define vmx_vmexit_instruction_info_vmx_and_xsaves_address_size(_) \
	(((_) >> 7) & 0x07)
		uint64 reserved2 : 5;

		/**
                 * @brief segment register
                 *
                 * [bits 17:15] 0: es
                 * 1: cs
                 * 2: ss
                 * 3: ds
                 * 4: fs
                 * 5: gs
                 * other values not used.
                 */
		uint64 segmentregister : 3;
#define vmx_vmexit_instruction_info_vmx_and_xsaves_segment_register_bit 15
#define vmx_vmexit_instruction_info_vmx_and_xsaves_segment_register_flag 0x38000
#define vmx_vmexit_instruction_info_vmx_and_xsaves_segment_register_mask 0x07
#define vmx_vmexit_instruction_info_vmx_and_xsaves_segment_register(_) \
	(((_) >> 15) & 0x07)

		/**
                 * [bits 21:18] general-purpose register. undefined for instructions with no index register (bit 22 is set).
                 */
		uint64 generalpurposeregister : 4;
#define vmx_vmexit_instruction_info_vmx_and_xsaves_general_purpose_register_bit \
	18
#define vmx_vmexit_instruction_info_vmx_and_xsaves_general_purpose_register_flag \
	0x3c0000
#define vmx_vmexit_instruction_info_vmx_and_xsaves_general_purpose_register_mask \
	0x0f
#define vmx_vmexit_instruction_info_vmx_and_xsaves_general_purpose_register(_) \
	(((_) >> 18) & 0x0f)

		/**
                 * [bit 22] indexreg invalid (0 = valid; 1 = invalid).
                 */
		uint64 generalpurposeregisterinvalid : 1;
#define vmx_vmexit_instruction_info_vmx_and_xsaves_general_purpose_register_invalid_bit \
	22
#define vmx_vmexit_instruction_info_vmx_and_xsaves_general_purpose_register_invalid_flag \
	0x400000
#define vmx_vmexit_instruction_info_vmx_and_xsaves_general_purpose_register_invalid_mask \
	0x01
#define vmx_vmexit_instruction_info_vmx_and_xsaves_general_purpose_register_invalid( \
	_)                                                                           \
	(((_) >> 22) & 0x01)

		/**
                 * [bits 26:23] basereg (encoded as indexreg above). undefined for memory instructions with no base register (bit 27 is
                 * set).
                 */
		uint64 baseregister : 4;
#define vmx_vmexit_instruction_info_vmx_and_xsaves_base_register_bit 23
#define vmx_vmexit_instruction_info_vmx_and_xsaves_base_register_flag 0x7800000
#define vmx_vmexit_instruction_info_vmx_and_xsaves_base_register_mask 0x0f
#define vmx_vmexit_instruction_info_vmx_and_xsaves_base_register(_) \
	(((_) >> 23) & 0x0f)

		/**
                 * [bit 27] basereg invalid (0 = valid; 1 = invalid).
                 */
		uint64 baseregisterinvalid : 1;
#define vmx_vmexit_instruction_info_vmx_and_xsaves_base_register_invalid_bit 27
#define vmx_vmexit_instruction_info_vmx_and_xsaves_base_register_invalid_flag \
	0x8000000
#define vmx_vmexit_instruction_info_vmx_and_xsaves_base_register_invalid_mask \
	0x01
#define vmx_vmexit_instruction_info_vmx_and_xsaves_base_register_invalid(_) \
	(((_) >> 27) & 0x01)
		uint64 reserved3 : 36;
	};

	uint64 flags;
} vmx_vmexit_instruction_info_vmx_and_xsaves;

/**
 * @brief vm-exit instruction-information field as used for vmread and vmwrite
 */
typedef union {
	struct {
		/**
                 * @brief scaling
                 *
                 * [bits 1:0] 0: no scaling
                 * 1: scale by 2
                 * 2: scale by 4
                 * 3: scale by 8 (used only on processors that support intel 64 architecture)
                 * undefined for register instructions (bit 10 is set) and for memory instructions with no index register (bit 10 is clear
                 * and bit 22 is set).
                 */
		uint64 scaling : 2;
#define vmx_vmexit_instruction_info_vmread_vmwrite_scaling_bit 0
#define vmx_vmexit_instruction_info_vmread_vmwrite_scaling_flag 0x03
#define vmx_vmexit_instruction_info_vmread_vmwrite_scaling_mask 0x03
#define vmx_vmexit_instruction_info_vmread_vmwrite_scaling(_) \
	(((_) >> 0) & 0x03)
		uint64 reserved1 : 1;

		/**
                 * [bits 6:3] reg1. undefined for memory instructions (bit 10 is clear).
                 */
		uint64 register1 : 4;
#define vmx_vmexit_instruction_info_vmread_vmwrite_register_1_bit 3
#define vmx_vmexit_instruction_info_vmread_vmwrite_register_1_flag 0x78
#define vmx_vmexit_instruction_info_vmread_vmwrite_register_1_mask 0x0f
#define vmx_vmexit_instruction_info_vmread_vmwrite_register_1(_) \
	(((_) >> 3) & 0x0f)

		/**
                 * @brief address size
                 *
                 * [bits 9:7] 0: 16-bit
                 * 1: 32-bit
                 * 2: 64-bit (used only on processors that support intel 64 architecture)
                 * other values not used. undefined for register instructions (bit 10 is set).
                 */
		uint64 addresssize : 3;
#define vmx_vmexit_instruction_info_vmread_vmwrite_address_size_bit 7
#define vmx_vmexit_instruction_info_vmread_vmwrite_address_size_flag 0x380
#define vmx_vmexit_instruction_info_vmread_vmwrite_address_size_mask 0x07
#define vmx_vmexit_instruction_info_vmread_vmwrite_address_size(_) \
	(((_) >> 7) & 0x07)

		/**
                 * [bit 10] mem/reg (0 = memory; 1 = register).
                 */
		uint64 memoryregister : 1;
#define vmx_vmexit_instruction_info_vmread_vmwrite_memory_register_bit 10
#define vmx_vmexit_instruction_info_vmread_vmwrite_memory_register_flag 0x400
#define vmx_vmexit_instruction_info_vmread_vmwrite_memory_register_mask 0x01
#define vmx_vmexit_instruction_info_vmread_vmwrite_memory_register(_) \
	(((_) >> 10) & 0x01)
		uint64 reserved2 : 4;

		/**
                 * @brief segment register
                 *
                 * [bits 17:15] 0: es
                 * 1: cs
                 * 2: ss
                 * 3: ds
                 * 4: fs
                 * 5: gs
                 * other values not used. undefined for register instructions (bit 10 is set).
                 */
		uint64 segmentregister : 3;
#define vmx_vmexit_instruction_info_vmread_vmwrite_segment_register_bit 15
#define vmx_vmexit_instruction_info_vmread_vmwrite_segment_register_flag 0x38000
#define vmx_vmexit_instruction_info_vmread_vmwrite_segment_register_mask 0x07
#define vmx_vmexit_instruction_info_vmread_vmwrite_segment_register(_) \
	(((_) >> 15) & 0x07)

		/**
                 * [bits 21:18] general-purpose register. undefined for register instructions (bit 10 is set) and for memory instructions
                 * with no index register (bit 10 is clear and bit 22 is set).
                 */
		uint64 generalpurposeregister : 4;
#define vmx_vmexit_instruction_info_vmread_vmwrite_general_purpose_register_bit \
	18
#define vmx_vmexit_instruction_info_vmread_vmwrite_general_purpose_register_flag \
	0x3c0000
#define vmx_vmexit_instruction_info_vmread_vmwrite_general_purpose_register_mask \
	0x0f
#define vmx_vmexit_instruction_info_vmread_vmwrite_general_purpose_register(_) \
	(((_) >> 18) & 0x0f)

		/**
                 * [bit 22] indexreg invalid (0 = valid; 1 = invalid). undefined for register instructions (bit 10 is set).
                 */
		uint64 generalpurposeregisterinvalid : 1;
#define vmx_vmexit_instruction_info_vmread_vmwrite_general_purpose_register_invalid_bit \
	22
#define vmx_vmexit_instruction_info_vmread_vmwrite_general_purpose_register_invalid_flag \
	0x400000
#define vmx_vmexit_instruction_info_vmread_vmwrite_general_purpose_register_invalid_mask \
	0x01
#define vmx_vmexit_instruction_info_vmread_vmwrite_general_purpose_register_invalid( \
	_)                                                                           \
	(((_) >> 22) & 0x01)

		/**
                 * [bits 26:23] basereg (encoded as reg1 above). undefined for register instructions (bit 10 is set) and for memory
                 * instructions with no base register (bit 10 is clear and bit 27 is set).
                 */
		uint64 baseregister : 4;
#define vmx_vmexit_instruction_info_vmread_vmwrite_base_register_bit 23
#define vmx_vmexit_instruction_info_vmread_vmwrite_base_register_flag 0x7800000
#define vmx_vmexit_instruction_info_vmread_vmwrite_base_register_mask 0x0f
#define vmx_vmexit_instruction_info_vmread_vmwrite_base_register(_) \
	(((_) >> 23) & 0x0f)

		/**
                 * [bit 27] basereg invalid (0 = valid; 1 = invalid).
                 */
		uint64 baseregisterinvalid : 1;
#define vmx_vmexit_instruction_info_vmread_vmwrite_base_register_invalid_bit 27
#define vmx_vmexit_instruction_info_vmread_vmwrite_base_register_invalid_flag \
	0x8000000
#define vmx_vmexit_instruction_info_vmread_vmwrite_base_register_invalid_mask \
	0x01
#define vmx_vmexit_instruction_info_vmread_vmwrite_base_register_invalid(_) \
	(((_) >> 27) & 0x01)

		/**
                 * [bits 31:28] reg2 (same encoding as indexreg above).
                 */
		uint64 register2 : 4;
#define vmx_vmexit_instruction_info_vmread_vmwrite_register_2_bit 28
#define vmx_vmexit_instruction_info_vmread_vmwrite_register_2_flag 0xf0000000
#define vmx_vmexit_instruction_info_vmread_vmwrite_register_2_mask 0x0f
#define vmx_vmexit_instruction_info_vmread_vmwrite_register_2(_) \
	(((_) >> 28) & 0x0f)
		uint64 reserved3 : 32;
	};

	uint64 flags;
} vmx_vmexit_instruction_info_vmread_vmwrite;

/**
 * @}
 */

/**
 * @brief - the low 16 bits correspond to bits 23:8 of the upper 32 bits of a 64-bit segment descriptor. while bits 19:16
 *        of code-segment and data-segment descriptors correspond to the upper 4 bits of the segment limit, the corresponding bits
 *        (bits 11:8) are reserved in this vmcs field.
 *        - bit 16 indicates an unusable segment. attempts to use such a segment fault except in 64-bit mode. in general, a
 *        segment register is unusable if it has been loaded with a null selector.
 *        - bits 31:17 are reserved
 *
 * @note there are a few exceptions to this statement. for example, a segment with a non-null selector may be unusable
 *       following a task switch that fails after its commit point. in contrast, the tr register is usable after processor reset
 *       despite having a null selector
 * @see segment_descriptor_32
 * @see segment_descriptor_64
 * @see xxx_access_rights fields of 32_bit_guest_state_fields
 * @see vol3c[24.4.2(guest non-register state)] (reference)
 */
typedef union {
	struct {
		/**
                 * [bits 3:0] segment type.
                 */
		uint32 type : 4;
#define vmx_segment_access_rights_type_bit 0
#define vmx_segment_access_rights_type_flag 0x0f
#define vmx_segment_access_rights_type_mask 0x0f
#define vmx_segment_access_rights_type(_) (((_) >> 0) & 0x0f)

		/**
                 * [bit 4] s - descriptor type (0 = system; 1 = code or data).
                 */
		uint32 descriptortype : 1;
#define vmx_segment_access_rights_descriptor_type_bit 4
#define vmx_segment_access_rights_descriptor_type_flag 0x10
#define vmx_segment_access_rights_descriptor_type_mask 0x01
#define vmx_segment_access_rights_descriptor_type(_) (((_) >> 4) & 0x01)

		/**
                 * [bits 6:5] dpl - descriptor privilege level.
                 */
		uint32 descriptorprivilegelevel : 2;
#define vmx_segment_access_rights_descriptor_privilege_level_bit 5
#define vmx_segment_access_rights_descriptor_privilege_level_flag 0x60
#define vmx_segment_access_rights_descriptor_privilege_level_mask 0x03
#define vmx_segment_access_rights_descriptor_privilege_level(_) \
	(((_) >> 5) & 0x03)

		/**
                 * [bit 7] p - segment present.
                 */
		uint32 present : 1;
#define vmx_segment_access_rights_present_bit 7
#define vmx_segment_access_rights_present_flag 0x80
#define vmx_segment_access_rights_present_mask 0x01
#define vmx_segment_access_rights_present(_) (((_) >> 7) & 0x01)
		uint32 reserved1 : 4;

		/**
                 * [bit 12] avl - available for use by system software.
                 */
		uint32 availablebit : 1;
#define vmx_segment_access_rights_available_bit_bit 12
#define vmx_segment_access_rights_available_bit_flag 0x1000
#define vmx_segment_access_rights_available_bit_mask 0x01
#define vmx_segment_access_rights_available_bit(_) (((_) >> 12) & 0x01)

		/**
                 * [bit 13] reserved (except for cs). l - 64-bit mode active (for cs only).
                 */
		uint32 longmode : 1;
#define vmx_segment_access_rights_long_mode_bit 13
#define vmx_segment_access_rights_long_mode_flag 0x2000
#define vmx_segment_access_rights_long_mode_mask 0x01
#define vmx_segment_access_rights_long_mode(_) (((_) >> 13) & 0x01)

		/**
                 * [bit 14] d/b - default operation size (0 = 16-bit segment; 1 = 32-bit segment).
                 */
		uint32 defaultbig : 1;
#define vmx_segment_access_rights_default_big_bit 14
#define vmx_segment_access_rights_default_big_flag 0x4000
#define vmx_segment_access_rights_default_big_mask 0x01
#define vmx_segment_access_rights_default_big(_) (((_) >> 14) & 0x01)

		/**
                 * [bit 15] g - granularity.
                 */
		uint32 granularity : 1;
#define vmx_segment_access_rights_granularity_bit 15
#define vmx_segment_access_rights_granularity_flag 0x8000
#define vmx_segment_access_rights_granularity_mask 0x01
#define vmx_segment_access_rights_granularity(_) (((_) >> 15) & 0x01)

		/**
                 * [bit 16] segment unusable (0 = usable; 1 = unusable).
                 */
		uint32 unusable : 1;
#define vmx_segment_access_rights_unusable_bit 16
#define vmx_segment_access_rights_unusable_flag 0x10000
#define vmx_segment_access_rights_unusable_mask 0x01
#define vmx_segment_access_rights_unusable(_) (((_) >> 16) & 0x01)
		uint32 reserved2 : 15;
	};

	uint32 flags;
} vmx_segment_access_rights;

/**
 * @brief the ia-32 architecture includes features that permit certain events to be blocked for a period of time. this
 *        field contains information about such blocking
 *
 * @see interruptibility_state of 32_bit_guest_state_fields
 * @see vol3c[24.4.2(guest non-register state)] (reference)
 */
typedef union {
	struct {
		/**
                 * [bit 0] execution of sti with rflags.if = 0 blocks maskable interrupts on the instruction boundary following its
                 * execution.1 setting this bit indicates that this blocking is in effect.
                 *
                 * @see vol2b[4(sti-set interrupt flag)]
                 */
		uint32 blockingbysti : 1;
#define vmx_interruptibility_state_blocking_by_sti_bit 0
#define vmx_interruptibility_state_blocking_by_sti_flag 0x01
#define vmx_interruptibility_state_blocking_by_sti_mask 0x01
#define vmx_interruptibility_state_blocking_by_sti(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] execution of a mov to ss or a pop to ss blocks or suppresses certain debug exceptions as well as interrupts
                 * (maskable and nonmaskable) on the instruction boundary following its execution. setting this bit indicates that this
                 * blocking is in effect. this document uses the term "blocking by mov ss," but it applies equally to pop ss.
                 *
                 * @see vol3a[6.8.3(masking exceptions and interrupts when switching stacks)]
                 */
		uint32 blockingbymovss : 1;
#define vmx_interruptibility_state_blocking_by_mov_ss_bit 1
#define vmx_interruptibility_state_blocking_by_mov_ss_flag 0x02
#define vmx_interruptibility_state_blocking_by_mov_ss_mask 0x01
#define vmx_interruptibility_state_blocking_by_mov_ss(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] system-management interrupts (smis) are disabled while the processor is in system-management mode (smm). setting
                 * this bit indicates that blocking of smis is in effect.
                 *
                 * @see vol3c[34.2(system management interrupt (smi))]
                 */
		uint32 blockingbysmi : 1;
#define vmx_interruptibility_state_blocking_by_smi_bit 2
#define vmx_interruptibility_state_blocking_by_smi_flag 0x04
#define vmx_interruptibility_state_blocking_by_smi_mask 0x01
#define vmx_interruptibility_state_blocking_by_smi(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] delivery of a non-maskable interrupt (nmi) or a system-management interrupt (smi) blocks subsequent nmis until
                 * the next execution of iret. setting this bit indicates that blocking of nmis is in effect. clearing this bit does not
                 * imply that nmis are not (temporarily) blocked for other reasons. if the "virtual nmis" vm-execution control is 1, this
                 * bit does not control the blocking of nmis. instead, it refers to "virtual-nmi blocking" (the fact that guest software is
                 * not ready for an nmi).
                 *
                 * @see vol3c[6.7.1(handling multiple nmis)]
                 * @see vol3c[25.3(changes to instruction behavior in vmx non-root operation)]
                 * @see vol3c[24.6.1(pin-based vm-execution controls)]
                 */
		uint32 blockingbynmi : 1;
#define vmx_interruptibility_state_blocking_by_nmi_bit 3
#define vmx_interruptibility_state_blocking_by_nmi_flag 0x08
#define vmx_interruptibility_state_blocking_by_nmi_mask 0x01
#define vmx_interruptibility_state_blocking_by_nmi(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] a vm exit saves this bit as 1 to indicate that the vm exit was incident to enclave mode.
                 */
		uint32 enclaveinterruption : 1;
#define vmx_interruptibility_state_enclave_interruption_bit 4
#define vmx_interruptibility_state_enclave_interruption_flag 0x10
#define vmx_interruptibility_state_enclave_interruption_mask 0x01
#define vmx_interruptibility_state_enclave_interruption(_) (((_) >> 4) & 0x01)
		uint32 reserved1 : 27;
	};

	uint32 flags;
} vmx_interruptibility_state;

typedef enum {
	/**
         * the logical processor is executing instructions normally.
         */
	vmxactive = 0x00000000,

	/**
         * the logical processor is inactive because it executed the hlt instruction.
         */
	vmxhlt = 0x00000001,

	/**
         * the logical processor is inactive because it incurred a triple fault1 or some other serious error.
         */
	vmxshutdown = 0x00000002,

	/**
         * the logical processor is inactive because it is waiting for a startup-ipi (sipi).
         */
	vmxwaitforsipi = 0x00000003,
} vmx_guest_activity_state;

/**
 * @}
 */

/**
 * @brief format of exit reason
 *
 * exit reason (32 bits). this field encodes the reason for the vm exit and has the structure.
 *
 * @see vol3c[24.9.1(basic vm-exit information)] (reference)
 */
typedef union {
	struct {
		/**
                 * [bits 15:0] provides basic information about the cause of the vm exit (if bit 31 is clear) or of the vm-entry failure
                 * (if bit 31 is set).
                 */
		uint32 basicexitreason : 16;
#define vmx_vmexit_reason_basic_exit_reason_bit 0
#define vmx_vmexit_reason_basic_exit_reason_flag 0xffff
#define vmx_vmexit_reason_basic_exit_reason_mask 0xffff
#define vmx_vmexit_reason_basic_exit_reason(_) (((_) >> 0) & 0xffff)

		/**
                 * [bit 16] always cleared to 0.
                 */
		uint32 always0 : 1;
#define vmx_vmexit_reason_always0_bit 16
#define vmx_vmexit_reason_always0_flag 0x10000
#define vmx_vmexit_reason_always0_mask 0x01
#define vmx_vmexit_reason_always0(_) (((_) >> 16) & 0x01)
		uint32 reserved1 : 10;
#define vmx_vmexit_reason_reserved1_bit 17
#define vmx_vmexit_reason_reserved1_flag 0x7fe0000
#define vmx_vmexit_reason_reserved1_mask 0x3ff
#define vmx_vmexit_reason_reserved1(_) (((_) >> 17) & 0x3ff)

		/**
                 * [bit 27] a vm exit saves this bit as 1 to indicate that the vm exit was incident to enclave mode.
                 */
		uint32 enclavemode : 1;
#define vmx_vmexit_reason_enclave_mode_bit 27
#define vmx_vmexit_reason_enclave_mode_flag 0x8000000
#define vmx_vmexit_reason_enclave_mode_mask 0x01
#define vmx_vmexit_reason_enclave_mode(_) (((_) >> 27) & 0x01)

		/**
                 * [bit 28] pending mtf vm exit.
                 */
		uint32 pendingmtfvmexit : 1;
#define vmx_vmexit_reason_pending_mtf_vm_exit_bit 28
#define vmx_vmexit_reason_pending_mtf_vm_exit_flag 0x10000000
#define vmx_vmexit_reason_pending_mtf_vm_exit_mask 0x01
#define vmx_vmexit_reason_pending_mtf_vm_exit(_) (((_) >> 28) & 0x01)

		/**
                 * [bit 29] vm exit from vmx root operation.
                 */
		uint32 vmexitfromvmxroor : 1;
#define vmx_vmexit_reason_vm_exit_from_vmx_roor_bit 29
#define vmx_vmexit_reason_vm_exit_from_vmx_roor_flag 0x20000000
#define vmx_vmexit_reason_vm_exit_from_vmx_roor_mask 0x01
#define vmx_vmexit_reason_vm_exit_from_vmx_roor(_) (((_) >> 29) & 0x01)
		uint32 reserved2 : 1;
#define vmx_vmexit_reason_reserved2_bit 30
#define vmx_vmexit_reason_reserved2_flag 0x40000000
#define vmx_vmexit_reason_reserved2_mask 0x01
#define vmx_vmexit_reason_reserved2(_) (((_) >> 30) & 0x01)

		/**
                 * [bit 31] vm-entry failure:
                 *   - 0 = true vm exit
                 *   - 1 = vm-entry failure
                 */
		uint32 vmentryfailure : 1;
#define vmx_vmexit_reason_vm_entry_failure_bit 31
#define vmx_vmexit_reason_vm_entry_failure_flag 0x80000000
#define vmx_vmexit_reason_vm_entry_failure_mask 0x01
#define vmx_vmexit_reason_vm_entry_failure(_) (((_) >> 31) & 0x01)
	};

	uint32 flags;
} vmx_vmexit_reason;

typedef struct {
#define io_bitmap_a_min 0x00000000
#define io_bitmap_a_max 0x00007fff
#define io_bitmap_b_min 0x00008000
#define io_bitmap_b_max 0x0000ffff
	uint8 ioa[4096];
	uint8 iob[4096];
} vmx_io_bitmap;

typedef struct {
#define msr_id_low_min 0x00000000
#define msr_id_low_max 0x00001fff
#define msr_id_high_min 0xc0000000
#define msr_id_high_max 0xc0001fff
	uint8 rdmsrlow[1024];
	uint8 rdmsrhigh[1024];
	uint8 wrmsrlow[1024];
	uint8 wrmsrhigh[1024];
} vmx_msr_bitmap;

/**
 * @defgroup ept \
 *           the extended page-table mechanism
 *
 * the extended page-table mechanism (ept) is a feature that can be used to support the virtualization of physical memory.
 * when ept is in use, certain addresses that would normally be treated as physical addresses (and used to access memory)
 * are instead treated as guest-physical addresses. guest-physical addresses are translated by traversing a set of ept
 * paging structures to produce physical addresses that are used to access memory.
 *
 * @see vol3c[28.2(the extended page table mechanism (ept))] (reference)
 * @{
 */
/**
 * @brief extended-page-table pointer (eptp)
 *
 * the extended-page-table pointer (eptp) contains the address of the base of ept pml4 table, as well as other ept
 * configuration information.
 *
 * @see vol3c[28.2.2(ept translation mechanism]
 * @see vol3c[24.6.11(extended-page-table pointer (eptp)] (reference)
 */

typedef union {
	struct {
		/**
                 * [bits 2:0] ept paging-structure memory type:
                 * - 0 = uncacheable (uc)
                 * - 6 = write-back (wb)
                 * other values are reserved.
                 *
                 * @see vol3c[28.2.6(ept and memory typing)]
                 */
		uint64 memorytype : 3;
#define ept_pointer_memory_type_bit 0
#define ept_pointer_memory_type_flag 0x07
#define ept_pointer_memory_type_mask 0x07
#define ept_pointer_memory_type(_) (((_) >> 0) & 0x07)

		/**
                 * [bits 5:3] this value is 1 less than the ept page-walk length.
                 *
                 * @see vol3c[28.2.6(ept and memory typing)]
                 */
		uint64 pagewalklength : 3;
#define ept_pointer_page_walk_length_bit 3
#define ept_pointer_page_walk_length_flag 0x38
#define ept_pointer_page_walk_length_mask 0x07
#define ept_pointer_page_walk_length(_) (((_) >> 3) & 0x07)
#define ept_page_walk_length_4 0x00000003

		/**
                 * [bit 6] setting this control to 1 enables accessed and dirty flags for ept.
                 *
                 * @see vol3c[28.2.4(accessed and dirty flags for ept)]
                 */
		uint64 enableaccessanddirtyflags : 1;
#define ept_pointer_enable_access_and_dirty_flags_bit 6
#define ept_pointer_enable_access_and_dirty_flags_flag 0x40
#define ept_pointer_enable_access_and_dirty_flags_mask 0x01
#define ept_pointer_enable_access_and_dirty_flags(_) (((_) >> 6) & 0x01)
		uint64 reserved1 : 5;

		/**
                 * [bits 47:12] bits n-1:12 of the physical address of the 4-kbyte aligned ept pml4 table.
                 */
		uint64 pageframenumber : 36;
#define ept_pointer_page_frame_number_bit 12
#define ept_pointer_page_frame_number_flag 0xfffffffff000
#define ept_pointer_page_frame_number_mask 0xfffffffff
#define ept_pointer_page_frame_number(_) (((_) >> 12) & 0xfffffffff)
		uint64 reserved2 : 16;
	};

	uint64 flags;
} ept_pointer;

/**
 * @brief format of an ept pml4 entry (pml4e) that references an ept page-directory-pointer table
 *
 * a 4-kbyte naturally aligned ept pml4 table is located at the physical address specified in bits 51:12 of the
 * extended-page-table pointer (eptp), a vm-execution control field. an ept pml4 table comprises 512 64-bit entries (ept
 * pml4es). an ept pml4e is selected using the physical address defined as follows:
 * - bits 63:52 are all 0.
 * - bits 51:12 are from the eptp.
 * - bits 11:3 are bits 47:39 of the guest-physical address.
 * - bits 2:0 are all 0.
 * because an ept pml4e is identified using bits 47:39 of the guest-physical address, it controls access to a 512- gbyte
 * region of the guest-physical-address space.
 *
 * @see vol3c[24.6.11(extended-page-table pointer (eptp)]
 */
typedef union {
	struct {
		/**
                 * [bit 0] read access; indicates whether reads are allowed from the 512-gbyte region controlled by this entry.
                 */
		uint64 readaccess : 1;
#define ept_pml4_read_access_bit 0
#define ept_pml4_read_access_flag 0x01
#define ept_pml4_read_access_mask 0x01
#define ept_pml4_read_access(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] write access; indicates whether writes are allowed from the 512-gbyte region controlled by this entry.
                 */
		uint64 writeaccess : 1;
#define ept_pml4_write_access_bit 1
#define ept_pml4_write_access_flag 0x02
#define ept_pml4_write_access_mask 0x01
#define ept_pml4_write_access(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] if the "mode-based execute control for ept" vm-execution control is 0, execute access; indicates whether
                 * instruction fetches are allowed from the 512-gbyte region controlled by this entry.
                 * if that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
                 * allowed from supervisor-mode linear addresses in the 512-gbyte region controlled by this entry.
                 */
		uint64 executeaccess : 1;
#define ept_pml4_execute_access_bit 2
#define ept_pml4_execute_access_flag 0x04
#define ept_pml4_execute_access_mask 0x01
#define ept_pml4_execute_access(_) (((_) >> 2) & 0x01)
		uint64 reserved1 : 5;

		/**
                 * [bit 8] if bit 6 of eptp is 1, accessed flag for ept; indicates whether software has accessed the 512-gbyte region
                 * controlled by this entry. ignored if bit 6 of eptp is 0.
                 *
                 * @see vol3c[28.2.4(accessed and dirty flags for ept)]
                 */
		uint64 accessed : 1;
#define ept_pml4_accessed_bit 8
#define ept_pml4_accessed_flag 0x100
#define ept_pml4_accessed_mask 0x01
#define ept_pml4_accessed(_) (((_) >> 8) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * [bit 10] execute access for user-mode linear addresses. if the "mode-based execute control for ept" vm-execution control
                 * is 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 512-gbyte region
                 * controlled by this entry. if that control is 0, this bit is ignored.
                 */
		uint64 usermodeexecute : 1;
#define ept_pml4_user_mode_execute_bit 10
#define ept_pml4_user_mode_execute_flag 0x400
#define ept_pml4_user_mode_execute_mask 0x01
#define ept_pml4_user_mode_execute(_) (((_) >> 10) & 0x01)
		uint64 reserved3 : 1;

		/**
                 * [bits 47:12] physical address of 4-kbyte aligned ept page-directory-pointer table referenced by this entry.
                 */
		uint64 pageframenumber : 36;
#define ept_pml4_page_frame_number_bit 12
#define ept_pml4_page_frame_number_flag 0xfffffffff000
#define ept_pml4_page_frame_number_mask 0xfffffffff
#define ept_pml4_page_frame_number(_) (((_) >> 12) & 0xfffffffff)
		uint64 reserved4 : 16;
	};

	uint64 flags;
} ept_pml4;

/**
 * @brief format of an ept page-directory-pointer-table entry (pdpte) that maps a 1-gbyte page
 */
typedef union {
	struct {
		/**
                 * [bit 0] read access; indicates whether reads are allowed from the 1-gbyte page referenced by this entry.
                 */
		uint64 readaccess : 1;
#define epdpte_1gb_read_access_bit 0
#define epdpte_1gb_read_access_flag 0x01
#define epdpte_1gb_read_access_mask 0x01
#define epdpte_1gb_read_access(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] write access; indicates whether writes are allowed from the 1-gbyte page referenced by this entry.
                 */
		uint64 writeaccess : 1;
#define epdpte_1gb_write_access_bit 1
#define epdpte_1gb_write_access_flag 0x02
#define epdpte_1gb_write_access_mask 0x01
#define epdpte_1gb_write_access(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] if the "mode-based execute control for ept" vm-execution control is 0, execute access; indicates whether
                 * instruction fetches are allowed from the 1-gbyte page controlled by this entry.
                 * if that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
                 * allowed from supervisor-mode linear addresses in the 1-gbyte page controlled by this entry.
                 */
		uint64 executeaccess : 1;
#define epdpte_1gb_execute_access_bit 2
#define epdpte_1gb_execute_access_flag 0x04
#define epdpte_1gb_execute_access_mask 0x01
#define epdpte_1gb_execute_access(_) (((_) >> 2) & 0x01)

		/**
                 * [bits 5:3] ept memory type for this 1-gbyte page.
                 *
                 * @see vol3c[28.2.6(ept and memory typing)]
                 */
		uint64 memorytype : 3;
#define epdpte_1gb_memory_type_bit 3
#define epdpte_1gb_memory_type_flag 0x38
#define epdpte_1gb_memory_type_mask 0x07
#define epdpte_1gb_memory_type(_) (((_) >> 3) & 0x07)

		/**
                 * [bit 6] ignore pat memory type for this 1-gbyte page.
                 *
                 * @see vol3c[28.2.6(ept and memory typing)]
                 */
		uint64 ignorepat : 1;
#define epdpte_1gb_ignore_pat_bit 6
#define epdpte_1gb_ignore_pat_flag 0x40
#define epdpte_1gb_ignore_pat_mask 0x01
#define epdpte_1gb_ignore_pat(_) (((_) >> 6) & 0x01)

		/**
                 * [bit 7] must be 1 (otherwise, this entry references an ept page directory).
                 */
		uint64 largepage : 1;
#define epdpte_1gb_large_page_bit 7
#define epdpte_1gb_large_page_flag 0x80
#define epdpte_1gb_large_page_mask 0x01
#define epdpte_1gb_large_page(_) (((_) >> 7) & 0x01)

		/**
                 * [bit 8] if bit 6 of eptp is 1, accessed flag for ept; indicates whether software has accessed the 1-gbyte page
                 * referenced by this entry. ignored if bit 6 of eptp is 0.
                 *
                 * @see vol3c[28.2.4(accessed and dirty flags for ept)]
                 */
		uint64 accessed : 1;
#define epdpte_1gb_accessed_bit 8
#define epdpte_1gb_accessed_flag 0x100
#define epdpte_1gb_accessed_mask 0x01
#define epdpte_1gb_accessed(_) (((_) >> 8) & 0x01)

		/**
                 * [bit 9] if bit 6 of eptp is 1, dirty flag for ept; indicates whether software has written to the 1-gbyte page referenced
                 * by this entry. ignored if bit 6 of eptp is 0.
                 *
                 * @see vol3c[28.2.4(accessed and dirty flags for ept)]
                 */
		uint64 dirty : 1;
#define epdpte_1gb_dirty_bit 9
#define epdpte_1gb_dirty_flag 0x200
#define epdpte_1gb_dirty_mask 0x01
#define epdpte_1gb_dirty(_) (((_) >> 9) & 0x01)

		/**
                 * [bit 10] execute access for user-mode linear addresses. if the "mode-based execute control for ept" vm-execution control
                 * is 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 1-gbyte page controlled
                 * by this entry. if that control is 0, this bit is ignored.
                 */
		uint64 usermodeexecute : 1;
#define epdpte_1gb_user_mode_execute_bit 10
#define epdpte_1gb_user_mode_execute_flag 0x400
#define epdpte_1gb_user_mode_execute_mask 0x01
#define epdpte_1gb_user_mode_execute(_) (((_) >> 10) & 0x01)
		uint64 reserved1 : 19;

		/**
                 * [bits 47:30] physical address of 4-kbyte aligned ept page-directory-pointer table referenced by this entry.
                 */
		uint64 pageframenumber : 18;
#define epdpte_1gb_page_frame_number_bit 30
#define epdpte_1gb_page_frame_number_flag 0xffffc0000000
#define epdpte_1gb_page_frame_number_mask 0x3ffff
#define epdpte_1gb_page_frame_number(_) (((_) >> 30) & 0x3ffff)
		uint64 reserved2 : 15;

		/**
                 * [bit 63] suppress \#ve. if the "ept-violation \#ve" vm-execution control is 1, ept violations caused by accesses to this
                 * page are convertible to virtualization exceptions only if this bit is 0. if "ept-violation \#ve" vmexecution control is
                 * 0, this bit is ignored.
                 *
                 * @see vol3c[25.5.6.1(convertible ept violations)]
                 */
		uint64 suppressve : 1;
#define epdpte_1gb_suppress_ve_bit 63
#define epdpte_1gb_suppress_ve_flag 0x8000000000000000
#define epdpte_1gb_suppress_ve_mask 0x01
#define epdpte_1gb_suppress_ve(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} epdpte_1gb;

/**
 * @brief format of an ept page-directory-pointer-table entry (pdpte) that references an ept page directory
 */
typedef union {
	struct {
		/**
                 * [bit 0] read access; indicates whether reads are allowed from the 1-gbyte region controlled by this entry.
                 */
		uint64 readaccess : 1;
#define epdpte_read_access_bit 0
#define epdpte_read_access_flag 0x01
#define epdpte_read_access_mask 0x01
#define epdpte_read_access(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] write access; indicates whether writes are allowed from the 1-gbyte region controlled by this entry.
                 */
		uint64 writeaccess : 1;
#define epdpte_write_access_bit 1
#define epdpte_write_access_flag 0x02
#define epdpte_write_access_mask 0x01
#define epdpte_write_access(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] if the "mode-based execute control for ept" vm-execution control is 0, execute access; indicates whether
                 * instruction fetches are allowed from the 1-gbyte region controlled by this entry.
                 * if that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
                 * allowed from supervisor-mode linear addresses in the 1-gbyte region controlled by this entry.
                 */
		uint64 executeaccess : 1;
#define epdpte_execute_access_bit 2
#define epdpte_execute_access_flag 0x04
#define epdpte_execute_access_mask 0x01
#define epdpte_execute_access(_) (((_) >> 2) & 0x01)
		uint64 reserved1 : 5;

		/**
                 * [bit 8] if bit 6 of eptp is 1, accessed flag for ept; indicates whether software has accessed the 1-gbyte region
                 * controlled by this entry. ignored if bit 6 of eptp is 0.
                 *
                 * @see vol3c[28.2.4(accessed and dirty flags for ept)]
                 */
		uint64 accessed : 1;
#define epdpte_accessed_bit 8
#define epdpte_accessed_flag 0x100
#define epdpte_accessed_mask 0x01
#define epdpte_accessed(_) (((_) >> 8) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * [bit 10] execute access for user-mode linear addresses. if the "mode-based execute control for ept" vm-execution control
                 * is 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 1-gbyte region controlled
                 * by this entry. if that control is 0, this bit is ignored.
                 */
		uint64 usermodeexecute : 1;
#define epdpte_user_mode_execute_bit 10
#define epdpte_user_mode_execute_flag 0x400
#define epdpte_user_mode_execute_mask 0x01
#define epdpte_user_mode_execute(_) (((_) >> 10) & 0x01)
		uint64 reserved3 : 1;

		/**
                 * [bits 47:12] physical address of 4-kbyte aligned ept page-directory-pointer table referenced by this entry.
                 */
		uint64 pageframenumber : 36;
#define epdpte_page_frame_number_bit 12
#define epdpte_page_frame_number_flag 0xfffffffff000
#define epdpte_page_frame_number_mask 0xfffffffff
#define epdpte_page_frame_number(_) (((_) >> 12) & 0xfffffffff)
		uint64 reserved4 : 16;
	};

	uint64 flags;
} epdpte;

/**
 * @brief format of an ept page-directory entry (pde) that maps a 2-mbyte page
 */
typedef union {
	struct {
		/**
                 * [bit 0] read access; indicates whether reads are allowed from the 2-mbyte page referenced by this entry.
                 */
		uint64 readaccess : 1;
#define epde_2mb_read_access_bit 0
#define epde_2mb_read_access_flag 0x01
#define epde_2mb_read_access_mask 0x01
#define epde_2mb_read_access(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] write access; indicates whether writes are allowed from the 2-mbyte page referenced by this entry.
                 */
		uint64 writeaccess : 1;
#define epde_2mb_write_access_bit 1
#define epde_2mb_write_access_flag 0x02
#define epde_2mb_write_access_mask 0x01
#define epde_2mb_write_access(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] if the "mode-based execute control for ept" vm-execution control is 0, execute access; indicates whether
                 * instruction fetches are allowed from the 2-mbyte page controlled by this entry.
                 * if that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
                 * allowed from supervisor-mode linear addresses in the 2-mbyte page controlled by this entry.
                 */
		uint64 executeaccess : 1;
#define epde_2mb_execute_access_bit 2
#define epde_2mb_execute_access_flag 0x04
#define epde_2mb_execute_access_mask 0x01
#define epde_2mb_execute_access(_) (((_) >> 2) & 0x01)

		/**
                 * [bits 5:3] ept memory type for this 2-mbyte page.
                 *
                 * @see vol3c[28.2.6(ept and memory typing)]
                 */
		uint64 memorytype : 3;
#define epde_2mb_memory_type_bit 3
#define epde_2mb_memory_type_flag 0x38
#define epde_2mb_memory_type_mask 0x07
#define epde_2mb_memory_type(_) (((_) >> 3) & 0x07)

		/**
                 * [bit 6] ignore pat memory type for this 2-mbyte page.
                 *
                 * @see vol3c[28.2.6(ept and memory typing)]
                 */
		uint64 ignorepat : 1;
#define epde_2mb_ignore_pat_bit 6
#define epde_2mb_ignore_pat_flag 0x40
#define epde_2mb_ignore_pat_mask 0x01
#define epde_2mb_ignore_pat(_) (((_) >> 6) & 0x01)

		/**
                 * [bit 7] must be 1 (otherwise, this entry references an ept page table).
                 */
		uint64 largepage : 1;
#define epde_2mb_large_page_bit 7
#define epde_2mb_large_page_flag 0x80
#define epde_2mb_large_page_mask 0x01
#define epde_2mb_large_page(_) (((_) >> 7) & 0x01)

		/**
                 * [bit 8] if bit 6 of eptp is 1, accessed flag for ept; indicates whether software has accessed the 2-mbyte page
                 * referenced by this entry. ignored if bit 6 of eptp is 0.
                 *
                 * @see vol3c[28.2.4(accessed and dirty flags for ept)]
                 */
		uint64 accessed : 1;
#define epde_2mb_accessed_bit 8
#define epde_2mb_accessed_flag 0x100
#define epde_2mb_accessed_mask 0x01
#define epde_2mb_accessed(_) (((_) >> 8) & 0x01)

		/**
                 * [bit 9] if bit 6 of eptp is 1, dirty flag for ept; indicates whether software has written to the 2-mbyte page referenced
                 * by this entry. ignored if bit 6 of eptp is 0.
                 *
                 * @see vol3c[28.2.4(accessed and dirty flags for ept)]
                 */
		uint64 dirty : 1;
#define epde_2mb_dirty_bit 9
#define epde_2mb_dirty_flag 0x200
#define epde_2mb_dirty_mask 0x01
#define epde_2mb_dirty(_) (((_) >> 9) & 0x01)

		/**
                 * [bit 10] execute access for user-mode linear addresses. if the "mode-based execute control for ept" vm-execution control
                 * is 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 2-mbyte page controlled
                 * by this entry. if that control is 0, this bit is ignored.
                 */
		uint64 usermodeexecute : 1;
#define epde_2mb_user_mode_execute_bit 10
#define epde_2mb_user_mode_execute_flag 0x400
#define epde_2mb_user_mode_execute_mask 0x01
#define epde_2mb_user_mode_execute(_) (((_) >> 10) & 0x01)
		uint64 reserved1 : 10;

		/**
                 * [bits 47:21] physical address of 4-kbyte aligned ept page-directory-pointer table referenced by this entry.
                 */
		uint64 pageframenumber : 27;
#define epde_2mb_page_frame_number_bit 21
#define epde_2mb_page_frame_number_flag 0xffffffe00000
#define epde_2mb_page_frame_number_mask 0x7ffffff
#define epde_2mb_page_frame_number(_) (((_) >> 21) & 0x7ffffff)
		uint64 reserved2 : 15;

		/**
                 * [bit 63] suppress \#ve. if the "ept-violation \#ve" vm-execution control is 1, ept violations caused by accesses to this
                 * page are convertible to virtualization exceptions only if this bit is 0. if "ept-violation \#ve" vmexecution control is
                 * 0, this bit is ignored.
                 *
                 * @see vol3c[25.5.6.1(convertible ept violations)]
                 */
		uint64 suppressve : 1;
#define epde_2mb_suppress_ve_bit 63
#define epde_2mb_suppress_ve_flag 0x8000000000000000
#define epde_2mb_suppress_ve_mask 0x01
#define epde_2mb_suppress_ve(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} epde_2mb;

/**
 * @brief format of an ept page-directory entry (pde) that references an ept page table
 */
typedef union {
	struct {
		/**
                 * [bit 0] read access; indicates whether reads are allowed from the 2-mbyte region controlled by this entry.
                 */
		uint64 readaccess : 1;
#define epde_read_access_bit 0
#define epde_read_access_flag 0x01
#define epde_read_access_mask 0x01
#define epde_read_access(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] write access; indicates whether writes are allowed from the 2-mbyte region controlled by this entry.
                 */
		uint64 writeaccess : 1;
#define epde_write_access_bit 1
#define epde_write_access_flag 0x02
#define epde_write_access_mask 0x01
#define epde_write_access(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] if the "mode-based execute control for ept" vm-execution control is 0, execute access; indicates whether
                 * instruction fetches are allowed from the 2-mbyte region controlled by this entry.
                 * if that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
                 * allowed from supervisor-mode linear addresses in the 2-mbyte region controlled by this entry.
                 */
		uint64 executeaccess : 1;
#define epde_execute_access_bit 2
#define epde_execute_access_flag 0x04
#define epde_execute_access_mask 0x01
#define epde_execute_access(_) (((_) >> 2) & 0x01)
		uint64 reserved1 : 5;

		/**
                 * [bit 8] if bit 6 of eptp is 1, accessed flag for ept; indicates whether software has accessed the 2-mbyte region
                 * controlled by this entry. ignored if bit 6 of eptp is 0.
                 *
                 * @see vol3c[28.2.4(accessed and dirty flags for ept)]
                 */
		uint64 accessed : 1;
#define epde_accessed_bit 8
#define epde_accessed_flag 0x100
#define epde_accessed_mask 0x01
#define epde_accessed(_) (((_) >> 8) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * [bit 10] execute access for user-mode linear addresses. if the "mode-based execute control for ept" vm-execution control
                 * is 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 2-mbyte region controlled
                 * by this entry. if that control is 0, this bit is ignored.
                 */
		uint64 usermodeexecute : 1;
#define epde_user_mode_execute_bit 10
#define epde_user_mode_execute_flag 0x400
#define epde_user_mode_execute_mask 0x01
#define epde_user_mode_execute(_) (((_) >> 10) & 0x01)
		uint64 reserved3 : 1;

		/**
                 * [bits 47:12] physical address of 4-kbyte aligned ept page table referenced by this entry.
                 */
		uint64 pageframenumber : 36;
#define epde_page_frame_number_bit 12
#define epde_page_frame_number_flag 0xfffffffff000
#define epde_page_frame_number_mask 0xfffffffff
#define epde_page_frame_number(_) (((_) >> 12) & 0xfffffffff)
		uint64 reserved4 : 16;
	};

	uint64 flags;
} epde;

/**
 * @brief format of an ept page-table entry that maps a 4-kbyte page
 */
typedef union {
	struct {
		/**
                 * [bit 0] read access; indicates whether reads are allowed from the 4-kbyte page referenced by this entry.
                 */
		uint64 readaccess : 1;
#define epte_read_access_bit 0
#define epte_read_access_flag 0x01
#define epte_read_access_mask 0x01
#define epte_read_access(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] write access; indicates whether writes are allowed from the 4-kbyte page referenced by this entry.
                 */
		uint64 writeaccess : 1;
#define epte_write_access_bit 1
#define epte_write_access_flag 0x02
#define epte_write_access_mask 0x01
#define epte_write_access(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] if the "mode-based execute control for ept" vm-execution control is 0, execute access; indicates whether
                 * instruction fetches are allowed from the 4-kbyte page controlled by this entry.
                 * if that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
                 * allowed from supervisor-mode linear addresses in the 4-kbyte page controlled by this entry.
                 */
		uint64 executeaccess : 1;
#define epte_execute_access_bit 2
#define epte_execute_access_flag 0x04
#define epte_execute_access_mask 0x01
#define epte_execute_access(_) (((_) >> 2) & 0x01)

		/**
                 * [bits 5:3] ept memory type for this 4-kbyte page.
                 *
                 * @see vol3c[28.2.6(ept and memory typing)]
                 */
		uint64 memorytype : 3;
#define epte_memory_type_bit 3
#define epte_memory_type_flag 0x38
#define epte_memory_type_mask 0x07
#define epte_memory_type(_) (((_) >> 3) & 0x07)

		/**
                 * [bit 6] ignore pat memory type for this 4-kbyte page.
                 *
                 * @see vol3c[28.2.6(ept and memory typing)]
                 */
		uint64 ignorepat : 1;
#define epte_ignore_pat_bit 6
#define epte_ignore_pat_flag 0x40
#define epte_ignore_pat_mask 0x01
#define epte_ignore_pat(_) (((_) >> 6) & 0x01)
		uint64 reserved1 : 1;

		/**
                 * [bit 8] if bit 6 of eptp is 1, accessed flag for ept; indicates whether software has accessed the 4-kbyte page
                 * referenced by this entry. ignored if bit 6 of eptp is 0.
                 *
                 * @see vol3c[28.2.4(accessed and dirty flags for ept)]
                 */
		uint64 accessed : 1;
#define epte_accessed_bit 8
#define epte_accessed_flag 0x100
#define epte_accessed_mask 0x01
#define epte_accessed(_) (((_) >> 8) & 0x01)

		/**
                 * [bit 9] if bit 6 of eptp is 1, dirty flag for ept; indicates whether software has written to the 4-kbyte page referenced
                 * by this entry. ignored if bit 6 of eptp is 0.
                 *
                 * @see vol3c[28.2.4(accessed and dirty flags for ept)]
                 */
		uint64 dirty : 1;
#define epte_dirty_bit 9
#define epte_dirty_flag 0x200
#define epte_dirty_mask 0x01
#define epte_dirty(_) (((_) >> 9) & 0x01)

		/**
                 * [bit 10] execute access for user-mode linear addresses. if the "mode-based execute control for ept" vm-execution control
                 * is 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 4-kbyte page controlled
                 * by this entry. if that control is 0, this bit is ignored.
                 */
		uint64 usermodeexecute : 1;
#define epte_user_mode_execute_bit 10
#define epte_user_mode_execute_flag 0x400
#define epte_user_mode_execute_mask 0x01
#define epte_user_mode_execute(_) (((_) >> 10) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * [bits 47:12] physical address of the 4-kbyte page referenced by this entry.
                 */
		uint64 pageframenumber : 36;
#define epte_page_frame_number_bit 12
#define epte_page_frame_number_flag 0xfffffffff000
#define epte_page_frame_number_mask 0xfffffffff
#define epte_page_frame_number(_) (((_) >> 12) & 0xfffffffff)
		uint64 reserved3 : 15;

		/**
                 * [bit 63] suppress \#ve. if the "ept-violation \#ve" vm-execution control is 1, ept violations caused by accesses to this
                 * page are convertible to virtualization exceptions only if this bit is 0. if "ept-violation \#ve" vmexecution control is
                 * 0, this bit is ignored.
                 *
                 * @see vol3c[25.5.6.1(convertible ept violations)]
                 */
		uint64 suppressve : 1;
#define epte_suppress_ve_bit 63
#define epte_suppress_ve_flag 0x8000000000000000
#define epte_suppress_ve_mask 0x01
#define epte_suppress_ve(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} epte;

/**
 * @brief format of a common ept entry
 */
typedef union {
	struct {
		uint64 readaccess : 1;
#define ept_entry_read_access_bit 0
#define ept_entry_read_access_flag 0x01
#define ept_entry_read_access_mask 0x01
#define ept_entry_read_access(_) (((_) >> 0) & 0x01)
		uint64 writeaccess : 1;
#define ept_entry_write_access_bit 1
#define ept_entry_write_access_flag 0x02
#define ept_entry_write_access_mask 0x01
#define ept_entry_write_access(_) (((_) >> 1) & 0x01)
		uint64 executeaccess : 1;
#define ept_entry_execute_access_bit 2
#define ept_entry_execute_access_flag 0x04
#define ept_entry_execute_access_mask 0x01
#define ept_entry_execute_access(_) (((_) >> 2) & 0x01)
		uint64 memorytype : 3;
#define ept_entry_memory_type_bit 3
#define ept_entry_memory_type_flag 0x38
#define ept_entry_memory_type_mask 0x07
#define ept_entry_memory_type(_) (((_) >> 3) & 0x07)
		uint64 ignorepat : 1;
#define ept_entry_ignore_pat_bit 6
#define ept_entry_ignore_pat_flag 0x40
#define ept_entry_ignore_pat_mask 0x01
#define ept_entry_ignore_pat(_) (((_) >> 6) & 0x01)
		uint64 largepage : 1;
#define ept_entry_large_page_bit 7
#define ept_entry_large_page_flag 0x80
#define ept_entry_large_page_mask 0x01
#define ept_entry_large_page(_) (((_) >> 7) & 0x01)
		uint64 accessed : 1;
#define ept_entry_accessed_bit 8
#define ept_entry_accessed_flag 0x100
#define ept_entry_accessed_mask 0x01
#define ept_entry_accessed(_) (((_) >> 8) & 0x01)
		uint64 dirty : 1;
#define ept_entry_dirty_bit 9
#define ept_entry_dirty_flag 0x200
#define ept_entry_dirty_mask 0x01
#define ept_entry_dirty(_) (((_) >> 9) & 0x01)
		uint64 usermodeexecute : 1;
#define ept_entry_user_mode_execute_bit 10
#define ept_entry_user_mode_execute_flag 0x400
#define ept_entry_user_mode_execute_mask 0x01
#define ept_entry_user_mode_execute(_) (((_) >> 10) & 0x01)
		uint64 reserved1 : 1;
		uint64 pageframenumber : 36;
#define ept_entry_page_frame_number_bit 12
#define ept_entry_page_frame_number_flag 0xfffffffff000
#define ept_entry_page_frame_number_mask 0xfffffffff
#define ept_entry_page_frame_number(_) (((_) >> 12) & 0xfffffffff)
		uint64 reserved2 : 15;
		uint64 suppressve : 1;
#define ept_entry_suppress_ve_bit 63
#define ept_entry_suppress_ve_flag 0x8000000000000000
#define ept_entry_suppress_ve_mask 0x01
#define ept_entry_suppress_ve(_) (((_) >> 63) & 0x01)
	};

	uint64 flags;
} ept_entry;

/**
 * @defgroup ept_table_level \
 *           ept table level numbers
 *
 * ept table level numbers.
 * @{
 */
#define ept_level_pml4e 0x00000003
#define ept_level_pdpte 0x00000002
#define ept_level_pde 0x00000001
#define ept_level_pte 0x00000000
/**
 * @}
 */

/**
 * @defgroup ept_entry_count \
 *           ept entry counts
 *
 * ept entry counts.
 * @{
 */
#define ept_pml4e_entry_count 0x00000200
#define ept_pdpte_entry_count 0x00000200
#define ept_pde_entry_count 0x00000200
#define ept_pte_entry_count 0x00000200
/**
 * @}
 */

/**
 * @}
 */

typedef enum {
	/**
         * if the invept type is 1, the logical processor invalidates all guest-physical mappings and combined mappings associated
         * with the ep4ta specified in the invept descriptor. combined mappings for that ep4ta are invalidated for all vpids and
         * all pcids. (the instruction may invalidate mappings associated with other ep4tas.)
         */
	inveptsinglecontext = 0x00000001,

	/**
         * if the invept type is 2, the logical processor invalidates guest-physical mappings and combined mappings associated with
         * all ep4tas (and, for combined mappings, for all vpids and pcids).
         */
	inveptallcontext = 0x00000002,
} invept_type;

typedef enum {
	/**
         * if the invvpid type is 0, the logical processor invalidates linear mappings and combined mappings associated with the
         * vpid specified in the invvpid descriptor and that would be used to translate the linear address specified in of the
         * invvpid descriptor. linear mappings and combined mappings for that vpid and linear address are invalidated for all pcids
         * and, for combined mappings, all ep4tas. (the instruction may also invalidate mappings associated with other vpids and
         * for other linear addresses).
         */
	invvpidindividualaddress = 0x00000000,

	/**
         * if the invvpid type is 1, the logical processor invalidates all linear mappings and combined mappings associated with
         * the vpid specified in the invvpid descriptor. linear mappings and combined mappings for that vpid are invalidated for
         * all pcids and, for combined mappings, all ep4tas. (the instruction may also invalidate mappings associated with other
         * vpids).
         */
	invvpidsinglecontext = 0x00000001,

	/**
         * if the invvpid type is 2, the logical processor invalidates linear mappings and combined mappings associated with all
         * vpids except vpid 0000h and with all pcids. (the instruction may also invalidate linear mappings with vpid 0000h.)
         * combined mappings are invalidated for all ep4tas.
         */
	invvpidallcontext = 0x00000002,

	/**
         * if the invvpid type is 3, the logical processor invalidates linear mappings and combined mappings associated with the
         * vpid specified in the invvpid descriptor. linear mappings and combined mappings for that vpid are invalidated for all
         * pcids and, for combined mappings, all ep4tas. the logical processor is not required to invalidate information that was
         * used for global translations (although it may do so). (the instruction may also invalidate mappings associated with
         * other vpids).
         *
         * @see vol3c[4.10(caching translation information)]
         */
	invvpidsinglecontextretainingglobals = 0x00000003,
} invvpid_type;

typedef struct {
	uint64 eptpointer;

	/**
         * must be zero.
         */
	uint64 reserved;
} invept_descriptor;

typedef struct {
	uint16 vpid;

	/**
         * must be zero.
         */
	uint16 reserved1;

	/**
         * must be zero.
         */
	uint32 reserved2;
	uint64 linearaddress;
} invvpid_descriptor;

/**
 * @brief format of the vmcs region
 *
 * a logical processor uses virtual-machine control data structures (vmcss) while it is in vmx operation. these manage
 * transitions into and out of vmx non-root operation (vm entries and vm exits) as well as processor behavior in vmx
 * non-root operation. this structure is manipulated by the new instructions vmclear, vmptrld, vmread, and vmwrite.
 * a vmcs region comprises up to 4-kbytes. the exact size is implementation specific and can be determined by consulting
 * the vmx capability msr ia32_vmx_basic.
 *
 * @see vol3c[24.2(format of the vmcs region)] (reference)
 */
typedef struct {
	struct {
		/**
                 * @brief vmcs revision identifier
                 *
                 * [bits 30:0] processors that maintain vmcs data in different formats (see below) use different vmcs revision identifiers.
                 * these identifiers enable software to avoid using a vmcs region formatted for one processor on a processor that uses a
                 * different format.
                 * software should write the vmcs revision identifier to the vmcs region before using that region for a vmcs. the vmcs
                 * revision identifier is never written by the processor; vmptrld fails if its operand references a vmcs region whose vmcs
                 * revision identifier differs from that used by the processor.
                 * software can discover the vmcs revision identifier that a processor uses by reading the vmx capability msr
                 * ia32_vmx_basic.
                 *
                 * @see vol3c[24.6.2(processor-based vm-execution controls)]
                 * @see vol3d[a.1(basic vmx information)]
                 */
		uint32 revisionid : 31;

		/**
                 * @brief shadow-vmcs indicator
                 *
                 * [bit 31] software should clear or set the shadow-vmcs indicator depending on whether the vmcs is to be an ordinary vmcs
                 * or a shadow vmcs. vmptrld fails if the shadow-vmcs indicator is set and the processor does not support the 1-setting of
                 * the "vmcs shadowing" vm-execution control. software can discover support for this setting by reading the vmx capability
                 * msr ia32_vmx_procbased_ctls2.
                 *
                 * @see vol3c[24.10(vmcs types ordinary and shadow)]
                 */
		uint32 shadowvmcsindicator : 1;
	};

	/**
         * @brief vmx-abort indicator
         *
         * the contents of these bits do not control processor operation in any way. a logical processor writes a non-zero value
         * into these bits if a vmx abort occurs. software may also write into this field.
         *
         * @see vol3d[27.7(vmx aborts)]
         */
	uint32 abortindicator;

	/**
         * @brief vmcs data (implementation-specific format)
         *
         * these parts of the vmcs control vmx non-root operation and the vmx transitions.
         * the format of these data is implementation-specific. to ensure proper behavior in vmx operation, software should
         * maintain the vmcs region and related structures in writeback cacheable memory. future implementations may allow or
         * require a different memory type. software should consult the vmx capability msr ia32_vmx_basic.
         *
         * @see vol3c[24.11.4(software access to related structures)]
         * @see vol3d[a.1(basic vmx information)]
         */
	uint8 data[4088];
} vmcs;

/**
 * @brief format of the vmxon region
 *
 * before executing vmxon, software allocates a region of memory that the logical processor uses to support vmx operation.
 * this region is called the vmxon region.
 * a vmxon region comprises up to 4-kbytes. the exact size is implementation specific and can be determined by consulting
 * the vmx capability msr ia32_vmx_basic.
 *
 * @see vol3c[24.11.5(vmxon region)] (reference)
 */
typedef struct {
	struct {
		/**
                 * @brief vmcs revision identifier
                 *
                 * [bits 30:0] before executing vmxon, software should write the vmcs revision identifier to the vmxon region.
                 * (specifically, it should write the 31-bit vmcs revision identifier to bits 30:0 of the first 4 bytes of the vmxon
                 * region; bit 31 should be cleared to 0.)
                 *
                 * @see vmcs
                 * @see vol3c[24.2(format of the vmcs region)]
                 * @see vol3c[24.11.5(vmxon region)]
                 */
		uint32 revisionid : 31;

		/**
                 * [bit 31] bit 31 is always 0.
                 */
		uint32 mustbezero : 1;
	};

	/**
         * @brief vmxon data (implementation-specific format)
         *
         * the format of these data is implementation-specific. to ensure proper behavior in vmx operation, software should not
         * access or modify the vmxon region of a logical processor between execution of vmxon and vmxoff on that logical
         * processor. doing otherwise may lead to unpredictable behavior.
         *
         * @see vol3c[24.11.4(software access to related structures)]
         * @see vol3d[a.1(basic vmx information)]
         */
	uint8 data[4092];
} vmxon;

/**
 * @defgroup vmcs_fields \
 *           vmcs (vm control structure)
 *
 * every component of the vmcs is encoded by a 32-bit field that can be used by vmread and vmwrite. this enumerates all
 * fields in the vmcs and their encodings. fields are grouped by width (16-bit, 32-bit, etc.) and type (guest-state,
 * host-state, etc.).
 *
 * @see vol3d[b(appendix b field encoding in vmcs)] (reference)
 * @{
 */
typedef union {
	struct {
		/**
                 * [bit 0] access type (0 = full; 1 = high); must be full for 16-bit, 32-bit, and natural-width fields.
                 */
		uint16 accesstype : 1;
#define vmcs_component_encoding_access_type_bit 0
#define vmcs_component_encoding_access_type_flag 0x01
#define vmcs_component_encoding_access_type_mask 0x01
#define vmcs_component_encoding_access_type(_) (((_) >> 0) & 0x01)

		/**
                 * [bits 9:1] index.
                 */
		uint16 index : 9;
#define vmcs_component_encoding_index_bit 1
#define vmcs_component_encoding_index_flag 0x3fe
#define vmcs_component_encoding_index_mask 0x1ff
#define vmcs_component_encoding_index(_) (((_) >> 1) & 0x1ff)

		/**
                 * [bits 11:10] type:
                 * 0: control
                 * 1: vm-exit information
                 * 2: guest state
                 * 3: host state
                 */
		uint16 type : 2;
#define vmcs_component_encoding_type_bit 10
#define vmcs_component_encoding_type_flag 0xc00
#define vmcs_component_encoding_type_mask 0x03
#define vmcs_component_encoding_type(_) (((_) >> 10) & 0x03)

		/**
                 * [bit 12] reserved (must be 0).
                 */
		uint16 mustbezero : 1;
#define vmcs_component_encoding_must_be_zero_bit 12
#define vmcs_component_encoding_must_be_zero_flag 0x1000
#define vmcs_component_encoding_must_be_zero_mask 0x01
#define vmcs_component_encoding_must_be_zero(_) (((_) >> 12) & 0x01)

		/**
                 * [bits 14:13] width:
                 * 0: 16-bit
                 * 1: 64-bit
                 * 2: 32-bit
                 * 3: natural-width
                 */
		uint16 width : 2;
#define vmcs_component_encoding_width_bit 13
#define vmcs_component_encoding_width_flag 0x6000
#define vmcs_component_encoding_width_mask 0x03
#define vmcs_component_encoding_width(_) (((_) >> 13) & 0x03)
		uint16 reserved1 : 1;
	};

	uint16 flags;
} vmcs_component_encoding;

/**
 * @defgroup vmcs_16_bit \
 *           16-bit fields
 *
 * 16-bit fields.
 *
 * @see vol3d[b.1(16-bit fields)] (reference)
 * @{
 */
/**
 * @defgroup vmcs_16_bit_control_fields \
 *           16-bit control fields
 *
 * 16-bit control fields.
 * @{
 */
/**
 * virtual-processor identifier (vpid).
 *
 * @remarks this field exists only on processors that support the 1-setting of the "enable vpid" vm-execution control.
 */
#define vmcs_ctrl_virtual_processor_identifier 0x00000000

/**
 * posted-interrupt notification list.
 *
 * @remarks this field exists only on processors that support the 1-setting of the "process posted interrupts" vm-execution
 *          control.
 */
#define vmcs_ctrl_posted_interrupt_notification_list 0x00000002

/**
 * eptp index.
 *
 * @remarks this field exists only on processors that support the 1-setting of the "ept-violation \#ve" vm-execution
 *          control.
 */
#define vmcs_ctrl_eptp_index 0x00000004
/**
 * @}
 */

/**
 * @defgroup vmcs_16_bit_guest_state_fields \
 *           16-bit guest-state fields
 *
 * 16-bit guest-state fields.
 * @{
 */
/**
 * guest es selector.
 */
#define vmcs_guest_es_selector 0x00000800

/**
 * guest cs selector.
 */
#define vmcs_guest_cs_selector 0x00000802

/**
 * guest ss selector.
 */
#define vmcs_guest_ss_selector 0x00000804

/**
 * guest ds selector.
 */
#define vmcs_guest_ds_selector 0x00000806

/**
 * guest fs selector.
 */
#define vmcs_guest_fs_selector 0x00000808

/**
 * guest gs selector.
 */
#define vmcs_guest_gs_selector 0x0000080a

/**
 * guest ldtr selector.
 */
#define vmcs_guest_ldtr_selector 0x0000080c

/**
 * guest tr selector.
 */
#define vmcs_guest_tr_selector 0x0000080e

/**
 * guest interrupt status.
 *
 * @remarks this field exists only on processors that support the 1-setting of the "virtual-interrupt delivery"
 *          vm-execution control.
 */
#define vmcs_guest_interrupt_status 0x00000810

/**
 * pml index.
 *
 * @remarks this field exists only on processors that support the 1-setting of the "enable pml" vm-execution control.
 */
#define vmcs_guest_pml_index 0x00000812
/**
 * @}
 */

/**
 * @defgroup vmcs_16_bit_host_state_fields \
 *           16-bit host-state fields
 *
 * 16-bit host-state fields.
 * @{
 */
/**
 * host es selector.
 */
#define vmcs_host_es_selector 0x00000c00

/**
 * host cs selector.
 */
#define vmcs_host_cs_selector 0x00000c02

/**
 * host ss selector.
 */
#define vmcs_host_ss_selector 0x00000c04

/**
 * host ds selector.
 */
#define vmcs_host_ds_selector 0x00000c06

/**
 * host fs selector.
 */
#define vmcs_host_fs_selector 0x00000c08

/**
 * host gs selector.
 */
#define vmcs_host_gs_selector 0x00000c0a

/**
 * host tr selector.
 */
#define vmcs_host_tr_selector 0x00000c0c
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup vmcs_64_bit \
 *           64-bit fields
 *
 * 64-bit fields.
 *
 * @see vol3d[b.2(64-bit fields)] (reference)
 * @{
 */
/**
 * @defgroup vmcs_64_bit_control_fields \
 *           64-bit control fields
 *
 * 64-bit control fields.
 * @{
 */
/**
 * address of i/o bitmap a.
 */
#define vmcs_ctrl_io_bitmap_a_address 0x00002000

/**
 * address of i/o bitmap b.
 */
#define vmcs_ctrl_io_bitmap_b_address 0x00002002

/**
 * address of msr bitmaps.
 */
#define vmcs_ctrl_msr_bitmap_address 0x00002004

/**
 * vm-exit msr-store address.
 */
#define vmcs_ctrl_vmexit_msr_store_address 0x00002006

/**
 * vm-exit msr-load address.
 */
#define vmcs_ctrl_vmexit_msr_load_address 0x00002008

/**
 * vm-entry msr-load address.
 */
#define vmcs_ctrl_vmentry_msr_load_address 0x0000200a

/**
 * executive-vmcs pointer.
 */
#define vmcs_ctrl_executive_vmcs_pointer 0x0000200c

/**
 * pml address.
 */
#define vmcs_ctrl_pml_address 0x0000200e

/**
 * tsc offset.
 */
#define vmcs_ctrl_tsc_offset 0x00002010

/**
 * virtual-apic address.
 */
#define vmcs_ctrl_virtual_apic_address 0x00002012

/**
 * apic-access address.
 */
#define vmcs_ctrl_apic_access_address 0x00002014

/**
 * posted-interrupt descriptor address
 */
#define vmcs_ctrl_posted_interrupt_descriptor_address 0x00002016

/**
 * vm-function controls.
 */
#define vmcs_ctrl_vmfunc_controls 0x00002018

/**
 * ept pointer.
 */
#define vmcs_ctrl_ept_pointer 0x0000201a

/**
 * eoi-exit bitmap 0.
 */
#define vmcs_ctrl_eoi_exit_bitmap_0 0x0000201c

/**
 * eoi-exit bitmap 1.
 */
#define vmcs_ctrl_eoi_exit_bitmap_1 0x0000201e

/**
 * eoi-exit bitmap 2.
 */
#define vmcs_ctrl_eoi_exit_bitmap_2 0x00002020

/**
 * eoi-exit bitmap 3.
 */
#define vmcs_ctrl_eoi_exit_bitmap_3 0x00002022

/**
 * eptp-list address.
 */
#define vmcs_ctrl_ept_pointer_list_address 0x00002024

/**
 * vmread-bitmap address.
 */
#define vmcs_ctrl_vmread_bitmap_address 0x00002026

/**
 * vmwrite-bitmap address.
 */
#define vmcs_ctrl_vmwrite_bitmap_address 0x00002028

/**
 * virtualization-exception information address.
 */
#define vmcs_ctrl_virtualization_exception_information_address 0x0000202a

/**
 * xss-exiting bitmap.
 */
#define vmcs_ctrl_xss_exiting_bitmap 0x0000202c

/**
 * encls-exiting bitmap.
 */
#define vmcs_ctrl_encls_exiting_bitmap 0x0000202e

/**
 * tsc multiplier.
 */
#define vmcs_ctrl_tsc_multiplier 0x00002032
/**
 * @}
 */

/**
 * @defgroup vmcs_64_bit_read_only_data_fields \
 *           64-bit read-only data field
 *
 * 64-bit read-only data field.
 * @{
 */
/**
 * guest-physical address.
 */
#define vmcs_guest_physical_address 0x00002400
/**
 * @}
 */

/**
 * @defgroup vmcs_64_bit_guest_state_fields \
 *           64-bit guest-state fields
 *
 * 64-bit guest-state fields.
 * @{
 */
/**
 * vmcs link pointer.
 */
#define vmcs_guest_vmcs_link_pointer 0x00002800

/**
 * guest ia32_debugctl.
 */
#define vmcs_guest_debugctl 0x00002802

/**
 * guest ia32_pat.
 */
#define vmcs_guest_pat 0x00002804

/**
 * guest ia32_efer.
 */
#define vmcs_guest_efer 0x00002806

/**
 * guest ia32_perf_global_ctrl.
 */
#define vmcs_guest_perf_global_ctrl 0x00002808

/**
 * guest pdpte0.
 */
#define vmcs_guest_pdpte0 0x0000280a

/**
 * guest pdpte1.
 */
#define vmcs_guest_pdpte1 0x0000280c

/**
 * guest pdpte2.
 */
#define vmcs_guest_pdpte2 0x0000280e

/**
 * guest pdpte3.
 */
#define vmcs_guest_pdpte3 0x00002810

/**
 * guest ia32_bndcfgs.
 */
#define vmcs_guest_bndcfgs 0x00002812

/**
 * guest ia32_rtit_ctl.
 */
#define vmcs_guest_rtit_ctl 0x00002814
/**
 * @}
 */

/**
 * @defgroup vmcs_64_bit_host_state_fields \
 *           64-bit host-state fields
 *
 * 64-bit host-state fields.
 * @{
 */
/**
 * host ia32_pat.
 */
#define vmcs_host_pat 0x00002c00

/**
 * host ia32_efer.
 */
#define vmcs_host_efer 0x00002c02

/**
 * host ia32_perf_global_ctrl.
 */
#define vmcs_host_perf_global_ctrl 0x00002c04
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup vmcs_32_bit \
 *           32-bit fields
 *
 * 32-bit fields.
 *
 * @see vol3d[b.3(32-bit fields)] (reference)
 * @{
 */
/**
 * @defgroup vmcs_32_bit_control_fields \
 *           32-bit control fields
 *
 * 32-bit control fields.
 * @{
 */
/**
 * pin-based vm-execution controls.
 */
#define vmcs_ctrl_pin_based_vm_execution_controls 0x00004000

/**
 * primary processor-based vm-execution controls.
 */
#define vmcs_ctrl_processor_based_vm_execution_controls 0x00004002

/**
 * exception bitmap.
 */
#define vmcs_ctrl_exception_bitmap 0x00004004

/**
 * page-fault error-code mask.
 */
#define vmcs_ctrl_pagefault_error_code_mask 0x00004006

/**
 * page-fault error-code match.
 */
#define vmcs_ctrl_pagefault_error_code_match 0x00004008

/**
 * cr3-target count.
 */
#define vmcs_ctrl_cr3_target_count 0x0000400a

/**
 * vm-exit controls.
 */
#define vmcs_ctrl_vmexit_controls 0x0000400c

/**
 * vm-exit msr-store count.
 */
#define vmcs_ctrl_vmexit_msr_store_count 0x0000400e

/**
 * vm-exit msr-load count.
 */
#define vmcs_ctrl_vmexit_msr_load_count 0x00004010

/**
 * vm-entry controls.
 */
#define vmcs_ctrl_vmentry_controls 0x00004012

/**
 * vm-entry msr-load count.
 */
#define vmcs_ctrl_vmentry_msr_load_count 0x00004014

/**
 * vm-entry interruption-information field.
 */
#define vmcs_ctrl_vmentry_interruption_information_field 0x00004016

/**
 * vm-entry exception error code.
 */
#define vmcs_ctrl_vmentry_exception_error_code 0x00004018

/**
 * vm-entry instruction length.
 */
#define vmcs_ctrl_vmentry_instruction_length 0x0000401a

/**
 * tpr threshold.
 */
#define vmcs_ctrl_tpr_threshold 0x0000401c

/**
 * secondary processor-based vm-execution controls.
 */
#define vmcs_ctrl_secondary_processor_based_vm_execution_controls 0x0000401e

/**
 * ple_gap.
 */
#define vmcs_ctrl_ple_gap 0x00004020

/**
 * ple_window.
 */
#define vmcs_ctrl_ple_window 0x00004022
/**
 * @}
 */

/**
 * @defgroup vmcs_32_bit_read_only_data_fields \
 *           32-bit read-only data fields
 *
 * 32-bit read-only data fields.
 * @{
 */
/**
 * vm-instruction error.
 */
#define vmcs_vm_instruction_error 0x00004400

/**
 * exit reason.
 */
#define vmcs_exit_reason 0x00004402

/**
 * vm-exit interruption information.
 */
#define vmcs_vmexit_interruption_information 0x00004404

/**
 * vm-exit interruption error code.
 */
#define vmcs_vmexit_interruption_error_code 0x00004406

/**
 * idt-listing information field.
 */
#define vmcs_idt_listing_information 0x00004408

/**
 * idt-listing error code.
 */
#define vmcs_idt_listing_error_code 0x0000440a

/**
 * vm-exit instruction length.
 */
#define vmcs_vmexit_instruction_length 0x0000440c

/**
 * vm-exit instruction information.
 */
#define vmcs_vmexit_instruction_info 0x0000440e
/**
 * @}
 */

/**
 * @defgroup vmcs_32_bit_guest_state_fields \
 *           32-bit guest-state fields
 *
 * 32-bit guest-state fields.
 * @{
 */
/**
 * guest es limit.
 */
#define vmcs_guest_es_limit 0x00004800

/**
 * guest cs limit.
 */
#define vmcs_guest_cs_limit 0x00004802

/**
 * guest ss limit.
 */
#define vmcs_guest_ss_limit 0x00004804

/**
 * guest ds limit.
 */
#define vmcs_guest_ds_limit 0x00004806

/**
 * guest fs limit.
 */
#define vmcs_guest_fs_limit 0x00004808

/**
 * guest gs limit.
 */
#define vmcs_guest_gs_limit 0x0000480a

/**
 * guest ldtr limit.
 */
#define vmcs_guest_ldtr_limit 0x0000480c

/**
 * guest tr limit.
 */
#define vmcs_guest_tr_limit 0x0000480e

/**
 * guest gdtr limit.
 */
#define vmcs_guest_gdtr_limit 0x00004810

/**
 * guest idtr limit.
 */
#define vmcs_guest_idtr_limit 0x00004812

/**
 * guest es access rights.
 */
#define vmcs_guest_es_access_rights 0x00004814

/**
 * guest cs access rights.
 */
#define vmcs_guest_cs_access_rights 0x00004816

/**
 * guest ss access rights.
 */
#define vmcs_guest_ss_access_rights 0x00004818

/**
 * guest ds access rights.
 */
#define vmcs_guest_ds_access_rights 0x0000481a

/**
 * guest fs access rights.
 */
#define vmcs_guest_fs_access_rights 0x0000481c

/**
 * guest gs access rights.
 */
#define vmcs_guest_gs_access_rights 0x0000481e

/**
 * guest ldtr access rights.
 */
#define vmcs_guest_ldtr_access_rights 0x00004820

/**
 * guest tr access rights.
 */
#define vmcs_guest_tr_access_rights 0x00004822

/**
 * guest interruptibility state.
 */
#define vmcs_guest_interruptibility_state 0x00004824

/**
 * guest activity state.
 */
#define vmcs_guest_activity_state 0x00004826

/**
 * guest smbase.
 */
#define vmcs_guest_smbase 0x00004828

/**
 * guest ia32_sysenter_cs.
 */
#define vmcs_guest_sysenter_cs 0x0000482a

/**
 * vmx-preemption timer value.
 */
#define vmcs_guest_vmx_preemption_timer_value 0x0000482e
/**
 * @}
 */

/**
 * @defgroup vmcs_32_bit_host_state_fields \
 *           32-bit host-state field
 *
 * 32-bit host-state field.
 * @{
 */
/**
 * host ia32_sysenter_cs.
 */
#define vmcs_host_sysenter_cs 0x00004c00
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup vmcs_natural_width \
 *           natural-width fields
 *
 * natural-width fields.
 *
 * @see vol3d[b.4(natural-width fields)] (reference)
 * @{
 */
/**
 * @defgroup vmcs_natural_width_control_fields \
 *           natural-width control fields
 *
 * natural-width control fields
 * @{
 */
/**
 * cr0 guest/host mask.
 */
#define vmcs_ctrl_cr0_guest_host_mask 0x00006000

/**
 * cr4 guest/host mask.
 */
#define vmcs_ctrl_cr4_guest_host_mask 0x00006002

/**
 * cr0 read shadow.
 */
#define vmcs_ctrl_cr0_read_shadow 0x00006004

/**
 * cr4 read shadow.
 */
#define vmcs_ctrl_cr4_read_shadow 0x00006006

/**
 * cr3-target value 0.
 */
#define vmcs_ctrl_cr3_target_value_0 0x00006008

/**
 * cr3-target value 1.
 */
#define vmcs_ctrl_cr3_target_value_1 0x0000600a

/**
 * cr3-target value 2.
 */
#define vmcs_ctrl_cr3_target_value_2 0x0000600c

/**
 * cr3-target value 3.
 */
#define vmcs_ctrl_cr3_target_value_3 0x0000600e
/**
 * @}
 */

/**
 * @defgroup vmcs_natural_width_read_only_data_fields \
 *           natural-width read-only data fields
 *
 * natural-width read-only data fields.
 * @{
 */
/**
 * exit qualification.
 */
#define vmcs_exit_qualification 0x00006400

/**
 * i/o rcx.
 */
#define vmcs_io_rcx 0x00006402

/**
 * i/o rsi.
 */
#define vmcs_io_rsx 0x00006404

/**
 * i/o rdi.
 */
#define vmcs_io_rdi 0x00006406

/**
 * i/o rip.
 */
#define vmcs_io_rip 0x00006408

/**
 * guest-linear address.
 */
#define vmcs_exit_guest_linear_address 0x0000640a
/**
 * @}
 */

/**
 * @defgroup vmcs_natural_width_guest_state_fields \
 *           natural-width guest-state fields
 *
 * natural-width guest-state fields.
 * @{
 */
/**
 * guest cr0.
 */
#define vmcs_guest_cr0 0x00006800

/**
 * guest cr3.
 */
#define vmcs_guest_cr3 0x00006802

/**
 * guest cr4.
 */
#define vmcs_guest_cr4 0x00006804

/**
 * guest es base.
 */
#define vmcs_guest_es_base 0x00006806

/**
 * guest cs base.
 */
#define vmcs_guest_cs_base 0x00006808

/**
 * guest ss base.
 */
#define vmcs_guest_ss_base 0x0000680a

/**
 * guest ds base.
 */
#define vmcs_guest_ds_base 0x0000680c

/**
 * guest fs base.
 */
#define vmcs_guest_fs_base 0x0000680e

/**
 * guest gs base.
 */
#define vmcs_guest_gs_base 0x00006810

/**
 * guest ldtr base.
 */
#define vmcs_guest_ldtr_base 0x00006812

/**
 * guest tr base.
 */
#define vmcs_guest_tr_base 0x00006814

/**
 * guest gdtr base.
 */
#define vmcs_guest_gdtr_base 0x00006816

/**
 * guest idtr base.
 */
#define vmcs_guest_idtr_base 0x00006818

/**
 * guest dr7.
 */
#define vmcs_guest_dr7 0x0000681a

/**
 * guest rsp.
 */
#define vmcs_guest_rsp 0x0000681c

/**
 * guest rip.
 */
#define vmcs_guest_rip 0x0000681e

/**
 * guest rflags.
 */
#define vmcs_guest_rflags 0x00006820

/**
 * guest pending debug exceptions.
 */
#define vmcs_guest_pending_debug_exceptions 0x00006822

/**
 * guest ia32_sysenter_esp.
 */
#define vmcs_guest_sysenter_esp 0x00006824

/**
 * guest ia32_sysenter_eip.
 */
#define vmcs_guest_sysenter_eip 0x00006826

/**
 * guest ia32_s_cet.
 */
#define vmcs_guest_s_cet 0x00006c28

/**
 * guest ssp.
 */
#define vmcs_guest_ssp 0x00006c2a

/**
 * guest ia32_interrupt_ssp_table_addr.
 */
#define vmcs_guest_interrupt_ssp_table_addr 0x00006c2c
/**
 * @}
 */

/**
 * @defgroup vmcs_natural_width_host_state_fields \
 *           natural-width host-state fields
 *
 * natural-width host-state fields.
 * @{
 */
/**
 * host cr0.
 */
#define vmcs_host_cr0 0x00006c00

/**
 * host cr3.
 */
#define vmcs_host_cr3 0x00006c02

/**
 * host cr4.
 */
#define vmcs_host_cr4 0x00006c04

/**
 * host fs base.
 */
#define vmcs_host_fs_base 0x00006c06

/**
 * host gs base.
 */
#define vmcs_host_gs_base 0x00006c08

/**
 * host tr base.
 */
#define vmcs_host_tr_base 0x00006c0a

/**
 * host gdtr base.
 */
#define vmcs_host_gdtr_base 0x00006c0c

/**
 * host idtr base.
 */
#define vmcs_host_idtr_base 0x00006c0e

/**
 * host ia32_sysenter_esp.
 */
#define vmcs_host_sysenter_esp 0x00006c10

/**
 * host ia32_sysenter_eip.
 */
#define vmcs_host_sysenter_eip 0x00006c12

/**
 * host rsp.
 */
#define vmcs_host_rsp 0x00006c14

/**
 * host rip.
 */
#define vmcs_host_rip 0x00006c16

/**
 * host ia32_s_cet.
 */
#define vmcs_host_s_cet 0x00006c18

/**
 * host ssp.
 */
#define vmcs_host_ssp 0x00006c1a

/**
 * host ia32_interrupt_ssp_table_addr.
 */
#define vmcs_host_interrupt_ssp_table_addr 0x00006c1c
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @brief valid interruption types
 */
typedef enum {
	/**
         * external interrupt.
         */
	externalinterrupt = 0x00000000,

	/**
         * non-maskable interrupt (nmi).
         */
	nonmaskableinterrupt = 0x00000002,

	/**
         * hardware exception (e.g,. \#pf).
         */
	hardwareexception = 0x00000003,

	/**
         * software interrupt (int n).
         */
	softwareinterrupt = 0x00000004,

	/**
         * privileged software exception (int1).
         */
	privilegedsoftwareexception = 0x00000005,

	/**
         * software exception (int3 or into).
         */
	softwareexception = 0x00000006,

	/**
         * other event. this type is used for injection of events that are not delivered through the idt.
         */
	otherevent = 0x00000007,
} interruption_type;

/**
 * @brief vm entry can be configured to conclude by delivering an event through the idt (after all guest state and msrs
 *        have been loaded). this process is called event injection and is controlled by these vm-entry control fields
 *
 * @see vol3a[24.8.3(vm-entry controls for event injection)] (reference)
 */
typedef union {
	struct {
		/**
                 * @brief list of interrupt or exception
                 *
                 * [bits 7:0] determines which entry in the idt is used or which other event is injected.
                 */
		uint32 list : 8;
#define vmentry_interrupt_information_list_bit 0
#define vmentry_interrupt_information_list_flag 0xff
#define vmentry_interrupt_information_list_mask 0xff
#define vmentry_interrupt_information_list(_) (((_) >> 0) & 0xff)

		/**
                 * @brief interruption type
                 *
                 * [bits 10:8] determines details of how the injection is performed.
                 */
		uint32 interruptiontype : 3;
#define vmentry_interrupt_information_interruption_type_bit 8
#define vmentry_interrupt_information_interruption_type_flag 0x700
#define vmentry_interrupt_information_interruption_type_mask 0x07
#define vmentry_interrupt_information_interruption_type(_) (((_) >> 8) & 0x07)

		/**
                 * @brief deliver error code (0 = do not deliver; 1 = deliver)
                 *
                 * [bit 11] determines whether delivery pushes an error code on the guest stack.
                 */
		uint32 delivererrorcode : 1;
#define vmentry_interrupt_information_deliver_error_code_bit 11
#define vmentry_interrupt_information_deliver_error_code_flag 0x800
#define vmentry_interrupt_information_deliver_error_code_mask 0x01
#define vmentry_interrupt_information_deliver_error_code(_) (((_) >> 11) & 0x01)
		uint32 reserved1 : 19;

		/**
                 * @brief valid
                 *
                 * [bit 31] vm entry injects an event if and only if the valid bit is 1. the valid bit in this field is cleared on every vm
                 * exit.
                 */
		uint32 valid : 1;
#define vmentry_interrupt_information_valid_bit 31
#define vmentry_interrupt_information_valid_flag 0x80000000
#define vmentry_interrupt_information_valid_mask 0x01
#define vmentry_interrupt_information_valid(_) (((_) >> 31) & 0x01)
	};

	uint32 flags;
} vmentry_interrupt_information;

/**
 * @brief vm entry can be configured to conclude by delivering an event through the idt (after all guest state and msrs
 *        have been loaded). this process is called event injection and is controlled by these vm-entry control fields
 *
 * @see vol3a[24.9.2(information for vm exits due to listed events)] (reference)
 */
typedef union {
	struct {
		/**
                 * [bits 7:0] list of interrupt or exception.
                 */
		uint32 list : 8;
#define vmexit_interrupt_information_list_bit 0
#define vmexit_interrupt_information_list_flag 0xff
#define vmexit_interrupt_information_list_mask 0xff
#define vmexit_interrupt_information_list(_) (((_) >> 0) & 0xff)

		/**
                 * [bits 10:8] interruption type.
                 */
		uint32 interruptiontype : 3;
#define vmexit_interrupt_information_interruption_type_bit 8
#define vmexit_interrupt_information_interruption_type_flag 0x700
#define vmexit_interrupt_information_interruption_type_mask 0x07
#define vmexit_interrupt_information_interruption_type(_) (((_) >> 8) & 0x07)

		/**
                 * [bit 11] deliver error code (0 = do not deliver; 1 = deliver).
                 */
		uint32 errorcodevalid : 1;
#define vmexit_interrupt_information_error_code_valid_bit 11
#define vmexit_interrupt_information_error_code_valid_flag 0x800
#define vmexit_interrupt_information_error_code_valid_mask 0x01
#define vmexit_interrupt_information_error_code_valid(_) (((_) >> 11) & 0x01)

		/**
                 * [bit 12] nmi unblocking due to iret.
                 */
		uint32 nmiunblocking : 1;
#define vmexit_interrupt_information_nmi_unblocking_bit 12
#define vmexit_interrupt_information_nmi_unblocking_flag 0x1000
#define vmexit_interrupt_information_nmi_unblocking_mask 0x01
#define vmexit_interrupt_information_nmi_unblocking(_) (((_) >> 12) & 0x01)
		uint32 reserved1 : 18;

		/**
                 * [bit 31] valid.
                 */
		uint32 valid : 1;
#define vmexit_interrupt_information_valid_bit 31
#define vmexit_interrupt_information_valid_flag 0x80000000
#define vmexit_interrupt_information_valid_mask 0x01
#define vmexit_interrupt_information_valid(_) (((_) >> 31) & 0x01)
	};

	uint32 flags;
} vmexit_interrupt_information;

/**
 * @}
 */

/**
 * @defgroup apic \
 *           advanced programmable interrupt controller (apic)
 *
 * software interacts with the local apic by reading and writing its registers. apic registers are memory-mapped to a
 * 4-kbyte region of the processor's physical address space with an initial starting address of fee00000h. for correct apic
 * operation, this address space must be mapped to an area of memory that has been designated as strong uncacheable (uc).
 *
 * @remarks registers are 32 bits, 64 bits, or 256 bits in width; all are aligned on 128-bit boundaries. all 32-bit
 *          registers should be accessed using 128-bit aligned 32-bit loads or stores. some processors may support loads and stores
 *          of less than 32 bits to some of the apic registers. this is model specific behavior and is not guaranteed to work on all
 *          processors. any fp/mmx/sse access to an apic register, or any access that touches bytes 4 through 15 of an apic register
 *          may cause undefined behavior and must not be executed. this undefined behavior could include hangs, incorrect results or
 *          unexpected exceptions, including machine checks, and may vary between implementations. wider registers (64-bit or
 *          256-bit) must be accessed using multiple 32-bit loads or stores, with all accesses being 128-bit aligned.
 * @see vol3a[10.4.1(the local apic block diagram)] (reference)
 * @{
 */
/**
 * local apic base address.
 *
 * @remarks reserved.
 */
#define apic_base_address 0xfee00000

/**
 * local apic id register.
 */
#define apic_id 0x00000020

/**
 * local apic version register.
 */
#define apic_version 0x00000030

/**
 * task priority register (tpr).
 */
#define apic_task_priority 0x00000080

/**
 * arbitration priority register (apr).
 */
#define apic_arbitration_priority 0x00000090

/**
 * processor priority register (ppr).
 */
#define apic_processor_priority 0x000000a0

/**
 * eoi register.
 */
#define apic_eoi 0x000000b0

/**
 * remote read register (rrd).
 */
#define apic_remote_read 0x000000c0

/**
 * logical destination register.
 */
#define apic_logical_destination 0x000000d0

/**
 * destination format register.
 *
 * @see vol3a[10.6.2.2(logical destination mode)]
 */
#define apic_destination_format 0x000000e0

/**
 * spurious interrupt list register.
 *
 * @see vol3a[10.9(spurious interrupt)]
 */
#define apic_spurious_interrupt_list 0x000000f0

/**
 * in-service register (isr); bits 31:0.
 */
#define apic_in_service_bits_31_0 0x00000100

/**
 * in-service register (isr); bits 63:32.
 */
#define apic_in_service_bits_63_32 0x00000110

/**
 * in-service register (isr); bits 95:64.
 */
#define apic_in_service_bits_95_64 0x00000120

/**
 * in-service register (isr); bits 127:96.
 */
#define apic_in_service_bits_127_96 0x00000130

/**
 * in-service register (isr); bits 159:128.
 */
#define apic_in_service_bits_159_128 0x00000140

/**
 * in-service register (isr); bits 191:160.
 */
#define apic_in_service_bits_191_160 0x00000150

/**
 * in-service register (isr); bits 223:192.
 */
#define apic_in_service_bits_223_192 0x00000160

/**
 * in-service register (isr); bits 255:224.
 */
#define apic_in_service_bits_255_224 0x00000170

/**
 * trigger mode register (tmr); bits 31:0.
 */
#define apic_trigger_mode_bits_31_0 0x00000180

/**
 * trigger mode register (tmr); bits 63:32.
 */
#define apic_trigger_mode_bits_63_32 0x00000190

/**
 * trigger mode register (tmr); bits 95:64.
 */
#define apic_trigger_mode_bits_95_64 0x000001a0

/**
 * trigger mode register (tmr); bits 127:96.
 */
#define apic_trigger_mode_bits_127_96 0x000001b0

/**
 * trigger mode register (tmr); bits 159:128.
 */
#define apic_trigger_mode_bits_159_128 0x000001c0

/**
 * trigger mode register (tmr); bits 191:160.
 */
#define apic_trigger_mode_bits_191_160 0x000001d0

/**
 * trigger mode register (tmr); bits 223:192.
 */
#define apic_trigger_mode_bits_223_192 0x000001e0

/**
 * trigger mode register (tmr); bits 255:224.
 */
#define apic_trigger_mode_bits_255_224 0x000001f0

/**
 * interrupt request register (irr); bits 31:0.
 */
#define apic_interrupt_request_bits_31_0 0x00000200

/**
 * interrupt request register (irr); bits 63:32.
 */
#define apic_interrupt_request_bits_63_32 0x00000210

/**
 * interrupt request register (irr); bits 95:64.
 */
#define apic_interrupt_request_bits_95_64 0x00000220

/**
 * interrupt request register (irr); bits 127:96.
 */
#define apic_interrupt_request_bits_127_96 0x00000230

/**
 * interrupt request register (irr); bits 159:128.
 */
#define apic_interrupt_request_bits_159_128 0x00000240

/**
 * interrupt request register (irr); bits 191:160.
 */
#define apic_interrupt_request_bits_191_160 0x00000250

/**
 * interrupt request register (irr); bits 223:192.
 */
#define apic_interrupt_request_bits_223_192 0x00000260

/**
 * interrupt request register (irr); bits 255:224.
 */
#define apic_interrupt_request_bits_255_224 0x00000270

/**
 * error status register.
 */
#define apic_error_status 0x00000280

/**
 * lvt corrected machine check interrupt (cmci) register.
 */
#define apic_lvt_corrected_machine_check_interrupt 0x000002f0

/**
 * interrupt command register (icr); bits 0-31.
 */
#define apic_interrupt_command_bits_0_31 0x00000300

/**
 * interrupt command register (icr); bits 32-63.
 */
#define apic_interrupt_command_bits_32_63 0x00000310

/**
 * lvt timer register.
 */
#define apic_lvt_timer 0x00000320

/**
 * lvt thermal sensor register.
 */
#define apic_lvt_thermal_sensor 0x00000330

/**
 * lvt performance monitoring counters register.
 */
#define apic_lvt_performance_monitoring_counters 0x00000340

/**
 * lvt lint0 register.
 */
#define apic_lvt_lint0 0x00000350

/**
 * lvt lint1 register.
 */
#define apic_lvt_lint1 0x00000360

/**
 * lvt error register.
 */
#define apic_lvt_error 0x00000370

/**
 * initial count register (for timer).
 */
#define apic_initial_count 0x00000380

/**
 * current count register (for timer).
 */
#define apic_current_count 0x00000390

/**
 * divide configuration register (for timer).
 */
#define apic_divide_configuration 0x000003e0
/**
 * @}
 */

/**
 * the 32-bit eflags register contains a group of status flags, a control flag, and a group of system flags. the status
 * flags (bits 0, 2, 4, 6, 7, and 11) of the eflags register indicate the results of arithmetic instructions, such as the
 * add, sub, mul, and div instructions.
 * the system flags and iopl field in the eflags register control operating-system or executive operations.
 *
 * @see vol1[3.4.3(eflags)] (reference)
 */
typedef union {
	struct {
		/**
                 * @brief carry flag
                 *
                 * [bit 0] set if an arithmetic operation generates a carry or a borrow out of the mostsignificant bit of the result;
                 * cleared otherwise. this flag indicates an overflow condition for unsigned-integer arithmetic. it is also used in
                 * multiple-precision arithmetic.
                 */
		uint32 carryflag : 1;
#define eflags_carry_flag_bit 0
#define eflags_carry_flag_flag 0x01
#define eflags_carry_flag_mask 0x01
#define eflags_carry_flag(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] reserved - always 1
                 */
		uint32 readas1 : 1;
#define eflags_read_as_1_bit 1
#define eflags_read_as_1_flag 0x02
#define eflags_read_as_1_mask 0x01
#define eflags_read_as_1(_) (((_) >> 1) & 0x01)

		/**
                 * @brief parity flag
                 *
                 * [bit 2] set if the least-significant byte of the result contains an even number of 1 bits; cleared otherwise.
                 */
		uint32 parityflag : 1;
#define eflags_parity_flag_bit 2
#define eflags_parity_flag_flag 0x04
#define eflags_parity_flag_mask 0x01
#define eflags_parity_flag(_) (((_) >> 2) & 0x01)
		uint32 reserved1 : 1;

		/**
                 * @brief auxiliary carry flag
                 *
                 * [bit 4] set if an arithmetic operation generates a carry or a borrow out of bit 3 of the result; cleared otherwise. this
                 * flag is used in binary-coded decimal (bcd) arithmetic.
                 */
		uint32 auxiliarycarryflag : 1;
#define eflags_auxiliary_carry_flag_bit 4
#define eflags_auxiliary_carry_flag_flag 0x10
#define eflags_auxiliary_carry_flag_mask 0x01
#define eflags_auxiliary_carry_flag(_) (((_) >> 4) & 0x01)
		uint32 reserved2 : 1;

		/**
                 * @brief zero flag
                 *
                 * [bit 6] set if the result is zero; cleared otherwise.
                 */
		uint32 zeroflag : 1;
#define eflags_zero_flag_bit 6
#define eflags_zero_flag_flag 0x40
#define eflags_zero_flag_mask 0x01
#define eflags_zero_flag(_) (((_) >> 6) & 0x01)

		/**
                 * @brief sign flag
                 *
                 * [bit 7] set equal to the most-significant bit of the result, which is the sign bit of a signed integer. (0 indicates a
                 * positive value and 1 indicates a negative value.)
                 */
		uint32 signflag : 1;
#define eflags_sign_flag_bit 7
#define eflags_sign_flag_flag 0x80
#define eflags_sign_flag_mask 0x01
#define eflags_sign_flag(_) (((_) >> 7) & 0x01)

		/**
                 * @brief trap flag
                 *
                 * [bit 8] set to enable single-step mode for debugging; clear to disable single-step mode.
                 */
		uint32 trapflag : 1;
#define eflags_trap_flag_bit 8
#define eflags_trap_flag_flag 0x100
#define eflags_trap_flag_mask 0x01
#define eflags_trap_flag(_) (((_) >> 8) & 0x01)

		/**
                 * @brief interrupt enable flag
                 *
                 * [bit 9] controls the response of the processor to maskable interrupt requests. set to respond to maskable interrupts;
                 * cleared to inhibit maskable interrupts.
                 */
		uint32 interruptenableflag : 1;
#define eflags_interrupt_enable_flag_bit 9
#define eflags_interrupt_enable_flag_flag 0x200
#define eflags_interrupt_enable_flag_mask 0x01
#define eflags_interrupt_enable_flag(_) (((_) >> 9) & 0x01)

		/**
                 * @brief direction flag
                 *
                 * [bit 10] controls string instructions (movs, cmps, scas, lods, and stos). setting the df flag causes the string
                 * instructions to auto-decrement (to process strings from high addresses to low addresses). clearing the df flag causes
                 * the string instructions to auto-increment (process strings from low addresses to high addresses).
                 */
		uint32 directionflag : 1;
#define eflags_direction_flag_bit 10
#define eflags_direction_flag_flag 0x400
#define eflags_direction_flag_mask 0x01
#define eflags_direction_flag(_) (((_) >> 10) & 0x01)

		/**
                 * @brief overflow flag
                 *
                 * [bit 11] set if the integer result is too large a positive number or too small a negative number (excluding the
                 * sign-bit) to fit in the destination operand; cleared otherwise. this flag indicates an overflow condition for
                 * signed-integer (two's complement) arithmetic.
                 */
		uint32 overflowflag : 1;
#define eflags_overflow_flag_bit 11
#define eflags_overflow_flag_flag 0x800
#define eflags_overflow_flag_mask 0x01
#define eflags_overflow_flag(_) (((_) >> 11) & 0x01)

		/**
                 * @brief i/o privilege level field
                 *
                 * [bits 13:12] indicates the i/o privilege level of the currently running program or task. the current privilege level
                 * (cpl) of the currently running program or task must be less than or equal to the i/o privilege level to access the i/o
                 * address space. the popf and iret instructions can modify this field only when operating at a cpl of 0.
                 */
		uint32 ioprivilegelevel : 2;
#define eflags_io_privilege_level_bit 12
#define eflags_io_privilege_level_flag 0x3000
#define eflags_io_privilege_level_mask 0x03
#define eflags_io_privilege_level(_) (((_) >> 12) & 0x03)

		/**
                 * @brief nested task flag
                 *
                 * [bit 14] controls the chaining of interrupted and called tasks. set when the current task is linked to the previously
                 * executed task; cleared when the current task is not linked to another task.
                 */
		uint32 nestedtaskflag : 1;
#define eflags_nested_task_flag_bit 14
#define eflags_nested_task_flag_flag 0x4000
#define eflags_nested_task_flag_mask 0x01
#define eflags_nested_task_flag(_) (((_) >> 14) & 0x01)
		uint32 reserved3 : 1;

		/**
                 * @brief resume flag
                 *
                 * [bit 16] controls the processor's response to debug exceptions.
                 */
		uint32 resumeflag : 1;
#define eflags_resume_flag_bit 16
#define eflags_resume_flag_flag 0x10000
#define eflags_resume_flag_mask 0x01
#define eflags_resume_flag(_) (((_) >> 16) & 0x01)

		/**
                 * @brief virtual-8086 mode flag
                 *
                 * [bit 17] set to enable virtual-8086 mode; clear to return to protected mode without virtual-8086 mode semantics.
                 */
		uint32 virtual8086modeflag : 1;
#define eflags_virtual_8086_mode_flag_bit 17
#define eflags_virtual_8086_mode_flag_flag 0x20000
#define eflags_virtual_8086_mode_flag_mask 0x01
#define eflags_virtual_8086_mode_flag(_) (((_) >> 17) & 0x01)

		/**
                 * @brief alignment check (or access control) flag
                 *
                 * [bit 18] if the am bit is set in the cr0 register, alignment checking of user-mode data accesses is enabled if and only
                 * if this flag is 1. if the smap bit is set in the cr4 register, explicit supervisor-mode data accesses to user-mode pages
                 * are allowed if and only if this bit is 1.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint32 alignmentcheckflag : 1;
#define eflags_alignment_check_flag_bit 18
#define eflags_alignment_check_flag_flag 0x40000
#define eflags_alignment_check_flag_mask 0x01
#define eflags_alignment_check_flag(_) (((_) >> 18) & 0x01)

		/**
                 * @brief virtual interrupt flag
                 *
                 * [bit 19] virtual image of the if flag. used in conjunction with the vip flag. (to use this flag and the vip flag the
                 * virtual mode extensions are enabled by setting the vme flag in control register cr4.)
                 */
		uint32 virtualinterruptflag : 1;
#define eflags_virtual_interrupt_flag_bit 19
#define eflags_virtual_interrupt_flag_flag 0x80000
#define eflags_virtual_interrupt_flag_mask 0x01
#define eflags_virtual_interrupt_flag(_) (((_) >> 19) & 0x01)

		/**
                 * @brief virtual interrupt pending flag
                 *
                 * [bit 20] set to indicate that an interrupt is pending; clear when no interrupt is pending. (software sets and clears
                 * this flag; the processor only reads it.) used in conjunction with the vif flag.
                 */
		uint32 virtualinterruptpendingflag : 1;
#define eflags_virtual_interrupt_pending_flag_bit 20
#define eflags_virtual_interrupt_pending_flag_flag 0x100000
#define eflags_virtual_interrupt_pending_flag_mask 0x01
#define eflags_virtual_interrupt_pending_flag(_) (((_) >> 20) & 0x01)

		/**
                 * @brief identification flag
                 *
                 * [bit 21] the ability of a program to set or clear this flag indicates support for the cpuid instruction.
                 */
		uint32 identificationflag : 1;
#define eflags_identification_flag_bit 21
#define eflags_identification_flag_flag 0x200000
#define eflags_identification_flag_mask 0x01
#define eflags_identification_flag(_) (((_) >> 21) & 0x01)
		uint32 reserved4 : 10;
	};

	uint32 flags;
} eflags;

/**
 * the 64-bit rflags register contains a group of status flags, a control flag, and a group of system flags in 64-bit mode.
 * the upper 32 bits of rflags register is reserved. the lower 32 bits of rflags is the same as eflags.
 *
 * @see eflags
 * @see vol1[3.4.3.4(rflags register in 64-bit mode)] (reference)
 */
typedef union {
	struct {
		/**
                 * @brief carry flag
                 *
                 * [bit 0] see the description in eflags.
                 */
		uint64 carryflag : 1;
#define rflags_carry_flag_bit 0
#define rflags_carry_flag_flag 0x01
#define rflags_carry_flag_mask 0x01
#define rflags_carry_flag(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] reserved - always 1
                 */
		uint64 readas1 : 1;
#define rflags_read_as_1_bit 1
#define rflags_read_as_1_flag 0x02
#define rflags_read_as_1_mask 0x01
#define rflags_read_as_1(_) (((_) >> 1) & 0x01)

		/**
                 * @brief parity flag
                 *
                 * [bit 2] see the description in eflags.
                 */
		uint64 parityflag : 1;
#define rflags_parity_flag_bit 2
#define rflags_parity_flag_flag 0x04
#define rflags_parity_flag_mask 0x01
#define rflags_parity_flag(_) (((_) >> 2) & 0x01)
		uint64 reserved1 : 1;

		/**
                 * @brief auxiliary carry flag
                 *
                 * [bit 4] see the description in eflags.
                 */
		uint64 auxiliarycarryflag : 1;
#define rflags_auxiliary_carry_flag_bit 4
#define rflags_auxiliary_carry_flag_flag 0x10
#define rflags_auxiliary_carry_flag_mask 0x01
#define rflags_auxiliary_carry_flag(_) (((_) >> 4) & 0x01)
		uint64 reserved2 : 1;

		/**
                 * @brief zero flag
                 *
                 * [bit 6] see the description in eflags.
                 */
		uint64 zeroflag : 1;
#define rflags_zero_flag_bit 6
#define rflags_zero_flag_flag 0x40
#define rflags_zero_flag_mask 0x01
#define rflags_zero_flag(_) (((_) >> 6) & 0x01)

		/**
                 * @brief sign flag
                 *
                 * [bit 7] see the description in eflags.
                 */
		uint64 signflag : 1;
#define rflags_sign_flag_bit 7
#define rflags_sign_flag_flag 0x80
#define rflags_sign_flag_mask 0x01
#define rflags_sign_flag(_) (((_) >> 7) & 0x01)

		/**
                 * @brief trap flag
                 *
                 * [bit 8] see the description in eflags.
                 */
		uint64 trapflag : 1;
#define rflags_trap_flag_bit 8
#define rflags_trap_flag_flag 0x100
#define rflags_trap_flag_mask 0x01
#define rflags_trap_flag(_) (((_) >> 8) & 0x01)

		/**
                 * @brief interrupt enable flag
                 *
                 * [bit 9] see the description in eflags.
                 */
		uint64 interruptenableflag : 1;
#define rflags_interrupt_enable_flag_bit 9
#define rflags_interrupt_enable_flag_flag 0x200
#define rflags_interrupt_enable_flag_mask 0x01
#define rflags_interrupt_enable_flag(_) (((_) >> 9) & 0x01)

		/**
                 * @brief direction flag
                 *
                 * [bit 10] see the description in eflags.
                 */
		uint64 directionflag : 1;
#define rflags_direction_flag_bit 10
#define rflags_direction_flag_flag 0x400
#define rflags_direction_flag_mask 0x01
#define rflags_direction_flag(_) (((_) >> 10) & 0x01)

		/**
                 * @brief overflow flag
                 *
                 * [bit 11] see the description in eflags.
                 */
		uint64 overflowflag : 1;
#define rflags_overflow_flag_bit 11
#define rflags_overflow_flag_flag 0x800
#define rflags_overflow_flag_mask 0x01
#define rflags_overflow_flag(_) (((_) >> 11) & 0x01)

		/**
                 * @brief i/o privilege level field
                 *
                 * [bits 13:12] see the description in eflags.
                 */
		uint64 ioprivilegelevel : 2;
#define rflags_io_privilege_level_bit 12
#define rflags_io_privilege_level_flag 0x3000
#define rflags_io_privilege_level_mask 0x03
#define rflags_io_privilege_level(_) (((_) >> 12) & 0x03)

		/**
                 * @brief nested task flag
                 *
                 * [bit 14] see the description in eflags.
                 */
		uint64 nestedtaskflag : 1;
#define rflags_nested_task_flag_bit 14
#define rflags_nested_task_flag_flag 0x4000
#define rflags_nested_task_flag_mask 0x01
#define rflags_nested_task_flag(_) (((_) >> 14) & 0x01)
		uint64 reserved3 : 1;

		/**
                 * @brief resume flag
                 *
                 * [bit 16] see the description in eflags.
                 */
		uint64 resumeflag : 1;
#define rflags_resume_flag_bit 16
#define rflags_resume_flag_flag 0x10000
#define rflags_resume_flag_mask 0x01
#define rflags_resume_flag(_) (((_) >> 16) & 0x01)

		/**
                 * @brief virtual-8086 mode flag
                 *
                 * [bit 17] see the description in eflags.
                 */
		uint64 virtual8086modeflag : 1;
#define rflags_virtual_8086_mode_flag_bit 17
#define rflags_virtual_8086_mode_flag_flag 0x20000
#define rflags_virtual_8086_mode_flag_mask 0x01
#define rflags_virtual_8086_mode_flag(_) (((_) >> 17) & 0x01)

		/**
                 * @brief alignment check (or access control) flag
                 *
                 * [bit 18] see the description in eflags.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint64 alignmentcheckflag : 1;
#define rflags_alignment_check_flag_bit 18
#define rflags_alignment_check_flag_flag 0x40000
#define rflags_alignment_check_flag_mask 0x01
#define rflags_alignment_check_flag(_) (((_) >> 18) & 0x01)

		/**
                 * @brief virtual interrupt flag
                 *
                 * [bit 19] see the description in eflags.
                 */
		uint64 virtualinterruptflag : 1;
#define rflags_virtual_interrupt_flag_bit 19
#define rflags_virtual_interrupt_flag_flag 0x80000
#define rflags_virtual_interrupt_flag_mask 0x01
#define rflags_virtual_interrupt_flag(_) (((_) >> 19) & 0x01)

		/**
                 * @brief virtual interrupt pending flag
                 *
                 * [bit 20] see the description in eflags.
                 */
		uint64 virtualinterruptpendingflag : 1;
#define rflags_virtual_interrupt_pending_flag_bit 20
#define rflags_virtual_interrupt_pending_flag_flag 0x100000
#define rflags_virtual_interrupt_pending_flag_mask 0x01
#define rflags_virtual_interrupt_pending_flag(_) (((_) >> 20) & 0x01)

		/**
                 * @brief identification flag
                 *
                 * [bit 21] see the description in eflags.
                 */
		uint64 identificationflag : 1;
#define rflags_identification_flag_bit 21
#define rflags_identification_flag_flag 0x200000
#define rflags_identification_flag_mask 0x01
#define rflags_identification_flag(_) (((_) >> 21) & 0x01)
		uint64 reserved4 : 42;
	};

	uint64 flags;
} rflags;

/**
 * @defgroup exceptions \
 *           exceptions
 * @{
 */
/**
 * @brief exceptions that can occur when the instruction is executed in protected mode.
 *        each exception is given a mnemonic that consists of a pound sign (\#) followed by two letters and an optional error code
 *        in parentheses. for example, \#gp(0) denotes a general protection exception with an error code of 0
 *
 * @see vol2a[3.1.1.13(protected mode exceptions section)] (reference)
 * @see vol3a[6.3.1(external interrupts)] (reference)
 */
typedef enum {
	/**
         * #de - divide error.
         * source: div and idiv instructions.
         * error code: no.
         */
	divideerror = 0x00000000,

	/**
         * #db - debug.
         * source: any code or data reference.
         * error code: no.
         */
	debug = 0x00000001,

	/**
         * nonmaskable interrupt.
         * source: generated externally by asserting the processor's nmi pin or
         *         through an nmi request set by the i/o apic to the local apic.
         * error code: no.
         */
	nmi = 0x00000002,

	/**
         * #bp - breakpoint.
         * source: int3 instruction.
         * error code: no.
         */
	breakpoint = 0x00000003,

	/**
         * #of - overflow.
         * source: into instruction.
         * error code: no.
         */
	overflow = 0x00000004,

	/**
         * #br - bound range exceeded.
         * source: bound instruction.
         * error code: no.
         */
	boundrangeexceeded = 0x00000005,

	/**
         * #ud - invalid opcode (undefined opcode).
         * source: ud instruction or reserved opcode.
         * error code: no.
         */
	invalidopcode = 0x00000006,

	/**
         * #nm - device not available (no math coprocessor).
         * source: floating-point or wait/fwait instruction.
         * error code: no.
         */
	devicenotavailable = 0x00000007,

	/**
         * #df - double fault.
         * source: any instruction that can generate an exception, an nmi, or an intr.
         * error code: yes (zero).
         */
	doublefault = 0x00000008,

	/**
         * #\## - coprocessor segment overrun (reserved).
         * source: floating-point instruction.
         * error code: no.
         *
         * @note processors after the intel386 processor do not generate this exception.
         */
	coprocessorsegmentoverrun = 0x00000009,

	/**
         * #ts - invalid tss.
         * source: task switch or tss access.
         * error code: yes.
         */
	invalidtss = 0x0000000a,

	/**
         * #np - segment not present.
         * source: loading segment registers or accessing system segments.
         * error code: yes.
         */
	segmentnotpresent = 0x0000000b,

	/**
         * #ss - stack segment fault.
         * source: stack operations and ss register loads.
         * error code: yes.
         */
	stacksegmentfault = 0x0000000c,

	/**
         * #gp - general protection.
         * source: any memory reference and other protection checks.
         * error code: yes.
         */
	generalprotection = 0x0000000d,

	/**
         * #pf - page fault.
         * source: any memory reference.
         * error code: yes.
         */
	pagefault = 0x0000000e,

	/**
         * #mf - floating-point error (math fault).
         * source: floating-point or wait/fwait instruction.
         * error code: no.
         */
	x87floatingpointerror = 0x00000010,

	/**
         * #ac - alignment check.
         * source: any data reference in memory.
         * error code: yes.
         */
	alignmentcheck = 0x00000011,

	/**
         * #mc - machine check.
         * source: model dependent machine check errors.
         * error code: no.
         */
	machinecheck = 0x00000012,

	/**
         * #xm - simd floating-point numeric error.
         * source: sse/sse2/sse3 floating-point instructions.
         * error code: no.
         */
	simdfloatingpointerror = 0x00000013,

	/**
         * #ve - virtualization exception.
         * source: ept violations.
         * error code: no.
         */
	virtualizationexception = 0x00000014,
} exception_list;

/**
 * @brief when an exception condition is related to a specific segment selector or idt list, the processor pushes an
 *        error code onto the stack of the exception handler (whether it is a procedure or task). the error code resembles a
 *        segment selector; however, instead of a ti flag and rpl field, the error code contains 3 different flags
 *
 * @see vol3a[6.13(error code)] (reference)
 */
typedef union {
	struct {
		/**
                 * [bit 0] when set, indicates that the exception occurred during delivery of an event external to the program, such as an
                 * interrupt or an earlier exception. the bit is cleared if the exception occurred during delivery of a software interrupt
                 * (int n, int3, or into).
                 */
		uint32 externalevent : 1;
#define exception_error_code_external_event_bit 0
#define exception_error_code_external_event_flag 0x01
#define exception_error_code_external_event_mask 0x01
#define exception_error_code_external_event(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] when set, indicates that the index portion of the error code refers to a gate descriptor in the idt; when clear,
                 * indicates that the index refers to a descriptor in the gdt or the current ldt.
                 */
		uint32 descriptorlocation : 1;
#define exception_error_code_descriptor_location_bit 1
#define exception_error_code_descriptor_location_flag 0x02
#define exception_error_code_descriptor_location_mask 0x01
#define exception_error_code_descriptor_location(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] only used when the idt flag is clear. when set, the ti flag indicates that the index portion of the error code
                 * refers to a segment or gate descriptor in the ldt; when clear, it indicates that the index refers to a descriptor in the
                 * current gdt.
                 */
		uint32 gdtldt : 1;
#define exception_error_code_gdt_ldt_bit 2
#define exception_error_code_gdt_ldt_flag 0x04
#define exception_error_code_gdt_ldt_mask 0x01
#define exception_error_code_gdt_ldt(_) (((_) >> 2) & 0x01)

		/**
                 * [bits 15:3] the segment selector index field provides an index into the idt, gdt, or current ldt to the segment or gate
                 * selector being referenced by the error code. in some cases the error code is null (all bits are clear except possibly
                 * ext). a null error code indicates that the error was not caused by a reference to a specific segment or that a null
                 * segment selector was referenced in an operation.
                 *
                 * @note the format of the error code is different for page-fault exceptions (#pf).
                 */
		uint32 index : 13;
#define exception_error_code_index_bit 3
#define exception_error_code_index_flag 0xfff8
#define exception_error_code_index_mask 0x1fff
#define exception_error_code_index(_) (((_) >> 3) & 0x1fff)
		uint32 reserved1 : 16;
	};

	uint32 flags;
} exception_error_code;

/**
 * @brief page fault exception
 *
 * @see vol3a[4.7(page-fault exceptions)] (reference)
 */
typedef union {
	struct {
		/**
                 * [bit 0] this flag is 0 if there is no translation for the linear address because the p flag was 0 in one of the
                 * pagingstructure entries used to translate that address.
                 */
		uint32 present : 1;
#define page_fault_exception_present_bit 0
#define page_fault_exception_present_flag 0x01
#define page_fault_exception_present_mask 0x01
#define page_fault_exception_present(_) (((_) >> 0) & 0x01)

		/**
                 * [bit 1] if the access causing the page-fault exception was a write, this flag is 1; otherwise, it is 0. this flag
                 * describes the access causing the page-fault exception, not the access rights specified by paging.
                 */
		uint32 write : 1;
#define page_fault_exception_write_bit 1
#define page_fault_exception_write_flag 0x02
#define page_fault_exception_write_mask 0x01
#define page_fault_exception_write(_) (((_) >> 1) & 0x01)

		/**
                 * [bit 2] if a user-mode access caused the page-fault exception, this flag is 1; it is 0 if a supervisor-mode access did
                 * so. this flag describes the access causing the page-fault exception, not the access rights specified by paging.
                 *
                 * @see vol3a[4.6(access rights)]
                 */
		uint32 usermodeaccess : 1;
#define page_fault_exception_user_mode_access_bit 2
#define page_fault_exception_user_mode_access_flag 0x04
#define page_fault_exception_user_mode_access_mask 0x01
#define page_fault_exception_user_mode_access(_) (((_) >> 2) & 0x01)

		/**
                 * [bit 3] this flag is 1 if there is no translation for the linear address because a reserved bit was set in one of the
                 * pagingstructure entries used to translate that address. (because reserved bits are not checked in a paging-structure
                 * entry whose p flag is 0, bit 3 of the error code can be set only if bit 0 is also set). bits reserved in the
                 * paging-structure entries are reserved for future functionality. software developers should be aware that such bits may
                 * be used in the future and that a paging-structure entry that causes a page-fault exception on one processor might not do
                 * so in the future.
                 */
		uint32 reservedbitviolation : 1;
#define page_fault_exception_reserved_bit_violation_bit 3
#define page_fault_exception_reserved_bit_violation_flag 0x08
#define page_fault_exception_reserved_bit_violation_mask 0x01
#define page_fault_exception_reserved_bit_violation(_) (((_) >> 3) & 0x01)

		/**
                 * [bit 4] this flag is 1 if (1) the access causing the page-fault exception was an instruction fetch; and (2) either (a)
                 * cr4.smep = 1; or (b) both (i) cr4.pae = 1 (either pae paging or 4-level paging is in use); and (ii) ia32_efer.nxe = 1.
                 * otherwise, the flag is 0. this flag describes the access causing the page-fault exception, not the access rights
                 * specified by paging.
                 */
		uint32 execute : 1;
#define page_fault_exception_execute_bit 4
#define page_fault_exception_execute_flag 0x10
#define page_fault_exception_execute_mask 0x01
#define page_fault_exception_execute(_) (((_) >> 4) & 0x01)

		/**
                 * [bit 5] this flag is 1 if (1) ia32_efer.lma = cr4.pke = 1; (2) the access causing the page-fault exception was a data
                 * access; (3) the linear address was a user-mode address with protection key i; and (5) the pkru register is such that
                 * either (a) adi = 1; or (b) the following all hold: (i) wdi = 1; (ii) the access is a write access; and (iii) either
                 * cr0.wp = 1 or the access causing the page-fault exception was a user-mode access.
                 *
                 * @see vol3a[4.6.2(protection keys)]
                 */
		uint32 protectionkeyviolation : 1;
#define page_fault_exception_protection_key_violation_bit 5
#define page_fault_exception_protection_key_violation_flag 0x20
#define page_fault_exception_protection_key_violation_mask 0x01
#define page_fault_exception_protection_key_violation(_) (((_) >> 5) & 0x01)
		uint32 reserved1 : 9;

		/**
                 * [bit 15] this flag is 1 if the exception is unrelated to paging and resulted from violation of sgx-specific
                 * access-control requirements. because such a violation can occur only if there is no ordinary page fault, this flag is
                 * set only if the p flag (bit 0) is 1 and the rsvd flag (bit 3) and the pk flag (bit 5) are both 0.
                 */
		uint32 sgx : 1;
#define page_fault_exception_sgx_bit 15
#define page_fault_exception_sgx_flag 0x8000
#define page_fault_exception_sgx_mask 0x01
#define page_fault_exception_sgx(_) (((_) >> 15) & 0x01)
		uint32 reserved2 : 16;
	};

	uint32 flags;
} page_fault_exception;

/**
 * @}
 */

/**
 * @defgroup memory_type \
 *           memory caching type
 *
 * the processor allows any area of system memory to be cached in the l1, l2, and l3 caches. in individual pages or regions
 * of system memory, it allows the type of caching (also called memory type) to be specified.
 *
 * @see vol3a[11.11(memory type range registers (mtrrs))]
 * @see vol3a[11.5(cache control)]
 * @see vol3a[11.3(methods of caching available)] (reference)
 * @{
 */
/**
 * @brief strong uncacheable (uc)
 *
 * system memory locations are not cached. all reads and writes appear on the system bus and are executed in program order
 * without reordering. no speculative memory accesses, pagetable walks, or prefetches of speculated branch targets are
 * made. this type of cache-control is useful for memory-mapped i/o devices. when used with normal ram, it greatly reduces
 * processor performance.
 */
#define memory_type_uncacheable 0x00000000

/**
 * @brief write combining (wc)
 *
 * system memory locations are not cached (as with uncacheable memory) and coherency is not enforced by the processor's bus
 * coherency protocol. speculative reads are allowed. writes may be delayed and combined in the write combining buffer (wc
 * buffer) to reduce memory accesses. if the wc buffer is partially filled, the writes may be delayed until the next
 * occurrence of a serializing event; such as, an sfence or mfence instruction, cpuid execution, a read or write to
 * uncached memory, an interrupt occurrence, or a lock instruction execution. this type of cache-control is appropriate for
 * video frame buffers, where the order of writes is unimportant as long as the writes update memory so they can be seen on
 * the graphics display. this memory type is available in the pentium pro and pentium ii processors by programming the
 * mtrrs; or in processor families starting from the pentium iii processors by programming the mtrrs or by selecting it
 * through the pat.
 *
 * @see vol3a[11.3.1(buffering of write combining memory locations)]
 */
#define memory_type_write_combining 0x00000001

/**
 * @brief write-through (wt)
 *
 * writes and reads to and from system memory are cached. reads come from cache lines on cache hits; read misses cause
 * cache fills. speculative reads are allowed. all writes are written to a cache line (when possible) and through to system
 * memory. when writing through to memory, invalid cache lines are never filled, and valid cache lines are either filled or
 * invalidated. write combining is allowed. this type of cache-control is appropriate for frame buffers or when there are
 * devices on the system bus that access system memory, but do not perform snooping of memory accesses. it enforces
 * coherency between caches in the processors and system memory.
 */
#define memory_type_write_through 0x00000004

/**
 * @brief write protected (wp)
 *
 * reads come from cache lines when possible, and read misses cause cache fills. writes are propagated to the system bus
 * and cause corresponding cache lines on all processors on the bus to be invalidated. speculative reads are allowed. this
 * memory type is available in processor families starting from the p6 family processors by programming the mtrrs.
 */
#define memory_type_write_protected 0x00000005

/**
 * @brief write-back (wb)
 *
 * writes and reads to and from system memory are cached. reads come from cache lines on cache hits; read misses cause
 * cache fills. speculative reads are allowed. write misses cause cache line fills (in processor families starting with the
 * p6 family processors), and writes are performed entirely in the cache, when possible. write combining is allowed. the
 * write-back memory type reduces bus traffic by eliminating many unnecessary writes to system memory. writes to a cache
 * line are not immediately forwarded to system memory; instead, they are accumulated in the cache. the modified cache
 * lines are written to system memory later, when a write-back operation is performed. write-back operations are triggered
 * when cache lines need to be deallocated, such as when new cache lines are being allocated in a cache that is already
 * full. they also are triggered by the mechanisms used to maintain cache consistency. this type of cache-control provides
 * the best performance, but it requires that all devices that access system memory on the system bus be able to snoop
 * memory accesses to insure system memory and cache coherency.
 */
#define memory_type_write_back 0x00000006

/**
 * @brief uncacheable (uc-)
 *
 * has same characteristics as the strong uncacheable (uc) memory type, except that this memory type can be overridden by
 * programming the mtrrs for the wc memory type. this memory type is available in processor families starting from the
 * pentium iii processors and can only be selected through the pat.
 */
#define memory_type_uncacheable_minus 0x00000007
#define memory_type_invalid 0x000000ff
/**
 * @}
 */

/**
 * @}
 */

#pragma pack(push, 1)
typedef struct {
	/**
         * reserved bits. set to 0.
         */
	uint32 reserved_0;

	/**
         * stack pointer for privilege level 0.
         */
	uint64 rsp0;

	/**
         * stack pointer for privilege level 1.
         */
	uint64 rsp1;

	/**
         * stack pointer for privilege level 2.
         */
	uint64 rsp2;

	/**
         * reserved bits. set to 0.
         */
	uint64 reserved_1;

	/**
         * interrupt stack table pointer (1).
         */
	uint64 ist1;

	/**
         * interrupt stack table pointer (2).
         */
	uint64 ist2;

	/**
         * interrupt stack table pointer (3).
         */
	uint64 ist3;

	/**
         * interrupt stack table pointer (4).
         */
	uint64 ist4;

	/**
         * interrupt stack table pointer (5).
         */
	uint64 ist5;

	/**
         * interrupt stack table pointer (6).
         */
	uint64 ist6;

	/**
         * interrupt stack table pointer (7).
         */
	uint64 ist7;

	/**
         * reserved bits. set to 0.
         */
	uint64 reserved_2;

	/**
         * reserved bits. set to 0.
         */
	uint16 reserved_3;

	/**
         * the 16-bit offset to the i/o permission bit map from the 64-bit tss base.
         */
	uint16 io_map_base;
} task_state_segment_64;
#endif
#pragma pack(pop)