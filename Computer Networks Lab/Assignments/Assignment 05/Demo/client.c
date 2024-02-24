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
	int sockfd,len;
	struct sockaddr_in address;
	int result;
	char ch='A';

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(8888);
	len=sizeof(address);

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

	write(sockfd,&ch,1);
	read(sockfd,&ch,1);
	printf("character from server : %c\n",ch);
	close(sockfd);
	exit(0);
}
