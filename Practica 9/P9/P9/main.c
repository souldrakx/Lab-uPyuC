#include <avr/io.h>
#include "UART.h"
#include "Timer0.h"

char *cad;

/* incluir lo necesario para hacer uso de UART0 */
//void UART0_AutoBaudRate(void);
int main(){
	/* llamar a función para inicializar puertos E/S */
	/* llamar a función para inicializar UART0 */

	UART_AutoBaudRate();
	UART_clrscr(0);
	UART_gotoxy(0,5,1);
	UART_puts(0,"Autobauding done. UBRR0=");
	itoa(UBRR0,cad,10);
	UART_puts(0,cad);
	UART_puts(0,'\n\r');

	Timer0_Ini(); /* Inicializar contador de millis.*/
	//Clock_Ini(1583049590000);

	while(1)
	{ /* == main loop == */
		if( Timer0_SecFlag() ){ /* ¿ha pasado un Segundo? */
			UART_gotoxy(0,5,2);
			UART_putchar(0,'x');
			//Clock_Display();
			UART_gotoxy(0,5,3);
		}
		} /* fin del loop principal */
		return 0; /* <-- no se llega aquí */
	}