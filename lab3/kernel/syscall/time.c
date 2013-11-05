/* time.c: Time system call
 *
 * Authors: Bujar Tagani <btagani@andrew.cmu.edu>
 *  	    Jonathan Lim <jlim2@andrew.cmu.edu>
 *	    	Norman Wu <luow@andrew.cmu.edu>
 * Date: Mon Nov  4 19:22:28 EST 2013
 */

#define MS_PER_TICK 10

extern volatile unsigned long num_timer_tick;

unsigned long time(void){
	unsigned long msec = num_timer_tick * MS_PER_TICK;
	return msec;
}
