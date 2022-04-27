// Round Robin CPU Scheduling Algorithm
#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>
using namespace std;

//We save all the process data into a structure
// struct process_struct
// {
//     int pid;
//     int at; //ArrivalTime
//     int bt; //BurstTime
//     int ct, wt, tat, rt, start_time; //WaitingTime //TurnAroundTime //TimeQuantum
//     int bt_remaining;
// } ps[100]; //process_struct to process

struct process{
int pid,processtype,BurstTime,ArrivalTime,Priority,TimeQuantum,WaitingTime,TurnAroundTime,ComplitionTime,StartTime, bt_remaining, ResponseTime;
}ps[100]; //SAHIL BHAI ADD StartTime, bt_remaining, ResponseTime, sum_tat = 0, sum_wt=0, sum_rt=0

//This is to compare processes on the basis of Arrival Time
bool compareAT(struct process a, struct process b) // arrival time compare karwane ke liye
{
    int x = a.ArrivalTime;
    int y = b.ArrivalTime;
    return x < y;
    //    if(x > y)
    //    return false;  // Apply sorting
    //    return true;   // no sorting
}

//This is to compare process ID of the processes
bool comparePID(struct process a, struct process b)
{
    int x = a.pid;
    int y = b.pid;
    return x < y;
}

int main()
{

    int n, index; // n is number of processes
    queue<int> q;
    bool visited[100] = {false}, is_first_process = true;
    int current_time = 0, max_completion_time;                // current time set to 0 at the beginning
    int completed = 0, TimeQuantum, total_idle_time = 0; 	      // completed also set to 0 at the beginning
    cout << "Enter total number of processes: ";
    cin >> n;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;

    cout << fixed << setprecision(2); // taking output upto 2 decimal places

    for (int i = 0; i < n; i++) // taking input of Arrival time of the processes
    {
        cout << "\nEnter Process " << i << " Arrival Time: ";
        cin >> ps[i].ArrivalTime; // ps[i].ArrivalTime is arrival time
        ps[i].pid = i;
    }

    for (int i = 0; i < n; i++) // Taking input of burst time of the processes
    {
        cout << "\nEnter Process " << i << " Burst Time: ";
        cin >> ps[i].BurstTime;
        ps[i].bt_remaining = ps[i].BurstTime;
    }

    cout << "\nEnter time slice: "; // Taking input of the time slice
    cin >> TimeQuantum;

    // sort structure on the basis of Arrival time in increasing order
    sort(ps, ps + n, compareAT);

    /////////////////////    LOGIC STARTS HERE    /////////////////////

    q.push(0);         // pushing the index in the queue
    visited[0] = true; // visited[ ] is false by default, it will become true once it gets assigned

    while (completed != n) // while n number of processes are not completed
    {
        index = q.front(); // push the index in front of the queue
        q.pop();

        if (ps[index].bt_remaining == ps[index].BurstTime) // process went in for the first time
        {
            // taking maximum of current time and arrival time, giving that value in start time
            ps[index].StartTime = max(current_time, ps[index].ArrivalTime);
            total_idle_time += (is_first_process == true) ? 0 : ps[index].StartTime - current_time;
            // assigning the current time as start time for current process
            current_time = ps[index].StartTime;
            is_first_process = false;
        }

        if (ps[index].bt_remaining - TimeQuantum > 0) // if remaining burst Time - time slice is more than 0
        {
            ps[index].bt_remaining -= TimeQuantum; // remaining burst time = remaining burst time - time slice
            current_time += TimeQuantum;           // current time will be changed to current time + time slice
        }
        else // If remaining burst - time slice is 0 (Means the process no longer needs to be executed)
        {
            current_time += ps[index].bt_remaining;
            ps[index].bt_remaining = 0; // BT remaining will be set to 0
            completed++;                // and the process will be completed

            ps[index].ComplitionTime = current_time;
            ps[index].TurnAroundTime = ps[index].ComplitionTime - ps[index].ArrivalTime;
            ps[index].WaitingTime = ps[index].TurnAroundTime - ps[index].BurstTime;
            ps[index].ResponseTime = ps[index].StartTime - ps[index].ArrivalTime;

            sum_tat += ps[index].TurnAroundTime;
            sum_wt += ps[index].WaitingTime;
            sum_rt += ps[index].ResponseTime;
        }

        // check which new process needs to be pushed to Ready Queue from Input list
        for (int i = 1; i < n; i++)
        {
            if (ps[i].bt_remaining > 0 && ps[i].ArrivalTime <= current_time && visited[i] == false)
            {
                q.push(i);
                visited[i] = true;
            }
        }
        // check if Process on CPU needs to be pushed to Ready Queue
        if (ps[index].bt_remaining > 0)
            q.push(index);

        // if queue is empty, just add one process from list, whose remaining burst time > 0
        if (q.empty())
        {
            for (int i = 1; i < n; i++)
            {
                if (ps[i].bt_remaining > 0)
                {
                    q.push(i);
                    visited[i] = true;
                    break;
                }
            }
        }
    } // while loop ends here

    // Calculate Length of Process completion cycle
    for (int i = 0; i < n; i++)
        max_completion_time = max(max_completion_time, ps[i].ComplitionTime);


    // sort so that process ID in output comes in Original input order
    sort(ps, ps + n, comparePID);

    // Output of all the calculations
    cout << "\nProcess No.\tAT\tBurst Time\tStart Time\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t\t" << ps[i].ArrivalTime << "\t" << ps[i].BurstTime << "\t\t" << ps[i].StartTime << "\t\t" << ps[i].ComplitionTime << "\t" << ps[i].TurnAroundTime << "\t" << ps[i].WaitingTime << "\t" << ps[i].ResponseTime << endl;
    cout << endl;

    cout << "\nAverage Turn Around time= " << (float)sum_tat / n;       // may not be needed
    cout << "\nAverage Waiting Time= " << (float)sum_wt / n;            // may not be needed
    cout << "\nAverage Response Time= " << (float)sum_rt / n;           // may not be needed
    return 0;
}
