/** @file crt0.S
 *
 * @brief Execution startup routine
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 07 Oct 2007 01:51:29 -0400
 */

#include <asm.h>
<<<<<<< HEAD
#include <bits/swi.h>
=======
>>>>>>> 3a8d0b7d1ecd47f57ab700d10ccd9ba555ef4cc8

	.file "crt0.S"

FUNC(_start)
<<<<<<< HEAD

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


=======
	@ needs code.  Put your names at the top.
>>>>>>> 3a8d0b7d1ecd47f57ab700d10ccd9ba555ef4cc8
