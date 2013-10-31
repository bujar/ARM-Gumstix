@ start.S: Kernel startup routine
@ We modified this file so we can grab the 
@ initial lr and r8 upon entering kernel.
@
@ Authors: Bujar Tagani <btagani@cmu.edu>
@  Jonathan Lim <jlim2@cmu.edu>
@	  Luo Wu <luow@cmu.edu>
@ Date:   SAT, 26 Oct 2013 07:20:33 -0400

	.file	"start.S"
	.text

	.global	_start
_start:


	@store the lr and other registers so we can use it to exit
	STMFD   sp!, {r0-r12, lr}  @ store registers on SVC stack
	
/*	PUSH	{r12}			@store the pc to global varibales
    LDR     r12, =SP_ADD
	SUB	sp, sp, #4
    STR     sp, [r12]
	ADD  sp, sp, #4
	pop	{r12}
*/
	PUSH	{r4}			@ use r4 as scratch reg
	LDR 	r4, =UBOOT_RetAddr
	STR	lr, [r4]
	
	@ store r8 in global value so we can preserve throughout
	LDR	r4, =SVC_r8	
	STR	r8, [r4]
	
	pop	{r4}			@restore value of r4

	@ Branch immediately to main without altering the execution environment.
	@ This indirection is needed to guarantee that the program entry point is
	@ LOAD_ADDR (probably 0xa3000000) without placing strict
	@ requirements on the layout of kernel.c.
	b	main
