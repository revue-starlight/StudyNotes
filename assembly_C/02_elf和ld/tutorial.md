### 写在前面
笔者也是按照本人的理解来描述笔者本人所看到的现象，如果有纰漏，请不要犹豫的与笔者联系。
我真的菜哇 qaq

# 阅读资料


在 `Unix` 上执行文件，也需要符合一些规范。而这些规范其实实用于不仅仅`.out`文件，而是在更多地方都有通行，不仅仅是可执行文件，更有共享库什么的东西。（这大概也能解释为什么`.o`和`.out`在`objdump`中看起来都差不多)。
那些010之类的代码其实就是在这里开始的。

## elf
```
Executable and Linkable Format is a common standard file format for executable files, object code, shared libraries, and core dumps. ---wikipedia
```

顾名思义啦。ELF 是可执行文件啊，目标代码啊，共享库啊，核心转储的通行的一种标准文件格式。

First published in the specification for the application binary interface (ABI) of the Unix operating system version named (SVR4)

在  `application binary interface (ABI)` (可以理解为向机器码对接的接口说明) 的名为 `System V Release 4` 中被首次提出。

现在 elf 是 unix 在 x86 下的标准二进制文件的格式

### format layout
- Program header table, describing zero or more memory segments

头文件，记录了辨识与执行文件的相关信息。比如是大端还是小端什么的。

- Section header table, describing zero or more sections

可执行的内容，比如机器码，还有数据段之类的。

code

data

section names

例: .text .rodata 之类
- Data referred to by entries in the program header table or section header table
存储了描述section的数据。服务sections，比如type,flag,address,offset 之类


## ld
