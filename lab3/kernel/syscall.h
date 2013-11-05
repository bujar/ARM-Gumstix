/*
 * syscall.h: Declares C syscalls
 *
 * Date:   Sun, 07 Oct 2007 01:38:16 -0400
 */
#ifndef SYSCALL_H
#define SYSCALL_H

#include <types.h>

void exit(int status);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
void sleep(unsigned long ms);
unsigned long time(void);

#endif /* SYSCALL_H */

