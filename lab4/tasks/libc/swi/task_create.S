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
    swi CREATE_SWI
    
    ldr r1, =errno
    str r0, [r1] 
    mov r0, #-1 
    mov pc, lr

