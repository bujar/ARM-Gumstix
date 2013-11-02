/* C_SWI_Handler.c: Handles all SWI
 *
 * Authors: Bujar Tagani <btagani@andrew.cmu.edu>
 *  	    Jonathan Lim <jlim2@andrew.cmu.edu>
 *	    Norman Wu <luow@andrew.cmu.edu>
 * Date	    Oct 26, 2013
 */

#include <exports.h>
#include <bits/fileno.h>
#include <bits/errno.h>

#define SDRAM_END 0xa3ffffff
#define SDRAM_START 0xa0000000

ssize_t read (int fd, void *buf, size_t count)
{
	char c;
	ssize_t b_read;
	char *cbuf = (char *)buf;
	unsigned int buf_begin, buf_end;
	
	buf_begin = (unsigned int) buf;
	buf_end = ((unsigned int) buf) + count;

	if (buf_begin < SDRAM_START || buf_end > SDRAM_END)
	return -EFAULT;

	if (fd != STDIN_FILENO)
	return -EBADF;
		
	/* This will get user input with getc and keep looping to get characters
	 * until user input is EOT or newline/return. c=getc() stores input into
	 * char c.
	 */
	for(b_read = 0; ((c=getc()) != 4) && ((size_t) b_read<count); b_read++)
	{	
		switch (c)
		{
		   case '\n':
		   case '\r':
		   {
		       putc('\n');
			   cbuf[b_read] = c;
			   b_read++;
			   return b_read;
		   }	// return/newline case
		   case 127:
		   {
		       if (b_read>0)	
		           b_read-=2;
		       putc('\b');
		       putc(' ');
		       putc('\b');
		       break;
		   }	// backspace/delete case
			
		   default:
		   {
			putc(c);
			cbuf[b_read] = c;
		   }	//default keeps looping until EOT
		}
    }

	return b_read;	//only reach this when c = EOT
}
