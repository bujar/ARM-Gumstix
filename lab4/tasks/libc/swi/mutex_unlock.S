/* 
 * Author: Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 * Date: Sat Nov  22 18:54:08 EDT 2013
 */

/** @file mutex_unlock.S
 *
 * @brief mutex unlock sycall wrapper
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 */

#include <asm.h>
#include <bits/swi.h>

	.file "mutex_unlock.S"

FUNC(mutex_unlock)
    
	@ Success returns positive value.
    @ If error, return errno=abs(r0)
    @    and return -1

    STMFD sp!, {r0-r12, lr}
    swi MUTEX_UNLOCK
    ADD sp, sp, #4
    LDMFD sp!, {r1-r12, lr}

    CMP r0, #0
    MOVEQ pc, lr
    RSB r1, r0, #0
    LDR r2, =errno
    STR r1, [r2]
    MOV r0, #-1          
    MOV pc, lr
