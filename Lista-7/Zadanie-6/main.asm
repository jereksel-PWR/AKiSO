global function1
global function2
global function3
global function4

section .data
temp: dd 0.0

section .text

function1:
	push   ebp
	mov    ebp,esp
	fldln2
	fld    DWORD [ebp+0x8]
	fyl2x
	pop    ebp
	ret

function2:
	push   ebp
	mov    ebp,esp
	fld    DWORD [ebp+0x8]

	fldl2e

	fmul

	fld st0

	frndint

	fsub

	f2xm1

	fld1

	fadd

	fld    DWORD [ebp+0x8]
	fldl2e
	fmul

	frndint

	fld1

	fscale


	fxch st1
	fxch st2

	fmul

	pop    ebp
	ret

function3:
	push   ebp
	mov    ebp,esp

	finit

	mov eax, [ebp+0x8]

	mov [temp], eax


	fld dword [temp]
	fchs
	fst dword [temp]

	mov eax, [temp]

	push eax
	call function2
	add esp, 4


	fld dword [temp]
	fchs
	fst dword [temp]

	mov eax, [temp]

	push eax
	call function2
	add esp, 4


	fxch st1
	fxch st3

	fsub

	fld1
	fld1

	faddp
	fdivp


	pop    ebp
	ret

function4:
	push   ebp
	mov    ebp,esp

	finit

	mov eax, [ebp+0x8]
	mov [temp], eax

	fld dword [temp]
	fld dword [temp]

	fmul

	fld1

	faddp

	fsqrt

	fld dword [temp]

	faddp


	fst dword [temp]

	mov eax, [temp]

	push eax
	call function1
	add esp, 4


	pop    ebp
	ret