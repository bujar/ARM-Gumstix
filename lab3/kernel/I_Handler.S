
@ I_Handler.S: Handles IRQ calls
@
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@          Luo Wu <luow@andrew.cmu.edu>
@ Date: Thu Oct 24 15:15:13 EDT 2013

/* Re-entrant IRQ handler which will save and restore
 * user registers
*/

.file  "I_Handler.S"
.text
.global I_Handler

I_Handler:

	STMFD	sp!, {r0-r12, lr}	@store user reg on stack
	LDR	r0, =SVC_r8		@restore r8
	LDR	r8, [r0]
	BL	C_IRQ_Handler
	ADD	sp, sp, #4		@make sp = r1
	LDMFD	sp!, {r1-r12, lr}	@unstack user reg
	SUBS	pc, lr, #4
/* I found this code on infocenter.arm website for making IRQ
   re-entrant. Looks a little confusing but let's use it as a 
   reference.
IRQ
    SUB     lr, lr, #4             ; construct the return address
    STR     lr, [sp, #-4]!         ; and push the adjusted lr_IRQ
    MRS     r14, SPSR              ; copy spsr_IRQ to r14
    STMFD   sp!, {r0-r4,r12, r14}  ; save AAPCS regs and spsr_IRQ
    BL identify_and_clear_source
    MSR     CPSR_c, #0x9f          ; switch to SYS mode, IRQ is
                                   ; still disabled. USR mode
                                   ; registers are now current.
    AND     r1, sp, #4             ; test alignment of the stack
    SUB     sp, sp, r1             ; remove any misalignment (0 or 4)
    STMFD   sp!, {r1, lr}          ; store the adjustment and lr_USR
    MSR     CPSR_c, #0x1f          ; enable IRQ
    BL      C_irq_handler          ; branch to C IRQ handler
    MSR     CPSR_c, #0x9f          ; disable IRQ, remain in SYS mode
    LDMFD   sp!, {r1,lr}           ; restore stack adjustment and lr_USR
    ADD     sp, sp, r1             ; add the stack adjustment (0 or 4)
    MSR     CPSR_c, #0x92          ; switch to IRQ mode and keep IRQ
                                   ; disabled. FIQ is still enabled.
    LDMFD   sp!, {r0-r4, r12, r14} ; restore registers and
    MSR     SPSR_csxf, r14         ; spsr_IRQ
    LDMFD   sp!, {pc}^             ; return from IRQ.
*/
