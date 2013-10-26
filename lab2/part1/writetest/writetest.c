

#include <unistd.h>
#include <stdlib.h>

#define LEN 10000
int main(){

  char buf[LEN];
  int i;
  //buf =  malloc (sizeof(char) * 10);
  for(i = 0; i < LEN; i+=2){
	 buf[i] = 'a';
	 buf[i+1] = 'b';
  }

  buf[LEN-1] = 'c';
  
  //tests that we can write 10000 a b ... a c
  write(1, buf, LEN);  
  
  write(1, "now we are going to print buf2\n", 31); 
  
  // tests what happens when we write count 
  char buf2[10] = {'1','2','3','4','5','6','7','8','9'};
  write(1, buf2, 10);  

  // tests what happens when we write count 20 when we have buffer 10
  char buf3[10] = {'a','b','c','d','e','f','g','h','i'};
  return write(1, buf3, 20);  
   
}

