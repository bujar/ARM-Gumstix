/** @file time.S
 *
 * @brief time sycall wrapper
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 */

#include <asm.h>
#include <bits/swi.h>

	.file "time.S"

FUNC(time)
	STMFD 	sp!, {r1-r12, lr}
	SWI	TIME_SWI
	LDMFD	sp!, {r1-r12, lr}
	MOV	pc, lr
