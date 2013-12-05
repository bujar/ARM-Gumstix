/** @file hello.c
 *
 * @brief Prints out Hello world using the syscall interface.
 *
 * Links to libc.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-10-29
 */
#include <unistd.h>

const char hello1[] = "1Hello World\r\n";
const char hello2[] = "2Hello World\r\n";
const char hello3[] = "3Hello World\r\n";
const char hello4[] = "4Hello World\r\n";

int main(int argc, char** argv)
{
	write(STDOUT_FILENO, hello1, sizeof(hello1) - 1);
	write(STDOUT_FILENO, hello2, sizeof(hello2) - 1);
	write(STDOUT_FILENO, hello3, sizeof(hello3) - 1);
	write(STDOUT_FILENO, hello4, sizeof(hello4) - 1);
	return 0;
}
