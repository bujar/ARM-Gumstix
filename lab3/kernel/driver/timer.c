#include<exports.h>
#include<types.h>
#include<arm/timer.h>
#include<arm/reg.h>

volatile size_t num_timer_tick;

void timer_init(void);
	
void timer_inc(void);
	
/* in this function, we configure the OS timer register */
void timer_init(void)
{
    //init OSCR to 0
    reg_write(OSTMR_OSCR_ADDR, 0);
    
    //init OSMR0 to 0
    reg_write(OSTMR_OSMR_ADDR(0), 0);
    			
}

void timer_inc(void)
{
    //increment the number of the timer ticks
    ++num_timer_tick;
    //reset the OSMR0 to 0
    reg_write(OSTMR_OSMR_ADDR(0), 0);
}

