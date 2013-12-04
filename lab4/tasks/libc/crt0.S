/** @file crt0.S
 *
 * @brief Execution startup routine
 *
 * @author Bujar Tagani <btagani@andrew.cmu.edu>
 * 		   Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 * @date   Mon Nov 18 12:04:04 EST 2013
 */

#include <asm.h>

	.file "crt0.S"

FUNC(_start)
    
    ldr r0, [sp]        /* loader argc into r0 */
    add r1, sp, #4      /* loader argv into r1 */
    bl main
    sub pc, pc, #8     /* infinite loop to main */

