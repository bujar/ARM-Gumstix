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
#define MS_TO_S 1000
#define BONUS_TIME 5
#define DIVIDER_LIMIT 13
#define REST_TIME 2000

/* points per challenge for different mode*/
#define POINT_HARD_MODE 3		
#define POINT_MIDDLE_MODE 2		
#define POINT_EASY_MODE 1		

/* HASH key for different mode, all are prime numbers */
#define HASH_FOR_SYMBOL 17
#define HASH_HARD_MODE 91		
#define HASH_MIDDLE_MODE 47		
#define HASH_EASY_MODE 17		

/* operations */
#define ADD 0
#define MINUS 1
#define MULTIPLY 2
#define DIVISION 3

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
int bonus_point = 0;

/* the four operations will used in the math game */
int symbol_table[5] = {'+', '-', '*', '/'};

unsigned long st, et;

/* psuedo random number generator */
int psuedo_rand_gen(int upbound)
{
	/* time is always mutiple of 10 because a tick is 10 ms
	 * so divide time by 10 to help to get a random number
	 */
	return ((time()/10) * (time()/10)) % upbound;
}

/* print math challenge */
void print_input(int a, int symbol, int b)
{	
	printf("\nPlease input the result of this math challenge\n");
	printf("%d %c %d = ", a, symbol_table[symbol], b);
}

/* swap two int number - used when operand 1 > operand 2*/
void swap(int *a, int *b){
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

/*calculate the time the user has used to solve one challenge*/
int time_cal(unsigned long start_time, unsigned long end_time)
{
	int tmp;
	tmp = (end_time - start_time) / MS_TO_S;
	return tmp;
}

/* set up mode for the game */
void mode_setup(void){

	/* game instructions */
	printf("\n\n\n\n");
	printf("Welcome to our Mental Math Game!\n");
	printf("Please choose the challenge mode:\n");
	printf("Earn bonus points by answering in %d sec\n", BONUS_TIME);
	printf("Choose your mode");
	printf("\nPlease press h to enter hard mode \n");
	printf("Please press m to enter medium mode \n");
	printf("Please press e to enter easy mode \n");
	printf("Please press q to quit math game \n");
	printf("*******************************************************\n");

	read(STDIN_FILENO, &mode, 1);
	printf("\n\n\n\n");

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
			exit(1);
			break;
		default :
			printf(" is a wrong input. Enter h, m, e, or q\n");
			mode_setup();	
	}
}

void game(){	
	int temp_time;
	
	/*reset point calculater*/
	total_point = 0;
	bonus_point = 0;

	for(i = 0; i < 10; i++)		
	{	
		sleep(SEED);	
		a = psuedo_rand_gen(hash);
		sleep(psuedo_rand_gen(SEED));
		b = psuedo_rand_gen(hash);
		sleep(psuedo_rand_gen(SEED));
		symbol = psuedo_rand_gen(HASH_FOR_SYMBOL)%4;

		/* if divide operation, make sure b is not zero */
		while((symbol == DIVISION) && (b == 0))
		{
			sleep(psuedo_rand_gen(HASH_FOR_SYMBOL));
		 	b = psuedo_rand_gen(hash); 
		} 
		st = time();
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
				if ((a < b) && (a != 0)){
				swap(&a, &b);
				}
				b = b % DIVIDER_LIMIT;
				print_input(a, symbol, b);
				read(STDIN_FILENO, result, 4);
				correct_result = a / b;
				break;
			default:
				printf("wrong symbol error, quitting...\n");
				return;
		}
	
		et = time();
		if(atoi(result) == correct_result){
			printf("\nCorrect!\n");
			total_point += mode_point;
			temp_time = time_cal(st, et);
			if(temp_time < BONUS_TIME){
				printf("Well done, you earned a bonus point!\n");
				++bonus_point;
			}
			sleep(REST_TIME);
		}

		else {
			printf("\nWrong! Result is %d!\n", correct_result);
			sleep(REST_TIME);
		}
	}
	
	printf("\nPoints: %d out of %d\n", total_point, i * mode_point);
	printf("Bonus Points: %d out of %d\n", bonus_point, i);
	printf("Total Score:  %d\n", total_point + bonus_point);
}

int main(int argc, char** argv){
	while(1){
		mode_setup();
		game();
	}

	return 1;
}
