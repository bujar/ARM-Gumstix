

#include <unistd.h>
#include <stdlib.h>

int main(){

  char buf[50];
  int i;
  //buf =  malloc (sizeof(char) * 10);
  for(i = 0; i < 10; i++)
	buf[i] = i + 'a'; 
  write(1, buf, 10);
  return 1;
}

