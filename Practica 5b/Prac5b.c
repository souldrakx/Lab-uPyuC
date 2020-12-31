#define BYTE unsigned char
#define WORD unsigned int

#define PA 0x40
#define PB 0x41
#define PC 0x42
#define RCtr 0x43

#define PTOs_all_out 0x80
#define PTOs_all_in 0x9B

#define PTOs_PA_y_PB_out 0x89
#define PTOs_PB_y_PCl_out 0x98
#define PTOs_PA_y_PCl_out 0x8A
#define PTOs_PCl_y_PCh_out 0x92

void printBin( BYTE dato);
void puts(char *str);

void extern outportb(WORD puerto, BYTE data);
BYTE extern inportb(WORD puerto);

void Lumus( BYTE bits);
void SetClrbitport(WORD Setport, BYTE s_nbit, WORD Clrport, BYTE c_nbit);

void SetBitPort(WORD Puerto, BYTE num_bit);
void ClrBitPort(WORD Puerto, BYTE num_bit);
void NotBitPort(WORD Puerto, BYTE num_bit);
BYTE TestBitPort(WORD Puerto, BYTE num_bit);
void ReverseBitPort(WORD Puerto);

void delay(BYTE i);

char dato;

void main( void ){
    BYTE num =0,i,nbit=0;

    puts("Practica 5b\n\r");  /*imprimir mensaje */
    outportb(RCtr, PTOs_all_in); /* inicializar 8255 */

    for(i = 0; i < 8; i++){
        getchar();
        nbit = TestBitPort(PC,4);
        putchar(nbit + '0');
        nbit <<= i;
        num |= nbit;
        }
    while(1){
        Lumus(num);
    }
}

void Lumus( BYTE bits ){
    BYTE aux, b = 0;/*b = led a encender*/

    while(1){
        aux = bits & (1 << b); /*Si un dato en binario es 1 entra al ciclo y lo enciende*/
        /*La funcion recorrera cada bit del dato ingresado
        Este determinara por que puertos debe salir*/
        if(aux){
            if( (b == 0) || (b == 1) ){/*Los bits 4 y 5 saldran por los puestos PA y PB*/
                outportb(RCtr,PTOs_PA_y_PB_out);
                if(b == 0){
                    SetClrbitport(PB,2,PA,1);
                }
                else{
                    SetClrbitport(PA,1,PB,2);
                }
            }
            else if(  (b == 2) || (b == 3)  ){/*Los bits 2 y 3 saldran por los puestos PB y PC*/
                outportb(RCtr,PTOs_PB_y_PCl_out);
                if(b == 2){
                    SetClrbitport(PC,3,PB,2);
                }
                else{
                    SetClrbitport(PB,2,PC,3);
                }
            }
            else if( (b == 4) || (b == 5)){                               /*Los bits 0 y 1 saldran por los puestos PA y PC*/
                outportb(RCtr, PTOs_PA_y_PCl_out);
                if(b == 4){
                    SetClrbitport(PA,1,PC,3);
                }
                else{
                    SetClrbitport(PC,3,PA,1);
                }
            }

            else if( (b == 6) || (b == 7) ){
                outportb(RCtr, PTOs_PCl_y_PCh_out);
                if(b == 6){
                    SetClrbitport(PC,4,PC,3);
                }
                else{
                    SetClrbitport(PC,3,PC,4);
                }
            }
            
            delay(10);
        }
        
        if(b == 8){
            b=0;
        }
        else{
            b++;
        }
    }
}   

void SetClrbitport(WORD Setport, BYTE s_nbit, WORD Clrport, BYTE c_nbit){
    SetBitPort(Setport,s_nbit);
    ClrBitPort(Clrport,c_nbit);
}

void delay(BYTE i){
    while(i--);
}

/* función simple para desplegar un byte en formato binario */
void printBin( BYTE dato ){
    BYTE msk=0x80;
    do{
        putchar( (dato & msk) ? '1' : '0' );
        msk>>=1;
    }while( msk );
}

void puts(char *str){
    while(*str){
        putchar(*str++);
    }
}

void SetBitPort(WORD Puerto, BYTE num_bit){ 
    outportb( Puerto , inportb( Puerto )|( 0x01 << num_bit ) );
}

void ClrBitPort(WORD Puerto, BYTE num_bit){
    outportb( Puerto, ( inportb( Puerto ) & ~( 1 << num_bit ) ) );
}

void NotBitPort(WORD Puerto, BYTE num_bit){
    outportb( Puerto, ( inportb( Puerto ) ^ ( 1 << num_bit)));
}

BYTE TestBitPort(WORD Puerto, BYTE num_bit){
    if( ( inportb( Puerto ) & ( 1 << num_bit ) ) == 0 ){
        return 0;
    }
    return 1;
}

void ReverseBitPort(WORD Puerto){
    BYTE reverse = 0,i=0,j=0,aux=0;

    aux = inportb(Puerto);

    for (i = 0; i < 8; i++){
        if(aux & j){
            reverse |= 1;
        }
        else{
            reverse |= 0;
        }
        j <<= 1;
        reverse <<= 1;
    }
    outportb(Puerto,reverse);
}

