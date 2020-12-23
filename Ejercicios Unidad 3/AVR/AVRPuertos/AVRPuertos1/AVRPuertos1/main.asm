;
; AVRPuertos1.asm
;
; Created: 15/12/2020 07:21:38 p. m.
; Author : Drakx
;
.INCLUDE "m2560def.inc"

ldi r16, high(RAMEND)
out sph, r16
ldi r16, low(RAMEND)
out spl, r16

start:
    inc r16
    rjmp start

t1seg:;5
	ldi r24, 241 ;1

L4:		ldi r25, 71 ;1

L5:			ldi r26, 186 ; 1    
L6:			nop ;z
			nop ;z
			dec r26 ;z 
			brne L6 ;2(z-1) + 1
		nop ;y
		nop ;y
		dec r25 ;y
		brne L5 ;2(y-1) + 1
	nop ;x
	nop ;x
	dec r24 ;x
	brne L4 ;2(x-1) + 1
ret;5

;5x + x*( 5y + y*(5z))+10 = 16 000 000 donde x = 241, y=71, z=186
;Ecu simplificada x (y (5 z + 5) + 5) + 10
;241*(71*((5*186) +5) +5) +10 =1 600 000 cilcos
;10 = Call/ret