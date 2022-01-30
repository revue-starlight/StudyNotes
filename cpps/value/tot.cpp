#include <iostream>
using namespace std;
int main(){
    int x = 3;
    const int &p = x++;
    x++;
    cout<<p<<endl;
}
/*
 x= 3
 eax = x
 edx = x+1
 x = edx
 0x-14 = eax
 eax = 销毁

 * 
 */