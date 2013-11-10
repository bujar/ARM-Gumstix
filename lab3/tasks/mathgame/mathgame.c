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

int symbol_table[5] = {'+', '-', '*', '/'};

int psg(int upbound)
{
	return (time()/10) % upbound;
}

void print_input(int a, int symbol, int b)
{	
	printf("\nplease input the result of the follwoing math problem\n");
	printf("%d %c %d = ", a, symbol_table[symbol], b);
}

int main(int argc, char** argv){
	
int a = 0, b = 0, i = 0, symbol = 0, point = 0, correct_result = 0;
char result[5];
for(i = 0; i < 10; i++)		
{	
	a = psg(100);
	sleep(psg(17));
	b = psg(100);
	/* if divide operation, make sure b is not zero */
	symbol = psg(4);
	while((symbol == 3) && (b == 0))
	{
		sleep(psg(17));
	 	b = psg(100); 
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
		printf("well done, congrats!\n");
		point += 1;
	}
	else{
		printf("wrong answer, result is %d", correct_result);
	}
}
	printf("you got %d point\n", point);
return 1;
}
