/*
 * kernel.c: Kernel main (entry) function
 *
 * Author: Group Member 1 <email address>
 *         Group Member 2 <email address>
 * Date:   The current time & date
 */

#define SWI_VECTOR ((int *) 0x08)
#define LDR_OPCODE 0xe59ff000 // opcode for the instruction LDR pc, [pc, #0]

int main(int argc, char *argv[]) {


   install_custom_handler((void *) S_Handler);	//takes address our S_HAndler.S function 

}

int install_custom_handler(Custom_S_Handler){

/* check whether SWI vector at 0x8 contains a 'ldr pc, [pc, #imm12]' */
   int *ptr = SWI_VECTOR;
   if(*ptr & LDR_OPCODE) 
 



/*else, exit with status 0x0badc0de 
 */

// the opcode for ldr pc, [pc, #imm12] would be b1110 0101 x001 1111 1111 xxxx xxxx xxxx 
if(((*SWI_VECTOR) & 0xe51ff000) != 0xe51ff000)
	puts("instruction unrecognized!");
	exit(0x0badc0de);			//will determine use with exit later

/*
* go to mem addr of UBoot SWI Handler
* and modify first instruction to change pc
* and 2nd instruction to address of custom 
* S_Handler.S function
*/


*UBOOT_SWI = 0xe51ff004;			//optcode for ldr pc, [pc, #-4]
*(UBOOT_SWI + 1) = Custom_S_Handler

}

