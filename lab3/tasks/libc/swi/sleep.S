/** @file sleep.S
 *
 * @brief sleep sycall wrapper
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 */

#include <asm.h>
#include <bits/swi.h>

	.file "sleep.S"

FUNC(sleep)
	STMFD 	sp!, {r1-r12, lr}
	SWI	SLEEP_SWI
	LDMFD	sp!, {r1-r12, lr}
	MOV	pc, lr
