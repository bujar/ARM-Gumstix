@ read.S: read sycall wrapper
@
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@	   Luo Wu <luow@andrew.cmu.edu>
@ Date:    SAT Oct 12 17:38:48 EDT 2013

	#include <bits/swi.h>
	
	.file	"read.S"
	.text

	.global	read
read:
	@Return value of read into r0
	@If r0<0, errno=abs(r0)
	@Return r0=-1

	swi	READ_SWI
	cmp	r0, #0
	movge	pc, lr
	asr	r1, r0, #31
	add	r0, r0, r1
	eor	r0, r0, r1
	ldr	r1, =errno
	str	r0, [r1]
	mov	r0, #-1
	mov pc, lr
