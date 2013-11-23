/** @file sched.c
 * 
 * @brief Top level implementation of the scheduler.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-20
 */

#include <types.h>
#include <assert.h>

#include <kernel.h>
#include <config.h>
#include "sched_i.h"

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>

tcb_t system_tcb[OS_MAX_TASKS]; /*allocate memory for system TCBs */

/**
 * @brief This is the idle task that the system runs when no other task is runnable
 */
 
static void __attribute__((unused)) idle(void)
{
	 enable_interrupts();
	 while(1);
}

/**
 * @brief This function is to init tcb
 * @use task to init tcb's context part
 */
 
void tcb_init(task_t* task, tcb_t* tcb, uint8_t prio)
{
	sched_context_t *ctx = &(tcb->context);

	tcb->native_prio = prio;
	tcb->cur_prio = prio;

	/* init context part, ????  */
	ctx->r4 = (uint32_t)task->lambda;
	ctx->r5 = (uint32_t)task->data; 
	ctx->r6 = (uint32_t)task->stack_pos;
	ctx->r7 = (uint32_t)task->C;
	ctx->r8 = (uint32_t)task->T;
	
	ctx->lr =  launch_task;
	ctx->sp = tcb->kstack_high[0];

	tcb->holds_lock = 0;
	tcb->sleep_queue = 0;
	//tcb->
}

void sched_init(task_t* main_task  __attribute__((unused)))
{
	// since global, system_tcb is all zeroed out.
	// however, we may need to use this for other purposes  
	// define of task_t is in include/task.h
	main_task->lambda = (task_fun_t) idle;		
//how to init the context?	
	main_task->data = 0;
//where to put the idle stack;
	main_task->stack_pos = 0;
	main_task->C = 0;
	main_task->T = 0; 
	tcb_init(main_task, &system_tcb[IDLE_PRIO], IDLE_PRIO);
	runqueue_add(&system_tcb[IDLE_PRIO], IDLE_PRIO);
}


/**
 * @brief Allocate user-stacks and initializes the kernel contexts of the
 * given threads.
 *
 * This function assumes that:
 * - num_tasks < number of tasks allowed on the system.
 * - the tasks have already been deemed schedulable and have been appropriately
 *   scheduled.  In particular, this means that the task list is sorted in order
 *   of priority -- higher priority tasks come first.
 *
 * @param tasks  A list of scheduled task descriptors.
 * @param size   The number of tasks is the list.
 */
void allocate_tasks(task_t** tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
	//set up system tcb for each task in 'tasks' - loop through each task
	uint8_t i;
	// changed i >= 0 to i > 0; since uint8_t is unsigned char, is always >= 0; could also change the uint8_t i to int8_t;
	for(i = num_tasks ; i > 0; i--){
		system_tcb[i - 1].native_prio = i - 1;
		system_tcb[i - 1].cur_prio = i - 1;
		//do we need to check the arguments to store for sched_context?	
	}	
}

