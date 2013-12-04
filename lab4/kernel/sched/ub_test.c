/* 
 * Author: Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 * Date: Sat Nov  22 18:54:08 EDT 2013
 */

/** @file ub_test.c
 * 
 * @brief The UB Test for basic schedulability
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-20
 */

#define DEBUG 0
#define FACTOR 10000
#include <sched.h>
#ifdef DEBUG
#include <exports.h>
#endif


/** @bried Lookup table for U(k) values
 *
 * Since we are not using float, these values are adjusted
 * by a factor of 10000 so we treat it as a long instead of 
 * a decminal.
 */
static long unsigned UKtable[] = {  
1000000, 828427, 779763, 756828, 743491, 734772, 728626, 
724061, 720537, 717734, 715451, 713557, 711958, 710592, 
709411, 708380, 707472, 706666, 705945, 705298, 704713, 
704182, 703697, 703253, 702845, 702469, 702121, 701797, 
701497, 701216, 700954, 700708, 700478, 700260, 700056,
699863, 699680, 699507, 699343, 699187, 699039, 698898, 
698763, 698635, 698513, 698395, 698283, 698176, 698072, 
697973, 697878, 697787, 697699, 697614, 697533, 697454, 
697378, 697305, 697234, 697166, 697100, 697036, 696974, 
696914
};


/**
 * @brief Perform UB Test and reorder the task list.
 *
 * The task list passed to this function will already be sorted in order 
 * -- from highest priority (lowest priority number) to lowest priority
 * (highest priority number). We then perform the UB test to determine
 * whether the tasks are schedulable in our kernel.
 *
 * @param tasks  An array of task pointers containing the task set to schedule.
 * @param num_tasks  The number of tasks in the array.
 *
 * @return 0  The test failed.
 * @return 1  Test succeeded.  The tasks are schedulable.
 */
int assign_schedule(task_t** tasks, size_t num_tasks)
{
	int i;
	unsigned long Esum;	//will store result of E-summation(C/T)
	unsigned long T_total = 0;
	unsigned long C_total = 0;
	unsigned long B_total = 0;
	for (i = 0; i < (int) num_tasks; i++) {
		C_total += tasks[i]->C;
		B_total += tasks[i]->B;
		T_total += tasks[i]->T;
		printf("C  = %lu\n", tasks[i]->C);
		printf("T  = %lu\n\n", tasks[i]->T);
	}
	
	C_total += B_total;	//adding blocking total to C (numerator)
	C_total *= FACTOR;	//adjusting so that we can perform division w/o float
	
	Esum = C_total/T_total;
	if (Esum <= UKtable[i]) {
//		printf("This is schedulable");
		return 1;
	}
	else {
//		printf("This is not schedulable");
		return 0;
	}
}
