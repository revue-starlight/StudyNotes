# memory model 

冷知识: c++ 中，线程可以通过指针搞到其他线程的自动变量 / 私有对象

冷知识: 线程执行是控制流，程序以 std::thread::thread / std::async 调用的程序流。

什么事 data races
## data races 是什么？
一个表达式读，另一个表达式写同一片内存的时候，就是data races。以下三种除外。

对于南大的那本书来说就是互斥区？

1. 同一个线程 / 同一个信号handler
2. atomic 修饰
3. memory order 的指定。

### 实验
#### 实验 1
``` cpp
int cnt = 0;
auto f = [&]{cnt++;};
std::thread t1{f}, t2{f}, t3{f}; // undefined behavior
```
output (while (true); ./a.out; | head -n 10000 | sort | uniq -c)
```
   6 2
   9994 3
```
#### 实验 2
``` cpp
std::atomic<int> cnt{0};
auto f = [&]{cnt++;};
std::thread t1{f}, t2{f}, t3{f}; // OK
```
output: (while (true); ./a.out; | head -n 10000 | uniq -c)
```
10000 3 
```

不加 atomic, 可能出现 data races, 具体的表现就是 两个线程同时从内存中读取了一个值，然后+1后又一起写回去。 比如t2,t3一起取出 1,执行+1后，都等于 2, 写回以后，爆炸了。

但是加了 atomic 后也不是万事大吉了，还存在着cpu的指令重排，以及编译器的指令重排。

## memory order
阅读资料 `Memory model synchronization modes` [<sup>[1]</sup>](#refer-anchor)

阅读资料 `std::memory_order` [<sup>[2]</sup>](#refer-anchor)

*这个也太复杂了，我看也看不懂，cpp reference好难*

### default 
default 是 最严格的内存序， std::memory_order_seq_cst
| Thread 1 | Thread 2|
|-|-|
|y = 1 | if (x.load() == 2)|
|x.store (2); | assert (y == 1)|

assert 不会失败，因为 y = 1 *`happens-before`* x.store(2). 如果 x.load() == 2 的话，thread 2 一定可以看见 x.store(2) 之前的所有 operations. 甚至是没有相互依赖的。

除此之外，读内存也是有 *`happens-before`* 规则，只能见到 happens-before 之前的内存操作。
为了方便程序员进行代码的编写，默认用最为严格的 `std::memory_order_seq_cst` , 以避免遇见不一样的结果。

### Relaxed
```
me, [3/5/22 11:47 AM]
-Thread 1-
x.store (1, memory_order_relaxed)
x.store (2, memory_order_relaxed)

-Thread 2-
y = x.load (memory_order_relaxed)
z = x.load (memory_order_relaxed)
assert (y <= z)

me, [3/5/22 11:47 AM]
https://gcc.gnu.org/wiki/Atomic/GCCMM/AtomicSync

me, [3/5/22 11:48 AM]
为啥不会触发assert，如果thread2在cpu运行时重排了呢？
```

### Acquire/Release
it only applies a happens-before relationship to dependent variables. 
This allows for a relaxing of the synchronization required between independent reads of independent writes. 


# 资料
<div id="refer-anchor">

[1] https://gcc.gnu.org/wiki/Atomic/GCCMM/AtomicSync

[2] https://en.cppreference.com/w/cpp/atomic/memory_order