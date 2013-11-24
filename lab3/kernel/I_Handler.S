@ I_Handler.S: Handles IRQ calls
@
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@          Luo Wu <luow@andrew.cmu.edu>
@ Date: Thu Nov  7 00:03:15 EST 2013

/* IRQ handler which will save and restore
 * registers as well as re-enable IRQ via cpsr
*/

#include <arm/psr.h>

.file  "I_Handler.S"
.text
.global I_Handler

I_Handler:

	STMFD	sp!, {r0-r12, lr}	@store reg on stack
	LDR	r0, =SVC_r8		@restore r8
	LDR	r8, [r0]

	BL	C_IRQ_Handler
	
	#MRS	ip, cpsr		@restore cpsr to enable IRQ
	#BIC	ip, ip, #PSR_IRQ
	#MSR	cpsr, ip
		
	#ADD	sp, sp, #4		@make sp = r1
	
	LDMFD	sp!, {r0-r12, lr}	@unstack reg
	SUBS	pc, lr, #4

