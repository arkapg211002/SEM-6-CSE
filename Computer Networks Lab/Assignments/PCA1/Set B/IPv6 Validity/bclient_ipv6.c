#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>

#define MAX 100

void main()
{
	int sockfd,len,result;
	struct sockaddr_un address;
	char input[MAX];
	int r;
	sockfd=socket(AF_UNIX,SOCK_STREAM,0);
	address.sun_family=AF_UNIX;
	strcpy(address.sun_path,"bserverip6");
	len=sizeof(address);
	result=connect(sockfd,(struct sockaddr *)&address,len);
	printf("Client Running\n");
	if(result==-1)
	{
		printf("Cannot connect to the server\n");
		perror("connect");
		exit(1);
	}
	else
	{
		printf("Connected to the server\n");
	}
	while(1)
	{
		printf("Enter the IPv6 Address : ");
		scanf("%[^\n]",input);
		getchar();
		if(strcmp(input,"end")==0)
		{
			write(sockfd,input,strlen(input)+1);
			break;
		}
		printf("Sending the IPv6 Address to the server\n");
		write(sockfd,input,strlen(input)+1);
		printf("Waiting for the server\n");
		sleep(1);
		read(sockfd,(void *)&r,sizeof(int));
		printf("Client Received : %d\n",r);
		if(r==1)
		{
			printf("The IPv6 Address %s is valid\n",input);
		}
		else
		{
			printf("The IPv6 Address %s is not valid\n",input);
		}
	}
	close(sockfd);
}
