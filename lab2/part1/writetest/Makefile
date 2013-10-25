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

objects = writetest.o

default: writetest.bin

.PHONY: default clean clobber

writetest.bin: writetest
	$(OBJCOPY) -O binary $< $@

writetest: $(objects)
	$(CC) $(LDFLAGS) -o $@ $(CRT0) $^ $(LDLIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f writetest $(objects)

clobber: clean
	rm -f writetest.bin
