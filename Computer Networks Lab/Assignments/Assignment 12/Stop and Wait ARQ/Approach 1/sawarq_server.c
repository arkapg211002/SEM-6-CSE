#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define MAX 100

void main()
{
	int serverfd,clientfd,server_len,client_len,reuse=1;
	int sequence_no=-1,ack=0,delay=0;
	float check;
	struct sockaddr_in server_address,client_address;
	
	serverfd=socket(AF_INET,SOCK_STREAM,0);
	setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(8888);
	server_len=sizeof(server_address);
	
	printf("Server Running\n");
	bind(serverfd,(struct sockaddr *)&server_address,server_len);
	listen(serverfd,1);
	
	client_len=sizeof(client_address);
	clientfd=accept(serverfd,(struct sockaddr *)&client_address,&client_len);
	
	srand(time(NULL));
	while(1)
	{
		read(clientfd,(void *)&sequence_no,sizeof(int));
		if(ack==sequence_no)
		{
			printf("Received frame with sequence number : %d\n",sequence_no);
			ack=(ack+1)&1;
		}
		else
		{
			printf("Received DUPLICATE frame with sequence number : %d\n",sequence_no);
			ack=(sequence_no+1)&1;
		}
		
		check=(float)rand()/(float)RAND_MAX;
		if(check>0.8)	printf("Simulating Lost Acknowledgement\n");
		else
		{
			if(check>0.6)
			{
				printf("Simulating Delayed Acknowledgement\n");
				delay=(rand()%3)+3;
				sleep(delay);
			}
			write(clientfd,(void *)&ack,sizeof(int));
			printf("Acknowledgement with sequence number %d sent\n",ack);
		}
	}
}
