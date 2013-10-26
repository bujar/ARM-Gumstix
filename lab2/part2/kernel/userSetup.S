
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
	
	/* store LR to a global for exit */
	@LDR r4, =UBOOT_RetAddr
	@STR	lr, [r4]
    
	/*since we need r0, we use r4 as a scratch reg.*/
	MRS	r4, cpsr
	BIC r4, r4, #3          @ change to user mode
    ORR r4, r4, #0x60   @ disable FIQ and IRQ bits
	MSR	cpsr, r4

	/* I think we can just use pseudo instructions addresses */
	LDR	sp, =0xa3000000		@ user stack set up
	
	/* What are the values of r0, r1 at this time (gdb)?*/
    /* copy all the pointers and push them on the user stack */

	MOV		r4, r0        @r4 = argc
	MOV		r5, r4
	LSL		r5, #2
loop:    
	LDR		r2, [r1, r5] 
	ADD		r5, r5, #-4
	STMFD	sp!, {r2} 
	SUBS	r4, r4, #1
	BGT		loop 

	PUSH	{r0}	
	MOV		lr, pc
	LDR		pc, =0xa2000000		@ jump to user program
    SWI 	0x900001            @ calling exit SWI

