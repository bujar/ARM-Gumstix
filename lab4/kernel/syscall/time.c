/** @file time.c
 *
 * @brief Kernel timer based syscall implementations
 *
 * @author Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *		   Norman Wu <luow@andrew.cmu.edu>
 * @date   Mon Nov 18 11:53:20 EST 2013
 */

#include <types.h>
#include <config.h>
#include <bits/errno.h>
#include <arm/timer.h>
#include <syscall.h>

#define MS_PER_TICK 10

extern volatile unsigned long num_timer_tick;

unsigned long time_syscall(void)
{
	unsigned long msec = num_timer_tick * MS_PER_TICK;
	return msec;
}


/** @brief Waits in a tight loop for at least the given number of milliseconds.
 *
 * @param millis  The number of milliseconds to sleep.
 *
 * 
 */
void sleep_syscall(unsigned long millis )
{
	unsigned long target_time;
	unsigned long start_time;

	start_time = num_timer_tick;
	target_time = start_time + (millis/MS_PER_TICK); 
	while(num_timer_tick < target_time);
}
