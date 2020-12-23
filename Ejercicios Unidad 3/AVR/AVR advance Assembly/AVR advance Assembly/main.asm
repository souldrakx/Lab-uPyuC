;
; AVR advance Assembly.asm
;
; Created: 13/12/2020 12:09:25 a. m.
; Author : Drakx
;
;------------- definiciones e includes ------------------------------
.INCLUDE "m2560def.inc" ; Incluir definiciones de Registros para 2560


start:
;HIGH() and LOW() funciones
	;LDI R16,LOW(0x4455);R16 = 55
	;LDI R17, HIGH(0x4455);R17 = 44

;Modo de Direccion indirecta a registros
;X-Register = R27:R26
;Y-Register = R29:R28
;Z-Register = R31:R30
	LDI XL,0x30; XL = R26 = 0x30
	LDI XH,0x01; XH = R27 = 0x01
	LD R24,X; R24 = 0x130
;Ejemplo programa que limpia los primeras 16 direciones empezando por la direccion $60
	LDI R16, 16
	LDI XL, 0x60
	LDI XH,0
	LDI R20, 0x0
L1:
	ST X+,R20
	DEC R16
	BRNE L1

rjmp start
