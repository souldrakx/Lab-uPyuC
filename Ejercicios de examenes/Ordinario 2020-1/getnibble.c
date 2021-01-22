/*funcion en C que retorna en ASCII el nibble menos significativi de un byte que recibe como parametro
char getnibble(uint8_t dato);

x = getnibble(0x3F); x = 'F'
*/

char getnibble(uint8_t dato){
    uint8_t mask = 0x0F,aux=0;

    dato &= mask;

    if(dato > 9){
        dato += 0x07;
    }

    aux = dato + '0';

    return aux ;
}