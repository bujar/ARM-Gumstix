/** @file stopwatch.c
 *
 * @This program is used to calculate the time for running.
 *
 * @author: Bujar Tagani <btagani@andrew.cmu.edu>
 *          Jonathan Lim <jlim2@andrew.cmu.edu>
 *          Norman Wu <luow@andrew.cmu.edu>
 * @date: Mon Nov  4 20:43:13 EST 2013
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <exports.h>

int main(int argc, char** argv){
	char a;
	int i,j = 0, k = 0;
	unsigned long start_time = 0, end_time = 0, tmp_s = 0, tmp_ms = 0;

	printf("please press s to start to count time\nonce started please press r to record a time\nand press q to quit the stopwatch\n");
	 
 for(i = 0; i < 100; i ++){
	//scanf(%c,&a);
	read(0, (void *)(&a), 1);
	if(i == 0 && (a =='r'))
	{
	printf(" is the input, please start time watch first\n");
	i = 0;
	continue;	
	}
	switch(a){
		case 's':
			k++;
			if(k > 1)
			{
			printf(" is the input, stopwatch already started\n");
			break;	
			}
			start_time = time();
			printf(" is the input, stopwatch started...\n");
			break;
		case 'q':
			printf(" is the input, gonna quit...\n");
			return 1;
		case 'r':
			end_time = time();
			tmp_ms = end_time - start_time;
			tmp_s = tmp_ms / 1000;
			tmp_ms %= 1000;
			j++;
			printf(" is the input\tRecord %d: %ld.%ld S \n", j, tmp_s, tmp_ms);
			break;
		default:
			printf(" is the input, it is wrong instruction, gonna ignore...\n");
	}
	//sleep(atoi(argv[1]));
	//printf("I've slept for %d milliseconds\n", atoi(argv[1]));
}	
	return 0;
}
