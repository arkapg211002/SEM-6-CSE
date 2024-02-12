#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <math.h>

#define MAX 100

struct message
{
	char word[MAX];
	char divisor[MAX];
};

// Function to convert integer to binary string
char* toBin(long long int num, int bits) {
    char *bin_str = (char *)malloc((bits + 1) * sizeof(char)); // Allocate memory for the binary string
    if (bin_str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Convert each bit of the integer to a binary character
    for (int i = bits - 1; i >= 0; i--) {
        bin_str[i] = (num & 1) + '0'; // Extract the least significant bit and convert it to a character
        num >>= 1; // Right shift the number to get the next bit
    }
    bin_str[bits] = '\0'; // Null-terminate the string
    return bin_str;
}

// Function to convert binary string to decimal
long long int toDec(char *bin) {
    long long int num = 0;
    int length = strlen(bin);
    for (int i = 0; i < length; i++) {
        if (bin[i] == '1')
            num += 1LL << (length - i - 1);
    }
    return num;
}

// Function to compute CRC and codeword
char* CRC(char *dataword, char *generator) {
    int l_gen = strlen(generator);
    long long int gen = toDec(generator);

    long long int dword = toDec(dataword);

    // Initialize the remainder with the dataword
    long long int remainder = dword;

    // Perform CRC division
    for (int i = 0; i < strlen(dataword); i++) {
        if (remainder & (1LL << (strlen(dataword) - i - 1))) {
            remainder ^= gen << (strlen(dataword) - l_gen - i);
        }
    }

    // Construct the codeword by appending the remainder to the dataword
    long long int codeword = (dword << (l_gen - 1)) | remainder;
    
    // Return the codeword as a binary string
    return toBin(codeword, strlen(dataword) + l_gen - 1);
}

void main()
{
	int server_fd,client_fd;
	int server_len,client_len;
	struct sockaddr_un server_address,client_address;
	struct message data;
	char *codeword;

	unlink("server");
	server_fd=socket(AF_UNIX,SOCK_STREAM,0);
	server_address.sun_family=AF_UNIX;
	strcpy(server_address.sun_path,"server");
	server_len=sizeof(server_address);
	bind(server_fd,(struct sockaddr *)&server_address,server_len);
	
	listen(server_fd,5);
	printf("Server Running\n\n");

	client_len=sizeof(client_address);
	client_fd=accept(server_fd,(struct sockaddr *)&client_address,&client_len);

	while(1)
	{
		printf("Waiting..\n");
		sleep(1);
		read(client_fd,(void *)&data,sizeof(data));
		printf("Server received from client\n");
		if(strcmp(data.word,"end")==0)
		{
			close(client_fd);
			break;
		}
		else
		{
			printf("Data word : %s\n",data.word);
			printf("Divisor : %s\n",data.divisor);
		}
		
		codeword=CRC(data.word,data.divisor);
		strcpy(data.word,codeword);
		printf("Sending back codeword : %s\n",data.word);
		write(client_fd,(void *)&data,sizeof(data));
	}
	close(server_fd);
}
