#include <exports.h>

#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>

#include "globals.h"

uint32_t global_data;

#define DEBUG 1

#ifdef DEBUG
#  define debug_printf(...) printf(__VA_ARGS__)
#else
#  define debug_printf(...)
#endif

uint32_t global_data;

int kmain(int argc, char** argv, uint32_t table)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;

	/* Add your code here */

	return 0;
}

/* This function will hijack U-Boot's SWI handler by
 * replacing the first two instructions
 * of UBoot's SWI Handler and make it jump to our own
 * SWI Handler S_Handler.S
 */

int install_handler(int vec_pos, int custom_handler){
   int *vec_ptr, *jumpentryaddr;
   int offset, opcode;

   //globals to be moved later
   int UBOOT_SWI_ADDR;
   int UBOOT_SWI_INST1;
   int UBOOT_SWI_INST2;

   /* does vector entry contains a 'ldr pc, [pc, #imm12]'? */
   
   vec_ptr = (int *)vec_pos;
   
   opcode = (*vec_ptr & LDR_OPCODE);
   if( opcode == LDR_OPCODE){
      debug_printf("we have a positive LDR\n");
   }   
   else if((opcode|U_MASK) == LDR_OPCODE){
      debug_printf("we have a negative LDR\n");
      return 0x0badc0de;           
   }   
   else{
      debuf_printf("NOT a LDR instruction\n");
      return 0x0badc0de;           
   }   

   offset = (*vec_ptr & 0x00000FFF);
   jumpentryaddr = (int *)(vec_pos + 0x8 + offset);
   UBOOT_SWI_ADDR = (int *)*jumpentryaddr;
   
   //  Store first two instructions of UBoot SWI
   UBOOT_SWI_INST1 = *UBOOT_SWI_ADDR;
   UBOOT_SWI_INST2 = *(UBOOT_SWI_ADDR + 1); 

   //Replace first two instructions of UBoot SWI
   *UBOOT_SWI_ADDR = (LDR_OPCODE ^ U_MASK) | 0x04;
   *(UBOOT_SWI_ADDR + 1) = custom_handler;

   debug_printf("vector position entry has value of %x\n", *vec_ptr);
   debug_printf("immediate offset is %d\n", offset);
   debug_printf("jump table address is %p\n", jumpentryaddr);
   debug_printf("jump table address entry is %x\n", UBOOT_SWI_ADDR);
   return 0;
}

