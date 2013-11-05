/* sleep.c: Sleep system call
 *
 * Authors: Bujar Tagani <btagani@andrew.cmu.edu>
 *  	    Jonathan Lim <jlim2@andrew.cmu.edu>
 * 			Norman Wu <luow@andrew.cmu.edu>
 * Date: Sat Nov  2 19:03:43 EDT 2013
 */

#define MS_PER_TICK 10

extern unsigned long num_timer_tick;

void sleep(unsigned long ms){
	unsigned long currTime = num_timer_tick * MS_PER_TICK;
	while(( (num_timer_tick * MS_PER_TICK) - currTime) < ms);
}
