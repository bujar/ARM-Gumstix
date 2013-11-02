/**
 * @file  start.S
 *
 * @brief Kernel startup routine
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Tue, 23 Oct 2007 11:20:33 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-07-06
 */

#include <asm.h>

	.file   "start.S"

FUNC(_start)


	@store the lr and other registers so we can restore state on exit
	STMFD   sp!, {r0-r12, lr}  @ store registers on SVC stack
	
	PUSH	{r4, r5}	
	LDR 	r4, =UBOOT_SP
	ADD	r5, sp, #8
	STR	r5, [r4]
	
	@ store r8 in global value so we can restore before syscall.
	LDR	r4, =SVC_r8	
	STR	r8, [r4]
	
	pop	{r4, r5}		

	
	/*
	 * Branch immediately to main without altering the execution environment.
	 * This indirection is needed to guarantee that the program entry point is
	 * LOAD_ADDR (probably 0xa3000000) without placing strict
	 * requirements on the layout of kernel.c.  Bit first, provide main with the
	 * jump table address as one of its arguments.
	 */
	mov     r2, r8
	b       kmain

