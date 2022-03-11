#include <stdio.h>
#include <unistd.h>
typedef struct {
    char ch[10];
    int a;
    long long b;
} A;

A getA(int a,int b,int c){
    A aa;
    aa.ch[0]=(char)a+'0';
    aa.a = b;
    aa.b = c;
    return aa;
}

int main(){
    A hello = getA(1,2,3);
    printf("%s\n",hello.ch);
}
/**
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */