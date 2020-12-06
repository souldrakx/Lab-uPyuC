#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#define BUFFER_SIZE 64

#define MYUBRR(baud) ( ( ( 16000000ul/16 ) / baud )-1 )
#define MOD(n) ( ( n ) & ( BUFFER_SIZE-1 ) )
#define IF_BUFFER_EMPTY(buffer) ( buffer.in_idx == buffer.out_idx )
#define IF_BUFFER_FULL(buffer) ( buffer.in_idx == MOD(buffer.out_idx - 1) )
/*
#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define PURPLE 35
#define CYAN 36
#define WHITE 37
*/
typedef struct{
	char buffer[BUFFER_SIZE]; /* espacio reservado */
	volatile unsigned char in_idx; /* indice entrada (Head) */
	volatile unsigned char out_idx; /* indice entrada (tail) */
} ring_buffer_t;

// Prototypes
ring_buffer_t buffer_rx0;
ring_buffer_t buffer_tx0;

ring_buffer_t buffer_rx1;
ring_buffer_t buffer_tx1;

ring_buffer_t buffer_rx2;
ring_buffer_t buffer_tx2;

ring_buffer_t buffer_rx3;
ring_buffer_t buffer_tx3;

// Initialization
void UART_Buffer_Ini(){
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

void UART_Ini(uint8_t com, uint16_t baudrate, uint8_t size, uint8_t parity, uint8_t stop){
	sei();
	
	uint8_t *UCSRnA, *UCSRnB, *UCSRnC;
	uint16_t *UBRRn;
	
	switch(com){
		case 0 :
			case 1:
				case 2:
				UCSRnA = (uint8_t*)0xC0 +( 8 * com);
				UCSRnB = (uint8_t*)0xC1 +( 8 * com);
				UCSRnC = (uint8_t*)0xC2 +( 8 * com);
				UBRRn = (uint16_t*)0xC4 +( 8 * com);
				break;
		
		case 3:
			UCSRnA = (uint8_t*)0x130;
			UCSRnB = (uint8_t*)0x131;
			UCSRnC = (uint8_t*)0x132;
			UBRRn = (uint16_t*)0x134;
			break;
	}
	
	if(parity == 1){
		parity = 3;
	}
	
	
	
	*UBRRn = MYUBRR(baudrate);
	
	*UCSRnA = 0;
	*UCSRnB = (1 << RXEN0) | (1 << TXEN0) | (1<<RXCIE0) & ~(1 << UCSZ02);
	*UCSRnC = ( (size-5) << UCSZ00 ) | (parity << UPM00) | ((stop-1) << USBS0);
	
}

// Send
void UART_puts(uint8_t com, char *str){
	while(*str){
		UART_putchar(com, *str++);
	}
}

void UART_putchar(uint8_t com, char data){
	switch(com){
		case 0:
			while ( IF_BUFFER_FULL(buffer_tx0) );
			
			buffer_tx0.buffer[buffer_tx0.in_idx++] = data;
			UCSR0B |= (1 << UDRIE0);
		break;
		
		case 1:
			while ( IF_BUFFER_FULL(buffer_tx1) );
			
			buffer_tx1.buffer[buffer_tx1.in_idx++] = data;
			UCSR1B |= (1 << UDRIE1);
		break;
		
		case 2:
			while ( IF_BUFFER_FULL(buffer_tx2) );
			
			buffer_tx2.buffer[buffer_tx2.in_idx++] = data;
			UCSR2B |= (1 << UDRIE2);
		break;
		
		case 3:
			while ( IF_BUFFER_FULL(buffer_tx3) );
			
			buffer_tx3.buffer[buffer_tx3.in_idx++] = data;
			UCSR3B |= (1 << UDRIE3);
		break;
	}
}

// Received
uint8_t UART_available(uint8_t com){
	switch(com){
		case 0:
			return (IF_BUFFER_EMPTY(buffer_tx0) ? 0 : 1);
		break;
		case 1:
			return (IF_BUFFER_EMPTY(buffer_tx1) ? 0 : 1);
		break;
		case 2:
			return (IF_BUFFER_EMPTY(buffer_tx2) ? 0 : 1);
		break;
		case 3:
			return (IF_BUFFER_EMPTY(buffer_tx3) ? 0 : 1);
		break;
	}
	return -1; 
}

char UART_getchar(uint8_t com ){
	char data =0;
	switch(com){
		case 0:
			while(IF_BUFFER_EMPTY(buffer_rx0));
			data = buffer_rx0.buffer[buffer_rx0.out_idx++];
		break;
		
		case 1:
			while(IF_BUFFER_EMPTY(buffer_rx1));
			data = buffer_rx1.buffer[buffer_rx1.out_idx++];
		break;
		
		case 2:
			while(IF_BUFFER_EMPTY(buffer_rx2));
			data = buffer_rx2.buffer[buffer_rx2.out_idx++];
		break;
		
		case 3:
			while(IF_BUFFER_EMPTY(buffer_rx3));
			data = buffer_rx3.buffer[buffer_rx3.out_idx++];
		break;
	}
	return data;	
}

void UART_gets(uint8_t com, char *str){
	unsigned char aux;
	unsigned int i =0;
	do {
		aux = UART_getchar(com);
		if ( (i < 18) && (aux!=8) && (aux!=13) ){
			UART_putchar(com, aux);
			*str++ = aux;
			i++;
		}
		if((aux == 8) && (i>0)){
			UART_putchar(com,'\b');
			UART_putchar(com,' ');
			UART_putchar(com,8);
			*str--='\0';
			i--;
		}
	} while (aux != 13);
	*str = '\0';
}

// Escape sequences
void UART_clrscr( uint8_t com ){
	UART_puts(com, "\033[2J");	
}

void UART_setColor(uint8_t com, uint8_t color){
	char colors[8];
	
	itoa(color,colors,10);
	UART_puts(com, "\033[");
	UART_puts(com, colors);
	UART_puts(com, ";40m");	
}

void UART_gotoxy(uint8_t com, uint8_t x, uint8_t y){
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
