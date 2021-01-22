/*Considere la siguente declaracion de tipo dato implementar las siguentes funcion insertar donde N = 128*/

#define BUFFER_SIZE 64

typedef struct{
	
	char buffer[BUFFER_SIZE]; /* espacio reservado */
	volatile unsigned char in; /* indice entrada (Head) */
	volatile unsigned char out; /* indice entrada (tail) */
} ring_buffer_t;

void insertar( ring_buffer_t *cola, char dato);
unsigned char available(ring_buffer_t *cola);
char remover(ring_buffer_t *cola);

void insertar(ring_buffer_t *cola, char dato){
    cola->buffer[cola->in++] = dato;
}

unsigned char available(ring_buffer_t *cola){
    if(cola->in == cola->out){
        return 0;
    }
    return 1
}

char remover(ring_buffer_t *cola){
    char aux;
    aux = cola->buffer[cola->out++];
    return aux;
}