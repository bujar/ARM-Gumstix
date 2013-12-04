/**
 * @file mutex.c
 *
 * @brief Implements mutexes.
 *
 * @author Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 *
 * @date:  Sat Nov  22 18:54:08 EDT 2013
 */

//#define DEBUG_MUTEX

#include <lock.h>
#include <task.h>
#include <sched.h>
#include <bits/errno.h>
#include <arm/psr.h>
#include <arm/exception.h>

#ifdef DEBUG_MUTEX
#include <exports.h> // temp
#endif

#define NULL 0

mutex_t gtMutex[OS_NUM_MUTEX];

void mutex_init()
{
	uint32_t i = 0;
	for(i = 0; i < OS_NUM_MUTEX; i++)
	{
		gtMutex[i].bAvailable = TRUE;
		gtMutex[i].pHolding_Tcb = NULL;
		gtMutex[i].bLock = FALSE;
		gtMutex[i].pSleep_queue = NULL;
		gtMutex[i].mprio = IDLE_PRIO;
	}	
}

/*
 *This function returns a unique identifier to a mutex object that the 
 *kernel has created. If the kernel is out of identifiers, it returns an error.
 *All valid ids are positive integers. The returned ids start at zero and 
 *monotonically increase by one for every successful subsequent call. This 
 *function should return successfully for at least 32 invocation.
*/

int mutex_create(void)
{
	uint32_t i = 0;
	for(i = 0; i < OS_NUM_MUTEX; i++)
	{
		if(gtMutex[i].bAvailable == TRUE)
		{	
			gtMutex[i].bAvailable  = FALSE;
			return i;
		}
	}	
	return -ENOMEM; 
}

/* add a task in mutex sleeping queue when mutex is busy */
void mutex_queue_add(int mutex, tcb_t *tcb)
{
	mutex_t *mtx = &gtMutex[mutex];
	tcb_t *p1;

	if(mtx->pSleep_queue==NULL)
	{
		mtx->pSleep_queue = tcb;
		tcb->sleep_queue = NULL;
	}
	else
	{
		p1 = mtx->pSleep_queue;

		/* find the last TCB in the sleep queue */
		while(p1->sleep_queue!=NULL)
		{
			p1 = p1->sleep_queue;
		}

		/* add this tcb to the end of sleep queue */
		p1->sleep_queue = tcb;
		tcb->sleep_queue = NULL;
	}
}

/* remove the first task in mutex sleeping queue
 * when a mutex is released, giving the lock to this 
 * task. 
 */
void mutex_queue_remove(int mutex)
{
	mutex_t *mtx = &gtMutex[mutex];
	tcb_t *p1,*p2;
	p1 = mtx->pSleep_queue;

	if(mtx->pSleep_queue == NULL)
		return;
	else
	{
		/* if mutex sleep queue only has one TCB*/
		if(p1->sleep_queue == NULL)
		{	
			/* give the first TCB on the queue the lock */
			gtMutex[mutex].bLock = TRUE;
			gtMutex[mutex].pHolding_Tcb = p1;
			p1->cur_prio = 0;
			/* make the task runnable */
			runqueue_add(p1, p1->cur_prio);
			mtx->pSleep_queue = NULL;

		/* more than one TCB in mutex sleeping queue */
		}else{
			
			p2 = p1;
			/* give the first TCB on the queue the lock */
			gtMutex[mutex].bLock = TRUE;
			gtMutex[mutex].pHolding_Tcb = p2;
			p2->cur_prio = 0;
			p1 = p1->sleep_queue;
			p2->sleep_queue = NULL;
			mtx->pSleep_queue = p1;

			/* make the task runnable */
			runqueue_add(p2, p2->cur_prio);	
		}
	}
}

int mutex_lock(int mutex)
{	
	tcb_t *cur_tcb;
	
	disable_interrupts(); 
	/* check if the mutex number within the mutex area
     * and check if the mutex was created */

	if((mutex >= OS_NUM_MUTEX) || (mutex < 0) || gtMutex[mutex].bAvailable)
	{	
		return -EINVAL;	
	}
	
	cur_tcb = get_cur_tcb();

	/* Check if the current task is already holding the lock */
	if(cur_tcb == gtMutex[mutex].pHolding_Tcb)
	{
		return -EDEADLOCK;
	}

	/* trying to obtain an unavailable lock */
	if(gtMutex[mutex].bLock == TRUE)
	{
		mutex_queue_add(mutex, cur_tcb);
		dispatch_sleep();
	}
	else{ /* mutex is available to grab */
		gtMutex[mutex].bLock = TRUE;
		gtMutex[mutex].pHolding_Tcb =  cur_tcb;
		cur_tcb->cur_prio = 0;
	}

	enable_interrupts(); 
	return 0;
}

int mutex_unlock(int mutex)
{
	tcb_t *cur_tcb;
	 
	disable_interrupts(); 
	
	/* check if the mutex number within the mutex area
     * and check if the mutex was created */
	if((mutex >= OS_NUM_MUTEX) || (mutex < 0) || gtMutex[mutex].bAvailable)
	{	
		return -EINVAL;	
	}
	
	cur_tcb = get_cur_tcb();

	/* Check if the current task is holding the lock */
	if(cur_tcb != gtMutex[mutex].pHolding_Tcb)
	{
		return -EPERM;
	}
	
	/* release mutex */
	gtMutex[mutex].bLock = FALSE;
	gtMutex[mutex].pHolding_Tcb->cur_prio = gtMutex[mutex].pHolding_Tcb->native_prio;
	gtMutex[mutex].pHolding_Tcb = NULL;
	
	/* put the first task in mutex queue runnable */
	/*    and give this first task the lock */
	mutex_queue_remove(mutex);
	dispatch_save();
	enable_interrupts(); 
		
	return 0;
}

