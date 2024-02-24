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

#define MAX 100

void main()
{
	int server_fd,client_fd;
	int server_len,client_len;

	struct sockaddr_in server_address,client_address;

	server_fd=socket(AF_INET,SOCK_STREAM,0);

	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(8888);
	server_len=sizeof(server_address);
	bind(server_fd,(struct sockaddr *)&server_address,server_len);

	listen(server_fd,5);
	while(1)
	{
		char ch;
		printf("server waiting\n");
		client_len=sizeof(client_address);
		client_fd=accept(server_fd,(struct sockaddr *)&client_address,&client_len);
		read(client_fd,&ch,1);
		ch+=1;
		write(client_fd,&ch,1);
		close(client_fd);
	}
}
