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

char* bitStuffing(char* bitStream)
{
    // Allocate memory for the stuffed bit stream
    char* stuffedStream = (char*)malloc(strlen(bitStream) * 2 + 1); // Maximum possible length after stuffing: input length * 2
    if (stuffedStream == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

     // Variables to traverse strings
    int i = 0, j = 0;

    // Flag to indicate if the previous bit was 0
    int prevBitZero = 0;

    // Loop through the input bit stream
    while (bitStream[i] != '\0') {
        // If the current bit is a set bit
        if (bitStream[i] == '1') {
            // Insert the bit into the stuffed stream
            stuffedStream[j] = bitStream[i];
            j++;

            // Variables to count consecutive ones
            int count = 1;

            // Loop to check for next 5 bits
            while (bitStream[i + 1] == '1' && count < 5) {
                i++;
                stuffedStream[j] = bitStream[i];
                j++;
                count++;

                // If 5 consecutive set bits are found, insert a 0 bit
                if (count == 5) {
                    // Check if the previous bit was 0
                    if (prevBitZero) {
                        stuffedStream[j] = '0';
                        j++;
                    }
                }
            }
        }
        // Otherwise, insert the bit into the stuffed stream
        else {
            stuffedStream[j] = bitStream[i];
            j++;

            // Update prevBitZero flag
            prevBitZero = (bitStream[i] == '0') ? 1 : 0;
        }
        i++;
    }

    // Null-terminate the stuffed stream
    stuffedStream[j] = '\0';

    // Return the stuffed bit stream
    return stuffedStream;
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

		strcpy(result,bitStuffing(input));

		printf("Sending back to client\n");
		write(client_fd,result,strlen(result)+1);
	}
	close(server_fd);
}
