/*
 * kernel.c: Kernel main (entry) function
 *
 * Author: Group Member 1 <email address>
 *         Group Member 2 <email address>
 * Date:   The current time & date
 */

void C_SWI_Handler(unsigned swi_num, unsigned *regs)
{
	int r0;

	switch (swi_num) {
	case READ_SWI:

	case WRITE_SWI:

	case EXIT_SWI:

	default:

	}
	return r0;
}
