; Public definitions for:
;   void pokew(unsigned int segment, unsigned int offset, unsigned int data)
dosseg
.model small
.code
    public _putchar
    public _peek
    public _poke
    public _pokew

    _putchar proc
        push bp
        mov bp,sp

        mov dl,[bp+4]
        mov ah,02
        int 21h

        pop bp
        ret
    _putchar endp

    _peek proc
        push bp
        mov bp,sp
        push ds

        mov ax,[bp+4]   ;segment
        
        mov ds,ax       ;se mueve al segmento seleccionado
        mov bx,[bp+6]   ;offset
        
        mov al,byte ptr[bx]    ;return AX
        mov ah,0

        pop ds
        pop bp
        ret
    _peek endp

    _poke proc
        push bp
        mov bp,sp
        push ds

        mov ax,[bp+4]   ;segment
        mov ds,ax
        mov bx,[bp+6]   ;offset
        mov dl,[bp+8]   ;data
        mov byte ptr[bx],dl ;el dato se almacena en la direccion establecida

        pop ds
        pop bp
        ret
    _poke endp

    _pokew proc
        push bp
        mov bp,sp
        push ds

        mov ax,[bp+4]   ;segment
        mov ds,ax
        mov bx,[bp+6]   ;offset
        mov dx,[bp+8]   ;data
        mov word ptr[bx],dx ;el dato se almacena en la direccion establecida

        pop ds
        pop bp
        ret
    _pokew endp
END