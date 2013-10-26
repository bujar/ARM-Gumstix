

#include <unistd.h>
#include <stdlib.h>

int main(){

  char buf[50];
  read(0, buf, 30);
  return 1;
}

