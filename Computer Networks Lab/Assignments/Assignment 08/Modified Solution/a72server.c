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
	int server_fd,server_len,client_len;
	struct sockaddr_in server_address,client_address;
	char input[MAX];

	server_fd=socket(AF_INET,SOCK_DGRAM,0);

	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(8080);
	server_len=sizeof(server_address);

	client_address.sin_family=AF_INET;
	client_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	client_address.sin_port=htons(8081);
	//client_len=sizeof(client_address);

	bind(server_fd,(struct sockaddr *)&server_address,server_len);

	while(1)
	{
		client_len=sizeof(client_address);
		recvfrom(server_fd,input,MAX,0,(struct sockaddr *)&client_address,&client_len);
		printf("%s\n",input);
		if(strcmp(input,"Client : end")==0)
		{
			//close(server_fd);
			exit(0);
		}
	}
	close(server_fd);
	pthread_exit(NULL);
}

void *sender(void *args)
{
	int server_fd,server_len,client_len;
	struct sockaddr_in server_address,client_address;
	char input[MAX],sendm[MAX];

	server_fd=socket(AF_INET,SOCK_DGRAM,0);
	
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(8080);
	server_len=sizeof(server_address);

	client_address.sin_family=AF_INET;
	client_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	client_address.sin_port=htons(8081);
	client_len=sizeof(client_address);

	bind(server_fd,(struct sockaddr *)&server_address,server_len);

	while(1)
	{
		scanf("%[^\n]",input);
		getchar();

		strcat(sendm,"Server : ");
		strcat(sendm,input);
		
		client_len=sizeof(client_address);
		sendto(server_fd,sendm,strlen(sendm)+1,0,(struct sockaddr *)&client_address,client_len);
		strcpy(sendm,"");
		if(strcmp(input,"end")==0)
		{
			//close(server_fd);
			exit(0);
		}
	}
	close(server_fd);
	pthread_exit(NULL);
}

void main()
{
	printf("Server Running\n");
	printf("Enter any message : (end) to stop\n\n");
	pthread_create(&rthread,NULL,(void *)&receiver,NULL);
	pthread_create(&sthread,NULL,(void *)&sender,NULL);
	pthread_join(rthread,NULL);
	pthread_join(sthread,NULL);
}
