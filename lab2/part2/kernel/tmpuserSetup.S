
@ userSetup.S: - changes CPSR to be in user mode
@              - configures the stack
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@          Luo Wu <luow@andrew.cmu.edu>
@ Date: Thu Oct 24 15:15:13 EDT 2013

.file  "userSetup.S"
.text
.global userSetup

userSetup:
	MRS		r0, cpsr
	BIC 	r0, r0, #3      @change to user mode
	ORR		r0, r0, #0x60   @disable FIQ and IRQ bits
	MSR		cpsr, r0      
    
    /* copy argc and argv to user stack */
	PUSH	{r0}            @may not be necessary
    LDR		r0, .L2         @r0 points to SVC stack
	MOV		r0, #0          @putting 0 into r0 as argc fake for now
	LDR		r1, .L2         @getting address of stack top 
	STR 	r0, [r1, #0]    @store argc onto stack top
	STR 	r0, [r1, #4]    @store argv as 0 onto stack top
	LDR		pc, .L1
	
    /*POP		{r0} */
    
.L1:
	.word 0xa2000000

.L2:
	.word 0xa3000000

