/*
 * Timers.c
 *
 * Created: 14/12/2020 12:06:00 p. m.
 * Author : Drakx
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"

void timerini();

int main(void)
/*inicializaciones*/
{	timerini();
	
sei();	
	DDRG = 0xFF;
	PORTG = (1<<PG5);
	
	DDRB = 0xFF;
	PORTB = (1<<PB7);
	
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C= ( 1 << USBS0) | (3 << UCSZ00);
	UBRR0 = 103;
	UDR0 = 'x';
    while (1) {
		while(!(UCSR0A &(1<<UDRE0)));
		UDR0 =TCNT0;
    }
}

void timerini(){
	TCNT0 = 0;
	
	TCCR0A = 0;
	 /*configuracion CTC*/
	TCCR0A |= (1<< COM0A0) | (1<<COM0A1) | (1<<COM0B1) | (1<<WGM10);
	TCCR0B = (1<<CS00);
	
	OCR0A = 5;
	OCR0B = 10;
}

ISR(TIMER0_COMPA_vect){
	
}
