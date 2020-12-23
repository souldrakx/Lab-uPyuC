
/*
 * TX0pin.S
 *
 * Created: 16/12/2020 11:31:13 a. m.
 *  Author: Drakx
 */ 

 .global TX0pin

 TX0pin:
	;r24 = dato
	;r16 = contador
	lds r16,8
	call t1seg
	
 fin:
	ret

t1seg:;5

	ldi r2, 241 ;1

L4:		ldi r3, 71 ;1

L5:			ldi r4, 186 ; 1    
L6:			nop ;z
			nop ;z
			dec r4 ;z 
			brne L6 ;2(z-1) + 1
		nop ;y
		nop ;y
		dec r3 ;y
		brne L5 ;2(y-1) + 1
	nop ;x
	nop ;x
	dec r2 ;x
	brne L4 ;2(x-1) + 1
ret;5