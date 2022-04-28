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
#include "class.h"
#include<vector>
//#include "struct.h"
#define size 100

//client send a single character 'a' to server and receive b from the server.
int main(){
	int l=1;
	int serv_fd=socket(AF_INET,SOCK_STREAM,0);
	if(serv_fd == -1)
	{
		perror("socket creation error");
		exit(1);
	}

	struct sockaddr_in sock_addr_serv;
	sock_addr_serv.sin_family = AF_INET;
	sock_addr_serv.sin_port = 9955;
	sock_addr_serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	socklen_t len = sizeof(sock_addr_serv);

	if(connect(serv_fd,(struct sockaddr *)&sock_addr_serv,len)==-1){
		perror("connect error");
		exit(1);
}	
	while(l){
	fstream file;
		file.open("dt.txt",ios::out|ios::trunc);
		file.close();
	cout<<"Press 1 for fcfs algorithm.\nPress 2 for algorithm.\nPress 3 for round robin algorithm.\nPress 4 for shortest job first algorithm.\nPress 5 for Comparing all algorithms.\nPress 0 for exit.\n";
	int k,pid,a,b,pr,n=0,tq;
	cin>>k;
	
	details d[size];
	struct process p[size];
	
	
	switch(k){
	case 0: l=0;
	
	write(serv_fd,&n,sizeof(n));
		break;
	
	case 1: cout<<"Enter no. of process."<<endl;
		cin>>n;
		write(serv_fd,&n,sizeof(n));
		
		for(int i=0;i<n;i++){
			
			cout<<"Enter process pid,Brust TIme,Arrival TIme"<<endl;
			cin>>pid>>b>>a;
			d[i].set(pid,a,b,1,0,0);
			write(serv_fd,&d[i],sizeof(d[i]));
	
		}
		cout<<"Pid  Arrival Time  Brust Time  Complition Time  Waiting Time  Turn Around Time"<<endl;
		
		for(int i=0;i<n;i++){
		//cout<<i<<endl;
		read(serv_fd,&p[i],sizeof(p[i]));
		cout<<p[i].pid<<"\t  "<<p[i].ArrivalTime<<"\t\t"<<p[i].BurstTime<<"\t\t"<<p[i].ComplitionTime<<"\t   "<<p[i].WaitingTime<<"\t\t"<<p[i].TurnAroundTime<<endl;
		//cout<<p[i].pid<<endl;
		}
		
		
		break;
		
	case 2: cout<<"Enter no. of process."<<endl;
		cin>>n;
		write(serv_fd,&n,sizeof(n));
		
		for(int i=0;i<n;i++){
			cout<<"Enter process pid,Brust Time,Arrival TIme,Priority."<<endl;
			cin>>pid>>b>>a>>pr;
			d[i].set(pid,a,b,2,pr,0);
			write(serv_fd,&d[i],sizeof(d[i]));
	
		}
		//struct process p[10];
		cout<<"Pid   priority   Brust Time   Waiting Time   Turn Around Time"<<endl;
		
		
		for(int i=0;i<n;i++){
		read(serv_fd,&p[i],sizeof(p[i]));
		//cout<<q[i].Priority<<endl;
		cout<<p[i].pid<<"\t  "<<p[i].Priority<<"\t\t  "<<p[i].BurstTime<<"\t\t"<<p[i].WaitingTime<<"\t\t"<<p[i].TurnAroundTime<<endl;
		}
		
		
		
		break;
		
	case 3: cout<<"Enter no. of process and Time Quantum."<<endl;
		cin>>n>>tq;
		write(serv_fd,&n,sizeof(n));
		
		for(int i=0;i<n;i++){
			cout<<"Enter process pid,Burst TIme,Arrival TIme,Time Quantum."<<endl;
			cin>>pid>>b>>a;
			d[i].set(pid,a,b,3,0,tq);
			write(serv_fd,&d[i],sizeof(d[i]));
	
		}
		cout<<"Pid   Time Quantum   Brust Time   Waiting Time   Turn Around Time"<<endl;
		
		
		for(int i=0;i<n;i++){
		read(serv_fd,&p[i],sizeof(p[i]));
		//cout<<r[i].pid<<endl;
		cout<<p[i].pid<<"\t  "<<p[i].TimeQuantum<<"\t\t"<<p[i].BurstTime<<"\t\t"<<p[i].WaitingTime<<"\t\t"<<p[i].TurnAroundTime<<endl;
		}
		
		
		
		break;
		
		case 4: cout<<"Enter no. of process."<<endl;
		cin>>n;
		write(serv_fd,&n,sizeof(n));
		
		for(int i=0;i<n;i++){
			cout<<"Enter process pid,Burst TIme,Arrival TIme."<<endl;
			cin>>pid>>b>>a;
			d[i].set(pid,a,b,4,0,0);
			write(serv_fd,&d[i],sizeof(d[i]));
	
		}
		cout<<"Pid   Arrival Time   Brust Time   Waiting Time   Turn Around Time"<<endl;
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
		//write(serv_fd,&n,sizeof(n));
		fstream file1;
		file1.open("dt.txt",ios::app);
		
		for(int i=0;i<n;i++){
			cout<<"enter process pid,Burst TIme,Arrival TIme,Priority."<<endl;
			cin>>pid>>b>>a>>pr;
			d[i].set(pid,a,b,5,pr,tq);
			//write(serv_fd,&d[i],sizeof(d[i]));
			string data;
		
		data+=to_string(d[i].ProcessType)+","+to_string(d[i].Pid)+","+to_string(d[i].ArrivalTime)+","+to_string(d[i].BurstTime)+","+to_string(d[i].Priority)+","+to_string(d[i].TimeQuantum);
		//cout<<data<<endl;


		file1<<data<<endl;
	
		}
		file1.close();
		

		struct process *q=fcfs();
		struct process *r=priority();
		struct process *s=rr();

		struct process *t=sjf();

		int arr[4]={0,0,0,0};
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
		


		
			
		
	
	
		
	}
	}
	
/*	read(serv_fd,&ch,5);
	cout<<"from server:"<<ch<< endl;
*/
if(close(serv_fd)==-1){
	perror("socket close");
		exit(1);
		}
		}

