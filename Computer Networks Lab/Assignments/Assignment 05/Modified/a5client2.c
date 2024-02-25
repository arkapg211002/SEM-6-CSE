#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX 100

void main()
{
	int sockfd,len,result;
	struct sockaddr_in address;
	char input[MAX];

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(8888);
	len=sizeof(address);
	printf("Client Started\n");
	result=connect(sockfd,(struct sockaddr *)&address,len);
	if(result==-1)
	{
		printf("Cannot connect to the server\n");
		perror("connect");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Connected to the server\n");
	}

	while(1)
	{
		printf("Enter the bit stream : ");
		scanf("%[^\n]",input);
		getchar();

		printf("\nSending %s to the server\n",input);
		write(sockfd,input,strlen(input)+1);
		if(strcmp(input,"end")==0)
		{
			break;
		}

		printf("Waiting for the server\n");
		sleep(1);
		read(sockfd,input,MAX);
		printf("Received from the server with bit stuffing : %s\n\n",input);
	}
	close(sockfd);
}
