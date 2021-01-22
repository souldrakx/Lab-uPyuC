#ifndef _TIMER0_H
#define _TIMER0_H

#include <inttypes.h>

/* Funci�n para inicializar el Timer0 y generar */
/* la temporizaci�n de 1 Sec. */
void Timer0_Ini ( void );

/* Funci�n para verificar bandera del segundo */
uint8_t Timer0_SecFlag ( void );

uint64_t millis();

#endif /* _TIMER0_H */