;
; Inst.Basicas.asm
;
; Created: 12/12/2020 11:09:40 p. m.
; Author : Drakx
;
;------------- definiciones e includes ------------------------------
.INCLUDE "m2560def.inc" ; Incluir definiciones de Registros para 2560

;Directivas
;.EQU
.EQU COUNT  = 0x26

;Tambien existen las directivas .SET los cuales funcionan igual que .EQU pero con la diferencia que no se pueden modificar

/*
start:
	;LoaD Immediate (LDI)
	;LDI Rd,k  16<=d<=31, 0<=k<=31
	LDI R20,0x25 ;R20 = 0x25

	;Load Direct from data Space (LDS)
	;LDS Rd,K  0<=d<=31, 0<=k<=FFFF
	LDS R0,0x14 ;0x14 = R20 ; R0 = R20 = 0x25

	;STore direct to data(STS)
	;STS K, Rd 0<=d<=31, 0<=k<=FFFF
	STS 0x1F, R0; 0x1F = R31; R31 = R0 = 0x25

	;MOV instruccion
	;MOV Rd,Rr Rd = Rr ;Solo registros
	MOV R2,R31; R2 = R31

	;COUNT = 0x26
	LDI R21,COUNT; R21 = 0x26
rjmp start*/

/*
;Saltos
start:
	;Existen diferentes Branch verlos en datashet del ATMega 2560
	;Branch Salto cortos BRNE etiqueta; BRNE = Branch if not Equal
	;Los Branch tanbien funcionan como para loops
	;Ejemplo el cual suma de 3 en 3 en el registro 20 hasta 10 veces
	LDI R16, 10 ;R16 = 10 contador
	LDI R20, 0; R20 = 0
	LDI R21, 3; R21 = 3
Again:
	ADD R20, R21; add 3 a R20
	DEC R16		;decrementa R16
	BRNE Again	;Salta hasta que R16 sea 0
	OUT PORTB,R20;Envia la suma a PORTB

rjmp start
*/

start:

rjmp start



