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
  unsigned long start_time_ms;
  unsigned long end_time_ms;
  unsigned long time_elapsed;
  unsigned long time_elapsed_s;
  unsigned long time_elapsed_ds;
  char input_buf[BUFLEN];
  int nread = 0;

  while(1){
   	putchar('>'); //print prompt
	putchar(' ');
   
	/* begin time and read input */	
	start_time_ms = time();
	nread = read(STDIN_FILENO, input_buf, BUFLEN);
	end_time_ms = time();
	/* end time */

	/* begin write */	
	write(STDOUT_FILENO, input_buf, nread);
	
	time_elapsed = end_time_ms - start_time_ms;
	time_elapsed_s  = time_elapsed / MILLI_TO_SEC;
	time_elapsed_ds = (time_elapsed % MILLI_TO_SEC) / 100;

	printf("\n%lu.%lus\n", time_elapsed_s, time_elapsed_ds);
   }

}
