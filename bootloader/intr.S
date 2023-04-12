#include "intr.h"
	.h8300h
	.section .text

	; exception
	.global _intr_softerr
	.type _intr_softerr,@function
_intr_softerr:
	; push registers values to stack.
	; er7 is stack pointer.
	; @-er7: decrement stack pointer, then access to the 
	; memory that the decremented pointer points
	mov.l	er6,@-er7
	mov.l	er5,@-er7
	mov.l	er4,@-er7
	mov.l	er3,@-er7
	mov.l	er2,@-er7
	mov.l	er1,@-er7
	mov.l	er0,@-er7

	mov.l	er7,er1				; 2nd arg: stack pointer
	mov.w	#SOFTVEC_TYPE_SOFTERR,r0	; 1st arg: SOFTVEC_TYPE_SOFTERR
	jsr	@_interrupt			; call interrupt()

	; recover registers
	mov.l	@er7+,er0
	mov.l	@er7+,er1
	mov.l	@er7+,er2
	mov.l	@er7+,er3
	mov.l	@er7+,er4
	mov.l	@er7+,er5
	mov.l	@er7+,er6
	rte

	; system call
	.global _intr_syscall
	.type _intr_syscall,@function
_intr_syscall:
	mov.l	er6,@-er7
	mov.l	er5,@-er7
	mov.l	er4,@-er7
	mov.l	er3,@-er7
	mov.l	er2,@-er7
	mov.l	er1,@-er7
	mov.l	er0,@-er7
	mov.l	er7,er1
	mov.w	#SOFTVEC_TYPE_SYSCALL,r0
	jsr	@_interrupt
	mov.l	@er7+,er0
	mov.l	@er7+,er1
	mov.l	@er7+,er2
	mov.l	@er7+,er3
	mov.l	@er7+,er4
	mov.l	@er7+,er5
	mov.l	@er7+,er6
	rte

	; serial
	.global _intr_serintr
	.type _intr_serintr,@function
_intr_serintr:
	mov.l	er6,@-er7
	mov.l	er5,@-er7
	mov.l	er4,@-er7
	mov.l	er3,@-er7
	mov.l	er2,@-er7
	mov.l	er1,@-er7
	mov.l	er0,@-er7
	mov.l	er7,er1
	mov.w	#SOFTVEC_TYPE_SERINTR,r0
	jsr	@_interrupt
	mov.l	@er7+,er0
	mov.l	@er7+,er1
	mov.l	@er7+,er2
	mov.l	@er7+,er3
	mov.l	@er7+,er4
	mov.l	@er7+,er5
	mov.l	@er7+,er6
	rte
