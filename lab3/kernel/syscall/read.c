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

ssize_t read (int fd, void *buf, size_t count)
{
	char c;
	ssize_t bytes_read;
	char *cbuf = (char *)buf;
	
	if (count > 0x4000000)
	return -EFAULT;

	if (fd != STDIN_FILENO)
	return -EBADF;
		
	/* This will get user input with getc and keep looping to get characters
	 * until user input is EOT or newline/return. c=getc() stores input into
	 * char c.
	 */
	for(bytes_read = 0; ((c=getc()) != 4) && (bytes_read<count); bytes_read++)
	{
		switch (c)
		{
		case '\n':		//Newline and Return case
		case '\r':
			putc('\n');
			cbuf[bytes_read] = c;
			bytes_read++;
			//printf("I read %d characters\n\n",bytes_read);
			return bytes_read;
			break;

		case 127:		//Backspace and Delete case
			if (bytes_read>0)	
			bytes_read-=2;			// -2 because when we loop again, bytes_read++
			cbuf[bytes_read+1] = '\0';	//putting null char at the end of buffer
			putc('\b');
			putc(' ');
			putc('\b');
			break;

		default:				//default case - keep looping and reading characters
			putc(c);
			cbuf[bytes_read] = c;
		}
	}
    		//printf("I read %d characters\n\n",bytes_read);
		cbuf[bytes_read+1] = '\0';
		return bytes_read;			//only reach this when c = EOT
}
