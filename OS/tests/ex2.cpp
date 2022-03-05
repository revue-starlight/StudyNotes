#include <bits/stdc++.h>
using namespace std;

// std::atomic<int> cnt{0};
int cnt = 0;
int main(){
    // int cnt = 0;
    auto f = [&]{cnt++;};
    std::thread t1{f}, t2{f}, t3{f}; // undefined behavior
    // return 0;


    // auto f = [&]{cnt++;};
    // std::thread t1{f}, t2{f}, t3{f}; // OK
    t1.join();t3.join();t2.join();
    printf("%d\n",cnt);
}