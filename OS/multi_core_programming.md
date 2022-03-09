# 多处理器编程:从入门到放弃。

# Three easy pieces
## 如何理解并发？
一个程序里有多个执行流，每次选取一步进行操作。
## 并发的挑战
因为并发带来了不确定性，所以有一些挑战

而操作系统是最早的并发程序。没有共享资源，但是系统调用的代码成为了最早的并发程序。

共享在计算机的世界里如何被刻画呢？如果把单线程改造成多线程呢？什么东西会被复制？

**全局状态** <- 共享

而栈帧上的变量，局部变量，不需要被共享。

程序执行流中，局部变量对应了执行流中的某种状态。

线程的局部状态需要有自己的。 而全局状态是共享的。

比如“教室（全局） 中有一个人（个人）"

## 入门
CPU 400%?
OS会自动将线程放到不同的CPU上运行，所以可以出现400%的线程呢！

join()

join() 是将当前线程的状态机不停的调用自身。

能否通过全局变量使得线程间可以通信呢？ A: 可以

线程具有独立的堆栈么? >< A: 

真的共享内存了么？ A: 共享了

# 三大问题
## 原子性 | 临界区

### 双线程求和
详见代码 tests/ex5.cc
``` c
void Tsum(){
    asm volatile("lock add $1,%0":"+m"(sum));
}
```
需要在`asm volatile` 中加上 lock。

### 原子性的丧失 
程序独占处理器运行 在现代的处理器中 无法成立

### 实现原子性
通过 lock unlock 以实现临界区的绝对串行化。


## 顺序 | 编译器乱搞 
eventual consistency 
原因: 编译器减少/打乱语句
编译器觉得单线程结果是一致的，就会那样去优化。更改了一些对内存的操作之后，导致当共享内存作为数据同步的工具时，工具失效了。


### **如何让编译器不做这些事情？**

asm volatile ("" ::: "memory"); | 告知可能有其他读写内存

extern int volatile v | 保持c语义与汇编语义一致

### 目标
优化不能穿越 barrier

## 可见性

由于存在处理器级的优化，处理器经常会打乱操作。

“按序提交，乱序执行”

每个 uop 都有fetch->issue->execute->commit四个阶段。

uop 多发射 （取出多个能执行的指令放进uop池子），尽可能多的执行（在不违反依赖关系的情况下），按序提交。

movl $1,(x) <总是cache miss
movl (y),%eax <- 所以先执行池子里的这一条。


### 如何保证cpu顺序？
mfence

__sync_synchronize() 



## 杂乱的知识
``` c
_thread int a; // 线程的局部变量
```

objdump

lea,jne

`LEA ax, [BP+SI+5] ; Compute address of value`

`MOV ax, [BP+SI+5] ; Load value at that address`[<sup>[1]</sup>](#refer-anchor)

__sync__synchronize()

uniq

# 问题超展开！
## __sync_synchronize() 是啥？
 Built-in functions for atomic memory access.(内存序和可见性绑在一起的？)
 
 In most cases, these builtins are considered a full barrier. That is, no memory operand will be moved across the operation, either forward or backward. Further, instructions will be issued as necessary to prevent the processor from speculating loads across the operation and from queuing stores after the operation. [<sup>[2]</sup>](#refer-anchor)

## __sync_synchronize() 和 atomic 的区别是？
Noteworthy is that operations on std::atomic ONLY affect the actual data stored in the atomic object. Not reads/writes of other data.

std::atomic is guaranteed to be a "compiler barrier", but in other cases, the compiler may well shuffle stuff around in a similar way.

为验证 atomic 不能代替 memory barrier, 做了实验 ex1.cpp , 但是无法观察到 0 的出现。 

``` sh
while (true); ./a.out | head -n 1000 | uniq -c
```

## volatile 干了啥？

    Every access (read or write operation, member function call, etc.) made through a glvalue expression of volatile-qualified type is treated as a visible side-effect for the purposes of optimization (that is, within a single thread of execution, volatile accesses cannot be optimized out or reordered with another visible side effect that is sequenced-before or sequenced-after the volatile access. This makes volatile objects suitable for communication with a signal handler, but not with another thread of execution, see std::memory_order). 

说人话，就是 每次通过一个带有volatile的泛左值表达式类型的获取，都会因为 `purposes of optimization`，当作是一个可见的副作用。
在单线程的执行中，volatile不可能被优化掉，或者是与另外一个可见的side-effect重新排序。这个使volatile修饰的对象能够更方便的和signal handler通信，但不与其他线程的对象通信。
as-if 原则 顺序可见性指 volatile 是可见的，输入输出也是可见的，证明不会对volatile进行重排。 


### `purposes of optimization`[<sup>[4]</sup>](#refer-anchor)

允许进行任何不改变程序可观察行为的代码转换。 

只要保证以下几点，就允许 C++ 编译器对程序进行任何修改：

1) 对 volatile 对象的访问（读或写）严格按照它们所发生的表达式的语义进行。特别地，它们和同一线程中的其他 volatile 访问之间不会发生重排。
2) 程序终止时，写入文件的数据完全如同程序是按照所写的代码那样执行的一般。
3) 发送到交互式设备的提示文本将在程序等待输入之前显示出来。
4) 如果 ISO C 编译指示 #pragma STDC FENV_ACCESS 受到支持并被设为 ON，则保证浮点算术运算符和函数调用会观察到对浮点环境（浮点异常和舍入模式）的修改，就如同按照所写的代码那样执行一般，除非
        除去转型和赋值以外的任何浮点表达式的结果可能有不同于表达式本身的浮点范围和精度（参见 FLT_EVAL_METHOD ）
        尽管如此，任何浮点表达式的中间结果可能按照无限的范围和精度进行计算（除非 #pragma STDC FP_CONTRACT 为 OFF ）

特别注意

由于编译器（通常）不能分析一个外部库的代码，以确定它是否执行 I/O 或者 volatile 访问，因此第三方库的调用同样不受这种优化的影响。然而，标准库调用可能会在优化过程中被其它调用替换，被消除，或者被添加到程序中。静态连接的第三方库代码可能会参与连接时优化。



# 引用
<div id="refer-anchor">

[1] https://stackoverflow.com/questions/1699748/what-is-the-difference-between-mov-and-lea

[2] http://gcc.gnu.org/onlinedocs/gcc-4.6.2/gcc/Atomic-Builtins.html

[3] https://en.cppreference.com/w/cpp/language/memory_model

[4] https://zh.cppreference.com/w/cpp/language/as_if
