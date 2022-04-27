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
struct process* sjf()
{
//int j,BrustTime[20],WaitingTime[20],TurnArroundTime[20],avwt=0,avtArrivalTime=0,i,j,arrival[20],ComplitionTime[20],ResponseTime[20];
string st,BrustTime,pid,ArrivalTime;
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
}
//cout<<"pid:"<<pid;
p[j].pid=stoi(pid);
p[j].ArrivalTime=stoi(ArrivalTime);
p[j].BrustTime=stoi(BrustTime);
pid.clear();
ArrivalTime.clear();
BrustTime.clear();
j++;
flag=0;
}
file1.close();

struct process_struct
{
  int Pid;
  int ArrivalTime;
  int BrustTime;
  int ComplitionTime,WaitingTime,TurnArroundTime,ResponseTime,StartTime;
}p[100];

int main()
{
    
    int j;
    bool is_completed[100]={false},is_first_process=true;
    int current_time = 0;
    int completed = 0;;
    cout<<"Enter total number of processes: ";
    //cin>>j;    
    int sum_tArrivalTime=0,sum_wt=0,sum_rt=0,total_idle_time=0,prev=0,length_cycle;
    floArrivalTime cpu_utilizArrivalTimeion;
    int max_completion_time,min_arrival_time;
    
    cout << fixed << setprecision(2);

    for(int i=0;i<j;i++)
    {
        cout<<"\nEnter Process " <<i<< " Arrival Time: ";
        //cin >> p[i].ArrivalTime;
        p[i].Pid=i;
    }
    
    for(int i=0;i<j;i++)
    {
        cout<<"\nEnter Process " <<i<< " Burst Time: ";
        //cin >> p[i].BrustTime;
    }
    
    
    while(completed!=j)
    {
        //find process with min. burst time in ready queue ArrivalTime current time
        int min_index = -1;
        int minimum = INT_MAX;
        for(int i = 0; i < j; i++) {
            if(p[i].ArrivalTime <= current_time && is_completed[i] == false) {
                if(p[i].BrustTime < minimum) {
                    minimum = p[i].BrustTime;
                    min_index = i;
                }
                if(p[i].BrustTime== minimum) {
                    if(p[i].ArrivalTime < p[min_index].ArrivalTime) {
                        minimum= p[i].BrustTime;
                        min_index = i;
                    }
                }
            }
        }

        if(min_index==-1)
        {
            current_time++;
        }
        else
        {
        p[min_index].StartTime = current_time;
        p[min_index].ComplitionTime = p[min_index].StartTime + p[min_index].BrustTime;
        p[min_index].TurnArroundTime = p[min_index].ComplitionTime - p[min_index].ArrivalTime;
        p[min_index].WaitingTime = p[min_index].TurnArroundTime - p[min_index].BrustTime;
        p[min_index].ResponseTime = p[min_index].WaitingTime;
        // p[min_index].ResponseTime = p[min_index].StartTime - p[min_index].ArrivalTime;
                
        sum_tArrivalTime +=p[min_index].TurnArroundTime;
        sum_wt += p[min_index].WaitingTime;
        sum_rt += p[min_index].ResponseTime;
        total_idle_time += (is_first_process==true) ? 0 : (p[min_index].StartTime -  prev);
        
        completed++;
        is_completed[min_index]=true;
        current_time = p[min_index].ComplitionTime;
        prev= current_time;
        is_first_process = false;  
        }
    }
    
    //CalculArrivalTimee Length of Process completion cycle
    max_completion_time = INT_MIN;
    min_arrival_time = INT_MAX;
    for(int i=0;i<j;i++)
    {
        max_completion_time = max(max_completion_time,p[i].ComplitionTime);
        min_arrival_time = min(min_arrival_time,p[i].ArrivalTime);
    }
    length_cycle = max_completion_time - min_arrival_time;

     //Output
    cout<<"\nProcess No.\TurnArroundTime\tCPU Burst Time\tCT\tTArrivalTime\tWT\tRT\j";
    for(int i=0;i<j;i++)
     cout<<i<<"\t\t"<<p[i].ArrivalTime<<"\t"<<p[i].BrustTime<<"\t\t"<<p[i].ComplitionTime<<"\t"<<p[i].TurnArroundTime<<"\t"<<p[i].WaitingTime<<"\t"<<p[i].ResponseTime<<endl;
    cout<<endl;  
    
    cpu_utilizArrivalTimeion = (floArrivalTime)(length_cycle - total_idle_time)/ length_cycle;

    cout<<"\nAverage Turn Around time= "<< (floArrivalTime)sum_tArrivalTime/j;
    cout<<"\nAverage Waiting Time= "<<(floArrivalTime)sum_wt/j;
    cout<<"\nAverage Response Time= "<<(floArrivalTime)sum_rt/j;    
    cout<<"\nThroughput= "<<j/(floArrivalTime)length_cycle;
    cout<<"\nCPU UtilizArrivalTimeion(Percentage)= " << cpu_utilizArrivalTimeion*100;
    return 0;
}
