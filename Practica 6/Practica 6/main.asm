; Practica 6.asm
;
; Created: 15/11/2020 10:54:51 a. m.
; Author : Drakx
;
;------------- definiciones e includes ------------------------------
.INCLUDE "m2560def.inc" ; Incluir definiciones de Registros para 2560

/*RZ= r31/r30 = 8000h*/
		ldi r31,0x80
		ldi r30,0
/*RY= r29/r28 = AA00h*/
		ldi r29,0xAA
		ldi r28,0
/*RX= r27/r26 = 5500h*/
		ldi r27,0x55
		ldi r26,0

start:
		/*R24 == 1 RZ/RY invierten sus posiciones */
		ldi r24,1  

		rcall Inviertir
		/*R24 == 0 RY/RX invierten sus posiciones */
		ldi r24,0

		rcall Inviertir


		rjmp start


/*Proc que invierto los bits de los Registros RZ/RY o RY/RX*/
Inviertir:
	push r16	//Salva el registro 26 para usarse como contador

	/*Se verifica que el valor del R24 sea 1 o 0 en caso de no ser finalizara el procedimiento
	*Dependiendo del valor de R24 se invierten las posiciones de los registros ya mencionados
	*R24 = 1 = RZ/RY
	*R24 = 0 = RY/RX
	*/
	cpi r24,0
	breq RZ_RY
	cpi r24,1
	brne fin
	
	ldi r16,8 

/*Se realizaon rotraciones a los registros RZh y RYl 
para invertir los bits usando los el bit de carry, para usarlos en los otros registros
finalizando con una rotacion en RZh */
RZh_RYl:								
	rol r31
	ror r28
	dec r16
	brne RZh_RYl
	rol r31

	ldi r16,8

/*Se realizan las misma rotaciones pero en los registros RZl y RYh*/
RZl_RYh:								
	rol r30
	ror r29
	dec r16
	brne RZl_RYh
	rol r30
	rjmp fin

RZ_RY: 							
	ldi r16,8
/*Se realizan las misma rotaciones pero en los registros RYh y RXl*/
RYh_RXl:								
	rol r29
	ror r26
	dec r16
	brne RYh_RXl
	rol r29

	ldi r16,8
/*Se realizan las misma rotaciones pero en los registros RYl y RXh*/
RYl_RXh:								
	rol r28
	ror r27
	dec r16
	brne RYl_RXh
	rol r28

fin:
	pop r16
	ret
