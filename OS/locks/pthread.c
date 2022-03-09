/**
 * @file pthread.c
 * @author revue-starlight (you@domain.com)
 * @brief thread 的 api 简介
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
typedef struct
{
    int a;
    int b;
} myarg_t;
typedef struct
{
    int x;
    int y;
} myret_t;
void *mythread(void *arg)
{
    pid_t pid = gettid();
    printf("%d\n",pid);
    myret_t *rvals = malloc(sizeof(myret_t));
    rvals->x = 1;
    rvals->y = 2;
    return (void *)rvals;
}

int main(int argc, char *argv[])
{
    pid_t pid = gettid();
    printf("%d\n",pid);
    pthread_t p;
    myret_t *rvals;
    myarg_t args = {10, 20};
    pthread_create(&p, NULL, mythread, &args);
    pthread_join(p, (void **)&rvals);
    printf("returned %d %d\n", rvals->x, rvals->y);
    free(rvals);
    return 0;
}