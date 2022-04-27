#include<iostream>
#include<sys/types.h>
using namespace std;
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<errno.h>
#include "class.h"
//#include "struct.h"

//client send a single character 'a' to server and receive b from the server.
int main(){
	int p=1;
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
	while(p){
	cout<<"1 for fcfs process, 2 for priority,3 for round robin and 0 for exit";
	int k,pid,a,b,pr,n=0,tq;
	cin>>k;
	details d[n];
	details z[n];
	details y[n];
	switch(k){
	case 0: p=0;
	
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
		struct process p[10];
		for(int i=0;i<n;i++){
		read(serv_fd,&p[i],sizeof(p[i]));
		//cout<<p[i].pid<<endl;
		}
		
		cout<<" pid   Brust Time   Waiting Time   Turn Around Time"<<endl;
		for(int i=0;i<n;i++)
		{
    		cout<<" "<<p[i].pid<<"\t"<<p[i].BurstTime<<"\t   "<<p[i].WaitingTime<<"\t   "<<p[i].TurnAroundTime<<endl;
		}
		
		break;
		
	case 2: cout<<"ener no of process"<<endl;
		cin>>n;
		write(serv_fd,&n,sizeof(n));
		
		for(int i=0;i<n;i++){
			cout<<"enter process pid,bt,at,priority"<<endl;
			cin>>pid>>b>>a>>pr;
			z[i].set(pid,a,b,2,pr,0);
			write(serv_fd,&z[i],sizeof(z[i]));
	
		}
		struct process q[10];
		for(int i=0;i<n;i++){
		read(serv_fd,&q[i],sizeof(q[i]));
		//cout<<q[i].Priority<<endl;
		}
		cout<<" pid   priority   Brust Time   Waiting Time   Turn Around Time"<<endl;
		for(int i=0;i<n;i++)
		{
    		cout<<" "<<q[i].pid<<"\t"<<q[i].Priority<<"\t  "<<q[i].BurstTime<<"\t  "<<q[i].WaitingTime<<"\t   "<<q[i].TurnAroundTime<<endl;
		}
		
		break;
		
	case 3: cout<<"ener no of process"<<endl;
		cin>>n;
		write(serv_fd,&n,sizeof(n));
		
		for(int i=0;i<n;i++){
			cout<<"enter process pid,bt,at,time quantum"<<endl;
			cin>>pid>>b>>a>>tq;
			y[i].set(pid,a,b,3,0,tq);
			write(serv_fd,&y[i],sizeof(y[i]));
	
		}
		struct process r[10];
		for(int i=0;i<n;i++){
		read(serv_fd,&r[i],sizeof(r[i]));
		cout<<r[i].pid<<endl;
		}
		cout<<" pid   TimeQuantum   Brust Time   Waiting Time   Turn Around Time"<<endl;
		for(int i=0;i<n;i++)
		{
    		cout<<" "<<r[i].pid<<"\t"<<r[i].TimeQuantum<<"\t  "<<r[i].BurstTime<<"\t   "<<r[i].WaitingTime<<"\t    "<<r[i].TurnAroundTime<<endl;
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

