#include <bits/stdc++.h>
using namespace std;
int r1,r2;
//atomic <int> x,y;
int x,y;
void T1(){
__sync_synchronize();
//r1 = y.load(std::memory_order_relaxed); // A
r1 = y;
__sync_synchronize();
//x.store(r1, std::memory_order_relaxed); // B
x = r1;
__sync_synchronize();
}
void T2(){
__sync_synchronize();
//r2 = x.load(std::memory_order_relaxed); // C
r2 = x;
__sync_synchronize();
//y.store(42, std::memory_order_relaxed); // D
y = 42;
__sync_synchronize();
}
int main(){
    x = 0; y = 0;
    __sync_synchronize();
    thread t(T1),tt(T2);
    t.join(); tt.join();
    cout<<(x==42 && y==42)<<endl;
    return 0;
}