/* @file C_IRQ_Handler.c: Handles timer IRQ
 * 
 * @author Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu> 
 * @date Thu Nov  7 00:02:30 EST 2013
 */

#include <bits/swi.h>
#include <exports.h>
#include "syscall.h"

extern void timer_inc(void);

void C_IRQ_Handler (void)
{
	timer_inc();
}
