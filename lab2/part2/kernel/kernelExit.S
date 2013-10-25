@kernelExit.S
@help kernel exit with dynamic status
@ Authors: Bujar Tagani <btagani@andrew.cmu.edu>
@          Jonathan Lim <jlim2@andrew.cmu.edu>
@          Luo Wu <luow@andrew.cmu.edu>
@ Date: Thu Oct 24 15:15:13 EDT 2013

.file	"kernelExit.S"
.text
.global kernelExit

kernelExit:
	movs pc, lr 
	
