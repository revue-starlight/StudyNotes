0x00005555555551ba  main+0  push   %rbp
0x00005555555551bb  main+1  mov    %rsp,%rbp
0x00005555555551be  main+4  sub    $0x20,%rsp
0x00005555555551c2  main+8  mov    %fs:0x28,%rax 
0x00005555555551cb  main+17 mov    %rax,-0x8(%rbp)
0x00005555555551cf  main+21 xor    %eax,%eax
0x00005555555551d1  main+23 lea    -0x20(%rbp),%rax
0x00005555555551d5  main+27 mov    $0x3,%ecx
0x00005555555551da  main+32 mov    $0x2,%edx


## reader
fs和gs寄存器指向特定于线程和其他操作系统定义的结构。修改段寄存器是受保护的指令，因此只有OS可以为您设置这些指令。
