#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX 100
struct timeval timeout;

void gobackn(int server_fd,int frames,int winsize)
{
	char input[MAX];
	int ack,i,j,n,w1=0,w2,flag = 0;
	
	w2=winsize-1;
	setsockopt(server_fd,SOL_SOCKET,SO_RCVTIMEO,(const char *)&timeout,sizeof(struct timeval));
	
	for(i=0;i<frames && i<=w2;i++)
	{
		snprintf(input,MAX,"%d",i);
		write(server_fd,input,strlen(input)+1);
		strcpy(input,"");
		printf("Frame %d sent\n",i);
	}
	
	while(1)
	{
		if(w2-w1!=winsize-1 && flag==0 && i!=frames)
		{
			snprintf(input,MAX,"%d",i);
			write(server_fd,input,strlen(input)+1);
			strcpy(input,"");
			printf("Frame %d sent\n",i);
			w2+=1;
			i+=1;
		}
		
		flag=0;
		n=read(server_fd,input,MAX);
		ack=atoi(input);
		
		if(n>0)
		{
			if(ack+1==frames)
			{
				printf("Acknowledgement received : %d\nExit\n",ack);
				strcpy(input,"Exit");
				write(server_fd,input,strlen(input)+1);
				break;
			}
			if (ack == w1)
			{
				w1++;
				printf("Acknowlegement received: %d\n", ack);
		        }
		}
		else
		{
			printf("Acknowledgement not received for %d\nResending frames\n", w1);
			for(j=w1; j < frames && j < w1 + winsize; j++)
			{
				snprintf(input,MAX,"%d",j);
				write(server_fd,input,strlen(input)+1);
				strcpy(input,"");
				printf("Frame %d sent\n", j);
			}
			flag=1;
		}
	}
	
}

void main()
{
	int server_fd,server_len,result,num,win;
	struct sockaddr_in server_address;
	
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(8888);
	server_len=sizeof(server_address);
	
	timeout.tv_sec=3;
	timeout.tv_usec=0;
	
	result=connect(server_fd,(struct sockaddr *)&server_address,server_len);
	if(result==-1)
	{
		printf("Connection failed\n");
		perror("connect");
		exit(0);
	}
	else printf("Connection successful\n\n");
	printf("Enter the number of frames : ");
	scanf("%d",&num);
	printf("Enter the window size : ");
	scanf("%d",&win);
	gobackn(server_fd,num,win);
	close(server_fd);	
}

