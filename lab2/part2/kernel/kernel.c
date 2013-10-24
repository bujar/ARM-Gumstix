/*
 * kernel.c: Kernel main (entry) function
 *
 * Author: Group Member 1 <email address>
 *         Group Member 2 <email address>
 * Date:   The current time & date
 */

#define SWI_VECTOR 0x08
#define UBOOT_SWI 0x28		
//#define LDR_OPCODE (opcode for the instruction LDR pc, [pc, #-4]

int main(int argc, char *argv[]) {


install_custom_handler((void *) S_Handler);	//takes address our S_HAndler.S function 

}

int install_custom_handler(Custom_S_Handler)
{
/*
* go to mem addr of UBoot SWI Handler
* and modify first instruction to change pc
* and 2nd instruction to address of custom 
* S_Handler.S function
*/

*UBOOT_SWI = 0xe51ff004			//optcode for ldr pc, [pc, #-4]
*(UBOOT_SWI + 1) = Custom_S_Handler

}

