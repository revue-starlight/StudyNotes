# 实现互斥的方法
Peterson, decker ...

# 为什么互斥那么困难？

不能同时读写内存

# load 锁 | 自旋锁

最小的load锁是 xchg (自带lock前缀,交换两个数字).

# 如何利用 xchg 实现互斥

举个例子:
1. 在厕所前放钥匙
2. 手上拿着纸
3. “你们停下来”
4. 用原子操作把我手里的纸和钥匙 做交换。
5. 回来之后， 我用原子操作重新做交换
6. 我上完厕所了。

处理器保证 lock 被序列化， 且所有 lock 发生之前的 lock 指令都被写入内存。

# 如何实现原子指令捏？
## 80486
```
cpu1   cpu2
 |      |
 ------------
 |          |
 | memory   |
 ------------
 可以 lock memory.由总线决定谁锁了。
```

## 今天
```
cpu1   cpu2
 |      |
 ------ ----
 |cache|cache|
 ------ ----
 |      |
 ------------
 |          |
 | memory   |
 ------------
 可以 lock memory.由总线决定谁锁了。
```

MESI(缓存一致性协议)

## RISC-V
LR/SC
load reserve, store conditional.

tag是放在cpu上的。

# 自旋锁的缺陷
## 性能问题:
0. 每次自旋会触发处理器间的缓存同步。
1. 其他处理器的线程在空转。争抢的越多，利用率越低。
2. 获得自旋锁的线程被OS操作系统切换出去，好耶！100%的资源浪费。

# Scalability 伸缩性
sum-scalability.c,stat.py

随着CPU的数量的变化，运行效率的变化是什么呢？

## 实验
用自旋锁来进行 sum++ 
起飞～
*三个和尚没水喝*

# 使用场景

1. 临界区不拥堵
2. 持有自旋锁时禁止执行流切换
使用场景: 操作系统内核的并发数据结构！

syscall 可以实现线程 + 长临界区

# Futex / 自旋锁 + 睡眠锁
性能: 114514 个线程也不会爆炸！
