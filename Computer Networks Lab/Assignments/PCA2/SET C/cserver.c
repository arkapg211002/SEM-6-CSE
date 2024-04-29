#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <math.h>

#define MAX 100

struct message
{
	char word[MAX];
	char divisor[MAX];
};

char cw[MAX],rm[MAX];
// function to convert integer to binary string
// function to convert integer to binary string
void toBin(long long int num, char *bin)
{
    int i = 0;
    while (num) {
        if (num & 1)
            bin[i++] = '1';
        else
            bin[i++] = '0';
        num = num >> 1;
    }
    bin[i] = '\0';
    // reverse the binary string
    int j = 0, k = i - 1;
    while (j < k) {
        char temp = bin[j];
        bin[j] = bin[k];
        bin[k] = temp;
        j++;
        k--;
    }
}

// function to convert binary string to decimal
long long int toDec(const char *bin)
{
    long long int num = 0;
    int len = strlen(bin);
    for (int i = 0; i < len; i++) {
        if (bin[i] == '1')
            num += 1 << (len - i - 1);
    }
    return num;
}

// function to compute CRC and codeword
void CRC(const char *dataword, const char *generator)
{
    int l_gen = strlen(generator);
    long long int gen = toDec(generator);

    long long int dword = toDec(dataword);

    // append 0s to dividend
    long long int dividend = dword << (l_gen - 1);

    // shft specifies the no. of least
    // significant bits not being XORed
    int shft = (int)(ceil(log2(dividend + 1)) - l_gen);
    long long int rem;

    while ((dividend >= gen) || (shft >= 0)) {
        // bitwise XOR the MSBs of dividend with generator
        // replace the operated MSBs from the dividend with
        // remainder generated
        rem = (dividend >> shft) ^ gen;
        dividend = (dividend & ((1LL << shft) - 1)) | (rem << shft);

        // change shft variable
        shft = (int)(ceil(log2(dividend + 1)) - l_gen);
    }

    // finally, AND the initial dividend with the remainder
    // (=dividend)
    long long int codeword = (dword << (l_gen - 1)) | dividend;
    char bin_dividend[100], bin_codeword[100];
    //toBin(dividend, bin_dividend);
    toBin(codeword, bin_codeword);
    strcpy(bin_dividend,bin_codeword+strlen(dataword));
    printf("Remainder: %s\n", bin_dividend);
    printf("Codeword : %s\n", bin_codeword);
    strcpy(cw,bin_codeword);
    strcpy(rm,bin_dividend);
}

void main()
{
	int server_fd,client_fd;
	int server_len,client_len;
	struct sockaddr_in server_address,client_address;
	struct message data;
	
	//unlink("server");
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family=AF_INET;
	//strcpy(server_address.sun_path,"server");
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(8888);
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
		
		CRC(data.word,data.divisor);
		
		strcpy(data.word,cw);
		strcpy(data.divisor,rm);

		printf("Sending back codeword : %s\n",data.word);
		printf("Sending back remainder : %s\n",data.divisor);

		write(client_fd,(void *)&data,sizeof(data));
	}
	close(server_fd);
}
