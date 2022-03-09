/**
 * @file pthread_create.c
 * @author revue-starlight (you@domain.com)
 * @brief 一个简单的程序，教你如何利用c语言自带的mutex锁实现互斥区。
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
typedef struct {int times;} arg;
int x;
pthread_mutex_t mtx;
int p = 0;
void* pthread(void* args){
    int n = ((arg*)args) -> times;

    for (int i=0;i<n;i++) {
        int p = pthread_mutex_trylock(&mtx);
        if (p!=0) {--i; continue;} //如果无法获取锁，那就重来。
        x++;
        pthread_mutex_unlock(&mtx);
    }
    return (void*)(&p);
}

int main(){
    int status = pthread_mutex_init(&mtx,NULL);
    assert(status == 0);
    pthread_t t1,t2;
    arg* p = malloc(sizeof(arg));
    p->times = 1e5;
    pthread_create(&t1,NULL,pthread,(void*)p);
    pthread_create(&t2,NULL,pthread,(void*)p);
    int *ret = malloc(sizeof(int));
    int *ret2 = malloc(sizeof(int));
    pthread_join(t1,(void**)(&ret));
    pthread_join(t2,(void**)(&ret2));
    printf("%d\n",x);
    return 0;
}