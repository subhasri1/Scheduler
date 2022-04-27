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
#include "class.h"
struct process* fcfs()
{   
//int n,bt[20],wt[20],tat[20],avwt=0,avtat=0,i,j,arrival[20],ct[20],rt[20];
string st,BurstTime,pid,ArrivalTime;
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
}
//cout<<"pid:"<<pid;
p[j].pid=stoi(pid);
p[j].ArrivalTime=stoi(ArrivalTime);
p[j].BurstTime=stoi(BurstTime);
pid.clear();
ArrivalTime.clear();
BurstTime.clear();
j++;
flag=0;
}
//cout<<p[0].pid<<"mila"<<endl;
file1.close();
/*
    cout<<"Enter total number of processes(maximum 20):";
    cin>>n;


    cout<<"\nEnter Process Arrival Time aka DURATION \n";
    for(i=0;i<n;i++)
    {
        cout<<"P["<<i+1<<"]:";
        cin>>arrival[i];
    }

    cout<<"\nEnter Process Burst Time aka DURATION \n";
    for(i=0;i<n;i++)
    {
        cout<<"P["<<i+1<<"]:";
        cin>>bt[i];
    }


    wt[0]=0;    //waiting time for first process is 0
    //calculating waiting time
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
    }
    cout<<"\nProcess\tArrival Time \tBurst Time\tWaiting Time\tTurnaround Time \tCompletion Time \tResponse Time";
    //calculating turnaround time
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        avwt+=wt[i];
        avtat+=tat[i];
        ct[i]=arrival[i]+tat[i];

     cout<<"\nP["<<i+1<<"]" "\t\t" <<arrival[i]<<"\t\t"<<bt[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i]<<"\t\t"<<ct[i];
    }
    avwt/=i;
    avtat/=i;
    cout<<"\n\nAverage Waiting Time:"<<avwt;
    cout<<"\nAverage Turnaround Time:"<<avtat;
    */
    //cout<<"pid:"<<p[0].pid;
    
	return p;
    
}
