
    SECTION .data
msg: db "Hello World",10
    SECTION .text
global myfunc
global main
global _start
myfunc:
    mov edx,1
    mov ecx,msg
    mov ebx,1
    mov eax,4
    int 0x80
    ret 
main:
_start:
    mov edx,-1
    mov eax,2
    add edx,eax
    mov edx,1
    mov ecx,msg
    mov ebx,1
    mov eax,4
    int 0x80

    mov    ebx,0              ; exit code, 0=normal
    mov    eax,1              ; exit command to kernel
    int    0x80     