/**
 * @file mutex.c
 *
 * @brief Implements mutices.
 *
 * @author Harry Q Bovik < PUT YOUR NAMES HERE
 *
 * 
 * @date  
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
	}	
}

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
		while(p1->sleep_queue!=NULL)
		{
			p1 = p1->sleep_queue;
		}
		p1 = tcb;
		tcb->sleep_queue = NULL;
	}	
}

/* remove a task in mutex sleeping queue when a mutex is released */
void mutex_queue_remove(int mutex)
{
	mutex_t *mtx = &gtMutex[mutex];
	tcb_t *p1,*p2;
	p1 = mtx->pSleep_queue;
	if(mtx->pSleep_queue==NULL)
		return;
	else
	{
		if(p1->sleep_queue == NULL)
		{	
			runqueue_add(p1, p1->cur_prio);
			mtx->pSleep_queue = NULL;
		}else{
			p2 = p1;
			p1 = p1->sleep_queue;
			runqueue_add(p2, p2->cur_prio);	
		}
	}
}

int mutex_lock(int mutex  __attribute__((unused)))
{	
	tcb_t *cur_tcb;
	 
	/* check if the mutex number within the mutex area, and check if the mutex was created */
	if((mutex > OS_NUM_MUTEX) || (mutex < 0) || gtMutex[mutex].bAvailable)
	{	
		return -EINVAL;	
	}
	
	cur_tcb = get_cur_tcb();
	/* Check if the current task is already holding the lock */
	if(cur_tcb == gtMutex[mutex].pHolding_Tcb)
	{
		return -EDEADLOCK;
	}

	/*   */
	if(gtMutex[mutex].bLock == FALSE)
	{	
		gtMutex[mutex].bLock = TRUE;
		gtMutex[mutex].pHolding_Tcb =  cur_tcb;
		return 0;	
	}else{
		mutex_queue_add(mutex, cur_tcb);
		dispatch_sleep();
	}

	return 0;
}

int mutex_unlock(int mutex  __attribute__((unused)))
{
	tcb_t *cur_tcb;
	 
	/* check if the mutex number within the mutex area, and check if the mutex was created */
	if((mutex > OS_NUM_MUTEX) || (mutex < 0) || gtMutex[mutex].bAvailable)
	{	
		return -EINVAL;	
	}
	
	cur_tcb = get_cur_tcb();

	/* Check if the current task is already holding the lock */
	if(cur_tcb == gtMutex[mutex].pHolding_Tcb)
	{
		return -EPERM;
	}
	
	/* release mutex */
	gtMutex[mutex].bLock = FALSE;
	gtMutex[mutex].pHolding_Tcb = NULL;
	
	/* put the first task in mutex queue runnable */
	mutex_queue_remove(mutex);
		
	return 0;
}

