;Funcion en ensamblador llamado en C el cual recive un dato entero con signo mediante apuntador
;y realiza corriemiento a la derecha respetando el signo
;El tamaño del dato puede ser de 8,16,32 bits

;void shr_s(int32_t *dato, int tam_bytes)
;ejem
;a = -126 //a= 0xFF82
;shr_s((int32_t*)&a, sizeof(a)); //a = 0xFFC1

_shr_s proc
    push bp
    mov bp,sp

    mov cx,[bp+4]
    cmp cx,16
    ja @@uint32

    mov ax,[bp+6]

    sar ax,1
    jmp @@fin


@@uint32:
    mov ax,[bp+6]
    mov dx,[bp+8]

    shr dx,1
    rcr ax,1

@@fin:
    pop bp
    ret
endp