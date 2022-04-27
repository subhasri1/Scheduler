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

//Function to sort processes a/c to their arrival time
bool compareAT(struct process a, struct process b)
{
    int x = a.ArrivalTime;
    int y = b.ArrivalTime;
    return x < y;
}

//Function to sort processes a/c to their pid
bool comparePID(struct process a, struct process b)
{
    int x = a.pid;
    int y = b.pid;
    return x < y;
}

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
    //////////////////////////////////////////////////////////////////////////////////////////////
    int tq = p[0].TimeQuantum;
    int index;
    queue<int> q;
    bool visited[100] = {false}, is_first_process = true;
    int current_time = 0, max_completion_time; // current time set to 0 at the beginning
    int completed = 0, total_idle_time; // completed also set to 0 at the beginning
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    //int tq = stoi(TimeQuantum);

    // sort structure on the basis of Arrival time in increasing order
    sort(p, p + j, compareAT);

    /////////////////////    LOGIC STARTS HERE    /////////////////////

    q.push(0);         // pushing the index in the queue
    visited[0] = true; // visited[ ] is false by default, it will become true once it gets assigned

    while (completed != j) // while n number of processes are not completed
    {
        index = q.front(); // push the index in front of the queue
        q.pop();

        if (p[index].bt_remaining == p[index].BurstTime) // process went in for the first time
        {
            // taking maximum of current time and arrival time, giving that value in start time
            p[index].StartTime = max(current_time, p[index].ArrivalTime);
            total_idle_time += (is_first_process == true) ? 0 : p[index].StartTime - current_time;
            // assigning the current time as start time for current process
            current_time = p[index].StartTime;
            is_first_process = false;
        }

        if (p[index].bt_remaining > tq) // if remaining burst Time - time slice is more than 0
        {
            p[index].bt_remaining -= tq; // remaining burst time = remaining burst time - time slice
            current_time += tq;          // current time will be changed to current time + time slice
        }
        else // If remaining burst - time slice is 0 (Means the process no longer needs to be executed)
        {
            current_time += p[index].bt_remaining;
            p[index].bt_remaining = 0; // BT remaining will be set to 0
            completed++;               // and the process will be completed

            p[index].ComplitionTime = current_time;
            p[index].TurnAroundTime = p[index].ComplitionTime - p[index].ArrivalTime;
            p[index].WaitingTime = p[index].TurnAroundTime - p[index].BurstTime;
            p[index].ResponseTime = p[index].StartTime - p[index].ArrivalTime;

            sum_tat += p[index].TurnAroundTime;
            sum_wt += p[index].WaitingTime;
            sum_rt += p[index].ResponseTime;
        }
        // check which new process needs to be pushed to Ready Queue from Input list
        for (int i = 1; i < j; i++)
        {
            if (p[i].bt_remaining > 0 && p[i].ArrivalTime <= current_time && visited[i] == false)
            {
                q.push(i);
                visited[i] = true;
            }
        }
        // check if Process on CPU needs to be pushed to Ready Queue
        if (p[index].bt_remaining > 0)
            q.push(index);

        // if queue is empty, just add one process from list, whose remaining burst time > 0
        if (q.empty())
        {
            for (int i = 1; i < j; i++)
            {
                if (p[i].bt_remaining > 0)
                {
                    q.push(i);
                    visited[i] = true;
                    break;
                }
            }
        }
    } // while loop ends here
    cout<<"ye"<<p[j].pid<<endl;

    // Calculate Length of Process completion cycle
    for (int i = 0; i < j; i++)
        // max_completion_time = max(max_completion_time, p[i].ComplitionTime);

        // sort so that process ID in output comes in Original input order
        sort(p, p + j, comparePID);

    // Output of all the calculations
    cout << "\nProcess No.\tAT\tBurst Time\tStart Time\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < j; i++)
        cout << i << "\t\t" << p[i].ArrivalTime << "\t" << p[i].BurstTime << "\t\t" << p[i].StartTime << "\t\t" << p[i].ComplitionTime << "\t" << p[i].TurnAroundTime << "\t" << p[i].WaitingTime << "\t" << p[i].ResponseTime << endl;
    cout << endl;

    cout << "\nAverage Turn Around time= " << (float)sum_tat / j; // may not be needed
    cout << "\nAverage Waiting Time= " << (float)sum_wt / j;      // may not be needed
    cout << "\nAverage Response Time= " << (float)sum_rt / j;     // may not be needed

    ////////////////////////////////////////////////////////////////////////////////////////////
    return p;
}
