#include <iostream>
#include <algorithm>
#include <iomanip>



// fcfs();
//process p[10];
//cout<<p[0].pid<<"jeet"<<endl;
//write(client_fd,&p,sizeof(p));

struct process{
int pid,processtype,BrustTime,ArrivalTime,Priority,TimeQuantum,WaitingTime,TurnAroundTime,ComplitionTime,rt, start_time;//Add rt & Start_Time
}ps[100];

using namespace std;
/*struct process_struct
{
    int pid;
    int at;                          // Arrival Time
    int bt;                          // CPU Burst time
    int ct, wt, tat, rt, start_time; // Completion, waiting, turnaround, response time
} ps[100];                           // Array of structure to store the info of each process.
*/
//struct process p[100];

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
int main()
{
    int n;
    cout << "Enter total number of processes: ";
    cin >> n;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    int length_cycle, total_idle_time = 0;

    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process " << i << " Arrival Time: ";
        cin >> ps[i].ArrivalTime;
        ps[i].pid = i;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process " << i << " Burst Time: ";
        cin >> ps[i].BrustTime;
    }

    // sort
    sort(ps, ps + n, comparisonAT);

    // calculation
    for (int i = 0; i < n; i++)
    {
        ps[i].start_time = (i == 0) ? ps[i].ArrivalTime : max(ps[i].ArrivalTime, ps[i - 1].ComplitionTime);
        ps[i].ComplitionTime = ps[i].start_time + ps[i].BrustTime;
        ps[i].TurnAroundTime = ps[i].ComplitionTime - ps[i].ArrivalTime;
        ps[i].WaitingTime = ps[i].TurnAroundTime - ps[i].BrustTime;
        ps[i].rt = ps[i].start_time - ps[i].ArrivalTime;

        sum_tat += ps[i].TurnAroundTime;
        sum_wt += ps[i].WaitingTime;
        sum_rt += ps[i].rt;
        total_idle_time += (i == 0) ? 0 : (ps[i].start_time - ps[i - 1].ComplitionTime);
    }
    length_cycle = ps[n - 1].ComplitionTime - ps[0].start_time;
    // sort so that process ID in output comes in Original order (just for interactivity)
    sort(ps, ps + n, comparisonPID);

    // Output
    cout << "\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t\t" << ps[i].ArrivalTime << "\t" << ps[i].BrustTime << "\t\t" << ps[i].ComplitionTime << "\t" << ps[i].TurnAroundTime << "\t" << ps[i].WaitingTime << "\t" << ps[i].rt << endl;
    cout << endl;

    cout << "\nAverage Turn Around time= " << sum_tat / n;
    cout << "\nAverage Waiting Time= " << sum_wt / n;
    cout << "\nAverage Response Time= " << sum_rt / n;
    return 0;
}
