#include <bits/errno.h>
#include <bits/fileno.h>

ssize_t read (int fd, const void *buf, size_t count)
{
	int c, bytes_read = 0;

	if (count > 0x3ffffff)
	return -EFAULT;

	if ( fd != STDOUT_FILENO 1)
	return -EBADF;

	while(((c = getc()) != EOT) && (bytes_read < count)) {
		if (c == '\b') {
			bytes_read--;
			buf(bytes_read) = '\0';
			puts('\b');
		}

		else if (c == '\n') {
			puts('\n');
			buf(bytes_read) = c;
		}
		
		else {
			buf[bytes_read] = c;
			bytes_read++;
		}
	}

	buf[bytes_read] = 0;	//add null character

	printf("Total Bytes Read: %d\n", bytes_read);
	return buf;
}
