//Server side to connect to client and accept process data then store them into a file
#include<iostream>
#include<fstream>
#include<sys/types.h>
using namespace std;
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>
#include "../inc/class.h"
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
	fout1.open("../bin/server_log.txt",ios::out|ios::trunc);
	fout1.clear();
	
	fout.open("../bin/server_log.txt",ios::app);
	//Making server socket.
	int serv_fd=socket(AF_INET,SOCK_STREAM,0);
	signal(SIGINT,sighandler);
	if(serv_fd == -1)
	{	fout<<"socket created error"<<endl;
		perror("Socket creation error");
		exit(1);
	}
	fout<<"socket generated"<<endl;
	//Storing server info in a structure.
	struct sockaddr_in sock_addr_serv;
	sock_addr_serv.sin_family = AF_INET;
	sock_addr_serv.sin_port = htons(PORT);
	sock_addr_serv.sin_addr.s_addr = inet_addr(IP);

	//Binding struct with server structure.
	if(bind(serv_fd,(struct sockaddr *)&sock_addr_serv,sizeof(sock_addr_serv))==-1)
	{	
		fout<<"Listning error"<<endl;
		perror("Bind error");
		exit(1);
	}
	fout<<"socket Binded successfully"<<endl;
	
	if(listen(serv_fd,5)==-1)
	{	fout<<"Listning error"<<endl;
		perror("listen error");
		exit(1);
	}
	fout<<"socket listning"<<endl;
		cout<<"server watiing for client request"<<endl;
		struct sockaddr_in sock_addr_cli;
		socklen_t cli_len = sizeof(sock_addr_cli);	
		int client_fd=accept(serv_fd,(struct sockaddr *)&sock_addr_cli,&cli_len);
		if(client_fd==-1)
		{	fout<<"socket accept"<<endl;
			perror("accept error");
			exit(1);
		}
		fout<<"socket accept"<<endl;
//Applying a infinite loop to read data sent from server.
while(1)
{
int n;
read(client_fd,&n,sizeof(n));

if(n!=0){

details d[n];
fstream file1;
//opening text file to store process info.

file1.open("../data/dt.txt",ios::app);
//reading every process data from client and storing it into a file.		
for(int i=0;i<n;i++){
read(client_fd,&d[i],sizeof(d[i]));

string data;
data+=to_string(d[i].ProcessType)+","+to_string(d[i].Pid)+","+to_string(d[i].ArrivalTime)+","+to_string(d[i].BurstTime)+","+to_string(d[i].Priority)+","+to_string(d[i].TimeQuantum);
cout<<data<<endl;


file1<<data<<endl;


}
file1.close();
//calling fcfs function.
if(d[0].ProcessType==1){

struct process *p=fcfs();
struct process q[size];

for(int i=0;i<n;i++){
q[i]=*p;

write(client_fd,&q[i],sizeof(q[i]));
p++;
}

	
}
//calling priority function.
else if(d[0].ProcessType==2){

struct process *p=priority();
struct process q[size];
for(int i=0;i<n;i++){
q[i]=*p;
write(client_fd,&q[i],sizeof(q[i]));
p++;
}

}
//calling round robin function.
else if(d[0].ProcessType==3){

struct process *p=rr();
struct process q[size];

for(int i=0;i<n;i++){
q[i]=*p;

write(client_fd,&q[i],sizeof(q[i]));
p++;
}

}
//calling Shortest job first function.
else if(d[0].ProcessType==4){

struct process *p=sjf();
struct process q[size];

for(int i=0;i<n;i++){
q[i]=*p;

write(client_fd,&q[i],sizeof(q[i]));
p++;
}

}
}
else{
break;
} 

}

//closing socket.
if(close(serv_fd)==-1){
	fout<<"socket closing error"<<endl;
	perror("socket close");
		exit(1);
		}
		fout<<"socket closed"<<endl;

fout.close();
		}

