.model tiny

   ;----- Insert INCLUDE "filename" directives here
   ;----- Insert EQU and = equates here
   
   locals
   
.data
      
      msgGet 	DB  'Introduce the secrete 4 digits:',10,13,0
	  msgBoard 	DB  'Bulls: ',9,'Cows: ',9,'Guesses:',10,13,0
	  msgGuess	DB 	'Guess the 4 digit sequence',10,10,13,0
	  msgWin	DB 	'You win!',10,10,13,0
	  msgLoose	DB 	'You LOOSE!',10,10,13,0
	  done		DB 	'Done.',10,13,0
	  new_line	DB 	10,13,0
	  secrete  	DB  5 dup(0)
	  guess    	DB  5 dup(0)

.code
             org 100h
	
;*************************************************************
;  Procedimiento principal
;*************************************************************	
	principal proc
            mov sp,0fffh	; inicializa SP (Stack Pointer)
			;mov ax,@data  	; inicializar DS al la direccion
			;mov ds,ax    	; del segmento de datos (.DATA)
			
			mov si, offset secrete 
			mov di, offset guess 
						
			mov dx, offset msgGet
			call puts
			mov dx,si
			call getDigits
			
			mov dx, offset done
			call puts
			mov dx, offset msgGuess
			call puts
			
			mov dx, offset msgBoard
			call puts

			;oportunidades de juego*
			mov cx,8

		@@nextGuess:
			mov dx,di
			call getDigits
			call evalGuess
			call printHint
			mov dx, offset new_line
			call puts

			cmp al,4
			je @@win
			loop @@nextGuess

			mov dx, offset msgLoose
			call puts
			jmp @@sigue

		@@win:
			mov dx,offset msgWin
			call puts

		@@sigue:
			jmp @@sigue
			
			ret						; nunca se llega aqu�
			endp

			
;***************************************************************
;  procedimientos
;***************************************************************            
    putchar	proc
			push ax
			push dx
			mov dl,al
			mov ah,2				; imprimir caracter DL
			int 21h					; usando servico 2 (ah=2)
			pop dx					; del int 21h
			pop ax
			ret
			endp
	
	getch	proc
			mov ah,8				; no echo
			int 21h				
			ret
			endp
	
	getche	proc
			mov ah,1				
			int 21h				
			ret
			endp
			
	puts	proc
			push ax
			push bx
			
			mov  bx,dx
		@@nxt: 
			mov  al,[bx]
			cmp  al,0
			je   @@end
			call putchar
			inc  bx
			jmp  @@nxt
			
		@@end: 
			pop  bx
			pop  ax
			ret
			endp
	
	getDigits proc
			push ax
			push bx
			push cx
			
			mov bx,dx
			mov cx,4
		@@gnxt: 
			call getch
			cmp al,'0'
			jb @@gnxt
			cmp al,'9'
			ja @@gnxt
			mov [bx],al
			inc bx
			loop  @@gnxt
			
			pop cx
			pop bx
			pop ax
			ret
			endp
	
	printHint proc
			push ax
			push dx
			
			add al,'0'
			call putchar ; print Bulls
			
			mov al,9
			call putchar ; tab
			
			mov al, ah
			add al,'0'
			call putchar ; print Cows
			
			mov al,9
			call putchar ; tab
			
			mov dx,di
			call puts
			
			pop dx
			pop ax
			ret
			endp

;***************************************************************
;  	Procedure that evaluates the Bulls (correct number in the correct place)
;  	and Cows (correct number but incorrect position) based on the two arrays
;	given by SI (secrete) and DI (guess).
;	Returns Bulls in AL, and Cows in AH	
;***************************************************************   
;Para determinar como se mueve en la cadena se utiliza cx
;ch = secrete , cl = guess         
	evalGuess proc
			push bx
			push cx
			push dx
			push di
			push si

			mov ax,0
			mov cx,0
			mov bx,di
			mov dx,si

;inicio
;Compara cada uno de los digitos de guess con el numero secrete
;si es menor a 4 el procedimiento seguira normalmente
;en caso contrario saltara a @@reset
		@@inicio:
			cmp cl,4
			jb @@compara
			jmp @@reset

;Comparar
;guarda las posiciones de los numero (cx) en la pila
;despues comparar los digitos de secret con guess
;encaso de ser iguales saltara a @@iguales caso contrario a @@noiguales
		@@compara:
			push cx
			mov ch, byte ptr[si]
			cmp ch, byte ptr[di]
			jne @@noiguales
			je @@iguales

;noiguales
;En caso de no se iguales recupera las posiciones de los numeros 
;para duespues recorrer una posicion en el numero guess(cl) y volver al inicio
		@@noiguales:
			pop cx
			inc di
			inc cl
			jmp @@inicio

;iguales
;En caso de ser iguales se recuperara la posicion de los numeros
;y se compara las posiciones de los numeros secrete(ch) y guess(cl)
;si son iguales salta a @@toro en caso contrario salta a @@vaca
		@@iguales:
			pop cx
			push cx
			cmp cl,ch
			je @@toro
			jne @@vaca

;toro
;Recupera las posiciones de las posiciones de los numeros
;incrementa el valor de los toros(AL)
;como ya encontro una similitud y ya no es necesario verificar otro digito se incrementa la posicion de guess(cl)
;y vuelve a inicio
		@@toro:
			pop cx
			inc al
			inc cl
			inc di
			jmp @@inicio

;toro
;Recupera las posiciones de las posiciones de los numeros
;incrementa el valor de las vacas(AH)
;como ya encontro una similitud y ya no es necesario verificar otro digito se incrementa la posicion de guess(cl)
;y vuelve a inicio

		@@vaca:
			pop cx
			inc ah
			inc cl
			inc di
			jmp @@inicio

;reset
;resetea la posicion de los digitos de el cual estaba guardado en bx y posicion de guess(cl) vuelve a 0
;incrementa la posicion de secrete(ch) y compara si no ah rebasado el tamaño del numero
;Si la posicion es mayor al tamaño de los digitos el procedimiento terminara en caso contrario volvera a inicio
		@@reset:
			mov di,bx
			mov cl,0
			inc si
			inc ch
			cmp ch,4
			je @@fin
			jne @@inicio

		@@fin:

			pop si
			pop di
			pop dx
			pop cx
			pop bx
			ret
			endp
						
end   principal              ; End of program 
