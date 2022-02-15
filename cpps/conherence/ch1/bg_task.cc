#include <ostream>
#include <thread>
#include <iostream>
#include <unistd.h>
class background_task{
  public:
    int operator () () const{
      std::cout<<"hey"<<std::endl;
      std::cout<<"hello~"<<std::endl;
      return 1;
    }
};
background_task f;
int main(){
  std::cout<<f()<<std::endl;

  std::thread my_thread(f);

  std::thread my_thread_2([]{
    std::cout<<"in lambda"<<std::endl;
  });
  my_thread.join();
  my_thread_2.join();
  std::thread my_thread_3([]{
    for (int i=1;i<=100;i++){
      for (int j=1;j<=100;j++){
	int k2;
	for (int k=1;k<=100;k++){
	  int p;
	  p = 1+3;
	  k2 +=p;
	}
	k2 = k2+1;
      }
      std::cout<<i<<">";
      std::cout<<std::endl;
    }
  });
  sleep(3);
  return 0;
}
