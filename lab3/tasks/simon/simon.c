/** @file simon.c
 *
 * @brief Follow Simon but with characters and time.
 *
 * @author: Bujar Tagani <btagani@andrew.cmu.edu>
 *          Jonathan Lim <jlim2@andrew.cmu.edu>
 *          Norman Wu <luow@andrew.cmu.edu>
 * @date: Fri Nov  8 23:39:14 EST 2013
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <bits/fileno.h>

#define BUFLEN 50
#define MILLI_TO_SEC 1000


char rand_letter();

//unfinished because I need a timer...
// and read is blocking..
int main (int argc, char **argv) {

	int cwind = 1;
	int i;
	char gamebuf[BUFLEN];
	int alive = 0;
	//int score = 0;
	printf("Characters in buffer: %d\n",  alive);
	printf("Adding %d more characters\n\n", cwind);
	for(i = cwind; i > 0; i++){
		char c = rand_letter();
		gamebuf[alive++] = c;
	}
	write(STDOUT_FILENO, gamebuf, alive);

	
	// spam characters per second
	// every time a character is written correctly
	//     double the num of characters that will be released
	//
	// when a quarter of the buffer is reached, only add one extra per window.
	//
	// if a user doesn't type in a correct character after 2 second
	//     , reset rate to one character per second
	//
    // if the buffer is full, you lose. print time last and num characters

	return 0;
}


char rand_letter(){
	unsigned long num = time()%25;
	return 'a' + num;
}



