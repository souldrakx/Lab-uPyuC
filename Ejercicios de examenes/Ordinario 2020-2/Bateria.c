/*Implementar funciones ADC_ini(), ADC_BatteryValue()

ADC_ini() Inicializa el adc para la bateria deacuerdo al circuito
ADC_BatteryValue()  Realiza la medicion  indirecta del voltaje total de las baterias del micro segun el circuito
                    Esta funcionregresa un valor de 8 bits que representa al valor digital correspondiente al 
                    porcentaje del valor real de las baterias
Si retorna 100 representa los 3V y las vaterias estan a l 100%, si retorna 90 representa el 90%
El micro opera a 3V a una frecuecia de 4Mhz
*/

void ADC_ini(){
    ADMUX = (1<<ADLAR);
    ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS0);
}

uint8_t ADC_BatteryValue(){
    uint8_t aux = 0;
    ADCSRA |= (1<< ADSC);

    while(ADCSRA & (1<<ADCS));

    return (aux = ADCH*100/512);
}