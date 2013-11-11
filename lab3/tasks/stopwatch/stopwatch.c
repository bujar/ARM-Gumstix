/** @file stopwatch.c
 *
 * @This is a simple stopwatch program that records times
 *
 * @author: Bujar Tagani <btagani@andrew.cmu.edu>
 *          Jonathan Lim <jlim2@andrew.cmu.edu>
 *          Norman Wu <luow@andrew.cmu.edu>
 * @date: Sat Nov  9 22:47:07 EST 2013
 */

#include <unistd.h>
#include <stdio.h>

#define BUFLEN 128
#define MS_PER_S 1000

/* Globals */
int record_num = 0;
int keep_running = 1;
unsigned long record_buf_s[BUFLEN];
unsigned long record_buf_ms[BUFLEN];

/* Functions */
void print_results();
void stopwatch();
void menu();

int main(int argc, char** argv){
   char r;
   stopwatch();

   /*Menu once first stopwatch is finished */
   while(1) {
	printf("\n\n\n\nWhat would you like to do?\n");
	printf("R - Restart\n");
	printf("P - Print Results\n");
	printf("Q - Quit Application\n");
	read(0, (void *)(&r), 1);

	switch(r) {
	   case 'r':
	   case 'R':
	   	keep_running = 1;	//sets keep_running so we can run stopwatch again
	   	stopwatch();
	   	break;
	   case 'p':
	   case 'P':
		print_results();
		break;
	   case 'q':
	   case 'Q':
		return 0;
	   default:
		return 0;
	}
   }
}

/* takes user input and stores recorded times into buffer */
void stopwatch()
{
  char a;
  int started = 0;
  unsigned long start_time = 0;
  unsigned long end_time = 0;
  unsigned long tmp_s = 0;	//used to store seconds
  unsigned long tmp_ms = 0;	//used to store milliseconds
	
  record_num = 0;		//resets record_num if running function more than once

  menu();

  while(keep_running == 1){
     read(0, (void *)(&a), 1);
     if((started == 0) && (a == 'r'))
     {
	printf(" You must start first\n");
	continue;	
     }
	
     switch(a){
	case 's':
	case 'S':
	   if(started == 1)
	   {
		printf(" Stopwatch already started\n");
		break;	
	   }
	   started = 1;
	   start_time = time();
	   printf(" Stopwatch Started\n");
	   break;

	case 'q':
	case 'Q':
	   printf("\n\n\nFinished Recording\n");
	   keep_running = 0;
	   break;

	case 'r':
	case 'R':
	   end_time = time();
	   tmp_ms = end_time - start_time;
	   tmp_s = tmp_ms / MS_PER_S;
	   tmp_ms %= MS_PER_S;
	   record_buf_s[record_num] = tmp_s;	//seconds buffer
	   record_buf_ms[record_num] = tmp_ms;	//milliseconds buffer
	   record_num++;
	   printf("ecord %d: %ld.%lds \n", record_num, tmp_s, tmp_ms);
	   break;

  	default:
	   printf("\t Unsupported Command\n\n");
	   menu();
	}
   }	
	
}

/* prints results of last running stopwatch() */
void print_results()
{
  int index = 0;
  for(; index < record_num; index++) {
     printf("\n\nRecorded Time %d:  ", index+1);
     printf("%lu.", record_buf_s[index]);
     printf("%lus", record_buf_ms[index]);
   }
}

/* main options menu */
void menu(){
  printf("\nWelcome to the Stopwatch. Input an option and press Enter\n");
  printf("\n******Options******\n");
  printf("S - Start\n");
  printf("R - Record Time\n");
  printf("Q - Quit\n");
}
