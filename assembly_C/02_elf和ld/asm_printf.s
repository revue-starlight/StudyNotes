.section .data
msg:
    .asciz "Printf In Assembly!!\n"

.section .text
.globl main
main:
    subq $8, %rsp
    leaq msg(%rip), %rdi
    xor %al, %al
    call printf

    xor %edi, %edi
    call exit 
