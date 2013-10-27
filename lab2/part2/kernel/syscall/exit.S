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
	LDR 	r1, =UBOOT_SWI_ADDR	@get the address of UBOOT_SWI_ADDR 
	LDR 	r2, =UBoot_swi_instruction1 		
	LDR	r3, =UBoot_swi_instruction2
    
	LDR	r1, [r1] 		@get the value of UBOOT_SWI_ADDR	
	LDR	r2, [r2]		@get the value of UBOOT_swi_instruction1
	LDR	r3, [r3]		@get the value of UBOOT_swi_instruction2
	STR	r2, [r1]		@restore the first instruction
	STR	r3, [r1, #4]		@restore the second instruction

	LDR 	r4, =SP_ADD
	LDR	sp, [r4]	
	LDMIA	sp, {r0-r12, lr}
	mov	pc, lr
	
   	@LDR	r4, =UBOOT_RetAddr	@get the address of UBOOT_RetAddr
	@LDR	pc, [r4]		@to go back to UBOOT	
	
	
    /* hardcoded values - not using these */
	@LDR	r1, =0x5c0009c0		@address of first instruction UBOOT_SWI
	@LDR	r2, =0xe51fd980		@original optcode at 0x5c0009c0
	@LDR	r3, =0xe24dda41		@original optcode at 0x5c0009c4
	@STR	r2, [r1]		@restore the first instruction
	@STR	r3, [r1, #4]		@restore the second instruction
