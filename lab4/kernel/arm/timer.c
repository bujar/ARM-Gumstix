/*
 * timer.c 	Sets up timer driver
 *
 * Author: Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu> 
 * Date:   Thu Nov  7 00:01:35 EST 2013
 */

#include <exports.h>
#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>

#include <device.h>

#define MS_PER_TICK 10
#define CLOCK_PER_TICK 32500
#define CLOCK_UPBOUND  195000000

volatile unsigned int num_timer_tick = 0;
volatile unsigned int num_timer_clock = 0;

/*function prototypes */
void timer_init(void);
void timer_inc(void);
	
/* in this function, we configure the OS timer register */
void timer_init(void)
{
    
    //calculate the clocks for a time unit: 10ms for now
    //Will change to the following line if set to 10ms
    //num_clock = OSTMR_FREQ/OS_TICKS_PER_SEC;
    num_timer_clock = CLOCK_PER_TICK;

    //init OSCR to 0
    reg_write(OSTMR_OSCR_ADDR, 0);
    
    //init OSMR0 to num_clock
    reg_write(OSTMR_OSMR_ADDR(0), num_timer_clock);

    /* 
     * set OIER last bit 1 to enbale match between OSCR 
     * and OSMR0 to assert OSSR[M0]
     */			
    reg_set(OSTMR_OIER_ADDR, OSTMR_OIER_E0);
}

//This function is called on all IRQ interrupts
void timer_inc(void)
{
    //add the clock counter
    num_timer_clock += CLOCK_PER_TICK;
    
    //set OSMR0 
    reg_write(OSTMR_OSMR_ADDR(0), num_timer_clock);
    	    
    //reset the OSSR[M0]bit
    reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);
    
    //reset the OSCR to 0
    //reg_write(OSTMR_OSCR_ADDR, 0);

    //increment the number of the timer ticks
    ++num_timer_tick;

	dev_update(num_timer_tick);
	
	/* Clcok cycle overflow handler, to avoid num_timer_clock 
	 *	exceed int range, reset timer after 6000 tick(1 mins)
	*/
	if(num_timer_clock >= CLOCK_UPBOUND)
	{
		timer_init();
		printf("clock reset\n");
	}
	/* Tick number overflow handler, when num_timer_tick 
	 * exceed int range, notify user, in about 50 days.
	*/
	if(num_timer_tick == 0)
		printf("system time reseted!\n");
}

