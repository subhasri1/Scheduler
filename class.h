#include<stdio.h>
#include<iostream>

using namespace std;

class details{
public:
//string name;
int rollno,standard,fee;
void set(int r,int s,int f){
rollno=r;
standard=s;
fee=f;
};
void get(){
cout<<rollno<<endl;
cout<<standard<<endl;
cout<<fee<<endl;
//cout<<name<<endl;
};
};
