/* btagani, jlim2, luow 
 * math.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "math.h"

#define INTBITS (sizeof(int) * 8)
/*local functions */
static void is_overflow(long long result);

int add(int x, int y){
   long long result;
   result = x + (long long) y;
   is_overflow(result);
   return result;
}

int sub(int x, int y){
   long long result;
   result = x - (long long) y;
   is_overflow(result);
   return result;
}

int mul(int x, int y){
   long long result;
   result = x * (long long) y;
   is_overflow(result);
   return result;
}

int cdiv(int x, int y){
   if(y == 0){
      printf("error: Division by 0\n");
      return -1;
   }
   long long result;
   result = x / (long long) y;
   is_overflow(result);
   return result;
}

int mod(int x, int y){
   if(y == 0){
      printf("error: Division by 0\n");
      return -1;
   }
   return x % (long long ) y;
}

static void is_overflow(long long result){
   if(result > INT_MAX || result < INT_MIN){
      fprintf(stderr, "error: overflow\n");
   }
}

