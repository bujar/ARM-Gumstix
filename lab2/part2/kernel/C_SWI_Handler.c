/*
 * kernel.c: Kernel main (entry) function
 *
 * Author: Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu> 
 * Date:   The current time & date
 */

#include <bits/swi.h>
#include <exports.h>

#include "syscall.h"

int C_SWI_Handler(unsigned swi_num, unsigned *regs){
	int r0;
	void *r1;
	size_t r2;

	/* Getting first three registers on stack */
	r0 = (int) regs[0];		//file descriptor
	r1 = (void *) regs[1];		//buffer array
	r2 = (size_t) regs[2];		//size

	switch (swi_num) {
	   case READ_SWI:
			r0 = read(r0, r1, r2);
		    break;

	   case WRITE_SWI:
          	r0 = write(r0, r1, r2);
			break;
	   case EXIT_SWI:
			exit(r0);
          	break;
	   default:
			printf("Invalid SWI called");
          		return(0x0badc0de);
	}

    return r0;

}
