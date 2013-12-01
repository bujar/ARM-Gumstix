/**
 * @file task_create.S
 *
 * @brief task create sycall wrapper
 *
 * @author: Bujar Tagani <btagani@andrew.cmu.edu>
 *          Jonathan Lim <jlim2@andrew.cmu.edu>
 *          Norman Wu <luow@andrew.cmu.edu>
 * @date: Sat Nov  22 18:54:08 EDT 2013
 */

#include <asm.h>
#include <bits/swi.h>

	.file "task_create.S"

FUNC(task_create)
	STMFD sp!, {r0-r12, lr}
    swi CREATE_SWI
	ADD sp, sp, #4
    LDMFD sp!, {r1-r12, lr}

	/*error if SWI returns...*/
    ldr r1, =errno
    str r0, [r1] 
    mov r0, #-1 
    mov pc, lr

