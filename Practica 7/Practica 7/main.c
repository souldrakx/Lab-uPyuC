#include <avr/io.h>

// Macros
#define SetBitPort(port, bit) __asm__ ( "sbi %0,%1" : :"I" ( (uint8_t) (_SFR_IO_ADDR(port))), "I"( (uint8_t) (bit) ) )
#define ClrBitPort(port, bit) __asm__ ( "cbi %0,%1" : :"I" ( (uint8_t) (_SFR_IO_ADDR(port))), "I"( (uint8_t) (bit) ) )

enum ButtonPressStates{
	eBtnUndefined = 0,
	eBtnShortPressed,
	eBtnLongPressed
};

// External definitions (ASM)
//extern void delay(uint16_t mseg);

// Local definitions prototypes
void    InitPorts(void);
uint8_t checkBtn(void);
void    updateLeds(void);

void delay(uint16_t ms);


// Global variables
uint8_t  globalCounter=0;
uint32_t millis;


int main(void){
	InitPorts();

	while(1){
		switch(checkBtn()){
			case eBtnShortPressed: 
				globalCounter++;
			break;
			case eBtnLongPressed:
				globalCounter--;
			break;
		}
		
		delay(1);
		millis++;
		updateLeds();
	}
}

void InitPorts(void){
	DDRF = 0x40;
	PORTF = 0x80;
}
/*
uint8_t checkBtn(){
	static uint32_t hit_time = 0;
	static uint8_t prev_state = 1;

	if ( bit_is_clear(PINF,PF7) ) {
		
		if(prev_state){
			prev_state = 0;
			hit_time = millis;
		}

	}
	else{
		if( (millis - hit_time) > 200 && prev_state == 0){
			
			prev_state=1;

			if((millis - hit_time) < 1000){
				return 1;
			}
			else {
				return 2;
			}
			
		}
		
	}
	
	return 0;
}

*/

void updateLeds(void){
static uint8_t led_num = 0;

PORTF &=  ~(1<<PF0) & ~(1<<PF1) & ~(1<<PF2) & ~(1<<PF3);
DDRF &= ~(1<<DDF0) & ~(1<<DDF1) & ~(1<<DDF2) & ~(1<<DDF3);

if (	(globalCounter) & (1<<led_num)){

	if (led_num == 0 || led_num ==1) {

		DDRF |= (1<<DDF0) | (1<<DDF1);

		if (led_num == 0) {
			SetBitPort(PORTF,PF1);
			} else {
			SetBitPort(PORTF,PF0);
		}
		
		
	}
	else if (led_num == 2 || led_num == 3) {
		
		DDRF |= (1<<DDF2) | (1<<DDF1);

		if (led_num == 2) {
			SetBitPort(PORTF,PF2);
			
			} else {
			SetBitPort(PORTF,PF1);
		}

		
	}
	else if (led_num == 4 || led_num == 5) {
		
		
		DDRF |= (1<<DDF0) | (1<<DDF2);
		

		if (led_num == 4) {
			SetBitPort(PORTF,PF0);
			} else {
			SetBitPort(PORTF,PF2);
		}

		
	}
	else if(led_num == 6|| led_num == 7){
		
		
		DDRF |= (1<<DDF3) | (1<<DDF2);
		
		if (led_num == 6) {
			SetBitPort(PORTF,PF3);
			
		}
		else{
			SetBitPort(PORTF,PF2);
		}
		
	}
	
}


led_num = ++led_num % 8;
}


void delay(uint16_t ms){
  
  uint16_t x ;

  while(ms--){
	  x=130;
	  while(x--);
  }
}

uint8_t checkBtn(void){
	static uint8_t bandera = 0,aux;
	if(!(PINF&(1<<PF7)) && !bandera){
		aux=millis;
		bandera=1;
	}
	if((aux+40) < millis && bandera)
	if((PINF&(1<<PF7))){
		bandera=0;
		if((aux+1000)> millis)
		return  1;
		else
		return  2;
	}
	
	return  1;
}