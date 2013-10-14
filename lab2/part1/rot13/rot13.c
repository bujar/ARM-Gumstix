/*
 * rot13.c: ROT13 cipher test application
 *
 * Authors: Bujar Tagani <btagani@andrew.cmu.edu>
 *          Jonathan Lim <jlim2@andrew.cmu.edu>
 *	    Luo Wu <luow@andrew.cmu.edu>
 * Date:    SUN Oct 13 21:32:12 EDT 2013
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void rot13(char arr[], int len)
{
	int i = 0;
	for (; i<=len; i++)
	{
		if(arr[i] >= 65 && arr[i] <= 77)
		arr[i] = arr[i]+13;
		
		else if(arr[i] >= 97 && arr[i] <= 109)
		arr[i] = arr[i]+13;
		
		else if (arr[i] >= 110 && arr[i] <= 122)
		arr[i] = arr[i]-13;
		
		else if(arr[i] >= 78 && arr[i] <= 90)
		arr[i] = arr[i]-13;
		
	}
}

int main(void) 
{
	char buf[128];
	int buf_len = 0;
	do 
	{
		buf_len = read(0, buf, 128);
	
		if (buf_len == 0)
		exit(0);
	
		else if (buf_len < 0)
		exit(1);
	
		rot13(buf, buf_len);	
	
		if (write(1, buf, buf_len) < 0)
		exit(1);
	
	}

	while (buf_len != EOF);

	exit(0);
}

