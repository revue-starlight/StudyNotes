nasm -f elf64 say_hi.asm -o say_hi.o
gcc example.c say_hi.o -o hello
./hello