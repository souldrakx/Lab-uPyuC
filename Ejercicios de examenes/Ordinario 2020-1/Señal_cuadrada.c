/*Funcion Generador_2Outs_init() inicializa recursos a utilizar
Funciones de soporte para lograr dicha funcion

uC = 16 MHZ
OC0A = 500 Hz
OC0B = 1 KHz*/

void Generador_2Outs_init(){

    TCCR0A = 0x52; //0101 0010 Toggle OC0A,OC0B, mode CTC
    TCCR0B = 0x03; //0000 0010 prescalador de 64
    TCNT0 = 0;
    OCR0A = 249;
    OCR0B = 124;

    DDRB |= (1<<PB7);
    DDRG |= (1<<PB5);
    TIMSKO = 0x04;
}

ISR(TIMER_COMPB_vect){
    TCCR0A |= (1<<F0COA);
}

