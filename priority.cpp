
#include <iostream>
#include<fstream>
#include<sys/types.h>
using namespace std;
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<errno.h>
#include "class.h"



struct process* priority()
{

string st,BrustTime,pid,ArrivalTime,Priority;
int flag=0,k,j=0;
fstream file1;
file1.open("dt.txt",ios::in);
//struct process* p = (process*)calloc(10,sizeof(struct process));
//struct process p[10];
struct process *p=new struct process[10];
//struct process *p;
while(getline(file1,st)){
//cout<<st<<endl;
for(int i=0;i<st.size();i++)
{


if(st[i]==','){

flag++;

}


else if(flag==1){

pid+=st[i];

}
else if(flag==2){

ArrivalTime+=st[i];

}
else if(flag==3){

BrustTime+=st[i];

}
else if(flag==5){

Priority+=st[i];

}
}
//cout<<"pid:"<<pid;
p[j].pid=stoi(pid);
p[j].ArrivalTime=stoi(ArrivalTime);
p[j].BrustTime=stoi(BrustTime);
p[j].Priority=stoi(Priority);
pid.clear();
ArrivalTime.clear();
BrustTime.clear();
Priority.clear();
j++;
flag=0;
}
//cout<<p[0].pid<<"mila"<<endl;
file1.close();

    int temp1,temp2,temp3;
    float sumtat=0.0,sumwt=0.0;

//sorting base on priority
for(int m=0;m<j;m++)
{
    for(int n=m+1;n<j;n++)
    {
        if(p[m].Priority>p[n].Priority)
        {
            temp1=p[m].BrustTime;
            p[m].BrustTime=p[n].BrustTime;
            p[n].BrustTime=temp1;
            temp2=p[m].Priority;
            p[m].Priority=p[n].Priority;
            p[n].Priority=temp2;
            temp3=p[m].pid;
            p[m].pid=p[n].pid;
            p[n].pid=temp3;
            
        }
    }
}

p[0].ComplitionTime=p[0].BrustTime;
p[0].WaitingTime=0;
for(int i=1;i<j;i++)
{
p[i].ComplitionTime=p[0].BrustTime+p[i-1].ComplitionTime;
}
for(int i=0;i<j;i++)
{
    p[i].Priority;
    p[i].BrustTime;
    p[i].ComplitionTime;
    p[i].pid;
}
for(int i=0;i<j;i++)
{
    p[i].TurnAroundTime=p[i].ComplitionTime;
    p[i].WaitingTime=p[i].TurnAroundTime-p[i].BrustTime;
    sumtat+=p[i].TurnAroundTime;
    sumwt+=p[i].WaitingTime;
}
cout<<" pid  Priority   Brust Time    Waiting Time    Turn Around Time "<<endl;
for(int i=0;i<j;i++)
{
    cout<<" "<<p[i].pid<<"\t  "<<p[i].Priority<<"\t   "<<p[i].BrustTime<<"\t\t  "<<p[i].WaitingTime<<"\t\t  "<<p[i].TurnAroundTime<<endl;
}
/*p[4].awt1=sumwt/n;
p[4].atat1=sumtat/n;
cout<<"Total waiting time: "<<sumwt<<endl;
cout<<"Average waiting time: "<<p[4].awt1<<endl;
cout<<"Total turm around time : "<<p[4].ttat1<<endl;
cout<<"Average turn around time: "<<p[4].atat1<<endl;
*/
    return p;
}

