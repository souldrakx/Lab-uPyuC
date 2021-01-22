#include <avr/io.h>

#include "UART.h"
#include "Timer0.h"

void Clock_Ini(uint64_t millis);
void Clock_Display(void);
uint8_t bisiesto( uint16_t year );
void Clock_Update();

uint8_t DM[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

uint16_t seg;
uint16_t min;
uint16_t hr;
uint16_t years;
uint16_t month;
uint16_t days;

/* incluir lo necesario para hacer uso de UART0 */
void UART_AutoBaudRate(void);

char str[10];

int main(){
	UART_Ini(0,0,8,1,2);
	
	UART_AutoBaudRate();
	Timer0_Ini(); 
	
	UART_clrscr(0);
	UART_gotoxy(0,5,1);
	UART_puts(0,"Autobauding done. UBRR0=");
	itoa(UBRR0,str,10);
	UART_puts(0,str);
	UART_puts(0,"\n\r");
	UART_getchar(0);
	
	
	Clock_Ini(1583049590000);
	
	/* == main loop == */
	while(1){
		if( Timer0_SecFlag() == 1){
			/* ¿ha pasado un Segundo? */
			UART_gotoxy(0,5,2);
			UART_clrscr(0);
			Clock_Display();
			UART_gotoxy(0,5,3);
		}
	}
	return 0; /* <-- no se llega aqui */
}

void Clock_Ini(uint64_t millis){
	millis /= 1000;
	
	seg = millis%60;
	millis /= 60;
	
	min = millis%60;
	millis /= 60;
	
	years = (millis/8760) + 1970;
	millis %= 8760;
	
	month = millis/730;
	millis %= 730;
	
	days = millis/24;
	millis %=24;
	
	hr = millis;
	
	millis = 0;
	
}

void Clock_Display(){
	char cad[5];
	
	Clock_Update();
	
	//hh:mm:ss dd/mm/aaaa
	itoa(hr,cad,10);
	UART_puts(0,cad);
	
	UART_putchar(0,':');
	
	itoa(min,cad,10);
	UART_puts(0,cad);
	
	UART_putchar(0,':');
	
	itoa(seg,cad,10);
	UART_puts(0,cad);
	
	UART_putchar(0,' ');
	
	itoa(days,cad,10);
	UART_puts(0,cad);
	
	UART_putchar(0,'/');
	
	itoa(month,cad,10);
	UART_puts(0,cad);
	
	UART_putchar(0,'/');
	
	itoa(years,cad,10);
	UART_puts(0,cad);
	
}

void Clock_Update(){
	seg++;
	
	if (seg == 60){
		seg = 0;
		min++;
	}
	if(min == 60){
		min = 0;
		hr++;
	}
	if (hr == 24){
		hr = 0;
		days++;
	}
	if (days >= DM[month-1]){
		if ( ( ( month == 2 ) && ( bisiesto(years) == 1 ) ) && (days <= 29) ){
			
		}
		else{
			days = 1;
			month++;
		}
	}
	if(month == 13){
		month = 1;
		years++;
		
	}
}

uint8_t bisiesto( uint16_t year ){
	if(  ( (year % 4 ==0) && (year % 100 != 0) ) || (year % 400 == 0) ){
		return 1;
	}
	return 0;
}
	
void UART_AutoBaudRate(){

	DDRE = ~(1<<PE0);
	TCCR0A = 0;
	TCCR0B = (2<<CS00);
	
	while(PINE & 1<<PE0);
	TCNT0 = 0;

	while(!(PINE & 1<<PE0));
	TCCR0B =0;
	UBRR0 = TCNT0 -1;
}
