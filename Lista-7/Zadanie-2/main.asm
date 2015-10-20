; Program przyjmuje argumenty ze standardowego wejścia: echo "24" | ./main

SECTION .data

    formatd:    db "%d", 0
    formatx:    db "%08x", 0

    name:   resb    20
    number: resb   4

    array resd 4
    backup resd 4


SECTION .text

extern printf
extern scanf

global main                    

main:
            push EBP
            mov EBP, ESP

            push number
            push formatd
            call scanf
            add ESP, 8

            mov ebx, dword [number]

            mov dword [array+0], 0x0
			mov dword [array+4], 0x0
  			mov dword [array+8], 0x0
   			mov dword [array+16], 0x0

            mov dword [backup+0], 0x0
			mov dword [backup+4], 0x0
  			mov dword [backup+8], 0x0
   			mov dword [backup+16], 0x0

			mov [array+0], eax



			outer_loop:


			cmp ebx, 0x1
			je end


   			mov eax, [array+0]
			mov [backup+0], eax

   			mov eax, [array+4]
			mov [backup+4], eax

			mov eax, [array+8]
			mov [backup+8], eax

			mov eax, [array+12]
			mov [backup+12], eax


			mov ecx, ebx
			dec ecx

 			inner_loop:

			clc

			; Dodawanie 128 bitowej liczby
			
 			mov eax, [backup+0]
			adc [array+0], eax

 			mov eax, [backup+4]
			adc [array+4], eax

			mov eax, [backup+8]
			adc [array+8], eax

			mov eax, [backup+12]
			adc [array+12], eax

			clc


 			loop inner_loop

 			dec ebx

 			jmp outer_loop

 			end:



            push dword [array+12]
            push formatx
            call printf
            add ESP, 8


            push dword [array+8]
            push formatx
            call printf
            add ESP, 8


            push dword [array+4]
            push formatx
            call printf
            add ESP, 8


            push dword [array+0]
            push formatx
            call printf
            add ESP, 8


           mov ESP, EBP
           pop EBP

           ret