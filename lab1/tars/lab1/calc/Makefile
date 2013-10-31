# btagani, jlim2, luow
# simple Makefile for calc program

CC     = gcc
CFLAGS = -O2 -Wall -Werror
OBJECTS = calc.o math.o


default: calc

.PHONY: default clean clobber

math.o: math.c math.h
calc.o: calc.c math.h

calc: $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJECTS)

clobber: clean
	rm calc
