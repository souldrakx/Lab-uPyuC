/*Ejercicio 4.c*/

/*Programa 
1.Muestra YES en pantalla por UART una vez
2.Recive un dato por el puerto A  y lo transmite a la pantalla via serie
3.Recive por teclado un dato y lo muestra por b
Ini UART
baud = 9600,8bit,1stop,no par
*/
#include <avr/io.h>


int main(void){
	uint8_t i = 0;
	char *cad = "YES";
	
	/*Ini UART*/
	UCSR0B |= (1<<RXC0) | (1<<TXEN0);
	UCSR0C |= (3 << UCSZ00);
	UBRR0 = 103;
	/*Iniports*/
	DDRA = 0;
	DDRB = 0xFF;
	PORTB = 0;
	
	for(i = 0; i< 3;i++){
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = cad[i];		
	}

    while (1){

		
		
		while(!(UCSR0A & (1<<RXC0)));
		PORTB = UDR0;
		
		//if(PORTA > 0){
			while(! (UCSR0A & (1<<UDRE0)));
			UDR0 = PORTA;
			//UDR0 =0;
		//}
		
		//PORTB = dato;
		
    }
}

