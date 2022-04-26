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
	cout<<"for fcfs ,1 for process and 2 for exit";
	int k,pid,a,b;
	cin>>k;
	details d;
	switch(k){
	case 1: cout<<"enter process pid,arrival and brust";
		cin>>pid>>a>>b;
		

	  	d.set(pid,a,b);
	//d.get();	
	//string ch;
	write(serv_fd,&d,sizeof(d));
	break;
	
	case 2: p=0;
	

	  	d.set(0,0,0);
	//d.get();	
	//string ch;
	write(serv_fd,&d,sizeof(d));
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

