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

int main(){
	/*fstream file1;
file1.open("dt.txt",ios::trunc);
file1.close();*/
	
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
	
details d;
read(client_fd,&d,sizeof(d));
if(d.rollno==0){
break;
}
else{
cout<<"from client:"<<endl;
d.get();
string data;
data+="Rollno is:";
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
}
//file1.close();
if(close(serv_fd)==-1){
	perror("socket close");
		exit(1);
		}

		}

