/*
 * C_SWI_Handler.c	Handles SWI Calls based on SWI Num
 *
 * Author: Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu> 
 * Date:   Thu Nov  7 00:01:35 EST 2013
 */

#include <bits/swi.h>
#include <exports.h>
#include "syscall.h"

int C_SWI_Handler(unsigned swi_num, unsigned *regs){
	int fd;
	void *buf;
	size_t size;
	unsigned int status;
	unsigned int millis;
	
	switch (swi_num) {
	    case READ_SWI:
			fd = regs[0];
			buf = (void *) regs[1];
			size = (size_t) regs[2];
	        return read(fd, buf, size);
		
		case WRITE_SWI:
			fd = regs[0];
			buf = (void *) regs[1];
			size = (size_t) regs[2];
        	return write(fd, buf, size);
		
		case EXIT_SWI:
			status = regs[0];
			exit(status);
		
		case SLEEP_SWI:
			millis = regs[0];
			sleep(millis);
			break;

		case TIME_SWI:
			return time();

		default:
			printf("Invalid SWI called");
			return(0x0badc0de);
	}

    return 0;
}
