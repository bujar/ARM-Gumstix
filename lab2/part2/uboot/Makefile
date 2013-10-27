CC      = gcc
CFLAGS  = -g -O2 -ffixed-r8 -ffreestanding -Wall -Werror -nostdinc -I include

#cross compiler options
#CC		= arm-linux-gcc
default: stubs.o

.PHONY: default clobber

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clobber:
	rm -f stubs.o
