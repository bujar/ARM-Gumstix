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

#include <sched.h>
#ifdef DEBUG
#include <exports.h>
#endif

static long unsigned UKtable[] = {  
1000000, 828427, 779763, 756828, 743491,
734772, 728626, 724061, 720537, 717734,
715451, 713557, 711958, 710592, 709411,
708380, 707472, 706666, 705945, 705298,
704713, 704182, 703697, 703253, 702845,
702469, 702121, 701797, 701497, 701216,
700954, 700708, 700478, 700260, 700056,
699863, 699680, 699507, 699343, 699187,
699039, 698898, 698763, 698635, 698513,
698395, 698283, 698176, 698072, 697973,
697878, 697787, 697699, 697614, 697533,
697454, 697378, 697305, 697234, 697166,
697100, 697036, 696974, 696914
};
/**
 * @brief Perform UB Test and reorder the task list.
 *
 * The task list at the end of this method will be sorted in order is priority
 * -- from highest priority (lowest priority number) to lowest priority
 * (highest priority number).
 *
 * @param tasks  An array of task pointers containing the task set to schedule.
 * @param num_tasks  The number of tasks in the array.
 *
 * @return 0  The test failed.
 * @return 1  Test succeeded.  The tasks are now in order.
 */
int assign_schedule(task_t** tasks, size_t num_tasks)
{
	int i;
	unsigned long sum;
	unsigned long T_total = 0;
	unsigned long C_total = 0;

	for (i = 0; i < (int) num_tasks; i++) {
		C_total += tasks[i]->C;
		T_total += tasks[i]->T;
		printf("C  = %lu\n", tasks[i]->C);
		printf("T  = %lu\n\n", tasks[i]->T);
	}
	
	C_total *= 10000;
	T_total *= 10000;
	sum = C_total/T_total;
	if (sum <= UKtable[i]) {
//		printf("This is schedulable");
		return 1;
	}
	else {
//		printf("This is not schedulable");
		return 0;
	}
}

/* This function assumes that the tasks are already sorted
 * so that it satisfies rate-monotonicity. 
 *
 * The UB test is performed to see if the tasks are schedulable
 *
 */
/*int ubtest(task_t **tasks, size_t num_tasks){

	int i;
	int bound;
	int k;
	
	k = num_tasks - 1;
	bound = k *
	for(i = 0; i < num_tasks; i++){
	
		
	return 1;
}
	

*/
