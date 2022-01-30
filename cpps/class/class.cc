#include "class.hpp"
#include <iostream>
using namespace std;
coor::coor(){
    cout<<"instruct"<<endl;
}

coor::~coor(){
    cout<<"delete"<<endl;
}

coor::coor(const coor &from){
    page = from.page;
    time = from.time;
}

coor& coor::operator=(const coor &from){
    this->page = from.page;
    this->time = from.time;
}

coor operator+(const int page,const coor &coor){
    return coor;
}