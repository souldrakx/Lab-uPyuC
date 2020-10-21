dosseg
.model small
.code

    public _putchar
    public _getchar

    _putchar proc
        push bp
        mov bp,sp

        mov dl,[bp+4]
        mov ah,02
        int 21h

        pop bp
        ret
    _putchar endp

    _getchar proc
        push bp
        mov bp,sp

        mov dl,[bp+4]
        mov ah,08
        int 21h

        pop bp
        ret
    _getchar endp
END