/* write.c: Linux system call for "write"
 * Author: Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 * Date: Sat Nov  2 18:54:08 EDT 2013
 */

/*
* write syscall:
* 1. check the file descriptor 
* 2. check size of buf and address range of buf as well as NULL pointer
* 3. write characters from the buffer to stdout until the buffer is empty
* 4. return with the number of characters to stdout
*/

#include <bits/fileno.h>
#include <bits/errno.h>
#include <exports.h>

#define MAX_WRITE_SIZE  0x4000000	//64MB; size of SDRAM
#define FREE_BEGIN_ADDR 0xa0000000
#define FREE_END_ADDR 0xa3FFFFFF

ssize_t write(int fd, const void *buf, size_t count)
{
  unsigned int i;
  unsigned int buf_begin;
  unsigned int buf_end;

  if(fd != STDOUT_FILENO)
     {  
	puts("file descriptor error!");	
	return -EBADF;
     } // 1. check the file descriptor
  
  if(count > MAX_WRITE_SIZE)
     {
	puts("count size err!");
	return -EFAULT;	
     } // 2. check the size of buf and the address of buf

  buf_begin = (int) buf;		//low bound of buf
  buf_end = ((int) buf) + count;	//high bound of buf
  if((buf_begin < FREE_BEGIN_ADDR) || (buf_end > FREE_END_ADDR))
     {
	puts("buf address range error!");
	return -EFAULT;	
     } //check if the buffer exceeds the SDRAM
   
  for(i = 0; i < count; i++) 		 
     {
	putc(((char *)buf)[i]); 			
     }  // 3. write characters from buffer to stdout until buffer is empty
 			
  // 4. return with the number of characters to stdout
  return count;
}
