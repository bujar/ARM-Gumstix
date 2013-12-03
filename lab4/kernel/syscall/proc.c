/** @file proc.c
 * 
 * @brief Implementation of `process' syscalls
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 14 Oct 2007 00:07:38 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-12
 * 
 * @author Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 * @date Sat Nov 30 21:27:29 EST 2013
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
#define TASK_ADDR_BEGIN 0xa0000000
#define TASK_ADDR_END	0xa3000000
#define NUM_TASKS 64

task_t *system_ptasks[OS_MAX_TASKS]; /* pointer to ptrs of tasks to be sorted */

// our functions
static int schedulable(task_t* tasks, size_t num_tasks);
static void sort_tasks( task_t* tasks, size_t num_tasks);
static void insertion_sort(task_t** tasks, size_t num_tasks);
static void clear_tasks(); // clears the ptasks array
 
static void clear_tasks(){
	int i;
	for(i = 0; i < OS_MAX_TASKS; i++){
		system_ptasks[i] = 0; //NULL it all
	}
}

static int schedulable(task_t* tasks, size_t num_tasks) {

	unsigned int i;

	// checks if tasks array is in proper memory addr?
	// NEED TO FIX BOUNDARIES.
	if(((unsigned int)tasks > TASK_ADDR_END) ||
	   ((unsigned int)tasks < TASK_ADDR_BEGIN))
		return EFAULT;		
	
	if (num_tasks > (OS_MAX_TASKS - 2)) {
		return EINVAL;
  	}

	for(i = 0; i < num_tasks; i++) {
		if (tasks[i].C > tasks[i].T) {
			return ESCHED;
		}
		
		if (tasks[i].T == 0) {
			return EINVAL;
		}
	}
	return 0;
}

/* implements the rate monotonic scheduling (RMS) algorithm
 * and sort tasks by period with the first task in the array
 * with the highest prio
 */

static void sort_tasks(task_t* tasks, size_t num_tasks) {
	
	// create pointers to tasks array for sorting
	int i;
	for( i = 0; i < (int) num_tasks; i++){
		system_ptasks[i] = &tasks[i];
	}

	insertion_sort(system_ptasks, num_tasks);	
	
}

static void insertion_sort(task_t** ptasks, size_t num_tasks){
	int i, j;
	unsigned long Tperiod;
	task_t *curr;
	for(i = 1; i < (int)num_tasks; i++){
		curr = ptasks[i];
		Tperiod = curr->T;
		
		j = i;
		/* move the value left until it's in proper place */ 
		while( j > 0 && ptasks[j - 1]->T > Tperiod){
			ptasks[j] = ptasks[j - 1];
			j = j - 1;
		}
		ptasks[j] = curr;
	}
}

/*
 * System call that manages the scheduling policy.
 */

int task_create(task_t* tasks, size_t num_tasks){

	int error;

	error = schedulable(tasks, num_tasks);
	if (error != 0) return error;

	clear_tasks(); // clears the ptasks array
	sort_tasks(tasks, num_tasks);
	//if (assign_schedule(system_ptasks, num_tasks) != 1) {
	//	return -ESCHED;
	//}
	allocate_tasks(system_ptasks, num_tasks);
	dispatch_nosave();

	/* should never reach here */
	return 1;
}


int event_wait(unsigned int dev)
{
	if(dev > NUM_DEVICES - 1){
		return EINVAL;
	}
	dev_wait(dev);
	return 0;
}

/* An invalid syscall causes the kernel to exit. */
void invalid_syscall(unsigned int call_num)
{
	printf("Kernel panic: invalid syscall -- 0x%08x\n", call_num);

	disable_interrupts();
	while(1);
}
