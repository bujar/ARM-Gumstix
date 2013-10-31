/** @file crt0.S
 *
 * @brief Execution startup routine
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 07 Oct 2007 01:51:29 -0400
 */

#include <asm.h>
#include <bits/swi.h>

	.file "crt0.S"

FUNC(_start)

    /* void _start(void){
     *    int argc;
     *    char **argv;
     *
     *    exit(main(argc, argv));
     *
     */
    
	@ 0. save registers that would be used
    @ since the registers are undefined in the beginning, 
    @ it is not necessary
    
    ldr r0, [sp]        /* loader argc into r0 */
    add r1, sp, #4      /* loader argv into r1 */
    bl main
    swi EXIT_SWI

