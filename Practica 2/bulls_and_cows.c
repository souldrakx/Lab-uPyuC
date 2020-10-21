/* To be defined in ASM as public procedures*/
extern void putchar(char data);
extern char getchar(void);

/*To be defined in C*/
void gets(char *str);
void puts(char *str);
void itoa(unsigned int number, char* str, unsigned char base);
unsigned int atoi(char *str);

typedef struct bullsAndCowsTag{
    unsigned bulls:4;
    unsigned cows:4;
} bullsAndCowsType;

bullsAndCowsType evalBullsAndCows(char *secrete, char *guess);

/*Measajes*/
char Inicio[] = {"Ingresa numero secreto de 4 digitos:\r\n"};
char msgGuess[] = {"\r\nIngresa tu numero de4 digitos:"};
/*Cambie la posicion del tablero ya que no mostraba los numeros dados por el usuario*/
char Board[] = {"\r\nGuesses:  Bulls:  Cows\n\r"}; 
char* EndGame[2] = {"You WIN!!!\n","You LOOSE :(\n"};

/*Cadenas*/;
char numsecrete[5];
char numguesse[5];
char cbulls[2];
char ccows[2];

#ifndef TEST_HARNESS
int main(void){
    bullsAndCowsType BCs;

    while(1){
        int fEG = 1;        /*flag EndGame*/
        int chances = 0;    

        puts(Inicio);
        gets(numsecrete);
        puts(msgGuess);

        puts(Board);
        /*Oportunidades para encontrar el numero secreto*/
        for(chances = 0; chances < 8; chances++){   
            
            gets(numguesse);
            BCs = evalBullsAndCows(numsecrete, numguesse);
            
            puts(numguesse);
            puts("\t  ");

            itoa(BCs.bulls, cbulls, 10);
            puts(cbulls);

            puts("\t  ");

            itoa(BCs.cows, ccows, 10);
            puts(ccows);

            puts("\r\n");            
            /**Si los bull son 4 cambia flag EndGame a 0 
             * para mostrar el mensaje de victoria
            */
            if(BCs.bulls == 4){
                fEG = 0;
                break;
            }
        }
        puts( EndGame[fEG] );
        puts("\n\r\n");
        getchar();
    }
    return 0;
}
#endif // main()

/**Proc gets
 * Recive una cadena vacia y almacena datos en dicha cadena 
 * Para finalizar el ingreso de datos a la cadena pulsar ENTER
*/
void gets(char *str){
    const unsigned char ENTER = 13, 
        BACKSPACE = 8, 
        MAXLine = 25; 
    char i = 0;
    int auxg = 0;

    while ( ( auxg = getchar() ) != ENTER ){
        
        if(auxg == BACKSPACE){
            if (i == 0){
                putchar(' ');
                putchar(BACKSPACE);
            }
            else{
                putchar(' ');
                putchar(BACKSPACE);
                str--;
                i--;
            }
        }
        else{
            if(i == MAXLine){
                putchar(BACKSPACE);
                putchar(' ');
                putchar(BACKSPACE);
            }
            else{
                /*Como el juego trata de encontar un numero secreto este no se muestra en pantalla por ese motivo
                get no mustra los datos a capturar*/
                /*putchar(auxg);*/
                *str = auxg;
                str++;
                i++;
            }
        }
    }
    *str = '\x0';
}

/**Proc puts
 * Recive una cadena la cual la muestra en pantalla
*/
void puts( char *str ){
    while( *str ){
        putchar( *str++ );
    }
}

/**Proc itoa
 * Convierte un valor numerico y lo guarda en una cadena
 * Se debe incluir la base a la que se desea guardar el valor numerico
*/
void itoa(unsigned int number, char* str, unsigned char base){
    char auxi = 0;
    char *straux = str;

    do{
        auxi = '0' + number % base;
        *(str++) = (auxi > '9') ? (auxi + 7) : auxi;
        number /= base;
    }while(number > 0);

    *(str--) = '\x0';

    while (str > straux){
        auxi = *straux;
        *straux = *str;
        *str = auxi;
        straux++;
        str--;
    }

}

/**Funcion atoi
 * Recive una cadena y lo retorna a su valor numerico en base 10
*/
unsigned int atoi(char *str){
    int auxa = 0;
    while ( ( *str ) && ( ( *str >= '0' ) && ( *str <= '9' ) ) ){
        auxa *= 10;
        (*str ) -= '0';
        auxa += *str;
        str++;
    }
    return auxa;
}

/**Funcion evalBullsAndCows
 * Compara 2 cadenas numericas siguiendo las reglas del juego Bulls and cows
 * si algun digito de la cadena secrete es igual a la cadena guess y comparten la misma posicion incrementa BULLS
 * si algun digito es igual pero no comparten la misma posicion incrementa COWS
*/
bullsAndCowsType evalBullsAndCows( char *secret, char *guess ){
    int i,j;
    bullsAndCowsType res;
    res.bulls = 0;
    res.cows = 0;

    for( i = 0; i < 4; i++ ){
        for( j = 0; j < 4; j++ ){
            if( secret[i] == guess[j] ){
                if( i == j ){
                    res.bulls++;
                }
                else{
                    res.cows++;
                }
            }
        }
    }
    return res;
}