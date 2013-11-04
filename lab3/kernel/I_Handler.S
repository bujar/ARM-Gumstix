
@ I_Handler.S: Handles IRQ calls
@
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@          Luo Wu <luow@andrew.cmu.edu>
@ Date: Thu Oct 24 15:15:13 EDT 2013

/* Re-entrant IRQ handler which will save and restore
 * user registers
*/

#include <arm/psr.h>

.file  "I_Handler.S"
.text
.global I_Handler

I_Handler:

	STMFD	sp!, {r0-r12, lr}	@store user reg on stack
	LDR	r0, =SVC_r8		@restore r8
	LDR	r8, [r0]

	MRS	ip, cpsr		@disable IRQ interrupts
	ORR	ip, ip, #PSR_IRQ
	MSR	cpsr, ip

	BL	C_IRQ_Handler
	
	MRS	ip, cpsr		@enable interrupts
	EOR	ip, ip, #PSR_IRQ
	MSR	cpsr, ip

	ADD	sp, sp, #4		@make sp = r1
	LDMFD	sp!, {r1-r12, lr}	@unstack user reg
	SUBS	pc, lr, #4
