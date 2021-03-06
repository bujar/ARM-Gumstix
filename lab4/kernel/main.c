/** @file main.c
 *
 * @brief kernel main
 * @author Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 * @date Tue Dec  3 13:47:47 EST 2013
 */

#include <kernel.h>
#include <task.h>
#include <sched.h>
#include <device.h>
#include <assert.h>
#include <arm/interrupt.h>
#include <arm/reg.h>
#include <sched.h>
#include <lock.h>

#include "globals.h"
#include "sched/sched_i.h"
#include "main_i.h"

//#define DEBUG
#ifdef DEBUG
#  define debug_printf(...) printf(__VA_ARGS__)
#else
#  define debug_printf(...)
#endif

uint32_t global_data;

int kmain(int argc __attribute__((unused)), char** argv  __attribute__((unused)), uint32_t table)
{

	task_t main_task; //main task used to initialize scheduler
	
	app_startup(); // bss is valid after this point
	global_data = table;

	int status = install_handler(SWI_VECTOR_ADDR, (int) &S_Handler);
	if (status != 0){
		panic("Installing SWI handler failed");
	}

	status = install_handler(IRQ_VECTOR_ADDR, (int) &irq_wrapper);
	if (status != 0){
		panic("Installing IRQ handler failed");
	}

	/* init the timer driver */
	timer_init();

	/* enable interrupts */
	reg_write(INT_ICMR_ADDR, (1 << INT_OSTMR_0));
	reg_write(INT_ICLR_ADDR, (0 << INT_OSTMR_0));

	runqueue_init();
	mutex_init();
	sched_init(&main_task);
	disable_interrupts();
	dispatch_nosave();

	assert(0);        /* should never get here */
	panic("error: reached end of kmain!!");
	return status;
}


/* This function will hijack U-Boot's SWI/IRQ handler by
 * replacing the first two instructions
 * of UBoot's SWI/IRQ Handler and make it jump to our own
 * SWI/IRQ Handler at S_Handler.S or I_Handler.S
 */

int install_handler(int vec_pos, int custom_handler){
	int *vec_ptr, *jumpentryaddr, *UBOOT_handler_addr;
	int offset;
	unsigned int opcode;

	/* does vector entry contains a 'ldr pc, [pc, #imm12]'? */
	vec_ptr = (int *)vec_pos;

	opcode = (*vec_ptr & LDR_OPCODE);
	if( opcode == LDR_OPCODE){
		debug_printf("we have a positive LDR\n");
	}
	else if((opcode|UP_BIT_MASK) == LDR_OPCODE){
		debug_printf("we have a negative LDR\n");
		return 0x0badc0de;
	}
	else{
		debug_printf("NOT a LDR instruction\n");
		return 0x0badc0de;
	}
	
	offset = (*vec_ptr & LDR_IMM_MASK);
	jumpentryaddr = (int *)(vec_pos + 0x8 + offset);
	UBOOT_handler_addr = (int *)*jumpentryaddr;

	if(vec_pos == SWI_VECTOR_ADDR){
		//  Store first two instructions of UBoot SWI
		UBOOT_SWI_ADDR = UBOOT_handler_addr;
		UBOOT_SWI_INST1 = *UBOOT_SWI_ADDR;
		UBOOT_SWI_INST2 = *(UBOOT_SWI_ADDR + 1);
	}
	else if(vec_pos == IRQ_VECTOR_ADDR){
		//  Store first two instructions of UBoot IRQ
		UBOOT_IRQ_ADDR = UBOOT_handler_addr;
		UBOOT_IRQ_INST1 = *UBOOT_IRQ_ADDR;
		UBOOT_IRQ_INST2 = *(UBOOT_IRQ_ADDR + 1);
	}
	else{
	//  Allow adding more interrupt such as FIQ in later lab 
		debug_printf("Interrupt style neither SWI nor IRQ");
	}

	//Replace first two instructions of UBoot SWI / IRQ
	*UBOOT_handler_addr = OPCODE_LDR_NEXT; //ldr pc, [pc, #4]
	*(UBOOT_handler_addr + 1) = custom_handler;

	debug_printf("vector position entry has value of %x\n", *vec_ptr);
	debug_printf("immediate offset is %d\n", offset);
	debug_printf("jump table address is %p\n", jumpentryaddr);
	debug_printf("jump table address entry is %p\n", UBOOT_handler_addr);
	return 0;
}


