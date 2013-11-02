@ syscall: exit
@ exit.S
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@          Luo Wu <luow@andrew.cmu.edu>
@ Date: Thu Oct 25 10:15:13 EDT 2013

@ 1. restore the instructions that were overwriten when install our handler
@ 2. exit with status

.file	"exit.S"
.text
.global exit

exit:
	LDR r1, =UBOOT_SWI_ADDR	@get the address of UBOOT_SWI_ADDR 
	LDR r2, =UBoot_swi_instruction1 		
	LDR	r3, =UBoot_swi_instruction2
    
	LDR	r1, [r1] 		@get the value of UBOOT_SWI_ADDR	
	LDR	r2, [r2]		@get the value of UBOOT_swi_instruction1
	LDR	r3, [r3]		@get the value of UBOOT_swi_instruction2
	STR	r2, [r1]		@restore the first instruction
	STR	r3, [r1, #4]	@restore the second instruction
   	
    LDR	r4, =UBOOT_SP	@get the address of UBOOT_RetAddr
	LDR	sp, [r4]		@to go back to UBOOT	

	@ADD	sp, sp, #4*18
	ADD sp, sp, #4
	LDMFD	sp!, {r1-r12, lr} @ restore state
	MOV	pc, lr

