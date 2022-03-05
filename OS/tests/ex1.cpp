#include <bits/stdc++.h>
using namespace std;
unsigned int value = 0;
std::atomic<bool> flag(false);

void thread1(){
  value = 42;
  flag.store(true);
}

void thread2(){
    while (!flag.load());
    cout<<value<<endl;
}

int main(){
    thread t2(thread2);
    thread t1(thread1);
    t2.join(); t1.join();
    return 0;
}