/*
 * @file timer.c      
 * @brief sets up timer driver
 *
 * @author Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 * @date   Thu Nov  7 00:01:35 EST 2013
 */

#include <exports.h>
#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include <device.h>
#define S_TO_MS 1000
#define MS_PER_TICK 10
#define CLOCKS_PER_TICK 32500

volatile unsigned int num_timer_tick;
volatile unsigned int osmr_count;

/*function prototypes */
void timer_init(void);
void timer_inc(void);

/* in this function, we configure the OS timer register */
void timer_init(void)
{
	osmr_count = CLOCKS_PER_TICK;
	
	// init OSCR to 0
	reg_write(OSTMR_OSCR_ADDR, 0);

	// init OSMR0 to num_clock
	reg_write(OSTMR_OSMR_ADDR(0), osmr_count);

	/*
	 * set OIER last bit 1 to enbale match between OSCR
	 * and OSMR0 to assert OSSR[M0]
	 */
	reg_set(OSTMR_OIER_ADDR, OSTMR_OIER_E0);
}

// This function is called on all IRQ interrupts
void timer_inc(void)
{
  	uint32_t ossr;
	
	/* increment the number of the timer ticks */
	++num_timer_tick;

	/* add clocks to OSMR */
	osmr_count += CLOCKS_PER_TICK;
	reg_write(OSTMR_OSMR_ADDR(0), osmr_count);
	
	/* acknowledge interupt and set OSSR */
	ossr = reg_read(OSTMR_OSSR_ADDR);
	ossr |= OSTMR_OSSR_M0;
	reg_write(OSTMR_OSSR_ADDR, ossr);

	/* wake up any tasks waiting on devices */
	dev_update(num_timer_tick * MS_PER_TICK);
}

