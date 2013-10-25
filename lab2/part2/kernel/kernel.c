/*
 * kernel.c: Kernel main (entry) function
 *
 * Author: Group Member 1 <email address>
 *         Group Member 2 <email address>
 * Date:   The current time & date
 */

#define SWI_VECTOR 0x08
#define LDR_OPCODE 0xe59ff000 // opcode for the instruction LDR pc, [pc, #0]
#define U_MASK 0x00800000 //used to determine if UP bit is set
#define LDR_IMM_MASK 0x00000FFF //used to determine if UP bit is set

#include <exports.h>

extern void S_Handler();
extern void userSetup(int argc, char **argv);
unsigned int Uboot_swi_instruction1;
unsigned int Uboot_swi_instruction2;
int *UBOOT_SWI_ADDR;

extern void kernelExit();

int install_custom_handler(int my_SWIaddr);

int main(int argc, char *argv[]) {
   int status = install_custom_handler((int) &S_Handler);	//takes address our S_Handler.S function 
   if(status != 0){
      return status;
   }

   userSetup(argc, argv);
   //call function to change to usermode
   // mask 
   return 0;
}

int install_custom_handler(int Custom_S_Handler){

   /* check whether SWI vector at 0x8 contains a 'ldr pc, [pc, #imm12]' */
   /* the opcode for ldr pc, [pc, #imm12] would be b1110 0101 x001 1111 1111 xxxx xxxx xxxx */
   int *ptr = (int *)SWI_VECTOR;
   printf("ptr entry has value of %x\n", *ptr);
   int opcode = (*ptr & LDR_OPCODE);
   if( opcode == LDR_OPCODE){
      printf("we have a positive LDR\n");
      
   }
   else if((opcode|U_MASK) == LDR_OPCODE){
      printf("we have a negative LDR\n");
	  return 0x0badc0de;			//will determine use with exit later
   }
   else{
      printf("NOT a LDR instruction\n");
	  return 0x0badc0de;			//will determine use with exit later
   }

   int offset = (*ptr & 0x00000FFF);
   printf("immediate offset is %d\n", offset);

   int *jumpentryaddr = (int *)(SWI_VECTOR + 0x8 + offset);
   UBOOT_SWI_ADDR = (int *)*jumpentryaddr;
   printf("jump table address is %p\n", jumpentryaddr);
   printf("jump table address entry is %x\n", UBOOT_SWI_ADDR);
   
   //modify the first two instructions of the orig. SWI handler


   Uboot_swi_instruction1 = *UBOOT_SWI_ADDR;
   Uboot_swi_instruction2 = *(UBOOT_SWI_ADDR + 1);
	
   *UBOOT_SWI_ADDR = (LDR_OPCODE ^ U_MASK) | 0x04; 
   *(UBOOT_SWI_ADDR + 1) = Custom_S_Handler;
   
   // a return that can help exit the program with dynamic exit status
   // kernelExit();
   return 0;
}


