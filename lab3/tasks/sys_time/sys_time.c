/** @file splat.c
 *
 * @brief Displays a spinning cursor.
 *
 * @author: Bujar Tagani <btagani@andrew.cmu.edu>
 *          Jonathan Lim <jlim2@andrew.cmu.edu>
 *          Norman Wu <luow@andrew.cmu.edu>
 * @date: Mon Nov  4 20:28:29 EST 2013
 */

#include <stdio.h>
#include <unistd.h>

#define SLEEPTIME 200
int main(int argc, char** argv){
	unsigned long temp; 
	while(1){
		 sleep(10);
	     temp = time();
         printf("%ld\t ", temp);
	}

	return 0;
}
