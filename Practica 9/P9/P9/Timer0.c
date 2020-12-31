#include <avr/interrupt.h>
#include <inttypes.h>

static volatile uint8_t SecFlag;
static volatile uint64_t ms;

void Timer0_Ini ( void ){
	
	TCNT0 = 0;
	TCCR0A |= (1<<WGM01);
	TCCR0B |= (1<<CS00) | (1<<CS01);
	TIMSK0 |= (1<<OCIE0A);
	OCR0A = 249;
	
	sei(); /* habilita interrupciones (global) */
}
uint8_t Timer0_SecFlag ( void ){
	if( SecFlag ){
		SecFlag=0;
		return 1;
	}
	else{
		return 0;
	}
}

ISR (TIMER0_OVF_vect){ /* TIMER0_OVF_vect */
	static uint16_t mSecCnt;
	TCNT0+=0x06; /* reinicializar Timer0 sin perder conteo */
	mSecCnt++; /* Incrementa contador de milisegundos */
	ms++;
	if( mSecCnt==1000 ){
		mSecCnt=0;
		SecFlag=1; /* Bandera de Segundos */
	}
}

uint16_t millis(){
	return ms;
}