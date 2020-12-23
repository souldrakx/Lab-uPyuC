/*
 * Ejercicio 1.c
 */ 

/*Programa que escribe G infinitamente
baud = 9600, 8bit, 1stop, no par
*/
#include <avr/io.h>


int main(void){
    UCSR0B |= (1 << TXEN0);
	UCSR0C |= (3 << UCSZ00);
	UBRR0 = 103;
    while (1) {
		while(! (UCSR0A & (1<<UDRE0)));
		UDR0 = 'G';
    }
}

