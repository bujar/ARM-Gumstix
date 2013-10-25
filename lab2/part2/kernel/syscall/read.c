#include <exports.h>
#include <bits/fileno.h>
#include <bits/errno.h>

ssize_t read (int fd, void *buf, size_t count)
{
	int c, bytes_read = 0;

    char *cbuf = (char *) buf;
	if (count > 0x4000000)
	return -EFAULT;

	if ( fd != STDIN_FILENO)
	return -EBADF;

	while(((c = getc()) != 4) && (bytes_read < count)) {	//EOT = 4
		if (c == 127) {		//ascii code for backspace
			bytes_read--;
			cbuf[bytes_read] = '\0'; 	//remove last char
			puts("\b \b");		//indicate backspace was pressed
	
		}

		else if (c == '\n' || '\r') {
			putc('\n');
			cbuf[bytes_read] = c;
            bytes_read++;
		    break;
        }
		
		else {
			putc(c);
			cbuf[bytes_read] = c;
			bytes_read++;
		}
	}

	cbuf[bytes_read] = 0;	//add null character

	return bytes_read;
}
