/** @file exit.S
 *
 * @brief exit sycall wrapper
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 07 Oct 2007 01:52:31 -0400
 * 
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-29
 */

#include <asm.h>
<<<<<<< HEAD
#include <bits/swi.h>

	.file "exit.S"

exit:
    swi EXIT_SWI
=======

	.file "exit.S"

FUNC(exit)
	@ Add code here.  Put your name at the top.
>>>>>>> 3a8d0b7d1ecd47f57ab700d10ccd9ba555ef4cc8
