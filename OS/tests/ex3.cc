#include <bits/stdc++.h>
using namespace std;
atomic <int> x = 0;

void yjsnpi(){
    x.store(1);
    x.store(2);
}

void nihaoa(){
    int y = x.load();
    int z = x.load();
    cout<<(y<=z)<<endl;
}
int main(){
    // auto p = [&](){
        
    // };
    // auto q = [&](){
    //     int y = x.load(memory_order_relaxed);
    //     int z = x.load(memory_order_relaxed);
    //     cout<<(y<=z)<<endl;
    // };
    
    thread t1{yjsnpi},t2{nihaoa};
    t2.join(); t1.join();
};