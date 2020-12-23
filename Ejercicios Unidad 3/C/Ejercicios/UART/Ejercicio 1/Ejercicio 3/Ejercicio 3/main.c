/*Ejercicio 3.c*/

/*Programa que recive un dato por UART y lo muestra por el puerto B
baud = 9600, 8 bits, 1 stop, no paridad
*/

#include <avr/io.h>


int main(void){
	uint8_t dato = 0;
	UCSR0B |= (1<<RXEN0);
	UCSR0C |= (3<< UCSZ00);
	UBRR0 = 103;
	
	DDRB = 0xFF;
	PORTB = 0;
    while (1){
		/*Recivir*/
		while (!(UCSR0A & (1<< RXC0)));
		dato = UDR0;
		
		PORTB = dato;
    }
}

