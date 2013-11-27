/** @file dagger.c
 *
 * @brief Creates two simple periodic tasks.
 *
 * @note  This is like knife -- but smaller :)
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-30
 */
#include <stdio.h>
#include <task.h>
#include <unistd.h>


void panic(const char* str)
{
	puts(str);
	while(1);
}

void fun1(void* str)
{
	while(1)
	{
		putchar((int)str);
		if (event_wait(0) < 0)
			panic("Dev 0 failed");
	}
}

int main(int argc, char** argv)
{
	task_t tasks[3];
	tasks[0].lambda = fun1;
	tasks[0].data = (void*)'@';
	tasks[0].stack_pos = (void*)0xa2000000;
	tasks[0].C = 1;
	tasks[0].T = PERIOD_DEV0;
	tasks[1].lambda = fun1;
	tasks[1].data = (void*)'>';
	tasks[1].stack_pos = (void*)0xa1000000;
	tasks[1].C = 1;
	tasks[1].T = PERIOD_DEV0;
	tasks[2].lambda = fun1;
	tasks[2].data = (void*)'@';
	tasks[2].stack_pos = (void*)0xa3000000;
	tasks[2].C = 1;
	tasks[2].T = PERIOD_DEV0;
	task_create(tasks, 3);
	argc=argc; /* remove compiler warning */
	argv[0]=argv[0]; /* remove compiler warning */

	puts("Why did your code get here!\n");
	return 0;
}
