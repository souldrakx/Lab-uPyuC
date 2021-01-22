; Corriemineto a un bit a la derecha SHR sobre dato de 16 apuntado por registro Z

.include "m2560def.inc"
start:

    ld r18,Z+
    ld r19,Z

    lsr r19
    ror r18

    st -Z,r19
    st Z,r18
    
    rjmp start
