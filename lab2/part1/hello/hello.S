@ hello.S: Hello world! in assembly
@
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@          Luo Wu <luow@andrew.cmu.edu>
@ Date:    The current time & date

#include <bits/swi.h>
#include <bits/fileno.h>

	.file	"hello.S"
	.text
	.global	_start

.LC0:
	.ascii "Hello world!\n"
	.text
	.align 2

_start:
	@ Calls the write system call with 
	@ arg1 = STDOUT_FILENO
	@ arg2 = address of "Hello world!\n"
	@ arg3 = size of Hello world string
	@ and exits with status code of 0 
	mov 	r0, #STDOUT_FILENO
	ldr	r1, .L1
	mov	r2, #13
	swi	WRITE_SWI
	mov	r0, #0
	swi	EXIT_SWI

.L1:
	.word .LC0


