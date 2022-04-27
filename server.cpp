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
#include "class.h"
//#include "fcfs.h"

int main(){
	fstream file1;
file1.open("dt.txt",ios::out|ios::trunc);
file1.close();
	
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

	if(bind(serv_fd,(struct sockaddr *)&sock_addr_serv,sizeof(sock_addr_serv))==-1)
	{
		perror("bind error");
		exit(1);
	}
	
	if(listen(serv_fd,5)==-1)
	{
		perror("listen error");
		exit(1);
	}
		cout<<"server watiing for client request"<<endl;
		struct sockaddr_in sock_addr_cli;
		socklen_t cli_len = sizeof(sock_addr_cli);	
		int client_fd=accept(serv_fd,(struct sockaddr *)&sock_addr_cli,&cli_len);
		if(client_fd==-1)
		{
			perror("accept error");
			exit(1);
		}
//cout<<sock_addr_cli.sin_port<<endl;
while(1)
{
int n;
read(client_fd,&n,sizeof(n));
fstream file;
file.open("dt.txt",ios::out|ios::trunc);
file.close();
if(n!=0){

details d[n];
fstream file1;
file1.open("dt.txt",ios::app);
for(int i=0;i<n;i++){
read(client_fd,&d[i],sizeof(d[i]));
d[i].get();
string data;
data+=to_string(d[i].ProcessType)+",";
data+=to_string(d[i].Pid)+","+to_string(d[i].ArrivalTime)+","+to_string(d[i].BurstTime)+","+to_string(d[i].Priority)+","+to_string(d[i].TimeQuantum);
cout<<data<<endl;

//data="haye ram";
file1<<data<<endl;


}
file1.close();

if(d[0].ProcessType==1){

struct process *p=fcfs();
struct process q[10];

for(int i=0;i<n;i++){
q[i]=*p;
cout<<q[i].pid<<endl;
//cout<<i<<endl;
write(client_fd,&q[i],sizeof(q[i]));
p++;
}/*
fstream file1;
file1.open("dt.txt",ios::out|ios::trunc);
file1.close();*/
	
}

else if(d[0].ProcessType==2){

struct process *p=priority();
struct process q[10];

for(int i=0;i<n;i++){
q[i]=*p;
cout<<q[i].pid<<endl;
//cout<<i<<endl;
write(client_fd,&q[i],sizeof(q[i]));
p++;
}

}

else if(d[0].ProcessType==3){

struct process *p=rr();
struct process q[10];

for(int i=0;i<n;i++){
q[i]=*p;
cout<<q[i].pid<<endl;
//cout<<i<<endl;
write(client_fd,&q[i],sizeof(q[i]));
p++;
}

}

else if(d[0].ProcessType==4){

struct process *p=sjf();
struct process q[10];

for(int i=0;i<n;i++){
q[i]=*p;
cout<<q[i].pid<<endl;
//cout<<i<<endl;
write(client_fd,&q[i],sizeof(q[i]));
p++;
}

}

else{
break;
} 
}
/*
if(d.rollno==0){
break;
}
else{
cout<<"from client:"<<endl;
d.get();
string data;
data+="process is:";
data+=to_string(d.rollno)+",arrival time is:"+to_string(d.standard)+",brust time is:"+to_string(d.fee)+"/n";
cout<<data<<endl;
fstream file1;
file1.open("dt.txt",ios::app);
//data="haye ram";
file1<<data;
file1.close();
}
//file1<<"aj1";
//file1 << data;
//write(client_fd,"hello",5);
}*/
//file1.close();
if(close(serv_fd)==-1){
	perror("socket close");
		exit(1);
		}

		}

