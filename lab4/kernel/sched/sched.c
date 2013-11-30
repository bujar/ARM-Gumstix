/* 
 * Author: Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 * Date: Sat Nov  22 18:54:08 EDT 2013
 */

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
#include <device.h>

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>

#define FIRST_MAIN_PRIO 0 /*unique number < IDLE_PRIO*/

tcb_t system_tcb[OS_MAX_TASKS]; /*allocate memory for system TCBs */

/* stack for idle, should we align by 8? */
uint32_t idle_kstack[OS_KSTACK_SIZE/sizeof(uint32_t)];
uint32_t idle_kstack_high[0];

/* static functions for sched.c */
static void tcb_init(task_t* task, tcb_t* tcb, uint8_t prio);
static void idle_init(void);


/**
 * @brief This is the idle task that the system runs when no other 
 * task is runnable
 */
 
static void idle(void)
{
	 enable_interrupts();
	 while(1);
}


/**
 * @brief This function initializes the idle TCB and makes it runnable
 */
static void idle_init(void){
	task_t idle_task;
	idle_task.lambda = (void *) idle;
	idle_task.data = 0;
	idle_task.C = 0;
	idle_task.T = 0; 
	idle_task.stack_pos = (void *) idle_kstack_high;
	tcb_init(&idle_task, &system_tcb[IDLE_PRIO], IDLE_PRIO);
	runqueue_add(&system_tcb[IDLE_PRIO], IDLE_PRIO);
}

/**
 * @brief This function is to init tcb
 * @use task to init tcb's context part
 */
 
static void tcb_init(task_t* task, tcb_t* tcb, uint8_t prio)
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
	
	ctx->lr = (void*)launch_task;
	ctx->sp = tcb->kstack_high;
	
	tcb->holds_lock = 0;
	tcb->sleep_queue = 0;
}

/**
 * @brief Creates the main user program as a main task
 * and sets it to run.
 *
 * This function is only called when the user program is
 * first run.
 *
 */
void sched_init(task_t* main_task)
{
	main_task->lambda =    (void *)0xa0000000;
	main_task->data = 0;
	main_task->stack_pos = (void *)0xa3000000;
	main_task->C = 1;
	main_task->T = 1; 
	tcb_init(main_task, &system_tcb[FIRST_MAIN_PRIO], FIRST_MAIN_PRIO);
//	printf("sched_init\n");
	runqueue_add(&system_tcb[FIRST_MAIN_PRIO], FIRST_MAIN_PRIO);
	dispatch_init(&system_tcb[FIRST_MAIN_PRIO]);
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
void allocate_tasks(task_t** tasks, size_t num_tasks)
{
	//set up system tcb for each task in 'tasks' - loop through each task
	uint8_t i;
	runqueue_init();
	dev_init();
	for(i = 0; i < num_tasks; i++)
	{
		tcb_init(tasks[i], &system_tcb[i], i);
//		printf("allocate_tasks:%d\n",i);
		runqueue_add(&system_tcb[i], i);
	}

	/* add the idle task */
	idle_init();
}

void tcb_debug( tcb_t *target_tcb){
	printf("=================TCB DEBUG\n");
	printf("Native Prio:%d\n",target_tcb->native_prio);
	printf("Current Prio:%d\n",target_tcb->cur_prio);
	printf("r4:%x(%d)\n",target_tcb->context.r4, target_tcb->context.r4);
	printf("r5:%x(%d)\n",target_tcb->context.r5, target_tcb->context.r5);
	printf("r6:%x(%d)\n",target_tcb->context.r6, target_tcb->context.r6);
	printf("r7:%x(%d)\n",target_tcb->context.r7, target_tcb->context.r7);
	printf("r8:%x(%d)\n",target_tcb->context.r8, target_tcb->context.r8);
	printf("r9:%x(%d)\n",target_tcb->context.r9, target_tcb->context.r9);
	printf("r10:%x(%d)\n",target_tcb->context.r10, target_tcb->context.r10);
	printf("r11:%x(%d)\n",target_tcb->context.r11, target_tcb->context.r11);
	printf("sp:%p\n",target_tcb->context.sp);
	printf("lr:%p\n",target_tcb->context.lr);
}

