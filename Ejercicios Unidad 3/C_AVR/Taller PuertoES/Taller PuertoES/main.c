/*
 * Taller PuertoES.c
 *
 * Created: 16/12/2020 11:27:52 a. m.
 * Author : Drakx
 */ 


/*
Funci�n de Transmisi�n de dato dato d 8 bits v�a comunicaci�n serie (por software)

Dise�e e implemente una procedimiento en lenguaje ensamblador del uC ATmega1280/2560 para transmitir un dato de 8 bits 
por un pin de salida considerando el formato serie 9600,8,N,1.

Para esta actividad considere lo siguiente:
La terminar de salida deber� ser PB7.
La terminar PB7 ya encuentra configurada como salida.
El procedimiento deber� dise�arse considerando que se invocar� desde programas en lenguaje C considerando la siguiente funci�n prototipo.
void TXoPin ( uint8_t dato);

Dise�e el procedimiento para que el transmitir un bit de valor 1 sea exactamente el mismo tiempo para transmitir un bit de valor 0.*/
#include <avr/io.h>


int main(void){
	extern void TX0Pin (uint8_t dato);
	
    while (1) {
		TX0Pin(0x55);
    }
}

