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
#include <time.h>

#define MAX 100

int main(int argc)
{
	int sockfd,len,count,reuse=1;
	struct sockaddr_in address;
	struct ip_mreq mreq;
	char input[MAX];

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))<0)
	{
		perror("setsockopt");
		return 1;
	}

	address.sin_family=AF_INET;
	address.sin_addr.s_addr=htonl(INADDR_ANY);
	address.sin_port=htons(8888);
	len=sizeof(address);
	
	// Send
	if(argc > 1)
	{
		address.sin_addr.s_addr=inet_addr("224.0.0.1");

		while(1)
		{
			printf("Enter the message : ");
			scanf("%[^\n]",input);
			getchar();

			printf("Sending Message to %s\n","224.0.0.1");
			sendto(sockfd,input,strlen(input)+1,0,(struct sockaddr *)&address,len);

			if(strcmp(input,"end")==0)
			{
				close(sockfd);
				break;
			}
			sleep(5);
		}
	}
	else // Receive
	{
		bind(sockfd,(struct sockaddr *)&address,len);
		
		mreq.imr_multiaddr.s_addr=inet_addr("224.0.0.1");
		mreq.imr_interface.s_addr=htonl(INADDR_ANY);

		if(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))<0)
		{
			printf("Error Adding\n");
			perror("setsockopt");
			return 1;
		}
		
		while(1)
		{		
			count=recvfrom(sockfd,input,MAX,0,(struct sockaddr *)&address,&len);
			if(count<0)
			{
				perror("recvfrom");
				return 1;
			}
			else if(count==0) break;

			printf("Received from %s : %s\n",inet_ntoa(address.sin_addr),input);

			if(strcmp(input,"end")==0)
			{
				close(sockfd);
				break;
			}
		}
	}

	return 0;
}
