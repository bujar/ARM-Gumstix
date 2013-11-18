/** @file io.c
 *
 * @brief Kernel I/O syscall implementations
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 14 Oct 2007 00:07:38 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-16
 * 
 * @author Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 * @date   Mon Nov 18 11:40:24 EST 2013
 */

#include <types.h>
#include <bits/errno.h>
#include <bits/fileno.h>
#include <arm/physmem.h>
#include <syscall.h>
#include <exports.h>
#include <kernel.h>

#define EOT_CHAR 0x04
#define DEL_CHAR 0x7f
#define SDRAM_END 0xa3ffffff
#define SDRAM_START 0xa0000000
#define MAX_WRITE_SIZE  0x4000000 //64MB; size of SDRAM

/* Read count bytes (or less) from fd into the buffer buf. */
ssize_t read_syscall(int fd __attribute__((unused)), void *buf __attribute__((unused)), size_t count __attribute__((unused)))
{
	char c;
	ssize_t b_read = 0;
	char *cbuf = (char *)buf;
	unsigned int buf_begin;
	unsigned int buf_end;

	buf_begin = (unsigned int) buf;
	buf_end = ((unsigned int) buf) + count;

	if (buf_begin < SDRAM_START || buf_end > SDRAM_END) {
		return -EFAULT;
  	}

	if (fd != STDIN_FILENO) {
		return -EBADF;
	}

	/* This will get user input with getc and keep looping to get characters
	 * until user input is EOT or newline/return. c=getc() stores input into
	 * char c.
	 */

	for(; ((c=getc()) != EOT_CHAR) && ((size_t) b_read<count); b_read++){
		switch (c){
			case '\n':
			case '\r':
			{
            	putc('\n');
            	cbuf[b_read] = c;
            	b_read++;
            	return b_read;
         	}  // prints '\n' to stdout and returns to user program

         	case DEL_CHAR:
         	{
            	if (b_read>0){
                	b_read-=2;
               		putc('\b');
                	putc(' ');
                	putc('\b');
            	}
            	else{
                	b_read--; //balance
            	}
            	break;
         	}//prints '\b' char to stdout

         	default:
         	{
            	putc(c);
            	cbuf[b_read] = c;
         	}  //default keeps looping until EOT
		}
	}

	return b_read; //reached when c = EOT	
}

/* Write count bytes to fd from the buffer buf. */
ssize_t write_syscall(int fd  __attribute__((unused)), const void *buf  __attribute__((unused)), size_t count  __attribute__((unused)))
{
	unsigned int i;
	unsigned int buf_begin;
	unsigned int buf_end;

	if(fd != STDOUT_FILENO){
		puts("file descriptor error!"); 
		return -EBADF;
	} // 1. check the file descriptor

	if(count > MAX_WRITE_SIZE){
		puts("count size err!");
		return -EFAULT; 
	} // 2. check the size of buf and the address of buf

	buf_begin = (int) buf;        //low bound of buf
	buf_end = ((int) buf) + count;    //high bound of buf
	if((buf_begin < SDRAM_START) || (buf_end > SDRAM_END)){
		puts("buf address range error!");
		return -EFAULT; 
	} //check if the buffer exceeds the SDRAM

	for(i = 0; i < count; i++){
		putc(((char *)buf)[i]);    
	}  // 3. write characters from buffer to stdout until buffer is empty

	// 4. return with the number of characters to stdout
	return count;
}

