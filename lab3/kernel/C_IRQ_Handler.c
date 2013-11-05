/* C_IRQ_Handler.c: Handles timer IRQ
 *
 *
 */

#include <bits/swi.h>
#include <exports.h>
#include "syscall.h"

void C_IRQ_Handler (void)
{
	time_inc();
	//timer stuff - will come back to this
}
