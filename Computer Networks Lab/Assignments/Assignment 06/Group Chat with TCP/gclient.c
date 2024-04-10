#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#define MAX 100

int sockfd,res,len;
struct sockaddr_in address;
char cno[MAX];
pthread_t rthread,sthread;

void *receive(void *args)
{
	int receivefd=sockfd;
	struct sockaddr_in raddress=address;
	char input[MAX];

	while(1)
	{
		read(receivefd,input,MAX);
		if(strstr(input,"end")!=NULL)
		{
			strcat(input," : Left the chat");
			printf("%s\n",input);
			strcpy(input,"");
		}
		else printf("%s\n",input);
	}
	pthread_exit(NULL);
}

void *sender(void *args)
{
	int sendfd=sockfd;
	struct sockaddr_in saddress=address;
	char input[MAX],sendm[MAX];

	while(1)
	{
		scanf("%[^\n]",input);
		getchar();
		strcat(sendm,"Client ");
		strcat(sendm,cno);
		strcat(sendm," : ");
		strcat(sendm,input);
		write(sendfd,sendm,strlen(sendm)+1);
		strcpy(sendm,"");

		if(strcmp(input,"end")==0)
		{
			printf("Client %s Disconnected\n",cno);
			close(sockfd);
			exit(0);
		}
	}
	pthread_exit(NULL);
}

int main(int argc,char **argv)
{
	printf("Client %s Running\n",argv[1]);
	strcpy(cno,argv[1]);

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(8888);
	len=sizeof(address);

	res=connect(sockfd,(struct sockaddr *)&address,len);
	if(res==-1)
	{
		printf("Cannot connect to the server\n");
		perror("connect");
		exit(1);
	}
	else
	{
		printf("Connected to the server\n");
		printf("Enter any messages (type 'end' for disconnecting)\n\n");
	}
	
	pthread_create(&rthread,NULL,(void *)&receive,NULL);
	pthread_create(&sthread,NULL,(void *)&sender,NULL);
	pthread_join(sthread,NULL);
	pthread_join(rthread,NULL);
}
