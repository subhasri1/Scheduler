//Function to Implement Priority algorithm.
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
#include "../inc/class.h"
#define max 100

struct process* priority()
{

string st,BurstTime,pid,ArrivalTime,Priority;
int flag=0,k,j=0;
fstream file1;
//we have open the file in the read mode below

file1.open("../data/dt.txt",ios::in);
		
//a structure pointer object in made below with .
struct process *p=new struct process[max];
//struct process *p;
//from the next line it will collect the data from each line .
while(getline(file1,st)){
//in each line file conatin the processid ,arrival time and burst time
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
//below lines stores the data in the process structure define in the class.h file 
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
//closer of file "dt.txt" .since all the data related to the process has been stored in the process structure define in  class.h 

file1.close();
		

    int temp1,temp2,temp3,temp4;
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
           temp4=p[m].ArrivalTime;
		p[m].ArrivalTime=p[n].ArrivalTime;
		p[n].ArrivalTime=temp4;
            
        }
    }
}
//time quantum is used to  store the data no any specific uses related to the process 
//waiting time is calculated below
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

//turn around time is calculated below
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

    return p;
}
