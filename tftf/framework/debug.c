/*
 * Copyright (c) 2018, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <console.h>
#include <debug.h>

#if DEBUG
void __attribute__((__noreturn__)) do_panic(const char *file, int line)
{
	printf("PANIC in file: %s line: %d\n", file, line);

	console_flush();

	while (1)
		continue;
}

void __attribute__((__noreturn__)) do_bug_unreachable(const char *file, int line)
{
	mp_printf("BUG: Unreachable code!\n");
	do_panic(file, line);
}

#else
void __attribute__((__noreturn__)) do_panic(void)
{
	printf("PANIC\n");

	console_flush();

	while (1)
		continue;
}

void __attribute__((__noreturn__)) do_bug_unreachable(void)
{
	mp_printf("BUG: Unreachable code!\n");
	do_panic();
}
#endif
