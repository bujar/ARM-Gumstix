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

objects = readtest.o

default: readtest.bin

.PHONY: default clean clobber

readtest.bin: readtest
	$(OBJCOPY) -O binary $< $@

readtest: $(objects)
	$(CC) $(LDFLAGS) -o $@ $(CRT0) $^ $(LDLIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f readtest $(objects)

clobber: clean
	rm -f readtest.bin
