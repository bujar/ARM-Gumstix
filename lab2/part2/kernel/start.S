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


	@store the lr and other registers so we can restore state on exit
	STMFD   sp!, {r0-r12, lr}  @ store registers on SVC stack
	
	PUSH	{r4, r5}	
	LDR 	r4, =UBOOT_SP
	ADD		r5, sp, #8
	STR		r5, [r4]
	
	@ store r8 in global value so we can restore before syscall.
	LDR	r4, =SVC_r8	
	STR	r8, [r4]
	
	pop	{r4, r5}		

	@ Branch immediately to main without altering the execution environment.
	@ This indirection is needed to guarantee that the program entry point is
	@ LOAD_ADDR (probably 0xa3000000) without placing strict
	@ requirements on the layout of kernel.c.
	b	main
