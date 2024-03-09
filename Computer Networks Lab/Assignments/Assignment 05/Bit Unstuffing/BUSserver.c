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

#define MAX 100

char* unbitStuffing(char* bitStream)
{
    char* unstuffedStream = (char*)malloc(strlen(bitStream) * 2 + 1); 
    int i = 0, j = 0;
    int prevBitZero = 0;
    
    while(bitStream[i] != '\0') 
    {
        if(bitStream[i] == '1') 
        {
            unstuffedStream[j] = bitStream[i];
            j++;
            int count = 1;
            while(bitStream[i + 1] == '1' && count < 5) 
            {
                i++;
                unstuffedStream[j] = bitStream[i];
                j++;
                count++;
                if(count == 5) 
                {
                    if(prevBitZero && (i+1) < strlen(bitStream)) 
                    {
                        if(bitStream[i+1] == '0') 
			{
				i+=1;
				break;
			}
                    }
                }
            }
	    i+=1;
        }
        else 
        {
            unstuffedStream[j] = bitStream[i];
            j++;
            prevBitZero = (bitStream[i] == '0') ? 1 : 0;
	    i+=1;
        }
    }

    unstuffedStream[j] = '\0';
    return unstuffedStream;
}


void main()
{
	int server_fd,client_fd,server_len,client_len;
	struct sockaddr_in server_address,client_address;
	char input[MAX],result[MAX];

	server_fd=socket(AF_INET,SOCK_STREAM,0);
	
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(8888);
	server_len=sizeof(server_address);

	bind(server_fd,(struct sockaddr *)&server_address,server_len);
	listen(server_fd,5);
	printf("Server Running\n");

	client_len=sizeof(client_address);
	client_fd=accept(server_fd,(struct sockaddr *)&client_address,&client_len);

	while(1)
	{
		printf("Waiting..\n");
		sleep(2);

		read(client_fd,input,MAX);
		printf("Server Received : %s\n",input);

		if(strcmp(input,"end")==0)
		{
			close(client_fd);
			break;
		}

		strcpy(result,unbitStuffing(input));

		printf("Sending back to client\n");
		write(client_fd,result,strlen(result)+1);
	}
	close(server_fd);
}
