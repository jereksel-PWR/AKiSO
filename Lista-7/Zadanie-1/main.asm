;
; kompilacja:
; nasm -f elf main.asm && gcc -m32 -o main main.o
;


global main


extern printf

section .text
main:

    mov ebp, 8

   ; Wypełnianie tabeli liczbami
    mov ecx, 10000
 	fill_loop:
	mov [array+ecx*4], ecx
	loop fill_loop



	mov ecx, 5000


	mov edx, 2


	outer_loop

	cmp edx, 5000
	jge outer_end


	mov eax, edx
	mov ebx, edx


	inner_loop:


	add eax,ebx
	cmp eax, 10000
	jge inner_end
	mov word [array+eax*4], 0x0
	jmp inner_loop

	inner_end


	inc edx

	jmp outer_loop


	outer_end



	mov eax, 2
	mov ebx, 0
	mov ecx, 0
	mov edx, 0




	print_loop

	cmp eax, 10000
	jge the_end




	mov ebx, [array+eax*4]
	cmp ebx, 0
	je increase

	push eax

	push dword ebx
    push message
    call printf
    add esp, 8



    pop eax

    increase

	inc eax

	jmp print_loop



	the_end

    ret



section .data
message db '%d, ', 10, 0
array resd 10000
backup 