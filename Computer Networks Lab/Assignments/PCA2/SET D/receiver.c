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

#define MAX 100

char* bitstuffing(char* bitStream)
{
    char* stuffedStream = (char*)malloc(strlen(bitStream) * 2 + 1); 
    int i = 0, j = 0;
    while (bitStream[i] != '\0') {
        if (bitStream[i] == '1') {
            stuffedStream[j] = bitStream[i];
            j++;
            int count = 1;
            while (bitStream[i + 1] == '1' && count < 5) 
            {
                i++;
                stuffedStream[j] = bitStream[i];
                j++;
                count++;
                if (count == 5) 
                {                
                    stuffedStream[j] = '0';
                    j++;     
                }
            }
        }
        else 
        {
            stuffedStream[j] = bitStream[i];
            j++;
        }
        i++;
    }
    stuffedStream[j] = '\0';
    return stuffedStream;
}

int main(int argc,char **argv)
{
	int sockfd,len,reuse=1;
	struct sockaddr_in address;
	char input[MAX],result[MAX];

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=htonl(INADDR_ANY);
	address.sin_port=htons(8888);
	len=sizeof(address);
	bind(sockfd,(struct sockaddr *)&address,len);
	
	printf("Receiver %s Running\n",argv[1]);

	while(1)
	{
		recvfrom(sockfd,input,MAX,0,NULL,0);
		printf("Broadcasted bitstream : %s\n",input);
		if(strcmp(input,"QUIT")==0) break;
		strcpy(result,bitstuffing(input));
		printf("Bitstream after bitstuffing is : %s\n",result);
	}
	close(sockfd);
	return 0;
}
