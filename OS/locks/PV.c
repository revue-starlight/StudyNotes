/**
 * @file PV.c
 * @author your name (you@domain.com)
 * @brief PV操作实现的线程安全的 producer 和 consumer。采用 mutex 锁实现。
 * 谨记: condition variable 如果不分开的话，会出现
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdatomic.h>

pthread_mutex_t lock;
pthread_cond_t pro,con;
int count;
int MAX = 1;
void *producer(void *arg){
    
    for (int i=0;i<1e6;++i){
        pthread_mutex_lock(&lock);
        while (!(count<MAX)){
            pthread_cond_wait(&pro,&lock);
        }
        
        ++count;
        printf("(");
        pthread_cond_signal(&con);
        pthread_mutex_unlock(&lock);
    }
    

}

void *consumer(void *arg){
    for (int i=0;i<1e6;++i){
        pthread_mutex_lock(&lock);
        while (!(count > 0)){
            pthread_cond_wait(&con,&lock);
        }
        count--;
        printf(")");
        pthread_cond_signal(&pro);
        pthread_mutex_unlock(&lock);
    }
}

int main(int argc,char **argv){
    if (*(argv+1)!=NULL)
        MAX = *(*(argv+1)) - '0';
    pthread_t P,V;
    pthread_create(&P,NULL,producer,NULL);
    pthread_create(&V,NULL,consumer,NULL);
    char *ch = malloc(sizeof(char));
    pthread_join(P,(void**)(&ch));
    pthread_join(V,(void**)(&ch));
    return 0;
}