#include <bits/stdc++.h>
#include <thread>
using namespace std;
int remain = 0;
class Thread{
  public:
  int operator()(){
    for (int i=0;i<1145141919;i++){ remain++;if (remain%1000000==0) cout<<"<"; }
    return 0; 
  } 
};
int main(){
  Thread p;
  std::thread pp(p);
  thread::id id = pp.get_id();
  thread::id id2 = (*(new std::thread)).get_id();
  thread::id id3 = (*(new std::thread)).get_id();
  cout<<id<<endl; 
  cout<<id2<<endl; 
  cout<<id3<<endl; 
  pp.join();
}
