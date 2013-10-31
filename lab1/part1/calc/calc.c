
#include <stdlib.h>
#include <stdio.h>
#include "math.h"

/* calc: reads lines from STDIN in the form "number operator number"
 * where an operator is "+, -, *, /, or %" and prints out the result. 
 * The program continues until an incorrect formatted input is 
 * given
 * Overflowing input are not caught.
 */

int main(){
   int x, y, result;
   char symbol;
   printf("WARNING: input should be within the int limits\n");
   
   while( scanf("%d %c %d", &x, &symbol, &y) == 3){
      switch(symbol){
         case '+':
            result = add(x, y);
            break;
         case '-':
            result = sub(x, y);
            break;
         case '/':
            result = cdiv(x, y);
            break;
         case '%':
            result = mod(x, y);
            break;
         case '*':
            result = mul(x, y);
            break;
         default:
            exit(0);
      }
  
   printf("%d\n\n", result);        
   }

return 0;
}
