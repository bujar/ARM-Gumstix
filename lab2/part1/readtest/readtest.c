

#include <unistd.h>
#include <stdlib.h>

int main(){

  char buf[50];
  ssize_t r;
  write(STDOUT_FILENO, "READTEST\n", 9);
   while((r = read(0, buf, 30))> 0){
      write(1, buf, r);
      write(1, "\n", 1);
   }
  return 23;//readval;
}

