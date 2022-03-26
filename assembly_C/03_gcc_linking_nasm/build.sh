#!/bin/bash
nasm -f elf64 -o hello_in_asm.o code.asm
gcc main.c hello_in_asm.o               
./a.out