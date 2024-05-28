#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define MAX 100

int sockfd,total=0,sequence_no=0,tcount=0;
struct sockaddr_in address;
pthread_t timer_thread;
sem_t sem;

void *timer(void *args)
{
	printf("Started timer %d\n",tcount);
	// tcount+=1;
	sleep(3);
	total=1;
	sem_post(&sem);
	pthread_exit(NULL);
}

void *receiver(void *args)
{
	int receiverfd=sockfd;
	int ack=-1;
	
	while(1)
	{
		read(receiverfd,(void *)&ack,sizeof(int));
		if(ack==sequence_no)
		{
			printf("Acknowledgement with sequence number %d received\n",ack);
			pthread_cancel(timer_thread);
			total=0;
			sem_post(&sem);
		}
		else printf("Delayed Acknowledgement received with sequence number %d : Discarded\n",ack);
	}
	pthread_exit(NULL);
}

void *sender(void *args)
{
	int senderfd=sockfd;
	
	while(1)
	{
		if(!total)
		{
			printf("Sending frame with sequence number : %d\n",sequence_no);
			write(senderfd,(void *)&sequence_no,sizeof(int));
		}	
		else
		{
			sequence_no=(sequence_no+1)&1;
			printf("Timer Timed Out! No Acknowledgement. Resending frame with sequence number : %d\n",sequence_no);
			write(senderfd,(void *)&sequence_no,sizeof(int));
		}
		
		sequence_no=(sequence_no+1)&1;
		total=0;
		tcount+=1;
		pthread_create(&timer_thread,NULL,(void *)&timer,NULL);
		sem_wait(&sem);
		pthread_join(timer_thread,NULL);
	}
	pthread_exit(NULL);
}

void main()
{
	int reuse=1,result,len;
	pthread_t rthread,sthread;
	sem_init(&sem,0,1);
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(8888);
	len=sizeof(address);
	
	printf("Client Running\n");
	
	result=connect(sockfd,(struct sockaddr *)&address,len);
	if(result==-1)
	{
		printf("Cannot connect to the server\n");
		perror("connect");
		exit(1);
	}
	else printf("Client Connected to the Server\n");
	
	pthread_create(&rthread,NULL,(void *)&receiver,NULL);
	pthread_create(&sthread,NULL,(void *)&sender,NULL);
	pthread_join(sthread,NULL);
	pthread_join(rthread,NULL);
	sem_destroy(&sem);		
}






