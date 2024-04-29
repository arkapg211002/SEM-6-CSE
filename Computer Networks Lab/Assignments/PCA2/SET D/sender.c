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

void main()
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
		printf("Enter the bitstream to be broadcasted : ");
		scanf("%[^\n]",input);
		getchar();
		sendto(sockfd,input,strlen(input)+1,0,(struct sockaddr *)&server_address,server_len);
		if(strcmp(input,"end")==0) break;
	}
	close(sockfd);
}
