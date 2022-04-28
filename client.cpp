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
	cout<<"1 for fcfs process, 2 for priority,3 for round robin,4 for shortest job first and 0 for exit";
	int k,pid,a,b,pr,n=0,tq;
	cin>>k;
	
	details d[10];
	struct process p[10];
	//struct process q[10];
	//struct process r[10];
	//struct process s[10];
	
	switch(k){
	case 0: l=0;
	
	write(serv_fd,&n,sizeof(n));
		break;
	
	case 1: cout<<"ener no of process"<<endl;
		cin>>n;
		write(serv_fd,&n,sizeof(n));
		
		for(int i=0;i<n;i++){
			
			cout<<"enter process pid,bt,at"<<endl;
			cin>>pid>>b>>a;
			d[i].set(pid,a,b,1,0,0);
			write(serv_fd,&d[i],sizeof(d[i]));
	
		}
		cout<<" pid  Arrival Time  Brust Time  Complition Time  Waiting Time  Turn Around Time"<<endl;
		
		for(int i=0;i<n;i++){
		//cout<<i<<endl;
		read(serv_fd,&p[i],sizeof(p[i]));
		cout<<" "<<p[i].pid<<"\t"<<p[i].ArrivalTime<<"\t"<<p[i].BurstTime<<"\t"<<p[i].ComplitionTime<<"\t   "<<p[i].WaitingTime<<"\t   "<<p[i].TurnAroundTime<<endl;
		//cout<<p[i].pid<<endl;
		}
		
		
		break;
		
	case 2: cout<<"ener no of process"<<endl;
		cin>>n;
		write(serv_fd,&n,sizeof(n));
		
		for(int i=0;i<n;i++){
			cout<<"enter process pid,bt,at,priority"<<endl;
			cin>>pid>>b>>a>>pr;
			d[i].set(pid,a,b,2,pr,0);
			write(serv_fd,&d[i],sizeof(d[i]));
	
		}
		//struct process p[10];
		cout<<" pid   priority   Brust Time   Waiting Time   Turn Around Time"<<endl;
		
		
		for(int i=0;i<n;i++){
		read(serv_fd,&p[i],sizeof(p[i]));
		//cout<<q[i].Priority<<endl;
		cout<<" "<<p[i].pid<<"\t"<<p[i].Priority<<"\t  "<<p[i].BurstTime<<"\t  "<<p[i].WaitingTime<<"\t   "<<p[i].TurnAroundTime<<endl;
		}
		
		
		
		break;
		
	case 3: cout<<"ener no of process and time Quantum"<<endl;
		cin>>n>>tq;
		write(serv_fd,&n,sizeof(n));
		
		for(int i=0;i<n;i++){
			cout<<"enter process pid,bt,at,time quantum"<<endl;
			cin>>pid>>b>>a;
			d[i].set(pid,a,b,3,0,tq);
			write(serv_fd,&d[i],sizeof(d[i]));
	
		}
		cout<<" pid   TimeQuantum   Brust Time   Waiting Time   Turn Around Time"<<endl;
		
		
		for(int i=0;i<n;i++){
		read(serv_fd,&p[i],sizeof(p[i]));
		//cout<<r[i].pid<<endl;
		cout<<" "<<p[i].pid<<"\t"<<p[i].TimeQuantum<<"\t  "<<p[i].BurstTime<<"\t   "<<p[i].WaitingTime<<"\t    "<<p[i].TurnAroundTime<<endl;
		}
		
		
		
		break;
		
		case 4: cout<<"enter no of process"<<endl;
		cin>>n;
		write(serv_fd,&n,sizeof(n));
		
		for(int i=0;i<n;i++){
			cout<<"enter process pid,bt,at"<<endl;
			cin>>pid>>b>>a;
			d[i].set(pid,a,b,4,0,0);
			write(serv_fd,&d[i],sizeof(d[i]));
	
		}
		cout<<" pid   Brust Time   Waiting Time   Turn Around Time"<<endl;
		for(int i=0;i<n;i++){
		read(serv_fd,&p[i],sizeof(p[i]));
		//cout<<s[i].pid<<endl;
		cout<<" "<<p[i].pid<<"\t  "<<p[i].BurstTime<<"\t   "<<p[i].WaitingTime<<"\t    "<<p[i].TurnAroundTime<<endl;
		}
		
		
		break;
		
		case 5: fstream file;
		file.open("dt.txt",ios::out|ios::trunc);
		file.close();
		
		
		cout<<"enter no of process and timeQuantum"<<endl;
		cin>>n;
		cin>>tq;
		//write(serv_fd,&n,sizeof(n));
		fstream file1;
		file1.open("dt.txt",ios::app);
		
		for(int i=0;i<n;i++){
			cout<<"enter process pid,bt,at,priority"<<endl;
			cin>>pid>>b>>a>>pr;
			d[i].set(pid,a,b,5,pr,tq);
			//write(serv_fd,&d[i],sizeof(d[i]));
			string data;
		
		data+=to_string(d[i].ProcessType)+","+to_string(d[i].Pid)+","+to_string(d[i].ArrivalTime)+","+to_string(d[i].BurstTime)+","+to_string(d[i].Priority)+","+to_string(d[i].TimeQuantum);
		cout<<data<<endl;


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
		cout<<"best algo is:";
		for(int i=0;i<4;i++){
		if(arr[i]==min){
		switch(i){
		case(0):cout<<"fcfs"<<endl;
			break;
		case(1):cout<<"priority"<<endl;
			break;
		case(2):cout<<"RR"<<endl;
			break;
		case(3):cout<<"sjf"<<endl;
			break;
		}
		}
		}
		break;
		


		
			
		
	/*case 1: cout<<"enter process pid,arrival and brust";
		cin>>pid>>a>>b;
		

	  	d.set(pid,a,b);
	//d.get();	
	//string ch;
	write(serv_fd,&d,sizeof(d));
	break;
	*/
	
		
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

