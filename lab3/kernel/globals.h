/*
 * globals.h: globals header file 
 *
 * Author: Bujar Tagani <btagani@andrew.cmu.edu>
 *         Jonathan Lim <jlim2@andrew.cmu.edu>
 *         Norman Wu <luow@andrew.cmu.edu>
 *  Date:  Oct 31. 2013
 */


/* kernel.c */
/* Vector Table Globals */

#include <arm/exception.h>

#define SWI_VECTOR_ADDR  GET_EXP_VEC_ADDR(EX_SWI)	//macro exception.h
#define IRQ_VECTOR_ADDR  GET_EXP_VEC_ADDR(EX_IRQ)
#define LDR_OPCODE       0xe59ff000 // LDR pc, [pc, #0]
#define UP_BIT_MASK      0x00800000 // detect UP bit
#define LDR_IMM_MASK     0x00000FFF 
#define OPCODE_LDR_NEXT  ((LDR_OPCODE ^ UP_BIT_MASK) | 0x04)

/* timer constants */
#define MS_PER_TICK		10
