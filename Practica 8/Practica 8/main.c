#include <avr/io.h>
#include "UART.h"

void portini();

int main( void ){
	
	char cad[20];
	char cadUart3[20];
	uint16_t num;
	
	portini();
	
	UART_Ini(0,12345,8,1,2);
	UART_Ini(2,115200,8,0,1);
	UART_Ini(3,115200,8,0,1);
	while(1){
		
		UART_getchar(0);
		UART_clrscr(0);
		
		UART_gotoxy(0,2,2);
		UART_setColor(0,YELLOW);
		UART_puts(0,"Introduce un numero:");
		
		UART_gotoxy(0,22,2);
		UART_setColor(0,GREEN);
		UART_gets(0,cad);
		// -------------------------------------------
		// Cycle through UART2->UART3
		UART_puts(0,"\n\r");
		UART_puts(0,cad);
		UART_puts(0,"\n\r");
		UART_gets(0,cadUart3);
		UART_gotoxy(0,5,4);
		UART_puts(0,cadUart3);
		// -------------------------------------------
		num = atoi(cad);
		itoa(num,cad,16);
		
		UART_gotoxy(0,5,5);
		UART_setColor(0,BLUE);
		UART_puts(0,"Hex: ");
		UART_puts(0,cad);
		itoa(num,cad,2);
		
		UART_gotoxy(0,5,6);
		UART_puts(0,"Bin: ");
		UART_puts(0,cad);
	}
}
void portini(){
	DDRJ = 0;
	DDRH = 0xFF;
}
