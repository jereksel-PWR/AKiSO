global atof
global ftoa

section .data
ten: dd 10.0
x:	dd 3.14
y:  dd 0.0
z:  dd 1.0
one: dd 1.0
zero:   dd 0.0
temp: dd 0.0
temp2: dd 0.0
ascii: dd 48.0
pol:  dd 0.5
backup: dd 0.0

length resd 4
dot_loc resd 4

array resd 10000

section .text

atof:
	finit

	push   ebp
	mov    edx, [esp+0x8]
	;rep scasb

	mov ecx,0x0

	string_length:

	inc ecx
	cmp BYTE [edx+ecx*1], 0

	jne string_length

	mov [length], ecx

	;ecx/edx są zajęte i nie można ich używać

	mov ebx, 0x0  ; ilość już wrzuconych cyfr
	mov eax, 0x0

	mov eax, [edx+0x0]

	fld dword [zero]

	czesc_dziesietna:


	fld dword [ten]

	fmul

	and    eax, 0xF

	mov    [y], DWORD eax

	fild dword [y]

	fadd


	inc ebx
	mov eax, [edx+ebx]
	and eax, 0x3F
; Czy jest już kropka?
	cmp eax, 0x2E

	;cmp ebx, ecx

	jne czesc_dziesietna


	mov [dot_loc], ebx

	inc ebx
	mov eax, [edx+ebx]



	po_przecinku:


	fld dword [ten]

	fmul

	and    eax, 0xF

	mov    [y], DWORD eax

	fild dword [y]

	fadd


	inc ebx
	mov eax, [edx+ebx]

	cmp ebx, ecx

	jne po_przecinku



	mov ebx, [length]
	mov ecx, [dot_loc]

	dec ebx

	lokalizacja_kropki:


	fld dword [ten]

	fdiv


	inc ecx

	cmp ebx, ecx

	jne lokalizacja_kropki


	fst dword [z]
	mov eax, [z]


	pop    ebp
	ret

ftoa:

	finit

	mov eax, 0
	mov ebx, 0
	mov ecx, 0

	push   ebp
	mov     ebp, esp

	mov    edx, [ebp+8]

	mov    [y], DWORD edx


	fld dword [y]


	mov ebx, 0x0

	czesc_dziesietna_2:


	fdiv DWORD [ten]

	inc ebx


	fist DWORD [temp]

	cmp dword [temp], 1


    jge czesc_dziesietna_2


	push ebx

	fld dword [y]
	fst dword [backup]

	fld dword [pol]

	fsubp

	fist dword [y]

	czesc_dziesietna_3:

	fild dword [y]

	fld dword [ten]

	fxch st1

	fprem

	fistp dword [temp]

	mov eax, [temp]

	or eax, 0x30

	dec ebx
	or [array+ebx], BYTE al
	inc ebx

	fild dword [y]

	fld dword [ten]

	fdivp

	fld dword [pol]

	fsubp

	fist dword [y]

	;Czyścimy stack
	FINIT


	dec ebx

	cmp ebx, 0

	jne czesc_dziesietna_3
	
	FINIT

	fld dword [backup]

	pop ebx

	or [array+ebx], BYTE 0x2e

	inc ebx


	fld st0

	; Aby na pewno zaokrągliło w dół
	fld dword [pol]
	fsubp
	frndint
	fsubp

	mov ecx, dword 0x0


	po_przecinku_2:

	fld dword [ten]
	fmulp
	fld st0
	fld dword [pol]
	fsubp
	frndint
	fist dword [temp]
	mov eax, [temp]
	or eax, 0x30
	or [array+ebx], BYTE al	
	inc ebx
	inc ecx
	fsubp


	cmp ecx, 0x06
	jne po_przecinku_2




	mov eax, array

	pop    ebp

	ret