/*
 * Timer Ejercicio 1.c
 *
 * Created: 13/12/2020 10:30:36 p. m.
 * Author : Drakx
 */ 
/*timer de 16bit ctc*/
#include <avr/io.h>
#include <inttypes.h>

void iniport();
void my_delay();

int main(void){
    while (1){
		PORTB = 0;
		my_delay();
		PORTB |= (1<<PB7);
		my_delay();
    }
}

void iniport(){
	/*Solo el bit 3 sera de salida*/
	DDRB = (1<<PB7);
	/*limpiar el puerto b*/
	PORTB = 0;
}

void my_delay(){
	TCNT0 = 0x9c;
	/*Timer0,normal mode, int clk,no prescalador*/
	TCCR0A = 0;
	TCCR0B = (4<<CS00);
	
	while(!(TIFR0 & (1<<TOV0)));

	TCCR0B = 0;
		
	TIFR0 = (1<<TOV0);
}



