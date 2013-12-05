ARM_OBJS := reg.o psr.o int_asm.o C_IRQ_Handler.o C_SWI_Handler.o\
			S_Handler.o timer.o		
ARM_OBJS := $(ARM_OBJS:%=$(KDIR)/arm/%)

KOBJS += $(ARM_OBJS)
