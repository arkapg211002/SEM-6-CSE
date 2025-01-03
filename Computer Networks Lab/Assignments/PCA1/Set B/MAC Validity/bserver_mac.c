#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>

#define MAX 100
int r;

void check(char *input)
{
	int i,c=0,cp=0;
	int len=strlen(input);
	r=1;
	if(len!=17)
	{
		r=0;
		return;
	}
	strcat(input,":");
	for(i=0;i<=len;i++)
	{
	
		if(input[i]==':')
		{
			cp+=1;
			printf("%d %d %d\n",c,cp,r);
			if(c>2)
			{
				c=0;
				r=0;
				break;
			}
			c=0;
		}
		if(((int)input[i]>=48 && (int)input[i]<=57) || ((int)input[i]>=97 && (int)input[i]<=102))
		{
			c+=1;
		}
	}
	if(cp!=6)
	{
		r=0;
	}

}

void main()
{
	int server_len,client_len,server_fd,client_fd;
	struct sockaddr_un server_address,client_address;
	char input[MAX];
	unlink("bserverm");
	server_fd=socket(AF_UNIX,SOCK_STREAM,0);
	server_address.sun_family=AF_UNIX;
	strcpy(server_address.sun_path,"bserverm");
	server_len=sizeof(server_address);
	bind(server_fd,(struct sockaddr *)&server_address,server_len);
	listen(server_fd,5);
	printf("Server Running\n");
	client_len=sizeof(client_address);
	client_fd=accept(server_fd,(struct sockaddr *)&client_address,&client_len);

	while(1)
	{
		printf("Waiting..\n");
		sleep(1);
		read(client_fd,input,MAX);
		if(strcmp(input,"end")==0)
		{
			close(client_fd);
			break;
		}
		printf("Server Received MAC Address : %s\n",input);
		check(input);
		printf("Server sending the result : %d\n",r);
		write(client_fd,(void *)&r,sizeof(r));
	}
	close(server_fd);
}
