#ifndef UART_H_
#define UART_H_

#define F_CPU 16000000ul
#define MyUBRRn(baud) ( ( ( F_CPU / 8 ) / baud ) - 1 )

void UARTn_Ini(uint8_t com, uint8_t parity, uint16_t baudrate, uint8_t stop, uint8_t sizeb);
void trasnmitByte(uint8_t data);
uint8_t reciveByte();
void printString(const char MyString[]);

void UART_gets(char *str);

#endif



