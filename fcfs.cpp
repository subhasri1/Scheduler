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
#include <algorithm>
#include <iomanip>


bool comparisonAT(struct process a, struct process b)
{
    int x = a.ArrivalTime;
    int y = b.ArrivalTime;
    return x < y;
    //    if(x > y)
    //      return false;  // Apply sorting
    //    return true;   // no sorting
}

bool comparisonPID(struct process a, struct process b)
{
    int x = a.pid;
    int y = b.pid;
    return x < y;
}


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



// fcfs();
//process p[10];
//cout<<p[0].pid<<"jeet"<<endl;
//write(client_fd,&p,sizeof(p));


//using namespace std;
/*struct process_struct
{
    int pid;
    int at;                          // Arrival Time
    int bt;                          // CPU Burst time
    int ct, wt, tat, rt, start_time; // Completion, waiting, turnaround, response time
} ps[100];                           // Array of structure to store the info of each process.
*/
//struct process p[100];


    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    int length_cycle, total_idle_time = 0;

    //cout << fixed << setprecision(2);
    /*for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process " << i << " Arrival Time: ";
        cin >> ps[i].ArrivalTime;
        ps[i].pid = i;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process " << i << " Burst Time: ";
       // cin >> ps[i].BurstTime;
    }
*/
    // sort
    sort(p, p + j, comparisonAT);

    // calculation
    for (int i = 0; i < j; i++)
    {
        p[i].StartTime = (i == 0) ? p[i].ArrivalTime : max(p[i].ArrivalTime, p[i - 1].ComplitionTime);
        p[i].ComplitionTime = p[i].StartTime + p[i].BurstTime;
        p[i].TurnAroundTime = p[i].ComplitionTime - p[i].ArrivalTime;
        p[i].WaitingTime = p[i].TurnAroundTime - p[i].BurstTime;
        p[i].ResponseTime = p[i].StartTime - p[i].ArrivalTime;

        sum_tat += p[i].TurnAroundTime;
        sum_wt += p[i].WaitingTime;
        sum_rt += p[i].ResponseTime;
        total_idle_time += (i == 0) ? 0 : (p[i].StartTime - p[i - 1].ComplitionTime);
    }
    length_cycle = p[j - 1].ComplitionTime - p[0].StartTime;
    // sort so that process ID in output comes in Original order (just for interactivity)
    sort(p, p + j, comparisonPID);

    // Output
    //cout << "\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n";
    /*for (int i = 0; i < j; i++)
        cout << i << "\t\t" << p[i].ArrivalTime << "\t" << p[i].BurstTime << "\t\t" << p[i].ComplitionTime << "\t" << p[i].TurnAroundTime << "\t" << p[i].WaitingTime << "\t" << p[i].ResponseTime << endl;
    cout << endl;*/

    //cout << "\nAverage Turn Around time= " << sum_tat / j;
    //cout << "\nAverage Waiting Time= " << sum_wt / j;
    //cout << "\nAverage Response Time= " << sum_rt / j;
    return p;
}
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
