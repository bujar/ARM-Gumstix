/** @file time.S
 *
 * @brief time sycall wrapper
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 *
 * @author Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 * @date   Mon Nov 18 12:25:30 EST 2013
 */

#include <asm.h>
#include <bits/swi.h>

	.file "time.S"

FUNC(time)
    STMFD   sp!, {r1-r12, lr}
    SWI TIME_SWI
    LDMFD   sp!, {r1-r12, lr}
    MOV pc, lr

