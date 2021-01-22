#ifndef UART_H_
#define UART_H_

#define MyUBRR(baud) (((16000000/8)/baud)-1)
#define BUFFER_SIZE 64
#define MOD(n) ((n) & (BUFFER_SIZE - 1))
#define IF_BUFFER_EMPTY(buffer) (buffer.in_idx == buffer.out_idx)
#define IF_BUFFER_FULL(buffer) (buffer.in_idx == MOD(buffer.out_idx - 1))

enum Color{
	BLACK = 30,RED,GREEN,YELLOW,BLUE,PURPLE,CYAN,WHITE
};

typedef struct{
	
	char buffer[BUFFER_SIZE]; /* espacio reservado */
	volatile unsigned char in_idx; /* indice entrada (Head) */
	volatile unsigned char out_idx; /* indice entrada (tail) */
} ring_buffer_t;

// Prototypes
// Initialization
void UART_Ini(uint8_t com, uint32_t baudrate, uint8_t size, uint8_t parity, uint8_t stop);

// Send
void UART_puts(uint8_t com, char *str);
void UART_putchar(uint8_t com, char data);

// Received
uint8_t UART_available(uint8_t com);
char UART_getchar(uint8_t com );
void UART_gets(uint8_t com, char *str);

// Escape sequences
void UART_clrscr( uint8_t com );
void UART_setColor(uint8_t com, uint8_t color);
void UART_gotoxy(uint8_t com, uint8_t x, uint8_t y);

// Utils
void itoa(uint16_t number, char* str, uint8_t base);
uint16_t atoi(char *str);

#endif