section .text
global hello_in_asm

hello_in_asm:

   mov eax,4            ; write()
	mov ebx,1            ; STDOUT
	ret