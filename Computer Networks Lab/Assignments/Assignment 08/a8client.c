#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX 100

void main()
{
	int sockfd,len,result;
	struct sockaddr_in address;
	char input[MAX],res[MAX];

	printf("Client Running\n");

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&address,sizeof(address));
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(8888);
	len=sizeof(address);
	result=connect(sockfd,(struct sockaddr *)&address,len);
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
		printf("[+] Client : ");
		scanf("%[^\n]",input);
		getchar();
		printf("Sedning message to the server\n\n");
		sendto(sockfd,input,strlen(input)+1,0,(struct sockaddr *)NULL,len);
		if(strcmp(input,"end")==0)
		{
			break;
		}

		sleep(1);
		recvfrom(sockfd,res,MAX,0,(struct sockaddr *)NULL,NULL);
		printf("[-] Server : %s\n\n",res);
	}

	
	close(sockfd);
}
