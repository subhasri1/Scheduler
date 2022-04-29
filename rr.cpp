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

    string st, BurstTime, pid, ArrivalTime, TimeQuantum;
    int flag = 0, k, j = 0;
    fstream file1;
    file1.open("dt.txt", ios::in); //ios::in opens dt.txt in read mode to read the process data

    struct process *p = new struct process[10]; //Structure pointer object is called

    while (getline(file1, st)) //getline will read the data from the txt file
    {

        for (int i = 0; i < st.size(); i++) //flag value is defined in class.h
        {
            if (st[i] == ',') //if there is a ',' the flag will increment and goto the next value
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
        //Data will be assigned to p[j] ans stoi converts string data to integer
        p[j].pid = stoi(pid);
        p[j].ArrivalTime = stoi(ArrivalTime);
        p[j].BurstTime = stoi(BurstTime);
        p[j].TimeQuantum = stoi(TimeQuantum);

        //Now the data is assigned the txt file will be cleared
        pid.clear();
        ArrivalTime.clear();
        BurstTime.clear();
        TimeQuantum.clear();
        j++;
        flag = 0;
    }
    //Now we close the file as we have got the input data
    file1.close();

    int tq = p[0].TimeQuantum;

    //Variables
    int complete, current_time, change, WaitingTime, ComplitionTime, bt_remaining;
    double total_WaitingTime = 0.0;
    double total_TurnAroundTime = 0.0;
    for (int i = 0; i < j; i++)
        p[i].bt_remaining = p[i].BurstTime;

    //complete and current_time is assigned to 0 at the start of the process
    complete = 0;
    current_time = 0;

    //j is the number of processes, while complete < j means there are still processes to run
    while (complete < j)
    {
        change = 0;
        for (int i = 0; i < j; i++)
        {
            if (p[i].ArrivalTime <= current_time && p[i].bt_remaining > 0)
            {
                if (p[i].bt_remaining <= tq)
                {
                    complete++; //complete increments and it checks back again with the while loop
                    current_time += p[i].bt_remaining;
                    
                    //CALCULATIONS
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
        if (change == 0)
        {
            current_time++; //current time increments and goes back to the loop
        }
    }
    // cout<<fixed<<setprecision(2);
    // cout<<"Average Waiting Time: "<<(total_WaitingTime/j)<<"\n";
    // cout<<"Average Turn Around Time: "<<(total_TurnAroundTime/j)<<"\n";
    // cout<<"Number of processes are: "<<j<<endl;

    return p;
}