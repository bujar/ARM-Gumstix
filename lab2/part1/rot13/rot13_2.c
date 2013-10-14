/*
 * rot13.c: ROT13 cipher test application
 *
 * Authors: Bujar Tagani <btagani@andrew.cmu.edu>
 *          Jonathan Lim <jlim2@andrew.cmu.edu>
 *	    Luo Wu <luow@andrew.cmu.edu>
 * Date:    Mon Oct 14 04:44:21 UTC 2013
 */

#include <unistd.h>
#include <stdlib.h>

#define BUFLEN 128
void rot13(char arr[], int len)
{
    int i = 0;
    for (; i<=len; i++){
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

int main(int argc, char **argv){
    
    char buf[BUFLEN];
    int nread = 0;
	
    /* main loop */
    while( (nread = read(STDIN_FILENO, buf, BUFLEN)) > 0){
	
	/* encrypt the input */
	rot13(buf, nread);	
	
	int nwrite = 0;
	int nleft = nread;
		
	/* write the encrypted input to STDOUT */
	while(nleft > 0){
	    if((nwrite = write(STDOUT_FILENO, buf, nleft)) < 0)
	        exit(1);
		nleft -= nwrite;
	    }
	}

	if(nread == 0) 
	    exit(0);
	else 
	    exit(1);

	return 0; /* unreachable */
}

