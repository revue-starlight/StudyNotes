#include <bits/stdc++.h>
using namespace std;
class D  
{  
public:  
    void printA()  
    {  
        cout<<this<<endl;
        cout<<"printA"<<endl;  
    }  
    virtual void printB()  
    {  
        cout<<"printB"<<endl;  
    }  
};  
int main(void)
{
	D *d=NULL;
	d->printA();
	d->printB();
}