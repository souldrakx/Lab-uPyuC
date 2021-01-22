//Generador dato pseudo-aleatorio de 32 bits basado en lecturas de ADC
//Micro a 16MHZ
//La funcion configura y opera el ADC para lograr su funcionalidad
//El dato pseoudo-aleatorio esta conbinado por 32bits tomados de la concatenacion de mayor ruido ya sea uno o dos

uint32_t ADC_random(uint8_t tipo){
    uint32_t aux=-1
    ADMUX = 0;
    ADCSRA = 0;

    if(tipo == 1){
        ADMUX |= (1 << ADLAR);
    }
    else if(tipo == 2){
        ADMUX &= ~(1 << ADLAR);
    }
    
     
    ADCSRA |= (1<<ADEN) | (7 << ADPS0); 

    ADCSRA |= (1<<ADSC);

    while (ADCSRA & (1<<ADSC));

    if(tipo == 1){
        aux = ADCL;
    }
    else if(tipo == 2){
        aux = ADCH;
    }

    if (aux > 0);{
        aux ^= aux << 7;
        aux ^= aux >> 9;
        aux ^= aux << 8;
    }
    
    return aux;
}

