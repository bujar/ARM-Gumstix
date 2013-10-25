
@ userSetup.S
@
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@          Luo Wu <luow@andrew.cmu.edu>
@ Date: Thu Oct 24 15:15:13 EDT 2013

.file  "userSetup.S"
.text
.global userSetup

userSetup:
	/* saving SVC regs, not sure if we need to do this */
	STMFD	sp!, {r4-r11, lr} 	@store on SVC stack	
	
	/*let's change r0 to a different register since 
	 we are passing it to main, here we just use a scratch reg */
	MRS	r0, cpsr
	BIC 	r0, r0, #3
	MSR	cpsr, r0

	/* I think we can just use pseudo instructions addresses */
	LDR	sp, =0xa3000000		@user stack set up
	
	/* What are the values of r0, r1 at this time (gdb)?
	 * r0 I think can be an arbitrary int value. r1 has to be
	 * a pointer to an array. So I think we should try to 
	 * set values for r0 and r1 here
	 */
	STMFD	sp!, {r0, r1}		@push argc argv to stack
	LDR	pc, =0xa200000		@jump to user program

