/* btagani, jlim2, luow
 * part2c.c
 *
 * The function provided to us is defined with DEFAULT
 * Our optimizations are defined with OPTIMIZEDx where
 * x = 1,2,3. 
 */

#include <stdlib.h>
#include <stdio.h>

/**
 * Function: oddball
 * Description: Baseline implementation for finding the number that
 *   occurs only once in the array.
 * Arguments:
 *   arr - pointer to start of integer array
 *   len - number of elements in array
 * Return:
 *   The number that occurs only once
 */
#ifdef DEFAULT
int oddball(int *arr, int len) {
	int i, j;
	int foundInner;
	int result = 0;

	for (i = 0; i < len; i++) {
		foundInner = 0;
		for (j = 0; j < len; j++) {
			if (i == j) {
				continue;
			}
			if (arr[i] == arr[j]) {
				foundInner = 1;
			}
		}
		if (foundInner != 1) {
			result = arr[i];
		}
	}

	return result;
}
#endif

#ifdef OPTIMIZE1
/*
 * Since there is only one single number, while the other number are pair, 
 * XORing all the elements will result in the duplicate numbers canceling 
 * each other out and equaling 0. XORing the oddball number with 0 has no
 * effect, and the oddball number is found.
 * This algorithm takes O(n) time and O(1) space.
 *
 * - Use countdown loop to save a clock cycle per iteration.
 * - Can we also loop unrolling to save anything? 
 */

int oddball(int *arr, int len) {
	int result;
	int i;
		
	result = arr[len - 1];		//set result to the last element of the array
	for(i = len - 2; i >= 0; i--){	//use result to XOR with each element and store into result 
		result ^= arr[i];
	}
	return result;
}

#endif

#ifdef OPTIMIZE2
/*
 * Given 2n - 1 elements where elements are from 1 to n inclusive, the oddball
 * value can be obtained by subtracting all the elements in the array from
 * twice the sum of 1 to n inclusive. Twice the sum equals "n * (n + 1)".   
 *
 * This algorithm takes O(n) time and O(1) space
 * - Use countdown loop to save a clock cycle per iteration. 
*/
int oddball(int *arr, int len){
	int i;
	long long result; //define result to long long in case n * (n + 1) exceed int TMAX 
	result = ((len >> 1) + 1) * ((len >> 1) + 2); //result = n * (n + 1)
	for(i = len - 1; i >= 0; i--){
		result -=  arr[i];
	}
	return (int) result;
}

#endif

#ifdef OPTIMIZE3
/*
 * Scan the array and record the number of times that a number has appeared
 * in a hash array of size 2n-1.
 * After the scan through the arr array, scan the 'hash' array and 
 * return the number that is counted only once in the array.
 * This algorithm takes O(n) time and O(n) space
 *
 * - Use countdown loop to save a clock cycle per iteration.
*/
int oddball(int *arr, int len) {
	int i;
	int hash_len, *hash;

	hash_len = (len >> 1) + 1; 		//hash_len = n, or is it (len + 1) >> 1?
	hash =  calloc(hash_len, 4);	//initialize 'hash' to zero

	for(i = len - 1; i >= 0; i--)	//map all the numbers to hash array
	{
		hash[arr[i] - 1] += 1;
	}

	for(i = hash_len - 1; i >= 0; i--)	//pop out the number only appeared once
	{
		if(hash[i] == 1)
			return i + 1;
	}
	return 0;
}
#endif

/**
 * Function: randGenerator
 * Description: Generate a random array that is in compliance with
 *   lab specification
 * Arguments:
 *   arr - pointer to start of integer array
 *   len - number of elements in array
 * Return:
 *   Unused, but feel free to utilize it.
 */

int randGenerator(int *arr, int len) {
	int i, j, r, rcount;
	for (i = 0; i < len; i++) {
		do {
			rcount = 0;
			r = rand()%(len/2 + 1) + 1;
			for (j = 0; j < i && rcount < 2; j++) {
				if (arr[j] == r) {
					rcount++;
				}
			}
		} while(rcount >= 2);
		arr[i] = r;
		printf("%d ", r);
	}
	printf("\nDone generating\n");
	return 0;
}





