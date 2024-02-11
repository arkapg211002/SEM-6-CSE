#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/un.h>
#include<sys/socket.h>

void main()
{
	int sockfd;
	int len;

	struct sockaddr_un address;
	int result;

	char ch='A';

	sockfd=socket(AF_UNIX,SOCK_STREAM,0);
	address.sun_family=AF_UNIX;
	strcpy(address.sun_path,"server");
	len=sizeof(address);

	result=connect(sockfd,(struct sockaddr *)&address,len);

	if(result==-1)
	{
		printf("Cannot connect to the server\n");
		exit(1);
	}

	write(sockfd,&ch,1);
	read(sockfd,&ch,1);
	printf("From Server : %c\n",ch);
	close(sockfd);
}
