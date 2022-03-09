/**
 * @file mutex.c
 * @author revue-starlight (you@domain.com)
 * @brief 麻了，为什么我没有SYSCALL_lock啊？
 * 编译失败
 * 总而言之，在「操作系统05 并发控制」中，源代码使用了SYSCALL_lock. 而且声称 “c语言 只提供计算，不提供锁，所以用交互.... (1:13:30)”
 * 是不是我跳过了什么？
 * gcc version 11.2.0
 * Linux archlinux 5.16.12-arch1-1 #1 SMP PREEMPT Wed, 02 Mar 2022 12:22:51 +0000 x86_64 GNU/Linux
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>
// volatile atomic_flag lk;
int flag;
// void *mutex_lock(void *arg){
//     syscall(SYSCALL_lock,&lk);
// }
// void *mutex_unlock(void *arg){
//     syscall(SYSCALL_unlock,&lk);
// }

// int main(){
    
// }

void init()
{
    flag = 0;
}
void lock()
{
    while (TestAndSet(&flag, 1) == 1)
        yield(); // give up the CPU
}
void unlock()
{
    flag = 0;
}