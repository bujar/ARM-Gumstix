
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
	MRS		r0, cpsr
	BIC 	r0, r0, #3
	MSR		cpsr, r0
	LDR		pc, .L1

.L1:
	.word 0xa2000000
