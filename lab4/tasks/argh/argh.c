/** @file argh.c
 *
 * @brief A simple part 2 test
 *
 * Purpose of the test:
 * 1.Ensure tasks inherit highest priority when grabbing a mutex
 *
 * @author Jonathan Lim jlim2)
 * @data 2010-12-01
 **/ 

#include <stdio.h>
#include <unistd.h>
#include <task.h>
#include <lock.h>
#include <bits/errno.h>
#include <errno.h>

#define MUTEX_NUM 32
#define YES_STR "\033[32;1mYes!\033[0m\n"
#define NO_STR  "\033[31;1mNo!\033[0m\n"
#define TEST_DONE "\033[32;1mTEST PASSED SUCCESSFULLY!\033[0m\n"

#define MUTEX1 1

void panic(const char* str)
{
	puts(str);
	while(1);
}

void fun3(void* str){
	if(mutex_lock(MUTEX1))
		panic("Failed to acquire mutex");
	putchar((int)str);   
	if(mutex_unlock(MUTEX1)){
		if(errno==EINVAL)
            puts("EINVAL");
        if(errno==EPERM)
            puts("EPERM");
        panic("Failed to release mutex");
    }
    
    if (event_wait(3) < 0)
		panic("Dev 3 failed");
	
	int i = 0;

	// delay task so a lower process can grab a mutex
    while(i < 5){
		if (event_wait(3) < 0)
            panic("Dev 3 failed");
		i++;
	}
}


void fun0(void* str){
	while(1){
		printf("bystander\n");
		if (event_wait(0) < 0)
            panic("Dev 0 failed");
	}
}   


void fun1(void* str){
	if(mutex_lock(MUTEX1))
		panic("Failed to acquire mutex");
	putchar((int)str);   
	if(mutex_unlock(MUTEX1)){
		if(errno==EINVAL)
            puts("EINVAL");
        if(errno==EPERM)
            puts("EPERM");
        panic("Failed to release mutex");
    }

	if (event_wait(1) < 0)
		panic("Dev 1 failed");
}
   
int main(int argc, char** argv)
{
	int mutex,i=0;
    puts("<<<TEST STARTING...");

    //creates an array of mutexes
    for(;i<MUTEX_NUM;i++)
    {
        mutex = mutex_create();
        if(errno == ENOMEM){
        	puts("failed to create a mutex!!");
		}
	}
    
    puts("Successfully created all the mutexes!!");
    puts(YES_STR);
	
    task_t tasks[3];
	tasks[0].lambda = fun0;
	tasks[0].data = (void*)'0';
	tasks[0].stack_pos = (void*)0xa2000000;
	tasks[0].C = 1;
	tasks[0].T = PERIOD_DEV0;

	tasks[1].lambda = fun1;
	tasks[1].data = (void*)'1';
	tasks[1].stack_pos = (void*)0xa1000000;
	tasks[1].C = 1;
	tasks[1].T = PERIOD_DEV1;

    //highest priority task
    tasks[2].lambda = fun3;
	tasks[2].data = (void*)'3';
	tasks[2].stack_pos = (void*)0xa2500000;
	tasks[2].C = 1;
	tasks[2].T = PERIOD_DEV3;

	task_create(tasks, 3);
	argc = argc ;
	argv = argv ;
	return 0;
}
