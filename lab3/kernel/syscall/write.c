/*
 * Author: Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 *  Date:  Oct 25. 2013
 */

/*
* write syscall:
* 1. check the file descriptor 
* 2. check the size of buf and the address range of buf as well as NULL pointer
* 3. write characters from the buffer to stdout until the buffer is empty
* 4. return with the number of characters to stdout
*/

#include <bits/fileno.h>
#include <bits/errno.h>
#include <exports.h>

#define MAX_WRITE_SIZE 0x4000000	//64MB; size of SDRAM

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
  if(count > MAX_WRITE_SIZE || count < 0)	//check size of buf 
     {
	puts("count size err!");
	return -EFAULT;	
     }

  buf_begin = (int) buf;		//low bound of buf
  buf_end = ((int) buf) + count;	//high bound of buf

  //check if the buffer exceeds the SDRAM, it automaticlly ignores NULL pointer
  if((buf_begin < 0xa0000000) || (buf_end > 0xa3ffffff))
     {
	puts("buf address range error!");
	return -EFAULT;	
     }
  

  // 3. write characters from the buffer to stdout until the buffer is empty
  for(i = 0; i < count; i++) 		 
     {
	putc(((char *)buf)[i]); 			
     }
				
  // 4. return with the number of characters to stdout
  return count;
}

	

