#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "UART.h"

volatile ring_buffer_t buffer_rx0; //buffer receive
volatile ring_buffer_t buffer_tx0; //buffer transmit

volatile ring_buffer_t buffer_rx1;
volatile ring_buffer_t buffer_tx1;

volatile ring_buffer_t buffer_rx2;
volatile ring_buffer_t buffer_tx2;

volatile ring_buffer_t buffer_rx3;
volatile ring_buffer_t buffer_tx3;

volatile ring_buffer_t buffer_rxn;
volatile ring_buffer_t buffer_txn;

void UART0Buf_Ini(){
	buffer_rx0.in_idx=0;
	buffer_rx0.out_idx=0;
	buffer_tx0.in_idx=0;
	buffer_tx0.out_idx=0;

	buffer_rx1.in_idx=0;
	buffer_rx1.out_idx=0;
	buffer_tx1.in_idx=0;
	buffer_tx1.out_idx=0;

	buffer_rx2.in_idx=0;
	buffer_rx2.out_idx=0;
	buffer_tx2.in_idx=0;
	buffer_tx2.out_idx=0;

	buffer_rx3.in_idx=0;
	buffer_rx3.out_idx=0;
	buffer_tx3.in_idx=0;
	buffer_tx3.out_idx=0;
}

// Initialization
void UART_Ini(uint8_t com, uint32_t baudrate, uint8_t size, uint8_t parity, uint8_t stop){

    uint16_t *UBRRn;
    uint8_t *UCSRnA, *UCSRnB, *UCSRnC;

    if(com == 3){
        //UART3 se encuentra a partir de direccion 0x130
        UCSRnA = (uint8_t *)0x130;
        UCSRnB = (uint8_t *)0x131;
        UCSRnC = (uint8_t *)0x132;
        UBRRn = (uint16_t *)0x134; 
    }
    else{
        //UART0 ..  UART2 se encuentra cada 8 bits
        UCSRnA = (uint8_t *)0xC0 +(8*com);
        UCSRnB = (uint8_t *)0xC1 +(8*com);
        UCSRnC = (uint8_t *)0xC2 +(8*com);
        UBRRn = (uint16_t *)0xC4 +(8*com);
    }

      
    if(parity == 1){  //no parity = 00; reservado = 01; par = 10; impar = 11.
        parity = 3;
    } 

	//*UBRRn = 16;
	*UBRRn = MyUBRR(baudrate);

    *UCSRnA |= (1 << U2X0);

    *UCSRnB = (3<<TXEN0) | ((1<<RXCIE0) & (~(1<<UCSZ02))); 
    // (3<<TXEN0) = Reciver and Transmiter Enable 
    // (~(1<<UCSZ02)) = desactivado para funcionar con 8 bit o menos

    *UCSRnC = (parity<<UPM00) | ((stop-1)<<USBS0) | ((size-5)<<UCSZ00);
    // parity<<UPM00 = parity mode
    //(stop-1)<<USBS0 = stop bit select
    //(size-5)<<UCSZ00 = Character ndatos
	
	    UART0Buf_Ini();
	    sei();
}

// Send
void UART_puts(uint8_t com,char *str){
	while( *str )
	UART_putchar(com, *str++ );
}

void UART_putchar(uint8_t com, char data){
	switch(com){
		case 0:
			while(IF_BUFFER_FULL(buffer_tx0));
		
			if(IF_BUFFER_EMPTY(buffer_tx0)){
				buffer_tx0.buffer[buffer_tx0.in_idx++] = data;
				UCSR0B |= (1<<UDRIE0);
			}
			else{
				buffer_tx0.buffer[buffer_tx0.in_idx++] = data;
			}

		break;
		case 1:
			while(IF_BUFFER_FULL(buffer_tx1));
			
			if(IF_BUFFER_EMPTY(buffer_tx1)){
				buffer_tx1.buffer[buffer_tx1.in_idx++] = data;
				UCSR1B |= (1<<UDRIE1);
			}
			else{
				buffer_tx1.buffer[buffer_tx1.in_idx++] = data;
			}
		break;
		case 2:
			while(IF_BUFFER_FULL(buffer_tx2));
			
			if(IF_BUFFER_EMPTY(buffer_tx2)){
				buffer_tx2.buffer[buffer_tx2.in_idx++] = data;
				UCSR2B |= (1<<UDRIE2);
			}
			else{
				buffer_tx2.buffer[buffer_tx2.in_idx++] = data;
			}
		break;
		case 3:
			while(IF_BUFFER_FULL(buffer_tx3));
			
			if(IF_BUFFER_EMPTY(buffer_tx3)){
				buffer_tx3.buffer[buffer_tx3.in_idx++] = data;
				UCSR3B |= (1<<UDRIE3);
			}
			else{
				buffer_tx3.buffer[buffer_tx3.in_idx++] = data;
			}
		break;
	}
}

// Received
uint8_t UART_available(uint8_t com){ //Función que retorna 1 si existe(n) dato(s) en la cola circular.
	switch(com){
		case 0:
		return (IF_BUFFER_EMPTY(buffer_rx0) ? 0 : 1);
		break;
		case 1:
		return (IF_BUFFER_EMPTY(buffer_rx1) ? 0 : 1);
		break;
		case 2:
		return (IF_BUFFER_EMPTY(buffer_rx2) ? 0 : 1);
		break;
		case 3:
		return (IF_BUFFER_EMPTY(buffer_rx3) ? 0 : 1);
		break;
	}
	return 0;
}


