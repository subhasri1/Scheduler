//client side to send a process informations to server.

#include<iostream>
#include<sys/types.h>
#include<fstream>
using namespace std;
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<errno.h>
#include "../inc/class.h"
#include<vector>
#include<signal.h>
fstream fout;
#define size 100
#define PORT 9955
#define IP "127.0.0.1"

void sighandler(int signum){
 fout<<"Termination signal received";
 fout.close();
 exit(1);
}


int main(){
	
	fstream fout1;
	fout1.open("../bin/client_log.txt",ios::out|ios::trunc);
	fout1.clear();
	fout.open("../bin/client_log.txt",ios::app);
	signal(SIGINT,sighandler);
	int l=1;
	//Making a client socket
	int serv_fd=socket(AF_INET,SOCK_STREAM,0);
	if(serv_fd == -1)
	{	fout<<"Socket creation error."<<endl;
		perror("socket creation error");
		exit(1);
	}fout<<"Socket generated."<<endl;
	//server information stored in a structure.
	struct sockaddr_in sock_addr_serv;
	sock_addr_serv.sin_family = AF_INET;
	sock_addr_serv.sin_port = htons(PORT);
	sock_addr_serv.sin_addr.s_addr = inet_addr("IP");

	socklen_t len = sizeof(sock_addr_serv);
	//connecting client socket and server.
	if(connect(serv_fd,(struct sockaddr *)&sock_addr_serv,len)==-1){
		fout<<"socket connect error"<<endl;
		perror("connect error");
		exit(1);
}	
	fout<<"Socket connection established."<<endl;
	while(l){
	fstream file;
	
	file.open("../data/dt.txt",ios::out|ios::trunc);
		

		
	file.close();
	//Taking input of process user want to run.	
	cout<<"Press 1 for fcfs algorithm.\nPress 2 for priority algorithm.\nPress 3 for round robin algorithm.\nPress 4 for shortest job first algorithm.\nPress 5 for Comparing all algorithms.\nPress 0 for exit.\n";
	int k,pid,a,b,pr,n=0,tq;
	cin>>k;
	
	details d[size];
	struct process p[size];
	fout<<"Switch case running."<<endl;
	
	//Switch for different features.
	switch(k){
	case 0: l=0;
	
	write(serv_fd,&n,sizeof(n));
		break;
	
	case 1: cout<<"Enter no. of process."<<endl;
		cin>>n;
		write(serv_fd,&n,sizeof(n));
		//Input info of different processes.
		for(int i=0;i<n;i++){
			
			cout<<"Enter process pid,Burst TIme,Arrival TIme"<<endl;
			cin>>pid>>b>>a;
			d[i].set(pid,a,b,1,0,0);
			write(serv_fd,&d[i],sizeof(d[i]));
	
		}
		cout<<"Pid  Arrival Time  Burst Time  Complition Time  Waiting Time  Turn Around Time"<<endl;
		//reading output from server after algo is executed
		for(int i=0;i<n;i++){
		
		read(serv_fd,&p[i],sizeof(p[i]));
		cout<<p[i].pid<<"\t  "<<p[i].ArrivalTime<<"\t\t"<<p[i].BurstTime<<"\t\t"<<p[i].ComplitionTime<<"\t   "<<p[i].WaitingTime<<"\t\t"<<p[i].TurnAroundTime<<endl;
		
		}
		
		
		break;
		
	case 2: cout<<"Enter no. of process."<<endl;
		cin>>n;
		write(serv_fd,&n,sizeof(n));
		//Input info of different processes.
		for(int i=0;i<n;i++){
			cout<<"Enter process pid,Burst Time,Arrival TIme,Priority."<<endl;
			cin>>pid>>b>>a>>pr;
			d[i].set(pid,a,b,2,pr,0);
			write(serv_fd,&d[i],sizeof(d[i]));
	
		}
		
		cout<<"Pid  priority  BurstTime  ArrivalTime  WaitingTime  TurnAroundTime  CompletionTime"<<endl;
		
		//reading output from server after algo is executed
		for(int i=0;i<n;i++){
		read(serv_fd,&p[i],sizeof(p[i]));
		
		cout<<p[i].pid<<"\t"<<p[i].Priority<<"\t  "<<p[i].BurstTime<<"\t\t"<<p[i].ArrivalTime<<"\t\t"<<p[i].WaitingTime<<"\t\t"<<p[i].TurnAroundTime<<"\t"<<p[i].ComplitionTime<<endl;
		}
		
		
		
		break;
		
	case 3: cout<<"Enter no. of process and Time Quantum."<<endl;
		cin>>n>>tq;
		write(serv_fd,&n,sizeof(n));
		//Input info of different processes.
		for(int i=0;i<n;i++){
			cout<<"Enter process pid,Burst TIme,Arrival TIme,Time Quantum."<<endl;
			cin>>pid>>b>>a;
			d[i].set(pid,a,b,3,0,tq);
			write(serv_fd,&d[i],sizeof(d[i]));
	
		}
		cout<<"Pid   Time Quantum   Burst Time   Waiting Time   Turn Around Time"<<endl;
		
		//reading output from server after algo is executed.
		for(int i=0;i<n;i++){
		read(serv_fd,&p[i],sizeof(p[i]));
		//cout<<r[i].pid<<endl;
		cout<<p[i].pid<<"\t  "<<p[i].TimeQuantum<<"\t\t"<<p[i].BurstTime<<"\t\t"<<p[i].WaitingTime<<"\t\t"<<p[i].TurnAroundTime<<endl;
		}
		
		
		
		break;
		
		case 4: cout<<"Enter no. of process."<<endl;
		cin>>n;
		write(serv_fd,&n,sizeof(n));
		//Input info of different processes.
		for(int i=0;i<n;i++){
			cout<<"Enter process pid,Burst TIme,Arrival TIme."<<endl;
			cin>>pid>>b>>a;
			d[i].set(pid,a,b,4,0,0);
			write(serv_fd,&d[i],sizeof(d[i]));
	
		}
		cout<<"Pid   Arrival Time   Burst Time   Waiting Time   Turn Around Time"<<endl;
		//reading output from server after algo is executed
		for(int i=0;i<n;i++){
		read(serv_fd,&p[i],sizeof(p[i]));
		//cout<<s[i].pid<<endl;
		cout<<p[i].pid<<"\t  "<<p[i].ArrivalTime<<"\t\t"<<p[i].BurstTime<<"\t\t"<<p[i].WaitingTime<<"\t\t"<<p[i].TurnAroundTime<<endl;
		}
		
		
		break;
		
		case 5: 
		
		
		cout<<"Enter no. of process and Time Quantum."<<endl;
		cin>>n;
		cin>>tq;
		
		fstream file1;
		
		
		file1.open("../data/dt.txt",ios::app);
		//Input info of different processes.
		for(int i=0;i<n;i++){
			cout<<"enter process pid,Burst TIme,Arrival TIme,Priority."<<endl;
			cin>>pid>>b>>a>>pr;
			d[i].set(pid,a,b,5,pr,tq);
			;
			string data;
		
		data+=to_string(d[i].ProcessType)+","+to_string(d[i].Pid)+","+to_string(d[i].ArrivalTime)+","+to_string(d[i].BurstTime)+","+to_string(d[i].Priority)+","+to_string(d[i].TimeQuantum);
		


		file1<<data<<endl;
	
		}
		
		file1.close();
		
		struct process *q=fcfs();
		struct process *r=priority();
		struct process *s=rr();

		struct process *t=sjf();
		
		

		int arr[4]={0,0,0,0};
		
		//calling all algorithms
		
		for(int i=0;i<n;i++){

		arr[0]+=q->WaitingTime;

		q++;
		arr[1]+=r->WaitingTime;

		r++;
		arr[2]+=s->WaitingTime;

		s++;
		arr[3]+=t->WaitingTime;

		t++;
		}
		
		int min=arr[0];
		for(int i=1;i<4;i++){
		if(min<arr[i]){
		min=arr[i];
		}
		}
		//Printing the best algo.
		cout<<"Best algorithm for these processes: \n";
		for(int i=0;i<4;i++){
		if(arr[i]==min){
		switch(i){
		case(0):cout<<"-First Come First Serve Algorithm\n"<<endl;
			break;
		case(1):cout<<"-Priority Algorithm\n"<<endl;
			break;
		case(2):cout<<"-Round Robin Algorithm\n"<<endl;
			break;
		case(3):cout<<"-Shortest Job First Algorthm\n"<<endl;
			break;
		}
		}
		}
		break;
		
		
	/*
		default: 
		cout<<"Invalid choice,please enter valid choice"<<endl;	
		break;	*/
		

		
			
		
	
	
		
	}
	}
	


if(close(serv_fd)==-1){
	fout<<"Socket Close Error."<<endl;
	perror("socket close");
		exit(1);
		}
		fout<<"Socket closed."<<endl;
		fout.close();
		}

