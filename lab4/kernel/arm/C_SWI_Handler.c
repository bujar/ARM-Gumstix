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
#include <syscall.h>

int C_SWI_Handler(unsigned swi_num, unsigned *regs){
	int fd;
	void *buf;
	size_t size;
	unsigned int millis;

	task_t *tasks;
	size_t num_tasks;

	unsigned int dev;

	switch (swi_num) {
	    case READ_SWI:
			fd = regs[0];
			buf = (void *) regs[1];
			size = (size_t) regs[2];
	        return read_syscall(fd, buf, size);
		
		case WRITE_SWI:
			fd = regs[0];
			buf = (void *) regs[1];
			size = (size_t) regs[2];
        	return write_syscall(fd, buf, size);
		
		case SLEEP_SWI:
			millis = regs[0];
			sleep_syscall(millis);
			break;

		case TIME_SWI:
			return time_syscall();

		case CREATE_SWI: /* task_create */
			tasks = (task_t *)regs[0];
			num_tasks = regs[1];
			return task_create(tasks, num_tasks);

		case MUTEX_CREATE:
			break;			
		case MUTEX_LOCK:
			break;			
		case MUTEX_UNLOCK:
			break;			
		case EVENT_WAIT:
			dev = regs[0];
			return event_wait(dev);

		default:
			printf("Invalid SWI called");
			return(0x0badc0de);
	}

    return 0;
}
