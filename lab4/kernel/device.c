/**
 * @file device.c
 *
 * @brief Implements simulated devices.
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-12-01
 *
 * @author Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 * @date: Sat Nov  22 18:54:08 EDT 2013
 */

#include <types.h>
#include <assert.h>

#include <task.h>
#include <sched.h>
#include <device.h>
#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <syscall.h>
#define NULL 0

/**
 * @brief Fake device maintainence structure.
 * Since our tasks are periodic, we can represent 
 * tasks with logical devices. 
 * These logical devices should be signalled periodically 
 * so that you can instantiate a new job every time period.
 * Devices are signaled by calling dev_update 
 * on every timer interrupt. In dev_update check if it is 
 * time to create a tasks new job. If so, make the task runnable.
 * There is a wait queue for every device which contains the tcbs of
 * all tasks waiting on the device event to occur.
 */

struct dev
{
	tcb_t* sleep_queue;
	unsigned long   next_match;
};
typedef struct dev dev_t;

/* devices will be periodically signaled at the following frequencies */
const unsigned long dev_freq[NUM_DEVICES] = {100, 200, 500, 50};
static dev_t devices[NUM_DEVICES];

void sleepqueue_wake(unsigned int dev);

/**
 * @brief Initialize the sleep queues and match values for all devices.
 */
void dev_init(void)
{
	int i;
	for(i = NUM_DEVICES - 1; i >= 0; i--){
		devices[i].next_match = dev_freq[i];
		devices[i].sleep_queue = NULL; //may not be needed
	}
}


/**
 * @brief Puts a task to sleep on the sleep queue until the next
 * event is signalled for the device.
 *
 * @param dev  Device number.
 */
void dev_wait(unsigned int dev)
{

	disable_interrupts();
	/* save new sleep task at front of queue */
	tcb_t *front = devices[dev].sleep_queue;
	if(front == NULL){ 
		/* assign a head of the queue */
		devices[dev].sleep_queue = get_cur_tcb();
	}
	else{
		/* add to front of queue, changing head */
		get_cur_tcb()->sleep_queue = front;
		devices[dev].sleep_queue = get_cur_tcb();
	}

	/* dispatch runnable task with highest priority
     * (not this one because it is sleeping) 
     */
	dispatch_sleep(); 
	enable_interrupts();
}


/**
 * @brief Signals the occurrence of an event on all applicable devices. 
 * This function should be called on timer interrupts to determine that 
 * the interrupt corresponds to the event frequency of a device. If the 
 * interrupt corresponded to the interrupt frequency of a device, this 
 * function should ensure that the task is made ready to run 
 */
void dev_update(unsigned long millis)
{
	disable_interrupts();
	int i;
	for(i = NUM_DEVICES - 1; i >= 0; i--){
		dev_t *dev = &devices[i];
		
		/* wake up all TCBs waiting on devices that fire off */
		if(dev->sleep_queue && (dev->next_match != 0) && 
							(millis % dev->next_match == 0)){
			sleepqueue_wake(i);
		}
	}
	dispatch_save();
	enable_interrupts();
}

/** 
 * @brief Removes all TCBs waiting on dev's sleep queue and adds
 * them to the runqueue, ensuring that the tasks are made runnable
 */
void sleepqueue_wake(unsigned int dev){
	tcb_t *curr = devices[dev].sleep_queue;
	tcb_t *next = curr;

	/* set device's sleep_queue as empty */
	devices[dev].sleep_queue = NULL;

	/* remove and set each TCB as runnable */ 
	while(curr != NULL){
		next = next->sleep_queue;
		runqueue_add(curr, curr->cur_prio); 
		curr->sleep_queue = NULL;
		curr = next;
	}

}
		
		






