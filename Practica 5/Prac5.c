#include "Timer.h"

#define BYTE unsigned char
#define WORD unsigned int

void UpdateClock( void );
void DisplayClock( void );
void PrintDec2d( BYTE );
void Delay( BYTE );

extern void putchar(char dato);
extern void poke(WORD segment, WORD offset, BYTE data);
void puts(char *str);

void SetClock( BYTE hora, BYTE minutos, BYTE segundos);

BYTE seg=0; /* para el manejo de los segundos */
BYTE min = 0;
BYTE hrs = 0;

void main(){
    SetClock(23,59,50);
    Timer_Ini(); /* inicialzaTimer de 1 segundo */
    while(1)
    {
        /* Verificación para actualizar el reloj */
        if(TimerSecFlag() )
        { /* Ha pasado un segundo? */
            UpdateClock(); /* actualiza y muestra el reloj */
            DisplayClock(); /* desplegar reloj en 0,0 */
            puts("\n\r");
            poke(0, 0xFFFF, seg);
            /* indicar en puerto */
        }
        /* otras cosas por hacer */
        Delay(100);
        /*putchar('.');  Imprime */
    }
}

void SetClock( BYTE hora, BYTE minutos, BYTE segundos){
    hrs = hora;
    min = minutos;
    seg = segundos-1;
}

void UpdateClock( void ){
    seg++;
    if(seg > 59){
        seg = 0;
        min++;
    }
    if(min > 59){
        min = 0;
        hrs++;
    }
    if(hrs > 23){
        hrs = 0;
    }

    /*falta minutos , horas etc. etc. */
} 

void DisplayClock( void ){
    /* imprimir reloj en formato "hh:mm:ss" */
    PrintDec2d(hrs);
    putchar(':');
    PrintDec2d(min);
    putchar(':');
    PrintDec2d(seg);
    
} 

void Delay( BYTE i){
    while(--i);
} 

void PrintDec2d( BYTE dato){
    putchar( dato/10 +'0'); /* Imprime decenas */
    putchar( dato%10 +'0'); /* Imprime unidades */
}

void puts(char *str){
    while (*str){
        putchar(*str++);
    }
    
}