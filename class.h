//#include<stdio.h>
//#include<iostream>

//using namespace std;




class details{
//int Pid,ArrivalTime,BurstTime,ProcessType,Priority,TimeQuantum;
public:
int Pid,ArrivalTime,BurstTime,ProcessType,Priority,TimeQuantum;
/*int getpid(){
	return pid;
}*/
void set(int r,int s,int f,int t,int p,int q){
Pid=r;
ArrivalTime=s;
BurstTime=f;
ProcessType=t;
Priority=p;
TimeQuantum=q;
};

};

struct process{
int pid,processtype,BurstTime,ArrivalTime,Priority,TimeQuantum,WaitingTime,TurnAroundTime,ComplitionTime,bt_remaining,StartTime,ResponseTime;
};

bool comparisonAT(struct process , struct process );
bool comparisonPID(struct process, struct process);

//class algorithm {
//public:
struct process* fcfs();
struct process* priority();
struct process* rr();
struct process* sjf();
//}
/*
void sighandler(int signum){

}*/



