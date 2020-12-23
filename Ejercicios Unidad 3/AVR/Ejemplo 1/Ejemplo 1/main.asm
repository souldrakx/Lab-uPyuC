;
; Ejemplo 1.asm
;
; Created: 13/12/2020 01:03:06 a. m.
; Author : Drakx
;
;Llenar todos los registros (0-31) con $FF
.INCLUDE "m2560def.inc"

; Replace with your application code
start:
	LDI R26,0 ; XL = R0
	LDI R31,$FF; R31 = 0xFF
L1:
	ST X+,R31 ;Guarda en la direccion 0x0 = 0xFF e incrementa
	
	cpi R26,26;en caso de alcanzar a XL incrementa 2 veces el registro XL y seguir con la rutina
	BRNE L2 ; caso contrario sigue con el programa
	inc R26
	inc R26
L2:
	cpi R30,$FF ;cuando el R30 sea 0xFF detiene el ciclo
	BRNE L1

	LDI R26,$FF;cuando termina el ciclo llena los registro restantes XL,XH
	LDI R27,$FF
    rjmp start
