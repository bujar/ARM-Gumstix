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
    r0 = 2; //must change

	switch (swi_num) {
	   case READ_SWI:
          break;
	   case WRITE_SWI:
          break;
	   case EXIT_SWI:
          break;
	   default:
          break;
	}

    return r0;

}
