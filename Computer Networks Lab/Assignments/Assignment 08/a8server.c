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
	int server_fd,server_len,client_len;
	struct sockaddr_in server_address,client_address;
	char input[MAX],result[MAX];

	bzero(&server_address,sizeof(server_address));

	server_fd=socket(AF_INET,SOCK_DGRAM,0);
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(8888);
	server_len=sizeof(server_address);

	bind(server_fd,(struct sockaddr *)&server_address,server_len);
	printf("Server Running\n");

	while(1)
	{
		client_len=sizeof(client_address);
		recvfrom(server_fd,input,MAX,0,(struct sockaddr *)&client_address,&client_len);
		printf("[-] Client : %s\n\n",input);
	
		if(strcmp(input,"end")==0)
		{
			break;
		}

		printf("[+] Server : ");
		scanf("%[^\n]",result);
		getchar();
		printf("Sending message to the client\n\n");
		sendto(server_fd,result,strlen(result)+1,0,(struct sockaddr *)&client_address,client_len);

	}

	close(server_fd);
	
}
