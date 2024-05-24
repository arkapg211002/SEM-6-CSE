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
#include <time.h>

#define MAX 100
unsigned int sequence_no;

void main()
{
	int server_fd,client_fd,reuse=1,server_len,client_len,seqno=0,ack=0;
	struct sockaddr_in server_address,client_address;
	struct timeval tv;
	
	tv.tv_sec=5;
	tv.tv_usec=0;
	
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
	setsockopt(client_fd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
	
	printf("Sender Running\n");
	
	while(1)
	{
		sequence_no=seqno;
		printf("Sending frame with sequence number : %d\n",seqno);
		write(client_fd,(void *)&sequence_no,sizeof(sequence_no));
		setsockopt(client_fd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
		time_t t1=time(NULL);
		
		while(1)
		{
			int bytes=read(client_fd,(void *)&ack,sizeof(ack));
			time_t t2=time(NULL);
			if(bytes>0)
			{
				if(ack==seqno+1)
				{
					printf("Acknowledgement for frame %d received\n",seqno);
					seqno=(seqno+1)%2;
					break;
				}
				else
				{
					time_t left=t1+5-t2;
					if(left>0)
					{
						printf("Previous ACK %d received. Ignoring\n",ack-1);
						struct timeval timeleft;
						timeleft.tv_sec=left;
						timeleft.tv_usec=0;
						setsockopt(client_fd,SOL_SOCKET,SO_RCVTIMEO,&timeleft,sizeof(struct timeval));
					}
					else
					{
						printf("Acknowledgement for frame %d not received. Retransmitting\n",seqno);
						break;
					}
				}
			}
			else
			{
				printf("Acknowledgement for frame %d not received. Retransmitting\n",seqno);
				break;
			}
		}
		printf("\n");
	}
}
