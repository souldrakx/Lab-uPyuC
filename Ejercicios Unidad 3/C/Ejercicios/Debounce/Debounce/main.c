/*
 * Debounce.c
 *
 * Created: 21/12/2020 10:44:07 a. m.
 * Author : Drakx
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000ul

//variable que dictamina si el boton fue presionado
//despues de ser presionado volver 0
volatile uint8_t button_down;

/*******************************************************
Verifica el estado y vuelve 1 button_down si el boton es presionado debounce
********************************************************/
static inline void debounce(){
	/*contador si los stados son iguales*/
	static uint8_t count = 0;
	/*estado del boton*/
	static uint8_t button_state = 0;
	
	/*Verifica si el boton esta en 1 o 0 en el momento*/
	uint8_t current_state = (~PINA & (1<<PA0));
	
	if (current_state != button_state){
		//si el estado de boton cambia incrementar el contador
		count++;
		if(count >= 4){
			//El boton no debounce por cuatro checks del estado del boton
			button_state = current_state;
			//Si el boton fue precionado (sin soltar), el el boton cambia a 1
			if(current_state != 0){
				button_down = 1;
			}
			count = 0;
		}
	}
	else{
		/*reinicia el ciclo*/
		count = 0;
	}
}

int main(void){
	//boton con pull-up
	PORTA |= (1<<PA0);
	
	//Salida del led
	DDRB |= (1<<PB0);
    while (1){
		//actualiza el estado del boton
		debounce();
		//Verifica s el boton fue precionado
		if(button_down){
			//libera el boton
			button_down = 0;
			//enciende el led
			PORTB ^= (1<<PB0);
		}
		_delay_ms(10);
    }
}

