/** @file sys_time.c
 *
 * @brief Displays how many seconds and miliseconds the system has been on.
 *
 * @author: Bujar Tagani <btagani@andrew.cmu.edu>
 *          Jonathan Lim <jlim2@andrew.cmu.edu>
 *          Norman Wu <luow@andrew.cmu.edu>
 * @date: Mon Nov  4 20:28:29 EST 2013
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
	unsigned long temp_ms, temp_s; 
	sleep(23450);
     	temp_ms = time();
	temp_s =  temp_ms / 1000;
	temp_ms %= 1000;
       	printf("Our System has been running for %ld.%ld S \n ", temp_s,temp_ms);
	return 0;
}
