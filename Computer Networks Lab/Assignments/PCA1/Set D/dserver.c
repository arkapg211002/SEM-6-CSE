#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define MAX 100

void main()
{
	int server_fd,client_fd,server_len,client_len;
	struct sockaddr_un server_address,client_address;
	char input[MAX],rev[MAX];
	int i,j=0;
	
	unlink("dserver");
	server_fd=socket(AF_UNIX,SOCK_STREAM,0);
	server_address.sun_family=AF_UNIX;
	strcpy(server_address.sun_path,"dserver");
	server_len=sizeof(server_address);
	bind(server_fd,(struct sockaddr *)&server_address,server_len);

	listen(server_fd,5);
	printf("Server Running\n");

	client_len=sizeof(client_address);
	client_fd=accept(server_fd,(struct sockaddr *)&client_address,&client_len);

	printf("Waiting for the client..\n");
	sleep(2);
	read(client_fd,input,MAX);
	printf("The MAC address received : %s\n",input);

	for(i=strlen(input)-1;i>=0;i--)
	{
		rev[j]=input[i];
		j+=1;
	}
	rev[j]='\0';
	printf("Sending the reverse of the MAC Address\n");
	sleep(2);
	write(client_fd,rev,strlen(rev)+1);
	printf("Sent\n");

	close(client_fd);
	close(server_fd);
}
