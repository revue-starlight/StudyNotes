/**
 *利用 atomic_flag_test_and_set 来测试自旋锁下互斥区的有效性。
 * 结果为有效
 * 在
 * while (true); ./a.out;  | head -n 10000 | sort | uniq -c 中
 * 10000 次 输出皆为 11000
 * spin_lock:
 * correct: yes
 * fair: no
 * performance: no{
 *  被 os scheduler 切换走的可能性存在着。
 * }
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdatomic.h>
typedef struct {int ret;} ret;
typedef struct {int args;} arg;
volatile atomic_flag flag = {0};
volatile int x = 0;
void* fn(void *args){
    asm("mfence");
    arg *argv = (arg*)args;
    ret *r = malloc(sizeof(ret));
    int n = argv->args;
    asm("mfence");
    for (int i=0;i<n;i++){
        while (atomic_flag_test_and_set(&flag) == 1);
        ++x;
        flag.__val = 0;
    }

    return (void*)r;
}

int main(){
    pthread_t p1,p2;
    arg arg1,arg2;
    arg1.args = 1e3;
    arg2.args = 1e4;
    ret ret1,ret2;
    ret *r1 = &ret1, *r2 = &ret2;
    pthread_create(&p1,NULL,fn,(void*)(&arg1));

    pthread_create(&p2,NULL,fn,(void*)(&arg2));

    pthread_join(p1,(void**)(&r1));
    pthread_join(p2,(void**)(&r2));

    printf("%d\n",x);

    return 0;
}