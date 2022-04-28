#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include "class.h"
using namespace std;

struct process *rr()
{
    // int n,bt[20],wt[20],tat[20],avwt=0,avtat=0,i,j,arrival[20],ct[20],rt[20];
    string st, BurstTime, pid, ArrivalTime, TimeQuantum;
    int flag = 0, k, j = 0;
    fstream file1;
    file1.open("dt.txt", ios::in);
    // struct process* p = (process*)calloc(10,sizeof(struct process));
    // struct process p[10];
    struct process *p = new struct process[10];
    // struct process *p;
    while (getline(file1, st))
    {
        // cout<<st<<endl;
        for (int i = 0; i < st.size(); i++)
        {
            if (st[i] == ',')
            {
                flag++;
            }
            else if (flag == 1)
            {
                pid += st[i];
            }
            else if (flag == 2)
            {
                ArrivalTime += st[i];
            }
            else if (flag == 3)
            {
                BurstTime += st[i];
            }
            else if (flag == 5)
            {
                TimeQuantum += st[i];
            }
        }

        p[j].pid = stoi(pid);
        p[j].ArrivalTime = stoi(ArrivalTime);
        p[j].BurstTime = stoi(BurstTime);
        p[j].TimeQuantum = stoi(TimeQuantum);

        pid.clear();
        ArrivalTime.clear();
        BurstTime.clear();
        TimeQuantum.clear();
        j++;
        flag = 0;
    }
    file1.close();
    int tq = p[0].TimeQuantum;
    
    int complete,current_time,change, WaitingTime, ComplitionTime, bt_remaining;
    double total_WaitingTime = 0.0;
    double total_TurnAroundTime = 0.0;
  cout<<"While ke ppehle tq:"<<tq<<endl;
    for(int i=0; i<j; i++)
        p[i].bt_remaining = p[i].BurstTime;

    complete = 0;
    current_time = 0;
    
    
 
    while(complete < j)
    {
        change = 0;
        for(int i=0; i<j; i++)
        {
            if(p[i].ArrivalTime <= current_time && p[i].bt_remaining > 0)
            {
                if(p[i].bt_remaining <= tq)
                {
                    complete++;
                    current_time += p[i].bt_remaining;
 
                    p[i].ComplitionTime = current_time;
                    p[i].TurnAroundTime = p[i].ComplitionTime - p[i].ArrivalTime;
                    p[i].WaitingTime = p[i].TurnAroundTime - p[i].BurstTime;
 
                    total_WaitingTime += p[i].WaitingTime;
                    total_TurnAroundTime += p[i].TurnAroundTime;
 
                    p[i].bt_remaining = 0;
                }
                else
                {
                    current_time += tq;
                    p[i].bt_remaining -= tq;
                }
                change++;
            }
        }
        if(change == 0)
        {
            current_time++;
        }
    }
    cout<<fixed<<setprecision(2);
    cout<<"Average Waiting Time: "<<(total_WaitingTime/j)<<"\n";
    cout<<"Average Turn Around Time: "<<(total_TurnAroundTime/j)<<"\n";
    //cout<<"Number of processes are: "<<j<<endl;
    
    return p;
}
