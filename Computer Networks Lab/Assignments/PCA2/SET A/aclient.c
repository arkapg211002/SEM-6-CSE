#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define MAX 100
void main()
{
	int sockfd,result,len;
	struct sockaddr_in address;
	char input[MAX],res[MAX];
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
		exit(1);
	}
	else printf("Connected to the server\n");
	while(1)
	{
		printf("Enter bitstream : ");
		scanf("%[^\n]",input);
		getchar();
		printf("Sending address to the server\n");
		write(sockfd,input,strlen(input)+1);
		if(strcmp(input,"end")==0) break;
		printf("Waiting for the server\n");
		sleep(1);
		read(sockfd,res,MAX);
		printf("Client Received bitstream after bitstuffing from the server : %s\n",res);
	}
	close(sockfd);
}
