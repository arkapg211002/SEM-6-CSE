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
#include <pthread.h>
#include <time.h>

#define MAX 100

void main()
{
	int sockfd,len,reuse=1,pos=0,frame=0;
	float check;
	struct sockaddr_in address;
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=htonl(INADDR_ANY);
	address.sin_port=htons(8888);
	len=sizeof(address);
	connect(sockfd,(struct sockaddr *)&address,len);
	
	srand(time(NULL));
	while(1)
	{
		read(sockfd,(void *)&frame,sizeof(int));
		printf("Received frame with sequence number : %d\n",frame);
		if(frame==pos)
		{
			check=(float)rand()/(float)RAND_MAX;
			if(check<0.9)
			{
				pos+=1;
				printf("Sending Acknowledgement %d for received frame %d\n",pos,frame);
				write(sockfd,(void *)&pos,sizeof(int));
			}
			else printf("Simulating lost acknowledgement %d\n",pos+1);
		}
		else
		{
			printf("Out Of Order Frame! Discarded!\n");
			write(sockfd,(void *)&pos,sizeof(int));
		}
	}
}
