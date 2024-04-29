#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX 100

int main(int argc,char **argv)
{
	int sockfd,len,result;
	struct sockaddr_in address;
	char input[MAX],res[MAX];

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(8888);
	len=sizeof(address);

	printf("Client %s Running\n",argv[1]);

	result=connect(sockfd,(struct sockaddr *)&address,len);
	if(result==-1)
	{
		printf("Cannot connect to the server\n");
		perror("connect");
		exit(1);
	}
	else
	{
		printf("Client connected to the server\n");
	}

	while(1)
	{
		printf("Enter the bitstream : ");
		scanf("%[^\n]",input);
		getchar();
		printf("Sending message to the server\n");
		write(sockfd,input,strlen(input)+1);
		if(strcmp(input,"end")==0)
		{
			printf("Client %s Ending..\n",argv[1]);
			break;
		}

		printf("Waiting for the server\n");
		sleep(1);
		read(sockfd,res,MAX);
		printf("Bitstream after bitstuffing : %s\n",res);
		
	}

	close(sockfd);
	return 0;
}
