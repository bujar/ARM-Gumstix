@ start.S: Kernel startup routine
@
@ Author: Mike Kasick <mkasick@andrew.cmu.edu>
@ Date:   Tue, 23 Oct 2007 11:20:33 -0400

	.file	"start.S"
	.text

	.global	_start
_start:
	@store the lr for later exit use
	PUSH	r4
	LDR 	r4, =UBOOT_RetAddr
        STR     lr, [r4]
	
	@ storing into global variable original r8 so we can preserve throughout
	LDR	r4, =SVC_r8	
	STR	r8, [r4]
	
	pop 	r4

	@ Branch immediately to main without altering the execution environment.
	@ This indirection is needed to guarantee that the program entry point is
	@ LOAD_ADDR (probably 0xa3000000) without placing strict
	@ requirements on the layout of kernel.c.
	b	main
