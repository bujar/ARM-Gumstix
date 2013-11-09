/** @file typo.c
 *
 * @brief Echos characters back with timing data.
 *
 * @author: Bujar Tagani <btagani@andrew.cmu.edu>
 *          Jonathan Lim <jlim2@andrew.cmu.edu>
 *          Norman Wu <luow@andrew.cmu.edu>
 * @date: Mon Nov  4 20:43:13 EST 2013
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFLEN 128
#define MILLI_TO_SEC 1000
int main (int argc, char **argv) {

	while(1){
		unsigned long start_time_ms;
		unsigned long end_time_ms;
   		unsigned long time_elapsed = 0; 
		unsigned long time_elapsed_s;
		unsigned long time_elapsed_ds;
		char input_buf[BUFLEN];
		int nleft = 0;
		int nwrite = 0;
		int nread = 0;
   		start_time_ms = time();
   
   		putchar('>'); //print prompt
   		nread = read(STDIN_FILENO, input_buf, BUFLEN);
	
   		nleft = nread;
   		while (nleft>0){
      		if ((nwrite = write(STDOUT_FILENO, input_buf, nleft)) < 0)
         		exit(1);
         	nleft -= nwrite;
   		}

   		end_time_ms = time();
   		time_elapsed = end_time_ms - start_time_ms;
   		time_elapsed_s  = time_elapsed / MILLI_TO_SEC;
   		time_elapsed_ds = (time_elapsed % MILLI_TO_SEC) / 100;

   		printf("%lu.%lus", time_elapsed_s, time_elapsed_ds);
   }
   return 0;
}
