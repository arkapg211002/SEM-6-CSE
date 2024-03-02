#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>

#define MAX 100

void main()
{
	int sockfd,len,result;
	struct sockaddr_un address;
	char input[MAX],res[MAX];

	sockfd=socket(AF_UNIX,SOCK_STREAM,0);
	address.sun_family=AF_UNIX;
	strcpy(address.sun_path,"server");
	len=sizeof(address);
	result=connect(sockfd,(struct sockaddr *)&address,len);

	printf("Client running\n");

	while(1)
	{
		printf("Enter the IP Address (a.b.c.d) : ");
		scanf("%[^\n]",input);
		getchar();
		printf("Sending to the server\n");
		write(sockfd,input,strlen(input)+1);
		if(strcmp(input,"end")==0)
		{
			break;
		}
		printf("Waiting for the server..\n");
		sleep(1);
		read(sockfd,res,sizeof(res));
		printf("The IP Address %s is %s\n",input,res);
	}
	close(sockfd);
}
