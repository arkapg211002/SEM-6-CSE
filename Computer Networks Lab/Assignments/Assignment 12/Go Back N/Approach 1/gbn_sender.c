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

int client_fd,server_fd,total=0,sequence_no,n,start=0,end=0,stop=0;
struct sockaddr_in server_address,client_address;
pthread_t *th;

void *timer(void *args)
{
	sleep(5);
	total=1;
	pthread_exit(NULL);
}

void *receiver(void *args)
{
	int receiver_fd=client_fd;
	int ack=-1,i;
	while(!stop)
	{
		read(receiver_fd,(void *)&ack,sizeof(int));
		if(ack>start && ack<=end)
		{
			printf("Acknowledgement %d Received\n",ack);
			for(i=0;i<(ack-1)%n;i++) pthread_cancel(th[i]);
			while(start<ack) start+=1;
			if(ack==sequence_no+1) stop=1; 
		}
		else printf("Duplicate Acknowledgement %d Received. Discarded\n",ack);
	}
	pthread_exit(NULL);
}

void *sender(void *args)
{
	int sender_fd=client_fd;
	int i;
	float check;
	
	srand(time(NULL));
	while(!stop)
	{
		if(total==1)
		{
			printf("Timer Timed out. Resending frames with sequence number %d to %d\n",start,end-1);
			for(i=start;i<end;i++)
			{	
				check=(float)rand()/(float)RAND_MAX;
				if(check<0.9)
				{
					printf("Frame with sequence number %d sent\n",i);
					write(sender_fd,(void *)&i,sizeof(int));	
					pthread_create(&th[i],NULL,(void*)&timer,NULL);	
				}
				else printf("Simulating lost packet %d\n",i);
			}
			total=0;
		}
		else
		{
			while(end-start<n && end<sequence_no+1){
				check=(float)rand()/(float)RAND_MAX;
				if(check<0.9){
					i=end%(n-1);
					printf("Sending frame with sequence number %d\n",end);
					write(sender_fd,(void *)&end,sizeof(int));
					end+=1;
					pthread_create(&th[i],NULL,(void*)&timer,NULL);	
				}
				else{
					printf("Simulating lost packet %d\n",end);
					end+=1;
				}
			}
		}
	}
	for(i=0;i<n;i++) pthread_join(th[i],NULL);
	pthread_exit(NULL);
}

void main()
{
	int reuse=1,server_len,client_len;
	pthread_t rthread,sthread;
	
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(8888);
	server_len=sizeof(server_address);
	
	bind(server_fd,(struct sockaddr *)&server_address,server_len);
	listen(server_fd,1);
	client_len=sizeof(client_address);
	client_fd=accept(server_fd,(struct sockaddr *)&client_address,&client_len);
	
	printf("Sender Started\n");
	printf("Enter size of window : ");
	scanf("%d",&n);
	sequence_no=1<<n+n;
	th=(pthread_t *)malloc(n*sizeof(pthread_t));
	
	pthread_create(&rthread,NULL,(void *)&receiver,NULL);
	pthread_create(&sthread,NULL,(void *)&sender,NULL);
	pthread_join(sthread,NULL);
	pthread_join(rthread,NULL);	
}
