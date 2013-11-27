/** @file time.S
 *
 * @brief time sycall wrapper
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 */

#include <asm.h>
#include <bits/swi.h>

	.file "task_create.S"

FUNC(task_create)
    STMFD sp!, {r0-r12, lr}
    swi CREATE_SWI
    add sp, sp, #4
    LDMFD sp!, {r1-r12, lr}
    
	# THIS MUST BE CHANGED TO SET ERRNO
    cmp r0, #0
    moveq   pc, lr
    ldr r1, =errno
    str r0, [r1] 
    mov r0, #-1 
    mov pc, lr

