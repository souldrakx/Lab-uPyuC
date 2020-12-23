#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"

/***********************************************************************
*Inicializacion del UARTn
* com = uartn
* parity = 0 no paridad, 1 = par, 2 impar
* baudrate = velocidad de transmicion
* stop = stop bit
* sizeb = tamanio del dato(5-9)
************************************************************************/
void UARTn_Ini(uint8_t com, uint8_t parity, uint16_t baudrate, uint8_t stop, uint8_t sizeb){
	
	uint8_t *UCSRnA = 0 , *UCSRnB = 0, *UCSRnC = 0;
	uint16_t *UBRRn = 0;
	
	/*Se asignara la direccion al UARTn (n = 0,1,2,3) dada por la variable com*/
	switch(com){
		case 0:
			case 1:
				case 2:
				UCSRnA = (uint8_t *) 0xC0 + (8*com);
				UCSRnB = (uint8_t *) 0xC1 + (8*com);
				UCSRnC = (uint8_t *) 0xC2 + (8*com);
				UBRRn = (uint16_t *) 0xC4 + (8*com);
				break;
		case 3:
			UCSRnA = (uint8_t *) 0x130;
			UCSRnB = (uint8_t *) 0x131;
			UCSRnC = (uint8_t *) 0x132;
			UBRRn = (uint16_t *) 0x134;
	}
	/*Parity solo puede ser 0 no paridad,2 par,3 impar; como el registro 01 esta reservado se modifica el valor de paridad a 3*/
	if(parity == 1){
		parity = 3;
	}
	
	*UBRRn = MyUBRRn(baudrate);
	
	/*USART a 2 velocidad*/
	*UCSRnA = (1<<U2X0);
	
	/*Transmitir y recivir activados*/
	*UCSRnB = (1<<RXEN0) | (1<<TXEN0);
	
	/*Paridad, Stop bit, tamano del dato(size) (Para datos de 9 bits activar bit en UCSRnB 1<< UCSZn2)*/
	*UCSRnC = (parity << UPM00) | ( ( stop - 1 ) << USBS0) | ((sizeb - 5) << UCSZ00);
	sei();
}
/*Funciones exclusivas para UART0*/
/*putchar(char)*/
void trasnmitByte(uint8_t data){
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = data;
}

/*getchar()*/
uint8_t reciveByte(){
	loop_until_bit_is_set(UCSR0A,RXC0);
	return UDR0;
}

/*puts(cad)*/
void printString(const char MyString[]){
	uint8_t i = 0;
	while (MyString[i]){
		trasnmitByte(MyString[i++]);
	}
}
/*gets(cad)*/
void UART_gets(char *str){
uint8_t aux;
	
	do {
		aux = reciveByte();
		if (aux != 13){
			*str++ = aux;
		}
	} while (aux != 13);
	//*str = '\0';
}


