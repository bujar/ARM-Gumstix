#include <exports.h>
#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>

#define S_TO_MS 1000
#define MS_PER_TICK 10

volatile unsigned int num_timer_tick;

/*function prototypes */
void timer_init(void);
void timer_inc(void);
	
/* in this function, we configure the OS timer register */
void timer_init(void)
{
    size_t num_clock;
    
    //calculate the clocks for a time unit: 10ms for now
    //Will change to the following line if set to 10ms
    //num_clock = OSTMR_FREQ/OS_TICKS_PER_SEC;
    num_clock = OSTMR_FREQ/(S_TO_MS/MS_PER_TICK);

    //init OSCR to 0
    reg_write(OSTMR_OSCR_ADDR, 0);
    
    //init OSMR0 to num_clock
    reg_write(OSTMR_OSMR_ADDR(0), num_clock);

    /* 
     * set OIER last bit 1 to enbale match between OSCR 
     * and OSMR0 to assert OSSR[M0]
     */			
    reg_set(OSTMR_OIER_ADDR, OSTMR_OIER_E0);
}

void timer_inc(void)
{
    //increment the number of the timer ticks
    ++num_timer_tick;
    
    //reset the OSSR[M0]bit
    reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);
    
    //reset the OSCR to 0
    reg_write(OSTMR_OSCR_ADDR, 0);
}

