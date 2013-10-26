
@ hello.S: Hello world! in assembly
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

.file  "S_Handler.S"
.text
.global S_Handler

S_Handler:

	@SUB	sp, sp, #4
	STMFD	sp!, {r0-r12, lr}
	@MRS	r2, spsr
	@STR	r2, [sp, #14*4]
	MOV	r1, sp
	LDR	r0, =SVC_r8	@restore r8
	LDR	r8, [r0]
	LDR	r0, [lr, #-4]
	BIC	r0, r0, #0xff000000
	BL	C_SWI_Handler
	@LDR	r2, [sp, #14*4]
	@MSR	spsr, r2
	LDMFD	sp!, {r0-r12, lr} /*r0-r12... */
    PUSH	{r2}
	LDR		r2, =GLOBALRET
	LDR		r0, [r2]
	POP		{r2}
	@ADD 	sp, sp, #8  /*used to be #4 */
	MOVS	pc, lr
