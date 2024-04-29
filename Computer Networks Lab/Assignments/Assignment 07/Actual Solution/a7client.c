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
	char check[MAX];
	char input[MAX],res[MAX];

	printf("Client Running\n");

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(8888);
	len=sizeof(address);
//	result=connect(sockfd,(struct sockaddr *)&address,len);
	
	strcpy(input,"Hello from client");
	printf("Sending %s to the server\n",input);
	sendto(sockfd,input,strlen(input)+1,0,(struct sockaddr *)&address,len);
	result=recvfrom(sockfd,res,MAX,0,(struct sockaddr *)&address,&len);
	if(result==-1)
	{
		printf("Cannot connect to the server\n");
		perror("recvfrom");
		exit(1);
	}
	else 
	{
		printf("Server sent : %s\n",res);
		printf("Connected to the server\n");
		strcpy(res,"");
		strcpy(input,"");
	}

	while(1)
	{
		printf("Enter the dataword : ");
		scanf("%[^\n]",input);
		getchar();
		printf("Sedning message to the server\n");
		sendto(sockfd,input,strlen(input)+1,0,(struct sockaddr *)&address,len);
		if(strcmp(input,"end")==0)
		{
			break;
		}

		printf("Waitng for the server\n");
		sleep(1);
		recvfrom(sockfd,res,MAX,0,(struct sockaddr *)&address,&len);
		printf("Client Received the codeword : %s\n",res);
	}

	
	close(sockfd);
}
