@ crt0.S: Execution startup routine
@
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@	   Luo Wu <luow.andrew.cmu.edu>
@ Date:    The current time & date

#include<bits/swi.h>

	.file	"crt0.S"
	.text

	.global	_start
_start:
	@ 0. save registers that would be used
	@ since the registers are undefined in the begining, it is not necessary
	
	@ 1. place values on stack into r0 and r1
	ldr r0, sp		/* loader argc into r0 */
	add r1, sp, #4		/* loader argv into r1 */

	@ 2. call main
.L2:	
	bl main
	
	@ 3. call exit
.L3:
	swi EXIT_SWI

