@ exit.S: exit sycall wrapper
@
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@	   Luo Wu <luow@andrew.cmu.edu>
@ Date:    SAT Oct 12 17:38:48 EDT 2013

#include <bits/swi.h>

	.file	"exit.S"
	.text

	.global	exit
exit:
	swi	EXIT_SWI
