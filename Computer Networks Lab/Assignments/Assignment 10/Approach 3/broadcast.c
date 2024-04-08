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

#define MAX 100

int main(int argc,char **argv)
{
	if(argc==1)
	{
		
		int sockfd,server_len,brd=1;
		struct sockaddr_in server_address;
		char input[MAX];

		sockfd=socket(AF_INET,SOCK_DGRAM,0);
		setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&brd,sizeof(brd));
		server_address.sin_family=AF_INET;
		server_address.sin_addr.s_addr=htonl(INADDR_BROADCAST);
		server_address.sin_port=htons(8888);
		server_len=sizeof(server_address);

		printf("Sender Running\n");

		while(1)
		{
			printf("Enter the message to be broadcasted : ");
			scanf("%[^\n]",input);
			getchar();
			sendto(sockfd,input,strlen(input)+1,0,(struct sockaddr *)&server_address,server_len);
			if(strcmp(input,"end")==0) break;
		}
		close(sockfd);
	}
	else
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
	
		printf("Receiver %s Running\n",argv[1]);

		while(1)
		{
			recvfrom(sockfd,input,MAX,0,NULL,0);
			printf("Broadcasted Message : %s\n",input);
			if(strcmp(input,"QUIT")==0) break;
		}
		close(sockfd);
	}
	return 0;
}
