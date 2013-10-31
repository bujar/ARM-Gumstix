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
void rot13(char buf[], int buf_len)
{
    int i = 0;
    for (; i<=buf_len; i++){
        if(buf[i] >= 65 && buf[i] <= 77)
	    buf[i] = buf[i]+13;
		
	else if(buf[i] >= 97 && buf[i] <= 109)
	    buf[i] = buf[i]+13;
		
	else if (buf[i] >= 110 && buf[i] <= 122)
 	    buf[i] = buf[i]-13;
		
	else if(buf[i] >= 78 && buf[i] <= 90)
	    buf[i] = buf[i]-13;

	/* Leave buf[i] unchanged if it's not alphabet value*/

    }
}

void print_args(int argc, char **argv){
   int i;
   char c[2] = {'\n'};
   for(i = 0; i < argc; i++){
      char *scan;
      for(scan = argv[i]; *scan != '\0'; scan++){
         write(STDOUT_FILENO, scan, 1);
      }
      write(STDOUT_FILENO, c, 1);
   }
}
	

int main(int argc, char **argv){
    
    print_args(argc, argv);
   
    char input_buf[BUFLEN];
    int nread = 0;
	
    /* main loop */
    while( (nread = read(STDIN_FILENO, input_buf, BUFLEN)) > 0){
	
	/* encrypt the input */
	rot13(input_buf, nread);	
	
	int nwrite = 0;
	int nleft = nread;
		
	/* write the encrypted input to STDOUT */
	while(nleft > 0){
	    if((nwrite = write(STDOUT_FILENO, input_buf, nleft)) < 0)
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

