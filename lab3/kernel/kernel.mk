KERNEL = $(KDIR)/kernel
KSTART = $(KDIR)/start.o
SDIR = syscall

DRIVER = driver/timer.o
SYSCALLS = $(SDIR)/read.o $(SDIR)/write.o $(SDIR)/exit.o $(SDIR)/time.o\
	$(SDIR)/sleep.o

# All core kernel objects go here.  Add objects here if you need to.
KOBJS := assert.o main.o raise.o userSetup.o S_Handler.o C_SWI_Handler.o\
	I_Handler.o C_IRQ_Handler.o $(SYSCALLS) $(DRIVER)


KOBJS := $(KOBJS:%=$(KDIR)/%)
ALL_OBJS += $(KOBJS) $(KSTART)
ALL_CLOBBERS += $(KERNEL) $(KERNEL).bin

-include $(KDIR)/arm/kernel.mk

# Put everything needed by the kernel into the final binary.
# KOBJS contains core kernel objects.
# AOBJS contains objects that are ARM dependent.
# UOBJS contains objects that are U-boot dependent.

$(KERNEL): $(KSTART) $(KOBJS) $(AOBJS) $(UOBJS)
	@echo LD $(notdir $@)
	@$(LD) -static $(LDFLAGS) -o $@ $^ $(LIBGCC)

