/** @file write.S
 *
 * @brief write sycall wrapper
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 07 Oct 2007 01:53:46 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-29
 */

#include <asm.h>
#include <bits/swi.h>

	.file "write.S"

FUNC(write)
    @ Success returns positive value or 0.
    @ If error, return errno=abs(r0)
    @    and return -1
   
    STMFD sp!, {r0-r12, lr}
	
    swi WRITE_SWI
    cmp r0, #0
    movge   pc, lr
    asr r1, r0, #31 
    add r0, r0, r1
    eor r0, r0, r1
    ldr r1, =errno
    ldr r0, [r1]
    str r0, [r1]
    mov r0, #-1 
    
    LDMFD sp!, {r1-r12, lr}
    mov pc, lr

    
