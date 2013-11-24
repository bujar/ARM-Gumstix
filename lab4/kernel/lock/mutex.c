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

void mutex_queue_add(int mutex, tcb_t *tcb)
{
	
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
	}
	

	return 1; // fix this to return the correct value
}

int mutex_unlock(int mutex  __attribute__((unused)))
{
	return 1; // fix this to return the correct value
}

