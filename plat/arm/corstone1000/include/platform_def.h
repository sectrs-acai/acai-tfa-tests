/*
 * Copyright (c) 2022, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <utils_def.h>

#include "../corstone1000_def.h"

/*******************************************************************************
 * Platform definitions used by common code
 ******************************************************************************/

#ifndef __PLATFORM_DEF_H__
#define __PLATFORM_DEF_H__

/*******************************************************************************
 * Platform binary types for linking
 ******************************************************************************/
#ifdef __aarch64__
#define PLATFORM_LINKER_FORMAT		"elf64-littleaarch64"
#define PLATFORM_LINKER_ARCH		aarch64
#else
#define PLATFORM_LINKER_FORMAT		"elf32-littlearm"
#define PLATFORM_LINKER_ARCH		arm
#endif

/*******************************************************************************
 * Run-time address of the TFTF image.
 * It has to match the location where the Trusted Firmware-A loads the BL33
 * image.
 ******************************************************************************/
#define TFTF_BASE			0x80000000

/******************************************************************************
 * Memory mapped Generic timer interfaces
 *******************************************************************************/
/* REFCLK CNTControl, Generic Timer. Secure Access only. */
#define SYS_CNT_CONTROL_BASE            0x1A200000
/* REFCLK CNTRead, Generic Timer. */
#define SYS_CNT_READ_BASE		0x1A210000
/* AP_REFCLK CNTBase1, Generic Timer. */
#define SYS_CNT_BASE1			0x1A240000

/*******************************************************************************
 * Base address and size of external NVM flash
 ******************************************************************************/
#define FLASH_BASE			0x08000000

#define NOR_FLASH_BLOCK_SIZE		0x40000
#define NOR_FLASH_BLOCKS_COUNT		255
#define FLASH_SIZE			(NOR_FLASH_BLOCK_SIZE * NOR_FLASH_BLOCKS_COUNT)

/* watchdog timer */
#define IRQ_TWDOG_INTID			56

/* Size of cacheable stacks */
#if IMAGE_NS_BL1U
#define PLATFORM_STACK_SIZE 0x1000
#elif IMAGE_NS_BL2U
#define PLATFORM_STACK_SIZE 0x1000
#elif IMAGE_TFTF
#define PLATFORM_STACK_SIZE 0x1400
#endif

/* Size of coherent stacks for debug and release builds */
#if DEBUG
#define PCPU_DV_MEM_STACK_SIZE 0x600
#else
#define PCPU_DV_MEM_STACK_SIZE 0x500
#endif

#define PLATFORM_SYSTEM_COUNT		1
#define PLATFORM_CLUSTER_COUNT		1
#define PLATFORM_CLUSTER0_CORE_COUNT	1 /* Cortex-A35 Cluster */
#define PLATFORM_CORE_COUNT		1
#define PLATFORM_NUM_AFFS		(PLATFORM_SYSTEM_COUNT + \
					PLATFORM_CLUSTER_COUNT + \
					PLATFORM_CORE_COUNT)
#define PLATFORM_MAX_AFFLVL		MPIDR_AFFLVL2
#define PLAT_MAX_PWR_LEVEL		PLATFORM_MAX_AFFLVL
#define PLAT_MAX_PWR_STATES_PER_LVL	2

#define CORSTONE1000_MAX_CPUS_PER_CLUSTER	4
#define CORSTONE1000_MAX_PE_PER_CPU		1

/* Local state bit width for each level in the state-ID field of power state */
#define PLAT_LOCAL_PSTATE_WIDTH		4

#if IMAGE_NS_BL1U
#define MAX_IO_DEVICES			2
#define MAX_IO_HANDLES			2
#else
#define MAX_IO_DEVICES			1
#define MAX_IO_HANDLES			1
#endif

/*
 * USE 0x200000 DRAM offset to store TFTF data
 *
 * Please note that this won't be suitable for all test scenarios and
 * for this reason some tests will be disabled in this configuration.
 */
#define TFTF_NVM_OFFSET		0x40000
#define TFTF_NVM_SIZE		(128 * SZ_1M)	/* 128 MB */

/*******************************************************************************
 * Platform specific page table and MMU setup constants
 ******************************************************************************/
#ifdef __aarch64__
#define PLAT_PHY_ADDR_SPACE_SIZE	(ULL(1) << 34)
#define PLAT_VIRT_ADDR_SPACE_SIZE	(ULL(1) << 34)
#else
#define PLAT_PHY_ADDR_SPACE_SIZE	(ULL(1) << 32)
#define PLAT_VIRT_ADDR_SPACE_SIZE	(ULL(1) << 32)
#endif

#if IMAGE_TFTF
/* For testing xlat tables lib v2 */
#define MAX_XLAT_TABLES			20
#define MAX_MMAP_REGIONS		50
#else
#define MAX_XLAT_TABLES			5
#define MAX_MMAP_REGIONS		16
#endif

/*******************************************************************************
 * Used to align variables on the biggest cache line size in the platform.
 * This is known only to the platform as it might have a combination of
 * integrated and external caches.
 ******************************************************************************/
#define CACHE_WRITEBACK_SHIFT   6
#define CACHE_WRITEBACK_GRANULE (1 << CACHE_WRITEBACK_SHIFT)

/*******************************************************************************
 * Non-Secure Software Generated Interupts IDs
 ******************************************************************************/
#define IRQ_NS_SGI_0		0
#define IRQ_NS_SGI_1		1
#define IRQ_NS_SGI_2		2
#define IRQ_NS_SGI_3		3
#define IRQ_NS_SGI_4		4
#define IRQ_NS_SGI_5		5
#define IRQ_NS_SGI_6		6
#define IRQ_NS_SGI_7		7

#define PLAT_MAX_SPI_OFFSET_ID	220

/* The IRQ generated by Ethernet controller */
#define IRQ_ETHERNET	116

#define IRQ_CNTPSIRQ1		92
/* Per-CPU Hypervisor Timer Interrupt ID */
#define IRQ_PCPU_HP_TIMER		26
/* Per-CPU Non-Secure Timer Interrupt ID */
#define IRQ_PCPU_NS_TIMER		30

/*
 * Times(in ms) used by test code for completion of different events.
 * Suspend entry time for debug build is high due to the time taken
 * by the VERBOSE/INFO prints. The value considers the worst case scenario
 * where all CPUs are going and coming out of suspend continuously.
 */
#if DEBUG
#define PLAT_SUSPEND_ENTRY_TIME		0x100
#define PLAT_SUSPEND_ENTRY_EXIT_TIME	0x200
#else
#define PLAT_SUSPEND_ENTRY_TIME		10
#define PLAT_SUSPEND_ENTRY_EXIT_TIME	20
#endif

#endif /* __PLATFORM_DEF_H__ */
