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


#define HARD_MODE 'h'		
#define MIDDLE_MODE 'm'		
#define EASY_MODE 'e'		
#define QUIT_MODE 'q'

/* points per challenge for different mode*/
#define POINT_HARD_MODE 3		
#define POINT_MIDDLE_MODE 2		
#define POINT_EASY_MODE 1		

/*
 * HASH key for different mode, all are prime numbers 
*/
#define HASH_HARD_MODE 91		
#define HASH_MIDDLE_MODE 47		
#define HASH_EASY_MODE 17		

/* operations */
#define ADD 0
#define MINUS 1
#define MULTIPLY 2
#define DIVISION 3

#define MS_TO_S 1000;

char mode;
char result[5];
	
int a = 0;
int b = 0;
int i = 0;
int hash;
int symbol = 0;
int point = 0;
int correct_result = 0;
int mode_point = 0; 	
int total_point = 0;
/* the four operations will used in the math game */
int symbol_table[5] = {'+', '-', '*', '/'};

/* psuedo random number generator */
int psuedo_rand_gen(int upbound)
{
	return ((time()/10) * (time()/10)) % upbound;
}

/* print math challenge */
void print_input(int a, int symbol, int b)
{	
	printf("\nPlease input the result of the followng math challenge\n");
	printf("%d %c %d = ", a, symbol_table[symbol], b);
}

/* swap two int number */
void swap(int *a, int *b){
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

/*calcute the time the user has used to solve one challenge*/
int time_cal(unsigned long start_time, unsigned long end_time)
{
	int tmp;
	tmp = (end_time - start_time) / MS_TO_S;
	return tmp;
}

/* set up mode for the game */
void mode_setup(void){
read(STDIN_FILENO, &mode, 1);
//mode = getchar();

switch(mode){
	case HARD_MODE:
		hash =  HASH_HARD_MODE;
		mode_point = POINT_HARD_MODE;
		break;		
	case MIDDLE_MODE:
		hash =  HASH_MIDDLE_MODE;
		mode_point = POINT_MIDDLE_MODE;
		break;		
	case EASY_MODE:
		hash =  HASH_EASY_MODE;
		mode_point = POINT_EASY_MODE;
		break;		
	case QUIT_MODE:
		return;
		break;
	default :
		printf("wrong mode, please enter h, m, e, or q\n");
		mode_setup();	
	}
}

void game(){
for(i = 0; i < 10; i++)		
{	
	sleep(SEED);	
	a = psuedo_rand_gen(hash);
	sleep(psuedo_rand_gen(SEED));
	b = psuedo_rand_gen(hash);
	sleep(psuedo_rand_gen(SEED));
	symbol = psuedo_rand_gen(17)%4;

	/* if divide operation, make sure b is not zero */
	while((symbol == 3) && (b == 0))
	{
		sleep(psuedo_rand_gen(17));
	 	b = psuedo_rand_gen(hash); 
	} 
 	switch(symbol){
		case ADD:
			print_input(a, symbol, b);
			read(STDIN_FILENO, result, 4);
			correct_result = a + b;
			break;
		case MINUS:
			if (a < b){
			swap(&a, &b);
			}
			print_input(a, symbol, b);
			read(STDIN_FILENO, result, 4);
			correct_result = a - b;
			break;
		case MULTIPLY:
			print_input(a, symbol, b);
			read(STDIN_FILENO, result, 4);
			correct_result = a * b;
			break;
		case DIVISION:
			if (a < b){
			swap(&a, &b);
			}
			b = b % 13;
			print_input(a, symbol, b);
			read(STDIN_FILENO, result, 4);
			correct_result = a / b;
			break;
		default:
			printf("wrong simbol error, gonna quit...\n");
			return;
	}

	if(atoi(result) == correct_result){
		printf("\nCorrect!\n");
		total_point += mode_point;
		//printf("Total Score: %d\n", point);
	}
	else{
		printf("\nWrong answer, result is %d !\n", correct_result);
		//printf("Total Score: %d\n", point);
	}
}
	printf("\nFinal Score: %d points out of %d !\n", total_point, i * mode_point);
}

int main(int argc, char** argv){

/* game instructions */
printf("Welcome to math game, please choose the challenge mode:\n");
printf("Please press h to enter hard mode \n");
printf("Please press m to enter middle mode \n");
printf("Please press e to enter easy mode \n");
printf("Please press q to quit math game \n");
printf("************************************************************");
printf("\n\n\n\n");

mode_setup();
game();

return 1;
}
