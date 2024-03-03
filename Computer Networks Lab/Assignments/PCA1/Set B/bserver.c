#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>

#define MAX 100
char r;

int count(int n)
{
	int c=0;
	if(n==0) return 1;
	while(n>0)
	{
		c+=1;
		n/=10;
	}
	return c;
}

void check(char *input)
{

	int len=strlen(input);
	int i,c=0,s=0,cp=0;
	int getc=0;
	r='1';
	if(len<7 || len>15)
	{
		r='0';
		return;
	}
	strcat(input,".");
	//printf("%s\n",input);
	for(i=0;i<=len;i++)
	{
		
		if(input[i]=='.')
		{
			//printf("%d\n",s);
			cp+=1;
			getc=0;
			if(c>3 || c==0 || s>255)
			{
				r='0';
				c=0;
				s=0;
				break;
			}
			else
			{
				getc=count(s);
				if(getc < c)
				{
					r='0';
					c=0;
					s=0;
					break;
				}
			}
			c=0;
			s=0;
			
		}
		if((int)input[i]>=48 && (int)input[i]<=57)
		{
			c+=1;
			s=(s*10)+(input[i]-'0');
		}
	}

	if(cp>4)
	{
		r='0';
	}

}

void main()
{
	int server_fd,client_fd,server_len,client_len;
	struct sockaddr_un server_address,client_address;
	char input[MAX],res[MAX];
	
	unlink("server");
	server_fd=socket(AF_UNIX,SOCK_STREAM,0);
	server_address.sun_family=AF_UNIX;
	strcpy(server_address.sun_path,"server");
	server_len=sizeof(server_address);
	bind(server_fd,(struct sockaddr *)&server_address,server_len);
	listen(server_fd,5);
	printf("Server running..\n");
	client_len=sizeof(client_address);
	client_fd=accept(server_fd,(struct sockaddr *)&client_address,&client_len);

	while(1)
	{
		printf("Waiting..\n");
		sleep(1);
		read(client_fd,input,sizeof(input));
		printf("Server Received : %s\n",input);
		if(strcmp(input,"end")==0)
		{
			close(client_fd);
			break;
		}

		check(input);
		res[0]=r;
		res[1]='\0';
		printf("Sending back result \n");
		write(client_fd,res,strlen(res)+1);
	}
	close(server_fd);
	printf("\n");
}
