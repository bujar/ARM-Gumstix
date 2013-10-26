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
		
	for(bytes_read = 0; ((c=getc()) != 4) && (bytes_read<count); bytes_read++)
	{
		switch (c)
		{
		case '\n':
		case '\r':
			putc('\n');
			cbuf[bytes_read] = c;
			bytes_read++;
			//printf("%d",bytes_read);
			return bytes_read;
			break;
		case 127:
			bytes_read-=2;
			cbuf[bytes_read] = '\0';
			puts("\b \b");
		default:
			putc(c);
			cbuf[bytes_read] = c;
		}
	}
//	printf("%d",bytes_read);
	cbuf[bytes_read+1] = 0;
	return bytes_read;
}
