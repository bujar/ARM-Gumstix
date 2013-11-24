/** @file event_wait.S
 *
 * @brief time sycall wrapper
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 *
 * @author Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu> 
 * @date   Sun Nov 24 15:15:34 EST 2013
 */


#include <asm.h>
#include <bits/swi.h>

	.file "event_wait.S"

FUNC(event_wait)

    STMFD sp!, {r0-r12, lr}
    swi EVENT_WAIT
    add sp, sp, #4
    LDMFD sp!, {r1-r12, lr}
    
    cmp r0, #0
    moveq   pc, lr
    ldr r1, =errno
    str r0, [r1] 
    mov r0, #-1 
    mov pc, lr

