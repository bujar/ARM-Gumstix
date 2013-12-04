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

#include <sched.h>

#define FACTOR 10000
#define DEBUG 0
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
10000, 8284, 7798, 7568, 7435, 7348, 7286, 
7241, 7205, 7177, 7155, 7136, 7120, 7106, 
7094, 7084, 7075, 7067, 7060, 7053, 7047, 
7042, 7037, 7033, 7029, 7025, 7021, 7018, 
7015, 7012, 7010, 7007, 7005, 7003, 7001,
6999, 6997, 6995, 6993, 6992, 6990, 6989, 
6988, 6986, 6985, 6984, 6983, 6982, 6981, 
6980, 6979, 6978, 6977, 6976, 6975, 6975, 
6974, 6973, 6972, 6972, 6971, 6970, 6970, 
6969
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
	unsigned long Esum = 0;	//will store result of E-summation(C+B/T)
	unsigned long curr_T = 0;
	unsigned long curr_C = 0;
	unsigned long curr_B = 0;
	for (i = 0; i < (int) num_tasks; i++) {
		curr_C = (tasks[i]->C * FACTOR);
		curr_B = (tasks[i]->B * FACTOR);
		curr_T = tasks[i]->T;
		Esum += ((curr_C + curr_B) / curr_T);
//		printf("C  = %lu\n", curr_C);
//		printf("B  = %lu\n", curr_B);
//		printf("T  = %lu\n", curr_T);
//		printf(" C/T = %lu\n", (curr_C + curr_B) / curr_T);
//		printf("Esum = %lu\n\n", Esum);
	}
	
	if (Esum <= UKtable[i]) {
//		printf("%lu is < %lu", Esum, UKtable[i]);
//		printf("This is schedulable");
		return 1;
	}
	else {
//		printf("%lu is < %lu", Esum, UKtable[i]);
//		printf("This is not schedulable");
		return 0;
	}
}
