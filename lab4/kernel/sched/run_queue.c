/* 
 * Author: Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 * Date: Sat Nov  22 18:54:08 EDT 2013
 */

/** @file run_queue.c
 * 
 * @brief Run queue maintainence routines.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-21
 */

#include <types.h>
#include <assert.h>

#include <kernel.h>
#include <sched.h>
#include "sched_i.h"

#define NULL 0

static tcb_t* run_list[OS_MAX_TASKS];

/* A high bit in this bitmap means that the task whose priority is
 * equal to the bit number of the high bit is runnable.
 */
static uint8_t run_bits[OS_MAX_TASKS/8];

/* This is a trie structure.  Tasks are grouped in groups of 8.  If any task
 * in a particular group is runnable, the corresponding group flag is set.
 * Since we can only have 64 possible tasks, a single byte can represent the
 * run bits of all 8 groups.
 */
static uint8_t group_run_bits;

/* This unmap table finds the bit position of the lowest bit in a given byte
 * Useful for doing reverse lookup.
 */
static uint8_t prio_unmap_table[] =
{

0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

// prints the runqueue numerically
void printit();

/**
 * @brief Clears the run-queues and sets them all to empty.
 */
void runqueue_init(void)
{
	int count;
	group_run_bits = 0;
	for(count = 0; count < OS_MAX_TASKS/8; ++count)
		run_bits[count] = 0;
	for(count = 0; count < OS_MAX_TASKS; ++count)
	{
		run_list[count] = NULL;
	}
		
}

/**
 * @brief Adds the thread identified by the given TCB to the runqueue at
 * a given priority.
 *
 * The native priority of the thread need not be the specified priority.  The
 * only requirement is that the run queue for that priority is empty.  This
 * function needs to be externally synchronized.
 */
void runqueue_add(tcb_t* tcb, uint8_t prio)
{
	uint8_t OSTCBX, OSTCBY;
	OSTCBX = prio & 0x7; // compute task pos.
	OSTCBY = prio >> 3;  // compute prio group

	/* set group_run_bits */
	group_run_bits |= 1 << OSTCBY;

	/* set run_bits */
	run_bits[OSTCBY] |= 1 << OSTCBX;

	/* add tcb to be runnable */
	run_list[prio] = tcb;
//	printit();
}


/**
 * @brief Empty the run queue of the given priority.
 *
 * @return  The tcb at enqueued at the given priority.
 *
 * This function needs to be externally synchronized.
 */
tcb_t* runqueue_remove(uint8_t prio)
{	
	int OSTCBX, OSTCBY;
	tcb_t *tmp_tcb = run_list[prio];
	
	/* remove the tcb from run_list */
	run_list[prio] = NULL;
		
	OSTCBX = prio & 0x7;	// compute priority group 
	OSTCBY = prio >> 3;     // compute task position in group

	/* reset run_bits */
	run_bits[OSTCBY] &= ~(1 << OSTCBX);
	
	/* reset group_run_bits if run_bits[OSTCBY] is 0 */	
	if(0 == run_bits[OSTCBY])
		group_run_bits &= ~(1 << OSTCBY);
	return tmp_tcb;
}

/**
 * @brief This function examines the run bits and the run queue and returns the
 * priority of the runnable task with the highest priority (lower number).
 */
uint8_t highest_prio(void)
{
	uint8_t x, y, prio;
	
	y = prio_unmap_table[group_run_bits];
	x = prio_unmap_table[run_bits[y]];
	prio = (y << 3) + x;
	return prio; 
}

void printit(){
	int i;
	printf("grouprunbits=%u\n", group_run_bits);
	for(i = 0; i < 8; i++ )
		printf("run_bits[%d]=%u\t", i, run_bits[i]);
	printf("\n\n");
}
