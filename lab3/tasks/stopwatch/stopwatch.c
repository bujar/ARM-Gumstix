/** @file stopwatch.c
 *
 * @This program is used to calculate the time for running.
 *
 * @author: Bujar Tagani <btagani@andrew.cmu.edu>
 *          Jonathan Lim <jlim2@andrew.cmu.edu>
 *          Norman Wu <luow@andrew.cmu.edu>
 * @date: Sat Nov  9 22:47:07 EST 2013
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MS_PER_S 1000

void usage(){
	printf("please press s to start to count time\n");
	printf("once it has started, please press r to record a time\n");
	printf("and press q to quit the stopwatch\n");
}

int main(int argc, char** argv){
	char a;
	int recordnum = 0, started = 0;
	unsigned long start_time = 0, end_time = 0, tmp_s = 0, tmp_ms = 0;


	while(1){
		read(0, (void *)(&a), 1);
		if((started == 0) && (a == 'r'))
		{
			printf(" is the input, please start time watch first\n");
			continue;	
		}
	
		switch(a){
			case 's':
				if(started == 1)
				{
					printf(" is the input, stopwatch already started\n");
					break;	
				}
				started = 1;
				start_time = time();
				printf(" is the input, stopwatch started...\n");
				break;

			case 'q':
				printf(" is the input, gonna quit...\n");
				return 1;

			case 'r':
				end_time = time();
				tmp_ms = end_time - start_time;
				tmp_s = tmp_ms / MS_PER_S;
				tmp_ms %= MS_PER_S;
				recordnum++;
				printf(" is the input\t");
				printf("Record %d: %ld.%lds \n", recordnum, tmp_s, tmp_ms);
				break;
			default:
				printf("unsupported command\n");
				usage();
		}
	}	
	return 0;
}
