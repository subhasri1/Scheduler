//Function to Implement Round Robin algorithm.
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
#include "../inc/class.h"
#define max 100

using namespace std;

struct process *rr()
{   
    // defining variables
    string st, BurstTime, pid, ArrivalTime, TimeQuantum;
    int flag = 0, k, j = 0;
    // fstream opens the file
    fstream file1;
    // dt.txt is opened in read mode to get the data
    file1.open("../data/dt.txt", ios::in);

    // max is a macro
    struct process *p = new struct process[max];
    // getline is used to read string from a source file
    while (getline(file1, st))
    {
        // flags are set so ',' is not taken as input and we get only the data
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
        // stoi is used to convert string to int for calculations
        p[j].pid = stoi(pid);
        p[j].ArrivalTime = stoi(ArrivalTime);
        p[j].BurstTime = stoi(BurstTime);
        p[j].TimeQuantum = stoi(TimeQuantum);

        // file is cleared after we took all the input required
        pid.clear();
        ArrivalTime.clear();
        BurstTime.clear();
        TimeQuantum.clear();
        j++;
        flag = 0;
    }
    // we close the file
    file1.close();
    
    // here we define tq(time quantum)
    int tq = p[0].TimeQuantum;

    int complete, current_time, change, WaitingTime, ComplitionTime, bt_remaining;
    double total_WaitingTime = 0.0;
    double total_TurnAroundTime = 0.0;

    // here we set bt remaining as their original bt before the calculations start
    for (int i = 0; i < j; i++)
        p[i].bt_remaining = p[i].BurstTime;

    complete = 0;
    current_time = 0;

    while (complete < j) // while completed processes are not equals to the number of processes
    {
        change = 0; // change is set to 0 at the start and will increment with the loop
        for (int i = 0; i < j; i++)
        {
            if (p[i].ArrivalTime <= current_time && p[i].bt_remaining > 0)
            {
                if (p[i].bt_remaining <= tq) //~~~~if bt rem <= tq means the process will complete in this run
                {
                    complete++; // hence complete is incremented
                    current_time += p[i].bt_remaining;

                    // calculations regarding the variable updates
                    p[i].ComplitionTime = current_time;
                    p[i].TurnAroundTime = p[i].ComplitionTime - p[i].ArrivalTime;
                    p[i].WaitingTime = p[i].TurnAroundTime - p[i].BurstTime;

                    total_WaitingTime += p[i].WaitingTime;
                    total_TurnAroundTime += p[i].TurnAroundTime;

                    p[i].bt_remaining = 0;
                }
                else //~~~~else if bt rem > tq means the process will run again
                {
                    current_time += tq;
                    p[i].bt_remaining -= tq;
                    
                }
                change++;
            }
        }
        if (change == 0)
        {
            current_time++;
        }
    }
   

    return p;
}

