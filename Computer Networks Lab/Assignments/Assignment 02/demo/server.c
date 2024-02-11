#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/un.h>
#include<sys/socket.h>

void main()
{
	int server_fd,client_fd;
	int server_len,client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;

	unlink("server");
	server_fd=socket(AF_UNIX,SOCK_STREAM,0);
	server_address.sun_family=AF_UNIX;
	strcpy(server_address.sun_path,"server");
	server_len=sizeof(server_address);
	bind(server_fd,(struct sockaddr *)&server_address,server_len);

	listen(server_fd,5);
	while(1)
	{
		char ch;
		printf("Waiting..\n");

		client_len=sizeof(client_address);
		client_fd=accept(server_fd,(struct sockaddr *)&client_address,&client_len);

		read(client_fd,&ch,1);
		ch++;
		write(client_fd,&ch,1);
		close(client_fd);
	}
}
