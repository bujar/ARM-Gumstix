#include <exports.h>
#include <bits/fileno.h>
#include <bits/errno.h>

ssize_t read (int fd, void *buf, size_t count)
{
	int c, bytes_read = 0;

	if (count > 0x4000000)
	return -EFAULT;

	if ( fd != STDOUT_FILENO)
	return -EBADF;

	while(((c = getc()) != 4) && (bytes_read < count)) {	//EOT = 4
		if (c == 127) {		//ascii code for backspace
			bytes_read--;
			buf[bytes_read] = '\0'; 	//remove last char
			puts('\b \b');		//indicate backspace was pressed
	
		}

		else if (c == '\n' || '\r') {
			putc('\n');
			buf[bytes_read] = c;
			return bytes_read;
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
