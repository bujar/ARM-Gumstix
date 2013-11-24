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

task_t *system_ptasks[OS_MAX_TASKS]; /* pointer to ptrs of tasks to be sorted */

// our functions
static int schedulable(task_t* tasks __attribute__((unused)), size_t num_tasks __attribute__((unused)));
static void sort_tasks( task_t* tasks, size_t num_tasks);
static void insertion_sort(task_t** tasks, size_t num_tasks);
 
static int schedulable(task_t* tasks __attribute__((unused)), size_t num_tasks __attribute__((unused))) {
  unsigned int i;

  for(i = 0; i < num_tasks; i++) {
	if (tasks[i].C > tasks[i].T) {
	   return ESCHED;
	}
	if (tasks[i].C == 0) {
	   return EINVAL;
	}
	if (tasks[i].T == 0) {
	   return EINVAL;
	}
  }
  if (num_tasks > OS_MAX_TASKS) {
	return EINVAL;
  }
  return 0;
}

/* implements the rate monotonic scheduling (RMS) algorithm
 *     sort them by period with shortest being the highest prio
 */

static void sort_tasks(task_t* tasks, size_t num_tasks) {
	// create pointers to tasks to sort instead
	int i;
	for( i = 0; i < (int) num_tasks; i++){
		system_ptasks[i] = &tasks[i];
	}

	insertion_sort(system_ptasks, num_tasks);	
}

static void insertion_sort(task_t** ptasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused))){
	int i, j;
	unsigned long Tperiod;
	task_t **curr;
	for(i = 1; i < (int)num_tasks; i++){
		curr = &ptasks[i];
		Tperiod = ptasks[i]->T;
		j = i - 1;
		while( j >= 0 && ptasks[j]->T > Tperiod){
			ptasks[i+1] = ptasks[j];
			j = j - 1;
		}
		ptasks[j+1] = *curr;
	}
}

int task_create(task_t* tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
  int error;
  error = schedulable(tasks, num_tasks);
  if (error != 0) {
  	return error;
  }
  sort_tasks(tasks, num_tasks);
  allocate_tasks(system_ptasks, num_tasks);
  dispatch_nosave(); //do we need this here?


  return 1; /* remove this line after adding your code */
}


int event_wait(unsigned int dev  __attribute__((unused)))
{
	if(dev > NUM_DEVICES - 1){
		return EINVAL;
	}
	dev_wait(dev);
	return 0;
}

/* An invalid syscall causes the kernel to exit. */
void invalid_syscall(unsigned int call_num  __attribute__((unused)))
{
	printf("Kernel panic: invalid syscall -- 0x%08x\n", call_num);

	disable_interrupts();
	while(1);
}
