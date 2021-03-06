/* 
 * Author: Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 * Date: Sat Nov  22 18:54:08 EDT 2013
 */

/** @file ctx_switch.c
 * 
 * @brief C wrappers around assembly context switch routines.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-21
 */
 

#include <types.h>
#include <assert.h>

#include <config.h>
#include <kernel.h>
#include "sched_i.h"

#ifdef DEBUG_MUTEX
#include <exports.h>
#endif
 
static tcb_t* cur_tcb; /* global */
extern void tcb_debug(tcb_t*);

/**
 * @brief Initialize the current TCB and priority.
 *
 * Set the initialization thread's priority to IDLE so that anything
 * will preempt it when dispatching the first task.
 */
void dispatch_init(tcb_t* idle)
{
	cur_tcb = idle;
}


/**
 * @brief Context switch to the highest priority task while saving off the 
 * current task state.
 *
 * This function needs to be externally synchronized.
 * We could be switching from the idle task.  The priority searcher has 
 * been tuned to return IDLE_PRIO for a completely empty run_queue case.
 *
 * When a task is done running, it is added back to the runqueue and considered
 * "ready to run" again. The next highest priority task is pulled off of the 
 * runqueue. Reasoning here is that only tasks waiting to be run belong in the 
 * runqueue.
 */


void dispatch_save(void)
{
	tcb_t* target_tcb;
	tcb_t* temp_cur_tcb;
	uint8_t next_task_prio;

	runqueue_add(cur_tcb, cur_tcb->cur_prio); 	//task is done add back to runq	
	next_task_prio = highest_prio();	 //grab next one to run
	if(cur_tcb->cur_prio == next_task_prio) {
		runqueue_remove(next_task_prio);
		return;
	}

	/* grab tcb of next task and remove from runqueue */
	target_tcb = runqueue_remove(next_task_prio);  

	temp_cur_tcb = cur_tcb;
	cur_tcb = target_tcb;	//update cur_tcb
	
	ctx_switch_full(&(target_tcb->context), &(temp_cur_tcb->context));
}

/**
 * @brief Context switch to the highest priority task that is not this task --
 * don't save the current task state.
 *
 * There is always an idle task to switch to.
 */
void dispatch_nosave(void)
{
	tcb_t* target_tcb;
	uint8_t next_task_prio;

	next_task_prio = highest_prio(); //grab next one to run

	/*grab tcb of next task and remove from runqueue*/
	target_tcb = runqueue_remove(next_task_prio);	
	
	cur_tcb = target_tcb;	//update cur_tcb

	ctx_switch_half(&(target_tcb->context));	
}


/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * and save the current task but don't mark is runnable.
 *
 * There is always an idle task to switch to.
 */

/* same as dispatch_save but does not add back to runequeue */
void dispatch_sleep(void)
{
	tcb_t* target_tcb;
	tcb_t* temp_cur_tcb;
	uint8_t next_task_prio;

	next_task_prio = highest_prio(); //grab next one to run

	/*grab tcb of next task and remove from runqueue*/
	target_tcb = runqueue_remove(next_task_prio);  

	temp_cur_tcb = get_cur_tcb();
	cur_tcb = target_tcb;	//update cur_tcb

	ctx_switch_full(&(target_tcb->context), &(temp_cur_tcb->context));
}

/** 
 * @brief Returns the priority value of the current task.
 */
uint8_t get_cur_prio(void)
{
	return cur_tcb->cur_prio;
}

/**
 * @brief Returns the TCB of the current task.
 */
tcb_t* get_cur_tcb(void)	
{
	return cur_tcb; 
}
