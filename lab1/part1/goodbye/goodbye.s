	.file	"goodbye.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Hello, world!\000"
	.align	2
.LC1:
	.ascii	"Goodbye world!\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	ldr	r0, .L3			/* stores Hello World into r0 */
	bl	puts			/* calls puts function to print r0 */
	ldr	r0, .L3+4		/* stores Goodbye World into r0 */
	bl	puts			/* calls puts function to print r0*/
	mov	r0, #42			/* stores 42 into r0 */
	bl	exit			/* program exits with status 42 */
.L4:
	.align	2
.L3:
	.word	.LC0			/* calls .LC0 - Hello World */
	.word	.LC1			/* L3+4; calls LC1 - Goodbye World */
	.size	main, .-main
	.ident	"GCC: (GNU) 4.1.2"
