#include "../include/bits/errno.h"
#include "../include/bits/fileno.h"
#include "../../uboot/include/exports.h"
/*

#include <exports.h>
#include <bits/fileno.h>
#include <bits/errno.h>
*/

ssize_t read (int fd, void *buf, size_t count)
{
	int c, bytes_read = 0;

	if (count > 0x4000000)
	return -EFAULT;

	if ( fd != STDOUT_FILENO)
	return -EBADF;

	while(((c = getc()) != EOF) && (bytes_read < count)) {
		if (c == 127) {		//ascii code for backspace
			bytes_read--;
			buf[bytes_read] = '\0'; 	//remove last char
			puts('\b \b');		//indicate backspace was pressed
		}

		else if (c == '\n') {
			putc('\n');
			buf[bytes_read] = c;
		}
		
		else {
			putc(c);
			buf[bytes_read] = c;
			bytes_read++;
		}
	}

	buf[bytes_read] = 0;	//add null character

	return bytes_read;
}



int main()
{
char buf[50];
int buflen = 50;
read(1, buf, buflen);
}

