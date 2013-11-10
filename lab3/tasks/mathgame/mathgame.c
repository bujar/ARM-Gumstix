/** @file mathgame.c
 *
 * @use pseudo random genernator to give simple math operation  
 *
 * @author: Bujar Tagani <btagani@andrew.cmu.edu>
 *          Jonathan Lim <jlim2@andrew.cmu.edu>
 *          Norman Wu <luow@andrew.cmu.edu>
 * @date: Mon Nov  4 20:28:29 EST 2013
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SEED 73
int symbol_table[5] = {'+', '-', '*', '/'};

int prg(int upbound)
{
	return (time() * (time()/10)) % upbound;
}

void print_input(int a, int symbol, int b)
{	
	printf("\nPlease input the result of the followng math problem\n");
	printf("%d %c %d = ", a, symbol_table[symbol], b);
}

int main(int argc, char** argv){
	
int a = 0;
int b = 0;
int i = 0;
int symbol = 0;
int  point = 0;
int correct_result = 0;
char result[5];

for(i = 0; i < 10; i++)		
{	
	a = prg(91);
	sleep(prg(SEED));
	b = prg(91);
	/* if divide operation, make sure b is not zero */
	symbol = prg(4);
	while((symbol == 3) && (b == 0))
	{
		sleep(prg(17));
	 	b = prg(100); 
	} 
 	switch(symbol){
		case 0:
			print_input(a, symbol, b);
			read(STDIN_FILENO, result, 4);
			correct_result = a + b;
			break;
		case 1:
			print_input(a, symbol, b);
			read(STDIN_FILENO, result, 4);
			correct_result = a - b;
			break;
		case 2:
			print_input(a, symbol, b);
			read(STDIN_FILENO, result, 4);
			correct_result = a * b;
			break;
		case 3:
			print_input(a, symbol, b);
			read(STDIN_FILENO, result, 4);
			correct_result = a / b;
			break;
	}

	if(atoi(result) == correct_result){
		printf("\nCorrect!\n");
		point += 1;
		printf("Total Score: %d\n", point);
	}
	else{
		printf("\nWrong answer, result is %d !\n", correct_result);
		printf("Total Score: %d\n", point);
	}
}
	printf("\nFinal Score: %d points out of %d !\n", point, i);
return 1;
}
