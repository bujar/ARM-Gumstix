
@ userSetup.S: given r0=argc, r1=argv
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@          Luo Wu <luow@andrew.cmu.edu>
@ Date: Thu Oct 24 15:15:13 EDT 2013

.file  "userSetup.S"
.text
.global userSetup

userSetup:
	STMFD	sp!, {r4-r11, lr} 	@store on SVC stack	
	
	LDR 	r12, =SP_ADD
	STR	sp, [r12]
		
	/*since we need r0, we use r4 as a scratch reg.*/
	MRS	r12, cpsr
	BIC 	r12, r12, #3          	@ change to user mode
	ORR 	r12, r12, #0x60  	@ disable FIQ and IRQ bits
	MSR	cpsr, r12

	LDR	sp, =0xa3000000		@ user stack set up
	
    	/* copy all the pointers and push them on the user stack */
	MOV	r4, r0     	@r4 = argc
	MOV	r5, r4     	  
	LSL	r5, #2		@r5 = displace from argv[0]
loop:    
	LDR	r2, [r1, r5]	@r2 = MEM[r1+r5]
	SUB	r5, r5, #4	@r5 = r5 - 4
	STMFD	sp!, {r2} 
	SUBS	r4, r4, #1
	BGE	loop 		@loop until you push all arguments

	PUSH 		{r0}

	LDR	pc, =0xa2000000		@ jump to user program
	SWI	0x900001            	@ calling exit SWI

