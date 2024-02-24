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

char* bitStuffing(char* input)
{
    // Allocate memory for the stuffed bit stream
    char* stuffed = (char*)malloc(strlen(input) * 2 + 1); // Maximum possible length after stuffing: input length * 2
    if (stuffed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Variables to traverse arrays
    int i = 0;
    int j = 0;

    // Loop through the input string
    while (input[i] != '\0') {

        // If the current bit is a set bit
        if (input[i] == '1') {

            // Stores the count of consecutive ones
            int count = 1;

            // Insert into array stuffed[]
            stuffed[j] = input[i];
            j++;

            // Loop to check for next 5 bits
            int k;
            for (k = i + 1; input[k] == '1' && count < 5; k++) {
                stuffed[j] = input[k];
                j++;
                count++;

                // If 5 consecutive set bits are found insert a 0 bit
                if (count == 5) {
                    stuffed[j] = '0';
                    j++;
                }
                i = k;
            }
        }

        // Otherwise insert input[i] into the array stuffed[]
        else {
            stuffed[j] = input[i];
            j++;
        }
        i++;
    }
    // Null-terminate the string
    stuffed[j] = '\0';

    // Return the stuffed bit stream
    return stuffed;
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
