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

static tcb_t* cur_tcb; /* use this if needed */

/**
 * @brief Initialize the current TCB and priority.
 *
 * Set the initialization thread's priority to IDLE so that anything
 * will preempt it when dispatching the first task.
 */
void dispatch_init(tcb_t* idle __attribute__((unused)))
{
	
}


/**
 * @brief Context switch to the highest priority task while saving off the 
 * current task state.
 *
 * This function needs to be externally synchronized.
 * We could be switching from the idle task.  The priority searcher has been tuned
 * to return IDLE_PRIO for a completely empty run_queue case.
 */
void dispatch_save(void)
{
  tcb_t* target_tcb;
  tcb_t* temp_cur_tcb;
  uint8_t next_task_prio;

  next_task_prio = highest_prio();	//grab next one to run
  runqueue_add(cur_tcb, cur_tcb->cur_prio);	//task is done add back to runq	
  target_tcb = runqueue_remove(next_task_prio);  //grab tcb of next task and remove from runq
  temp_cur_tcb = cur_tcb;
  cur_tcb = target_tcb;	//current tcb(global) after context switch
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

  next_task_prio = highest_prio();	//grab next one to run
  target_tcb = runqueue_remove(next_task_prio);		//grab tcb of next task and remove from runq
  cur_tcb = target_tcb;	//current tcb(global) after context switch
  ctx_switch_half(&(target_tcb->context));	//pass context of tcb to cts_switch
}


/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * and save the current task but don't mark is runnable.
 *
 * There is always an idle task to switch to.
 */
void dispatch_sleep(void)
{
	
}

/**
 * @brief Returns the priority value of the current task.
 */
uint8_t get_cur_prio(void)	//don't really need this...only one line
{
	return cur_tcb->cur_prio; //fix this; dummy return to prevent compiler warning
}

/**
 * @brief Returns the TCB of the current task.
 */
tcb_t* get_cur_tcb(void)	//don't really need this...
{
	return cur_tcb; //fix this; dummy return to prevent compiler warning
}
