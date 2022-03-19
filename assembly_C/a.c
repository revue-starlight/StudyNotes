#include <stdio.h>
int get(int a,int b,int c){
    return (a+b)*c+c;
}
int main(){
    int a = 3, b = 5,c = 5;
    int s = get(a,b,c) + get(b,c,a) + get(c,b,a);
    printf("%d",s);
    return 0;
}