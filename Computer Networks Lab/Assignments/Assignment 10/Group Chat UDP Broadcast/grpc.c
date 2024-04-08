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
char cno[MAX];
pthread_t rthread,sthread;
int flag=0;

void *sender(void *args)
{
	
	int sockfd,server_len,brd=1;
	struct sockaddr_in server_address;
	char input[MAX],sendm[MAX];

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&brd,sizeof(brd));
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_BROADCAST);
	server_address.sin_port=htons(8888);
	server_len=sizeof(server_address);

	while(1)
	{
		scanf("%[^\n]",input);
		getchar();

		flag=1;
		strcat(sendm,"Member ");
		strcat(sendm,cno);
		strcat(sendm," : ");
		strcat(sendm,input);
		
		sendto(sockfd,sendm,strlen(sendm)+1,0,(struct sockaddr *)&server_address,server_len);
		strcpy(sendm,"");

		if(strcmp(input,"end")==0)
		{
			printf("Member %s Disconnected\n",cno);
			close(sockfd);
			exit(0);
		}
	}
	pthread_exit(NULL);
}

void *receive(void *args)
{

	int sockfd,len,reuse=1;
	struct sockaddr_in address;
	char input[MAX];

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=htonl(INADDR_ANY);
	address.sin_port=htons(8888);
	len=sizeof(address);
	bind(sockfd,(struct sockaddr *)&address,len);

	while(1)
	{
		recvfrom(sockfd,input,MAX,0,NULL,0);
		if(!flag)
		{
			if(strstr(input,"end")!=NULL)
			{
				strcat(input," : Left the chat");
				printf("%s\n",input);
			}
			else printf("%s\n",input);
			strcpy(input,"");
		}
		flag=0;
	}
	pthread_exit(NULL);
}

int main(int argc,char **argv)
{
	printf("Member %s Running\n",argv[1]);
	printf("Enter any messages : (type 'end' to stop)\n\n");
	strcpy(cno,argv[1]);

	pthread_create(&rthread,NULL,(void *)&receive,NULL);
	pthread_create(&sthread,NULL,(void *)&sender,NULL);
	pthread_join(sthread,NULL);
	pthread_join(rthread,NULL);
	return 0;
}



