//Funcion en c escribir un bit en una determinada posicion de bit de un puerto o direccion de memoria

void Writebit(uint8_t *dir, uint8_t nbit, uint8_t bit){
    if(nbit >= 0 && nbit <= 7){
        if(bit){
            dir |= (1<< nbit);
        }
        else{
            dir &= ~(1<<nbit);
        }
    }
}