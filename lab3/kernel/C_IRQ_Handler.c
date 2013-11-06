/* C_IRQ_Handler.c: Handles timer IRQ
 *
 *
 */

#include <bits/swi.h>
#include <exports.h>
#include "syscall.h"

extern void timer_inc(void);

void C_IRQ_Handler (void)
{
	timer_inc();
}
