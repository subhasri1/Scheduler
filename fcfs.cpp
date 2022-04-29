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


bool comparisonAT(struct process a, struct process b)//Compare Arrival Time
{
    int x = a.ArrivalTime;
    int y = b.ArrivalTime;
    return x < y;

}

bool comparisonPID(struct process a, struct process b)//Compare Pid
{
    int x = a.pid;
    int y = b.pid;
    return x < y;
}


struct process* fcfs()//Structure contains FCFS scheduler
{

string st,BurstTime,pid,ArrivalTime;
int flag=0,k,j=0;
fstream file1;
file1.open("dt.txt",ios::in);
//hear we are opening the file dt.txt in read mode
struct process *p=new struct process[10];
//we are fetching each line of dt.txt file for storing Arrival Time Brust Time
while(getline(file1,st)){

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
//value for pid arrival time Brust time in structure process define in class.h file
p[j].pid=stoi(pid);
p[j].ArrivalTime=stoi(ArrivalTime);
p[j].BurstTime=stoi(BurstTime);
pid.clear();
ArrivalTime.clear();
BurstTime.clear();
j++;
flag=0;
}

file1.close();
//close





    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    int length_cycle, total_idle_time = 0;


    sort(p, p + j, comparisonAT);//sorting of Arrival time


    for (int i = 0; i < j; i++)
    {
        p[i].StartTime = (i == 0) ? p[i].ArrivalTime : max(p[i].ArrivalTime, p[i - 1].ComplitionTime);
        p[i].ComplitionTime = p[i].StartTime + p[i].BurstTime;
        p[i].TurnAroundTime = p[i].ComplitionTime - p[i].ArrivalTime;
        p[i].WaitingTime = p[i].TurnAroundTime - p[i].BurstTime;
        p[i].ResponseTime = p[i].StartTime - p[i].ArrivalTime;
//Calculation Of Complition Time, Turn Around Time, Waiting time, Response Time.
        sum_tat += p[i].TurnAroundTime;
        sum_wt += p[i].WaitingTime;
        sum_rt += p[i].ResponseTime;
        total_idle_time += (i == 0) ? 0 : (p[i].StartTime - p[i - 1].ComplitionTime);
    }
    length_cycle = p[j - 1].ComplitionTime - p[0].StartTime;

    sort(p, p + j, comparisonPID);//Sorting Of pid


    return p;
}
