#include <bits/stdc++.h>
using namespace std;
atomic <int> s;
int main(){
    auto p = [&]() {for (int i=0;i<10000;i++) s++;};
    thread t1{p},t2{p};
    t1.join();t2.join();
    cout<<s<<endl;
}