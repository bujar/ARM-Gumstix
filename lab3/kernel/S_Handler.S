
@ S_Handler.S: Handles SWI calls
@
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@          Luo Wu <luow@andrew.cmu.edu>
@ Date: Thu Oct 24 15:15:13 EDT 2013

/* assembly function which we will branch to
*  this function will store user reg and lr
*  also extract swi number and pass it to 
*  C_SWI_Handler
*/

#include <arm/psr.h>

.file  "S_Handler.S"
.text
.global S_Handler

S_Handler:

	SUB	sp, sp, #4               @ leave room on stack for SPSR
	STMFD	sp!, {r0-r12, lr}    @ store user's gp registers
	MRS	r2, spsr                 @ get SPSR into gp register 
	STR	r2, [sp, #14*4]          @ store SPSR above gp registers
	MOV	r1, sp                   @ pointer to parameter on stack
	LDR	r0, =SVC_r8	@restore r8  
	LDR	r8, [r0]
	LDR	r0, [lr, #-4]            @ extract SWI number
	BIC	r0, r0, #0xff000000      

	MRS	ip,cpsr			@enable IRQ
	BIC	ip, ip, #PSR_IRQ	
	MSR	cpsr, ip

	BL	C_SWI_Handler            @ goto handler
	LDR	r2, [sp, #14*4]          @ restore SPSR
	MSR	spsr, r2                 @ restore SPSR from r2
	ADD	sp, sp, #4               @ remove r0 from the top of stack
	LDMFD	sp!, {r1-r12, lr}    @ unstack user's registers
	ADD 	sp, sp, #4           @ remove space used to store SPSR 
	MOVS	pc, lr
