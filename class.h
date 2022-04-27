//#include<stdio.h>
//#include<iostream>

//using namespace std;

class details{
public:
int Pid,ArrivalTime,BurstTime,ProcessType,Priority,TimeQuantum;
void set(int r,int s,int f,int t,int p,int q){
Pid=r;
ArrivalTime=s;
BurstTime=f;
ProcessType=t;
Priority=p;
TimeQuantum=q;
};
void get(){
};
};

struct process{
int pid,processtype,BurstTime,ArrivalTime,Priority,TimeQuantum,WaitingTime,TurnAroundTime,ComplitionTime,bt_remaining,StartTime,ResponseTime;
};

struct process* fcfs();
struct process* priority();
struct process* rr();