char UART_getchar( uint8_t com ){ //Funciona toma el dato correspondiente a salir de la cola circular
	char data = 0;
	switch(com){
		case 0:
			while(UART_available(0));
			data = buffer_rx0.buffer[buffer_rx0.out_idx++];
		break;
		case 1:
			while(UART_available(1));
			data = buffer_rx1.buffer[buffer_rx1.out_idx++];
		break;
		case 2:
			while(UART_available(2));
			data = buffer_rx2.buffer[buffer_rx2.out_idx++];
		break;
		case 3:
			while(UART_available(3));
			data = buffer_rx3.buffer[buffer_rx3.out_idx++];
		break;
	}
	return data;
}

void UART_gets(uint8_t com,char *str){
    	unsigned char aux;
    	unsigned int i=0;
    	do{
	    	aux = UART_getchar(com);
	    	if( (i<=18)&&(aux!=8)&&(aux!=13) )	//validacion menor al fin del arreglo, backspace y enter
	    	{
		    	UART_putchar(com,aux);
		    	*str++ = aux;
		    	i++;
	    	}
	    	if( (aux==8) && (i>0) )		//validacion backspace
	    	{
		    	UART_putchar(com,aux);
		    	UART_putchar(com,' ');
		    	UART_putchar(com,aux);
		    	*str--='\0';
		    	i--;
	    	}
    	}while(aux != 13);
    	*str = '\0';
    }

// Escape sequences
void UART_clrscr( uint8_t com ){
	UART_puts(com,"\033[2J");
}

void UART_setColor(uint8_t com,uint8_t color){
	char colors[8];

	itoa(color,colors,10);
	UART_puts(com,"\033[");
	UART_puts(com,colors);
	UART_puts(com,";40m");
}

void UART_gotoxy(uint8_t com,uint8_t x, uint8_t y){
	char px[8],py[8];

	itoa(x,px,10);
	itoa(y,py,10);
	UART_puts(com,"\033[");
	UART_puts(com,py);
	UART_puts(com,";");
	UART_puts(com,px);
	UART_puts(com,"f");
}

// Utils
void itoa(uint16_t number, char* str, uint8_t base){
	uint16_t aux2=0;
	uint8_t i=0,j=0;

	if(number==0){
		aux2 += 48;
		str[i++] = aux2;
		str[i]='\x0';
	}

	while(number > 0){

		aux2 = number%base;
		if(aux2 > 9){
			aux2+=7;
		}

		aux2 += 48;
		str[i++] = aux2;
		number/=base;
		str[i]='\x0';
	}
	
	i--;
	while (i > j)
	{
		aux2 = str[j];
		str[j] = str[i];
		str[i] = aux2;
		j++;
		i--;
	}
}

uint16_t atoi(char *str){
	uint16_t aux=0;
	
	while((*str) && (*str >= '0' && *str <= '9')){
		aux*=10;
		(*str)-=48;
		aux+=(*str);
		str++;
	}
	return aux;
}

// ISRs
//ISR( USARTx_RX_vect )
ISR( USART0_RX_vect ){ //Rutina de servicio de interrupción para el evento de recepción completa. Esta rutina inserta a la cola circular el dato que fue recibido por el UARTx.
	while(IF_BUFFER_FULL(buffer_rx0));
	buffer_rx0.buffer[buffer_rx0.in_idx++] = UDR0;
}

ISR( USART1_RX_vect ){
	while(IF_BUFFER_FULL(buffer_rx1));
	buffer_rx1.buffer[buffer_rx1.in_idx++] = UDR1;

}

ISR( USART2_RX_vect ){
	while(IF_BUFFER_FULL(buffer_rx2));
	buffer_rx2.buffer[buffer_rx2.in_idx++] = UDR2;
	
}

ISR( USART3_RX_vect ){
	while(IF_BUFFER_FULL(buffer_rx3));
	buffer_rx3.buffer[buffer_rx3.in_idx++] = UDR3;
	
}

//ISR( USARTx_UDRE_vect )
ISR( USART0_UDRE_vect ){
	if(IF_BUFFER_EMPTY(buffer_tx0)){
		UCSR0B &= (~(1<<UDRIE0));
	}
	else{
		UDR0=buffer_tx0.buffer[buffer_tx0.out_idx++];
		
	}
}

ISR( USART1_UDRE_vect ){
	if(IF_BUFFER_EMPTY(buffer_tx1)){
		UCSR1B &= (~(1<<UDRIE1));
	}
	else{
		UDR1=buffer_tx1.buffer[buffer_tx1.out_idx++];
		
	}
}

ISR( USART2_UDRE_vect ){
	if(IF_BUFFER_EMPTY(buffer_tx2)){
		UCSR2B &= (~(1<<UDRIE2));
	}
	else{
		UDR2=buffer_tx2.buffer[buffer_tx2.out_idx++];
		
	}
}

ISR( USART3_UDRE_vect ){
	if(IF_BUFFER_EMPTY(buffer_tx3)){
		UCSR3B &= (~(1<<UDRIE3));
	}
	else{
		
		UDR3=buffer_tx3.buffer[buffer_tx3.out_idx++];

	}
}
