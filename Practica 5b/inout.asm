dosseg
.model small
.code

    public _inportb
    public _outportb
    public _getchar
    public _putchar

    ;unsigned char inportb(unsigned int port)
    _inportb proc
        push bp
        mov bp,sp

        mov dx,[bp+4]; port
        in al,dx

        pop bp
        ret
    _inportb endp

    ;void outportb(unsigned int port, unsigned data)
    _outportb proc
        push bp
        mov bp,sp

        mov dx,[bp+4]   ;port
        mov al,[bp+6]   ;data
        out dx,al

        pop bp
        ret
    _outportb endp

    _getchar proc
        push bp
        mov bp,sp

        mov dl,[bp+4]
        mov ah,08
        int 21h

        pop bp
        ret
    _getchar endp

    _putchar proc
        push bp
        mov bp,sp

        mov dl,[bp+4]
        mov ah,02
        int 21h

        pop bp
        ret
    _putchar endp

END