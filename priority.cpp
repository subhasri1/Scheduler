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

string st,BurstTime,pid,ArrivalTime,Priority;
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

BurstTime+=st[i];

}
else if(flag==4){

Priority+=st[i];

}
}
//cout<<"pid:"<<pid;
p[j].pid=stoi(pid);
p[j].ArrivalTime=stoi(ArrivalTime);
p[j].BurstTime=stoi(BurstTime);
p[j].Priority=stoi(Priority);
pid.clear();
ArrivalTime.clear();
BurstTime.clear();
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
            temp1=p[m].BurstTime;
            p[m].BurstTime=p[n].BurstTime;
            p[n].BurstTime=temp1;
            temp2=p[m].Priority;
            p[m].Priority=p[n].Priority;
            p[n].Priority=temp2;
            temp3=p[m].pid;
            p[m].pid=p[n].pid;
            p[n].pid=temp3;
            
        }
    }
}

p[0].TimeQuantum=p[0].ArrivalTime;
p[0].WaitingTime=0;
for(int i=1;i<j;i++)
{
p[i].TimeQuantum=p[i-1].BurstTime+p[i-1].TimeQuantum;
p[i].WaitingTime=p[i].TimeQuantum-p[i].ArrivalTime;
//if waiting time is negative
	if(p[i].WaitingTime<0)
	{
	p[i].WaitingTime=0;
	}
}
for(int i=0;i<j;i++)
{
    p[i].Priority;
    p[i].BurstTime;
    p[i].ComplitionTime;
    p[i].pid;
}
for(int i=0;i<j;i++)
{
    p[i].TurnAroundTime=p[i].BurstTime+p[i].WaitingTime;
    
    sumtat+=p[i].TurnAroundTime;
    sumwt+=p[i].WaitingTime;
}
//calculating the start time and end time
p[0].StartTime=p[0].ArrivalTime;
p[0].ComplitionTime=p[0].StartTime+p[0].TurnAroundTime;
for(int i=1;i<j;i++)
{
   p[i].StartTime=p[i-1].ComplitionTime;
   p[i].ComplitionTime=p[i].StartTime+p[i].TurnAroundTime-p[i].WaitingTime;
}
//cout<<" processid  Priority  Arrival Time   Completion Time   Burst Time    Waiting Time    Turn Around Time "<<endl;
/*for(int i=0;i<j;i++)
{
    cout<<" "<<p[i].pid<<"\t  "<<p[i].Priority<<"\t  "<<p[i].ArrivalTime<<"\t "<<p[i].ComplitionTime<<"\t"<<p[i].BurstTime<<"\t\t  "<<p[i].WaitingTime<<"\t\t  "<<p[i].TurnAroundTime<<endl;
}
//p[4].awt1=sumwt/n;
//p[4].atat1=sumtat/n;
cout<<"Total waiting time: "<<sumwt<<endl;
cout<<"Average waiting time: "<<sumwt/j<<endl;
cout<<"Total turm around time : "<<sumtat<<endl;
cout<<"Average turn around time: "<<sumtat/j<<endl;
*/
    return p;
}

