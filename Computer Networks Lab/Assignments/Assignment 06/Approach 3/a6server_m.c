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

#define N 5
#define MAX 100

char r[MAX];

// Number of clients
int ac=0;

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
	
	strcpy(r,"YES");
	
	if(len<7 || len>15)
	{
		strcpy(r,"NO");
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
			if(c>3 || c==0 || s>255 || c>count(s))
			{
				strcpy(r,"NO");
				c=0;
				s=0;
				break;
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
		strcpy(r,"NO");
	}
	
	printf("Result Obtained : %s\n",r);
}

void *client(void *arg)
{
	int server_fd=*((int *)arg);
	struct sockaddr_in client_address;
	int client_len=sizeof(client_address);
	char input[MAX],result[MAX];
	int client_fd=accept(server_fd,(struct sockaddr *)&client_address,&client_len);
	printf("Client %ld : %s : %d Connected\n",pthread_self(),inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port));

	// Increment Number of Clients;
	ac+=1;

	while(1)
	{
		printf("Waiting..\n");
		read(client_fd,input,MAX);
		printf("Server Received : %s\n",input);
		if(strcmp(input,"end")==0)
		{
			printf("Client %ld : %s : %d Disconnected\n",pthread_self(),inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port));
			close(client_fd);
			break;
		}

		check(input);
		strcpy(result,r);
		
		printf("Sending result to client %ld : %s : %d\n",pthread_self(),inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port));
		write(client_fd,result,strlen(result)+1);
		printf("\n");
	}
	
	// Decrement Number of Clients
	ac-=1;
	if(ac==0)
	{
		printf("No more clients\n");
		printf("Server Ending..\n");
		close(server_fd);
		exit(0);
	}
	
	pthread_exit(NULL);
}

void main()
{
	pthread_t t[N];
	int i,server_fd,server_len;
	struct sockaddr_in server_address;

	server_fd=socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(8888);
	server_len=sizeof(server_address);
	bind(server_fd,(struct sockaddr *)&server_address,server_len);
	listen(server_fd,5);
	printf("Server Running\n");

	for(i=0;i<N;i++)
	{
		pthread_create(&t[i],NULL,&client,(void *)&server_fd);
	}

	for(i=0;i<N;i++)
	{
		pthread_join(t[i],NULL);
	}
}

