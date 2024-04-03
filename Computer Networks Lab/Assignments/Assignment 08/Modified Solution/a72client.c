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
pthread_t rthread, sthread;

void *receiver(void *args)
{
	int sockfd,server_len,client_len;
	struct sockaddr_in server_address,client_address;
	char input[MAX];

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(8080);
	//server_len=sizeof(server_address);

	client_address.sin_family=AF_INET;
	client_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	client_address.sin_port=htons(8081);
	client_len=sizeof(client_address);

	bind(sockfd,(struct sockaddr *)&client_address,client_len);

	while(1)
	{
		server_len=sizeof(server_address);
		recvfrom(sockfd,input,MAX,0,(struct sockaddr *)&server_address,&server_len);
		printf("%s\n",input);
		if(strcmp(input,"Server : end")==0)
		{
			//close(sockfd);
			exit(0);
		}
	}
	close(sockfd);
	pthread_exit(NULL);
}

void *sender(void *args)
{
	int sockfd,server_len,client_len;
	struct sockaddr_in server_address,client_address;
	char input[MAX],sendm[MAX];

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(8080);
	//server_len=sizeof(server_address);

	client_address.sin_family=AF_INET;
	client_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	client_address.sin_port=htons(8081);
	client_len=sizeof(client_address);

	bind(sockfd,(struct sockaddr *)&client_address,client_len);

	while(1)
	{
		scanf("%[^\n]",input);
		getchar();

		strcat(sendm,"Client : ");
		strcat(sendm,input);
		
		server_len=sizeof(server_address);
		sendto(sockfd,sendm,strlen(sendm)+1,0,(struct sockaddr *)&server_address,server_len);
		strcpy(sendm,"");
		if(strcmp(input,"end")==0)
		{
			//close(sockfd);
			exit(0);
		}
	}
	close(sockfd);
	pthread_exit(NULL);
}

void main()
{
	printf("Client Running\n");
	printf("Enter any message : 'end' to stop\n\n");
	pthread_create(&rthread,NULL,(void *)&receiver,NULL);
	pthread_create(&sthread,NULL,(void *)&sender,NULL);
	pthread_join(rthread,NULL);
	pthread_join(sthread,NULL);
}
