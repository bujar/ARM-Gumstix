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
	
	return 1; // fix this to return the correct value
}

int mutex_lock(int mutex  __attribute__((unused)))
{

	return 1; // fix this to return the correct value
}

int mutex_unlock(int mutex  __attribute__((unused)))
{
	return 1; // fix this to return the correct value
}

