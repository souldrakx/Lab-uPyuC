//Ejercicio 2.c 

/*Programa que escribe YES continuamente
*baud = 9600, 8 bit, 1stop, no par
*/

#include <avr/io.h>


int main(void){
	uint8_t i = 0;
	uint8_t max_cad = 3;
	char *cad = "YES";
	UCSR0B |= (1 << TXEN0);
	UCSR0C |= (3 << UCSZ00);
	UBRR0 = 103;
    while (1) {
		for(i = 0; i<max_cad; i++){
			while(!(UCSR0A & (1<<UDRE0)));
			UDR0 = cad[i];
		}
    }
}

