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
#include <pthread.h>

#define MAX 100
int sockfd,server_len,client_len;
struct sockaddr_in client_address;

void *receiver(void *args)
{
	char input[MAX];
	while(1)
	{
		recvfrom(sockfd,input,MAX,0,(struct sockaddr *)&client_address,&client_len);
		printf("%s\n",input);
		if(strcmp(input,"Server : end")==0)
		{
			close(sockfd);
			exit(0);
		}
	}
}

void *sender(void *args)
{
	char input[MAX];
	char sendm[MAX];
	while(1)
	{
		scanf("%[^\n]",input);
		getchar();
		strcat(sendm,"Client : ");
		strcat(sendm,input);
		sendto(sockfd,sendm,strlen(sendm)+1,0,(struct sockaddr *)&client_address,client_len);
		strcpy(sendm,"");
		if(strcmp(input,"end")==0)
		{
			close(sockfd);
			exit(0);
		}
	}
}

void main()
{
	pthread_t rthread,sthread;
	struct sockaddr_in server_address;
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(8081);
	server_len=sizeof(server_address);
	client_address.sin_family=AF_INET;
	client_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	client_address.sin_port=htons(8080);
	client_len=sizeof(client_address);
	bind(sockfd,(struct sockaddr *)&client_address,client_len);
	
	printf("Client Running\n");
	printf("Enter any message (Type : end --to stop chat)\n\n");
	
	pthread_create(&sthread,NULL,(void *)&sender,NULL);
	pthread_create(&rthread,NULL,(void *)&receiver,NULL);
	pthread_join(rthread,NULL);
	pthread_join(sthread,NULL);
}
