#include<iostream>
#include<fstream>
#include<sys/types.h>
using namespace std;
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<errno.h>
#include "class1.h"

int main(){
int j=0;
struct process *p=fcfs();
while(j<2){
cout<<p->pid;
p++;
j++;
}
}
