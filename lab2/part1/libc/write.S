@ write.S: write sycall wrapper
@
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@	   Luo Wu <luow@andrew.cmu.edu>
@ Date:    Sat Oct 12 17:38:48 EDT 2013

	#include <bits/swi.h>

	.file	"write.S"
	.text

	.global	write
write:
	@Return value of write into r0
	@If r0<0, errno=abs(r0)
	@Change return value r0 to default -1

	swi	WRITE_SWI
	cmp	r0, #0
	movge	pc, lr
	asr	r1, r0, #31
	add	r0, r0, r1
	eor	r0, r0, r1
	ldr	r1, =errno
	ldr	r0, [r1]
	str	r0, [r1]
	mov	r0, #-1
	mov	pc, lr
