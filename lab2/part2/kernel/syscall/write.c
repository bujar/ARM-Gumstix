/*
* write syscall:
* 1. check the file descriptor 
* 2. check the size of buf and the address of buf
* 3. write characters from the buffer to stdout until the buffer is empty
* 4. return with the number of characters to stdout
*/

#include "../../uboot/include/bits/types.h"
#include "../include/bits/fileno.h"
#include "../include/bits/errno.h"
#define MAX_WRITE_SIZE 0x4000000

ssize_t write(int fd, const void *buf, size_t count)
{
  int i, buf_begin, buf_end;

  // 1. check the file descriptor 
  if(fd != STDOUT_FILENO)  	//the file descriptor for stdout of uboot is 1
     {  
	puts("file descriptor error!");	
	return -EBADF;
     }
 
  // 2. check the size of buf and the address of buf
  if(count > MAX_WRITE_SIZE)
     {
	puts("buf too large!");
	return -EFAULT;	
     }

  buf_begin = (int) buf;	//determine the range of the buf and check
  buf_end = ((int) buf) + count;
  if((buf_begin < 0xa0000000) || (buf_end > 0xa3ffffff))
     {
	puts("out of write address range!");
	return -EFAULT;	
     }
	
  // 3. write characters from the buffer to stdout until the buffer is empty
  /*for(i = count; i > 0; i--) 	//use count down to save clock cycles 
     {
	puts(buf);		//trying to use putc
	buf++;	
     }
*/				
	puts(buf);	
	  
  // 4. return with the number of characters to stdout
  return count;
}

