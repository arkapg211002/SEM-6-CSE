#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

#define MAX 100
struct timeval timeout;

void gobackn(int client_fd)
{
	char input[MAX];
	int f,c,ack,next = 0;
	while (1)
	{
		sleep(1);
		read(client_fd,input,MAX);
		if(strcmp(input,"Exit")==0)
		{
			printf("Exit\n");
			close(client_fd);
			break;
		}
		
		f=atoi(input);
		strcpy(input,"");
		if(f != next)
		{
		    	printf("Frame %d discarded\nAcknowledgement sent: %d\n", f, ack);
		    	snprintf(input,MAX,"%d",ack);
		    	write(client_fd,input,strlen(input)+1);
		    	strcpy(input,"");
		    	continue;
		}
		c=rand() % 3;
		switch(c)
		{
		    	case 0:
		    		// printf("Frame %d not received\n",f);
		        	break;
		    	case 1:
				ack=f;
				sleep(2);
				printf("Frame %d received\nAcknowledement sent: %d\n", f, ack);
				snprintf(input,MAX,"%d", ack);
				write(client_fd,input,strlen(input)+1);
				strcpy(input,"");
				next=ack + 1;
				break;
		    	case 2:
				ack=f;
				printf("Frame %d received\nAcknowledement sent: %d\n", f, ack);
				snprintf(input,MAX,"%d",ack);
				write(client_fd,input,strlen(input)+1);
				strcpy(input,"");
				next=ack + 1;
				break;
		}
	}
}

void main()
{
	int server_fd,client_fd,client_len,server_len,result,num,win;
	struct sockaddr_in server_address,client_address;
	
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(8888);
	server_len=sizeof(server_address);
	bind(server_fd,(struct sockaddr *)&server_address,server_len);
	listen(server_fd,5);
	
	printf("Server Running\n");
	client_len=sizeof(client_address);
	client_fd=accept(server_fd,(struct sockaddr *)&client_address,&client_len);
	if(client_fd==-1)
	{
		printf("Client not connected\n");
		perror("accept");
		exit(1);
	}
	else 
	{
		printf("Client Connected Successfully\n");
		gobackn(client_fd);
	}
	close(server_fd);
}

