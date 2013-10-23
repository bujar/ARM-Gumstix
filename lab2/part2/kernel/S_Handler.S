/* assembly function which we will branch to
*  this function will store user reg and lr
*  also extract swi number and pass it to 
*  C_SWI_Handler
*/

S_Handler
	SUB	sp, sp, #4
	STMFD	sp!, {r0-r12, lr}
	MRS	r2, spsr
	STR	r2, [sp, #14*4]
	MOV	r1, sp
	LDR	r0, [lr, #-4]
	BIC	r0, r0, #0xff000000
	BL	C_SWI_Handler
	LDR	r2, [sp, #14*4]
	MSR	spsr, r2
	LDMFD	sp!, {r0-r12, lr}
	ADD 	sp, sp, #4
	MOVS	pc, lr
