#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void co_1(int a,int b,int c){
    printf("1%d\n",a+b+c);
    return;
}

void co_2(int a,int b,int c){
    printf("2%d\n",a+b+c);
    return;
}
int main(){
    co_1(1,2,3);
    co_2(1,2,3);
}