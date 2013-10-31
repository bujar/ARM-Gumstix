/*	Group 37
*	Bujar Tagani - btagani
*	Jonathan Lim - jlim2
*	Luo Wu - luow
*/

/*	Instructions 19		*/	
/*	Load/Store	 24		*/
/*	Branch		 24		*/
/*	Normal		 68		*/
/*	Total		337		*/
	
	.file	"part1-strTable.c"
	.text
	.align	2
	.global	strTable
	.type	strTable, %function
strTable:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0

/*	got rid of all the storing into r4, r5, r6 - only modifying free regs r9 and ip(r12) */
	
	cmp	r9, r3		/*r9 is our counter=0, comparing to dl */
	bge	.L11		/* if dl<=0, then exit */
.L9:
	ldrb	r3, [r1, r9]	@ zero_extendqisi2 /*stores ascii value of d into r3*/ 
	sub	r3, r3, #23
	cmp	r3, #22
	ble	.L13

/* Perform loop unrolling to save on branch instructions */

.L7:
	sub	r3, r3, #23	/* this loop performs ascii % 23 */
	cmp	r3, #22		
	subgt	r3, r3, #23	/*subtract again if greater than 22 */
	cmp	r3, #22		
	bge	.L7		 /* keep looping if >22 */
/*
* Got rid of instructions in .L13 which checks if the ascii value
* has already been used for replacement. We made this tradeoff
* after assessing the memory cost of these extra instructions
* since PENGUINS only runs into this case once.
*/

.L13:
	cmp	r3, r2		
	bgt	.L4		
	ldrb	ip, [r1, r9]	
	strb	ip, [r0, r3]
.L4:
	add	r9, r9, #1	/* kept it as incrementing so we can eliminate instructions from .L13*/
	cmp	r9, r5
	blt	.L9		/* loop back to beginning dl times */
.L11:
	mov pc, lr

	.size	strTable, .-strTable
	.ident	"GCC: (GNU) 3.4.5"
