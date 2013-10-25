/*
 * kernel.c: Kernel main (entry) function
 *
 * Author: Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu> 
 * Date:   The current time & date
 */

#include <bits/swi.h>

int C_SWI_Handler(unsigned swi_num, unsigned *regs){
	int r0;
	r0 = 2; //tmp'
	/* Getting first three registers on stack */
	//r0 = (int) regs[0];		//file descriptor
	//r1 = (void *) regs[1];		//buffer array
	//r2 = (size_t) regs[2];		//size

	switch (swi_num) {
	   case READ_SWI:
			//r0 = read(r0, r1, r2);
		        break;

	   case WRITE_SWI:
          		//r0 = write(r0, r1, r2);
			break;
	   case EXIT_SWI:
			//r0 = exit(r0);
          		break;
	   default:
			//printf("Invalid SWI called");
          		break;
	}

    return r0;

}
