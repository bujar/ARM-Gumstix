#CC      = gcc
#OBJCOPY = objcopy
CFLAGS  = -g -O2 -ffreestanding -Wall -Werror -nostdinc -I ../libc/include
LDFLAGS = -nostdlib -Wl,-Ttext,$(LOAD_ADDR) 

#cross compiler options
CC		= arm-linux-gcc
OBJCOPY = arm-linux-objcopy

LOAD_ADDR = 0xa2000000

CRT0    = ../libc/crt0.o
LDLIBS  = ../libc/libc.a

objects = exittest.o

default: exittest.bin

.PHONY: default clean clobber

exittest.bin: exittest
	$(OBJCOPY) -O binary $< $@

exittest: $(objects)
	$(CC) $(LDFLAGS) -o $@ $(CRT0) $^ $(LDLIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f exittest $(objects)

clobber: clean

	rm -f exittest.bin
