/*Utilizando la funcion getnibble escriba la funcion UART0_sendDataHEX para desplegar en terminal en formato hexadecimal 
el nibble byte o word que recibe como parametro
Si la funcio recibe tamaño no valido no envia dato*/

void UART0_senDataHEx(uint16_t dato, uint8_t tam){
    uint16_t mask = 0x8000,aux =0;
    uint8_t i ;
    if(tam >=0 && tam <= 4){
        for(i = tam; i=0; i--){
            aux = dato & mask;
            
        }
    }

    
}