#include <avr/io.h>

// Macros
#define SetBitPort(port, bit) __asm__ ( "sbi %0,%1" : :"I" ( ( uint8_t )( _SFR_IO_ADDR(port) ) ), "I" ( ( uint8_t ) ( bit ) ) )
#define ClrBitPort(port, bit) __asm__ ( "cbi %0,%1" : :"I" ( ( uint8_t )( _SFR_IO_ADDR(port) ) ), "I" ( ( uint8_t ) ( bit ) ) )


enum ButtonPressStates{
	eBtnUndefined = 0,
	eBtnShortPressed,
	eBtnLongPressed
};
// External definitions (ASM)
//extern void delay(uint16_t mseg);

void delay(uint16_t mseg);

// Local definitions prototypes
void InitPorts(void);
uint8_t checkBtn(void);
void updateLeds(void);

// Global variables
uint8_t  globalCounter=0;
uint32_t millis =0;


int main(void){
	InitPorts();

	while(1){
		switch(checkBtn()){
			case eBtnShortPressed: globalCounter++;
			break;
			case eBtnLongPressed:	globalCounter--;
			break;
		}
		
		delay(1);
		millis++;
		updateLeds();
	}
}

void InitPorts(){
	DDRF = 0x80; //PF7 = 1, PF6-PF0 = 0
	PORTF = 0x40;//PF6 = 1, PF6-PF0 = 0
}

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
	if( (millis - hit_time) > 100 && prev_state == 0){
		
		prev_state=1;

		if((millis - hit_time) > 500){
			return eBtnLongPressed;
		}
		else {
			return eBtnShortPressed;
		}
		
	}
	
}

return eBtnUndefined;
}


void updateLeds(void){
	static uint8_t led_num = 0;
	
	DDRF &= ~(1<<DDF0) & ~(1<<DDF1) & ~(1<<DDF2) & ~(1<<DDF3);
	PORTF &= ~(1<<PF0) & ~(1<<PF1) & ~(1<<PF2) & ~(1<<PF3);
	

	if ((globalCounter) & (1<<led_num)){
		if (led_num == 0 || led_num ==1) {
			DDRF |= (1<<DDF0) | (1<<DDF1);
			if (led_num == 0) {
				SetBitPort(PORTF,PF1);
			} 
			else {
				SetBitPort(PORTF,PF0);
			}
		}
		else if (led_num == 2 || led_num == 3) {
			DDRF |= (1<<DDF2) | (1<<DDF1);
			if (led_num == 2) {
				SetBitPort(PORTF,PF2);
			} 
			else {
				SetBitPort(PORTF,PF1);
			}
		}
		else if (led_num == 4 || led_num == 5) {
			DDRF |= (1<<DDF0) | (1<<DDF2);
			if (led_num == 4) {
				SetBitPort(PORTF,PF0);
			} 
			else {
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
	led_num++;
	if (led_num == 8){
		led_num = 0;
	}
	

}

void delay(uint16_t mseg){
	uint16_t x ;
	while(mseg--){
		x=130;
		while(x--);
	}
}

