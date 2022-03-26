### 阅读资料

#### inline-asm
https://gcc.gnu.org/onlinedocs/gcc/Basic-Asm.html#Basic-Asm


#### AT&T syntax
https://docs.oracle.com/cd/E53394_01/pdf/E54851.pdf

### 汇编语言
    汇编语言是任何一种用于电子计算机、微处理器、微控制器，或其他可编程器件的低级语言。

    在不同的设备中，汇编语言对应着不同的机器语言指令集。一种汇编语言专用于某种计算机系统结构，而不像许多高级语言，可以在不同系统平台之间移植。  
            ----wikipedia


### 汇编器

#### nasm

    基于英特尔 x86 架构的汇编与反汇编工具。
    NASM 使用英特尔汇编语法的变体而不是 AT&T 语法（GNU 汇编器采用的语法）
            （webster.cs.ucr.edu/AsmTools/NASM/）

#### masm
    an x86 assembler that uses the Intel syntax for MS-DOS and Microsoft Windows.

#### gas
    GNU Assembler
    GAS supports a general syntax that works for all of the supported architectures. The general syntax includes assembler directives and a method for commenting. The default syntax is AT&T syntax. 


### 寻找 GAS 的文档

#### 前言
就连谷歌搜索引擎也感到乏力。排在结果前面的都是".edu"之类的二手pdf文档。通过 stack overflow 找到了相关文档。

[stackoverflow: is-there-a-complete-x86-assembly-language-reference-that-uses-att-syntax?](https://stackoverflow.com/questions/1776570/is-there-a-complete-x86-assembly-language-reference-that-uses-att-syntax)

[x86-AT&T-ORACLE文档](https://docs.oracle.com/cd/E19253-01/817-5477/817-5477.pdf)

文章冗长。

#### 放弃原因

努力寻找只见到了快速上手的不详细的文档，决定继续使用更为广泛的 `nasm` 进行编程

https://tuttlem.github.io/2014/03/25/assembly-syntax-intel-at-t.html

http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html#s2
```
+------------------------------+------------------------------------+
|       Intel Code             |      AT&T Code                     |
+------------------------------+------------------------------------+
| mov     eax,1                |  movl    $1,%eax                   |   
| mov     ebx,0ffh             |  movl    $0xff,%ebx                |   
| int     80h                  |  int     $0x80                     |   
| mov     ebx, eax             |  movl    %eax, %ebx                |
| mov     eax,[ecx]            |  movl    (%ecx),%eax               |
| mov     eax,[ebx+3]          |  movl    3(%ebx),%eax              | 
| mov     eax,[ebx+20h]        |  movl    0x20(%ebx),%eax           |
| add     eax,[ebx+ecx*2h]     |  addl    (%ebx,%ecx,0x2),%eax      |
| lea     eax,[ebx+ecx]        |  leal    (%ebx,%ecx),%eax          |
| sub     eax,[ebx+ecx*4h-20h] |  subl    -0x20(%ebx,%ecx,0x4),%eax |
+------------------------------+------------------------------------+
```

#### use nasm in gcc
https://stackoverflow.com/questions/42169037/link-assembly-nasm-code-to-gcc

观察发现，在 `.c` 文件中设置 `extern` 声明外部函数，并且直接在 `.asm` 中编写该函数，具体编写方式为
``` asm
   section .text
   global your-function-name

   your-function-name:
    ...
    ...
    ret
```

在引入data段之后有了这样的问题。
```
➜  03_gcc_linking_nasm git:(master) ✗ gcc main.c hello_in_asm.o 
/usr/bin/ld: hello_in_asm.o: relocation R_X86_64_32 against `.DATA' can not be used when making a PIE object; recompile with -fPIE
/usr/bin/ld: failed to set dynamic section sizes: bad value
collect2: error: ld returned 1 exit status
```



删除data段后则可以正常编译了。
```
➜  03_gcc_linking_nasm git:(master) ✗ nasm -f elf64 -o hello_in_asm.o code.asm


➜  03_gcc_linking_nasm git:(master) ✗ objdump hello_in_asm.o -S            
hello_in_asm.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <hello_in_asm>:
   0:   b8 04 00 00 00          mov    $0x4,%eax
   5:   bb 01 00 00 00          mov    $0x1,%ebx
   a:   c3                      ret    


➜  03_gcc_linking_nasm git:(master) ✗ gcc main.c hello_in_asm.o          


➜  03_gcc_linking_nasm git:(master) ✗ 
```

好，我们可以用nasm解决问题了！

为什么不能用data段呢？
首先我们知道x64 assembly的通常内存模型是
```
2.5 Memory Layout
The general memory layout for a program is as shown:

+------------------------+    <--- high memory
|           stack        |
|           .            |
|           .            |
|           .            |
+------------------------+
|           heap         |
+------------------------+
|BSS – uninitialized data|
+------------------------+
|         data           |
+------------------------+
|      text (code)       |
+------------------------+
|       reserved         |
+------------------------+   <--- low memory
    General Memory Layout
```
(摘自 2.5 x86-64 Assembly Language Programming with Ubuntu)