#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX 100
unsigned int sequence_no;

void main()
{
	int sockfd,result,len,seqno=0,ack=0,delay;
	struct sockaddr_in address;
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=htonl(INADDR_ANY);
	address.sin_port=htons(8888);
	len=sizeof(address);
	
	result=connect(sockfd,(struct sockaddr *)&address,len);
	if(result==-1)
	{
		printf("Cannot connect to the sender\n");
		perror("connect");
		exit(1);
	}
	else printf("Receiver Connected\n");
	
	srand(time(NULL));
	while(1)
	{
		read(sockfd,(void *)&sequence_no,sizeof(sequence_no));
		if(sequence_no==seqno)
		{
			printf("Frame received : %d\n",seqno);
			delay=rand()%7+1;
			printf("Sending ACK after %d seconds\n",delay);
			sleep(delay);
			ack=sequence_no+1;
			write(sockfd,(void *)&ack,sizeof(int));
			seqno=(seqno+1)%2;
		}
		else
		{
			printf("Duplicate Frame %d received\n",sequence_no);
			ack=sequence_no+1;
			write(sockfd,(void *)&ack,sizeof(int));
		}
	}
}
