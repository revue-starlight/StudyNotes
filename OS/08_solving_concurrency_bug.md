# 并发bug与应对
更实在的方法 - 防御性编程

例如 peterson 算法

- 在每个语句后都加上 barrier
- 加上 assert() 检查。 比如平衡树

# 死锁！
## AA-死锁
锁没释放完，被中断了，中断要你现在持有的锁。
## ABBA-死锁
循环依赖了。

## 避免死锁
互斥，请求保持，不剥夺，循环等待。

绝不是传统教科书这样讲的，”破坏条件“。说起来很轻巧。傻逼。

# data-racing
内存访问同时发生时，且至少有一个是写。有一个被覆盖掉 or 读的不知道是哪一个

- peterson算法告诉大家
- 你们写不对无锁的并发程序

所以，用互斥锁保护好共享数据。用来消灭一切数据竞争。

# 绝大部分类型的并发bug
函数做一半被改了
上锁也不管用。TOCTTOU
```
 SENDMAIL           attacker
 checkifnotlink
                 ln -s /etc/passwd 

 sendmail
```

# 应对bug
    否定你自己
    检查检查再检查

    lock - ordering 彻底避免死锁？
    并发测试很难。bug 很 罕见。
    bug 并发出错 更罕见。

    上锁的顺序是可以检查的。
    对每一种类型的锁，观察他们上锁的顺序关系。 
