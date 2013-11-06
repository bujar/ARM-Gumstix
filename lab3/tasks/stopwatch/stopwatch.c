/** @file stopwatch.c
 *
 * @brief program prints message after X milliseconds
 *
 * @author: Bujar Tagani <btagani@andrew.cmu.edu>
 *          Jonathan Lim <jlim2@andrew.cmu.edu>
 *          Norman Wu <luow@andrew.cmu.edu>
 * @date: Mon Nov  4 20:43:13 EST 2013
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	sleep(atoi(argv[1]));
	printf("I've slept for %d milliseconds\n", atoi(argv[1]));
	return 0;
}
