#include <bits/stdc++.h>
volatile std::atomic<bool> lock_ = false;
volatile const std::atomic<bool> val = 1;
int lock(){
    while (!(std::atomic_exchange(&lock_,&val)==0));
}

int unlock(){
    lock_.store(0);
}
int main(){

}