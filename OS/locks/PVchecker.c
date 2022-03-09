// 检查括号匹配，输出最大的左括号栈中数量
// 比如 PV.out 9 | ./checker.out <- 如果栈空了还有 ) 比如 ())。 则输出 -1
#include <stdio.h>
int max(int a,int b){
    if (a>b) return a;
    else return b;
}
int main(int argc,char **argv){
    int get = 0;
    char ch;
    int flag = 0;
    while ((ch = getchar())!=EOF){
        if (ch == '(') get++;
        else get--;
        if (get<0){
            flag = -1;
        }
        if (flag != -1) flag = max(flag,get);
        ch++;
    }
    printf("%d\n",flag);
    return 0;
}