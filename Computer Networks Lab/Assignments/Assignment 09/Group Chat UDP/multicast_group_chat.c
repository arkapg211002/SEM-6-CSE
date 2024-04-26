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

int sockfd,multilen,reuse=1;
char cno[MAX];
struct sockaddr_in multicast;
struct ip_mreq mreq;
pthread_t rthread,sthread;
int flag=0;
	
void *receive(void *args)
{
	int receivefd=sockfd;
	struct sockaddr_in raddress=multicast;
	int rlen=sizeof(raddress);
	char input[MAX];
	
	while(1)
	{
		recvfrom(receivefd,input,MAX,0,(struct sockaddr *)&raddress,&rlen);
		if(!flag) 
		{
			if(strstr(input,"end")!=NULL)
			{
				strcat(input,": Left the chat");
				printf("%s\n",input);
			}
			else printf("%s\n",input);
			strcpy(input,"");
		}
		flag=0;
	}
	pthread_exit(NULL);
}

void *sender(void *args)
{
	int sendfd=sockfd;
	struct sockaddr_in saddress=multicast;
	int slen=sizeof(saddress);
	char input[MAX],sendm[MAX];
	
	while(1)
	{
		scanf("%[^\n]",input);
		getchar();
		
		flag=1;
		strcat(sendm,"Client ");
		strcat(sendm,cno);
		strcat(sendm," : ");
		strcat(sendm,input);
		
		sendto(sendfd,sendm,strlen(sendm)+1,0,(struct sockaddr *)&saddress,slen);
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
	printf("Member %s Running\n",argv[1]);
	printf("Enter any messages : (end to disconnect)\n\n");
	strcpy(cno,argv[1]);
	
	multicast.sin_family=AF_INET;
	multicast.sin_addr.s_addr=inet_addr("224.0.0.1");
	multicast.sin_port=htons(8888);
	multilen=sizeof(multicast);
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	bind(sockfd,(struct sockaddr *)&multicast,multilen);
	mreq.imr_multiaddr.s_addr=inet_addr("224.0.0.1");
	mreq.imr_interface.s_addr=INADDR_ANY;
	setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
	
	pthread_create(&rthread,NULL,(void *)&receive,NULL);
	pthread_create(&sthread,NULL,(void *)&sender,NULL);
	pthread_join(sthread,NULL);
	pthread_join(rthread,NULL);
}
