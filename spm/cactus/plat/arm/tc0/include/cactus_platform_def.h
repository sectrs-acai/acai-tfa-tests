/*
 * Copyright (c) 2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <platform_def.h>

#ifndef CACTUS_PLATFORM_DEF_H
#define CACTUS_PLATFORM_DEF_H

#define PLAT_ARM_DEVICE0_BASE		TC0_DEVICE0_BASE
#define PLAT_ARM_DEVICE0_SIZE		TC0_DEVICE0_SIZE

#define CACTUS_PL011_UART_BASE		PL011_UART1_BASE
#define CACTUS_PL011_UART_CLK_IN_HZ	PL011_UART1_CLK_IN_HZ

#define PLAT_CACTUS_RX_BASE		ULL(0xfe300000)

#define CACTUS_PRIMARY_EC_COUNT		(4U)
#define CACTUS_SECONDARY_EC_COUNT	(4U)
#define CACTUS_TERTIARY_EC_COUNT	(4U)

#endif /* CACTUS_PLATFORM_DEF_H */
