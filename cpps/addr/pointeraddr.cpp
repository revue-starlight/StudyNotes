#include <bits/stdc++.h>
using namespace std;
struct sttt{
    int a,b,c;
    char ch[40];
};

sttt ss[10],*p=ss;
int main(){
    
    for (int i=0;i<10;i++){
        ss[i].a = ss[i].b = ss[i].c = i;
        strcpy(ss[i].ch,"hello");
    }
    cout<<sizeof(sttt)<<endl;
    cout<<p<<endl;
    
    p = p+1;
    
    cout<<p<<endl;
    cout<<p->a<<endl;
}