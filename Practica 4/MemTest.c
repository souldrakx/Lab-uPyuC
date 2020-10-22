#define BYTE unsigned char
#define WORD unsigned int

/*External definitions*/
extern BYTE peek(WORD segment, WORD offset);
extern void poke(WORD segment, WORD offset, BYTE data);
extern char getchar( void );
extern void putchar( char dato );

/*Funciones de apoyo*/
void puts(char *str);
void printdec (BYTE dato);
void printHex(WORD dato);

/*Test de memoria*/
BYTE Datos(WORD segmento, WORD offset);
BYTE Direcciones(WORD segmento, WORD offset, BYTE lineas);
void veriDir(WORD segmento, WORD dirini, WORD dirfin);

/*Mensajes*/
char *msggood = ":Bien\r\n";
char *msgbad = ":Error\r\n";
char *msgLin = "Linea: ";
char *msgfatal = "Fallo catastrofico\r\n";
char *msgBData = "BUS DE DATOS\r\n";
char *msgBDir = "BUS DE DIRECCIONES\r\n";

/*segmento para probar la Memoria*/
WORD segini = 0x600;
WORD segespejo = 0x400;

WORD testdirini = 0x700;
WORD testdirfin = 0x710;

char lines = 11;

/*Flags*/
char Data,Dir;


int main(void){
    while (1){
        puts("\r\nDir Inicial 6000h\r\n");

        veriDir(segini,testdirini,testdirfin);
        getchar();

        puts("\r\nDir espejo 4000h\r\n");

        veriDir(segini,testdirini,testdirfin);
        getchar();

        puts("\r\nDir extra A000h\r\n");

        Datos(0xA00,0);
        Direcciones(0xA00,0,lines);
        getchar();
    }
    
    return 0;
}

/*Funcion Datos
 * 
 * Prueba el bus de datos mediante la prueba de walking 1´s en 
 * una direccion especifica
 * 
 * La funcion retorna 0 si la prueba falla y 1 se la prueba funciona
 * 
 * 
*/
BYTE Datos(WORD segmento, WORD offset){
    BYTE dato = 0,
        fstate = 1,
        i = 0,
        failData = 0;
    
    puts( msgBData );

/*se preuba cada una de las lineas de bus de datos en una sola direccion.
    En cada ciclo se recorre el valor de los datos hasta que este execede y vuelve 0
    00000001
    00000010
    */
    for (dato = 1; dato != 0 ; dato = ( dato << 1 ) ){
        poke( segmento, offset, dato );

        /*Despues se verifica y si el valor ingresado no es el mismo que se encuentra en la memoria
        se activara un bit en la variable faildata el cual al final determinara que lineas fallaron*/
        if(peek(segmento, offset) != dato ){
            failData |= dato;
        }
    }

/*Ciclo que visualiza que lineas fallaron*/
    while (i < 8)
    {
        puts(msgLin);
        printdec( i );
        /*Si algun bit esta activado mostrara el mensaje de error y
        volvera 0 la bandera fstate*/
        if( failData & ( 1 << i )){
            puts(msgbad);
            fstate = 0;
        }

        else{
            puts(msggood);
        }

        puts("\r\n");
        i++;

    }
    
    return fstate;
}

/*Funcion Direcciones
 * 
 * Prueba el bus de direcciones mediante la prueba de walking 1´s en 
 * con un patron especifico
 * 
 * La funcion retorna 0 si la prueba falla y 1 se la prueba funciona
 * 
 * 
*/
BYTE Direcciones(WORD segmento, WORD offset, BYTE lineas){
    WORD dir = 0,
        failDir = 0,
        i = 0;

    BYTE patron = 0x55,
        antipatron = 0xAA,
        fstate = 1;

    puts(msgBDir);

    /*Se escribira con un patron conocido todas los datos de la lineas de direcciones*/
    for(dir = 1; dir < ( 1 << lineas ); dir = ( dir << 1 ) ){
        poke(segmento, offset + dir, patron);
    }
    /*Comprueba si hay bits de dirección atascados en alto*/
    poke(segmento, offset, antipatron);

    for(dir = 1; dir < (1 << lineas); dir = ( dir << 1 ) ){
        /*Se verifica que el patron ingresado sea el correcto 
        si no lo es activara un bit el cual determinara que linea fallo*/
        if(peek(segmento,offset+ dir) != patron ){
            failDir |= dir;
        }
    }

    /*ciclo que visualiza si que lineas fallaron*/
    while (i < lines) {

        puts(msgLin);
        printdec(i);
        /*Si algun bit esta activado mostrara el mensaje de error y
        volvera 0 la bandera fstate*/
        if (failDir & (1 << i)){
            puts(msgbad);
            fstate = 0;
        }       
        else{
            puts(msggood);
        }

        puts("\r\n");
        i++;
        }

    return fstate;
}

/**Procedimeinto VeriDir
 * 
 * Prueba las direcciones 1 por 1 dadas por dirini y dirfin
 * 
 */
void veriDir(WORD segmento, WORD dirini, WORD dirfin){
    WORD i = 0;
    BYTE patron = 0x55;
    /*Ciclo para pueva de direcciones*/
    for(i = dirini; i< dirfin; i++){
        /*Se ingresa un patron a esa direccion especifica */
        poke(segmento,i,patron);
        printHex(i);
        /*Se comprueba que dicho patron se encuentra en la direccion
        el cual mostrara un mensaje de error si no se enncuentra dicho patron */
        if (peek(segmento,i) != patron)
        {
            puts(msgbad);
        }
        else
        {
            puts(msggood);
        }
    }
}

/**Procedimiento Puts
 * Imprime una cadena
*/
void puts(char *str){
    while( *str ){
        putchar( *str++ );
    }
}

/**Procedimineto printdec
 * Imprime un dato en base 10
*/
void printdec (BYTE dato){
    putchar( ( dato / 100 ) + 0x30 );
    dato %= 100;
    putchar( ( dato / 10 ) + 0x30 );
    putchar( ( dato % 10 ) + 0x30 );
}

/**Procedimineto printdec
 * Imprime un dato en hexadecimal
*/
void printHex(WORD dato) {
	
    int i, aux;
	for(i=12;i>=0;i=i-4){

		aux=(dato>>i) & 0xF;
        aux += (aux<10 ? 0x30: 0x37);
        putchar(aux);
	}
}