.include "m2560def.inc"

start:
	ldi r30,0x1D
	ldi r16,$ff
	mov r0,r16

L1: ST -Z,R0
	CPI r30,0
	brne L1

	rjmp start

	 



