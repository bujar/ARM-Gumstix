
@ userSetup.S: given r0=argc, r1=argv
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@          Luo Wu <luow@andrew.cmu.edu>
@ Date: Thu Oct 24 15:15:13 EDT 2013

.file  "userSetup.S"
.text
.global userSetup

userSetup:
	/* saving SVC regs, not sure if we need to do this */
    /* PROBLEM: if we save it on the SVC stack, will
	          we know that we need to pop r4 off the SVC stack,
	          even though we're mostly in user mode?
    */
	STMFD	sp!, {r4-r11, lr} 	@store on SVC stack	
	
	/*since we need r0, we use r4 as a scratch reg.*/
	MRS	r4, cpsr
	BIC r4, r4, #3          @ change to user mode
    ORR r4, r4, #0x60   @ disable FIQ and IRQ bits
	MSR	cpsr, r4

	/* I think we can just use pseudo instructions addresses */
	LDR	sp, =0xa3000000		@ user stack set up
	
	/* What are the values of r0, r1 at this time (gdb)?
	 * r0 I think can be an arbitrary int value. r1 has to be
	 * a pointer to an array. So I think we should try to 
	 * set values for r0 and r1 here
	 */
	STMFD	sp!, {r0, r1}	@ push argc argv to stack
	LDR	pc, =0xa2000000		@ jump to user program

