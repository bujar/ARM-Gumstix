/** @file proc.c
 * 
 * @brief Implementation of `process' syscalls
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 14 Oct 2007 00:07:38 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-12
 */

#include <exports.h>
#include <bits/errno.h>
#include <config.h>
#include <kernel.h>
#include <syscall.h>
#include <sched.h>

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>
#include <device.h>

int schedulable(task_t* tasks __attribute__((unused)), size_t num_tasks __attribute__((unused))) {
  unsigned int i;

  for(i = 0; i < num_tasks; i++) {
  // i is the index for tasks, perform validation test for each task[i]
  return 1;	//return 1 if error encountered
  }
 
  return 0;	//reach here if there were no errors
}

int sort_tasks( task_t* tasks __attribute__((unused)), size_t num_tasks __attribute__((unused))) {
  //sort some shit
  return 1;
}

int task_create(task_t* tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
  
  sort_tasks(tasks, num_tasks);
  allocate_tasks(&tasks, num_tasks);
  dispatch_nosave(); //do we need this here?


  return 1; /* remove this line after adding your code */
}

int event_wait(unsigned int dev  __attribute__((unused)))
{
  return 1; /* remove this line after adding your code */	
}

/* An invalid syscall causes the kernel to exit. */
void invalid_syscall(unsigned int call_num  __attribute__((unused)))
{
	printf("Kernel panic: invalid syscall -- 0x%08x\n", call_num);

	disable_interrupts();
	while(1);
}
