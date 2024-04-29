#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>

#define MAX 100

// Store hamming code
int code[32];
// Store the result
char res[MAX];

// Function to calculate bit for ith position
int ham_calc(int position, int c_l) 
{
    int count = 0, i, j;
    i = position - 1;

    // Traverse to store Hamming Code
    while(i < c_l) 
    {
        for(j = i; j < i + position; j++) 
        {
            // If current bit is 1
            if (code[j] == 1)
                count++;
        }
        // Update i
        i = i + 2 * position;
    }
    if(count % 2 == 0) return 0;
    else return 1;
}

char *reverse(char *data)
{
	char *rev=(char *)malloc((strlen(data)+1)*sizeof(char));
	int k=0;
	for(int i=strlen(data)-1;i>=0;i--)
	{
		rev[k]=data[i];
		k+=1;
	}
	rev[k]='\0';
	printf("Reverse is : %s\n",rev);
	return rev;
}

// Function to calculate hamming code
void solve(char *data) 
{
    int n = strlen(data);
    int i, p_n = 0, c_l, j, k;
    i = 0;

	strcpy(data,reverse(data));
    // Find msg bits having set bit at x'th position of number
    while(n > (int)pow(2, i) - (i + 1)) 
    {
        p_n++;
        i++;
    }

    c_l=p_n + n;
    j=k=0;

    // Traverse the msgBits
    for(i = 0; i < c_l; i++) 
    {
        // Update the code
        if(i == ((int)pow(2, k) - 1)) 
        {
            code[i] = 0;
            k++;
        }
        // Update the code[i] to the input character at index j
        else 
        {
            code[i] = data[j] - '0';
            j++;
        }
    }

    // Traverse and update the hamming code
    for(i = 0; i < p_n; i++) 
    {
        // Find current position
        int position = (int)pow(2, i);
        // Find value at current position
        int value = ham_calc(position, c_l);
        // Update the code
        code[position - 1] = value;
    }

    // Print the Hamming Code
    printf("\nThe generated Code Word is: ");
    for (i = 0; i < c_l; i++) 
    {
        printf("%d", code[i]);
        res[i]=(code[c_l-i-1]==0) ? '0':'1';
    }
    res[i]='\0';
    printf("\n");
}

void main()
{
	int server_fd,server_len,client_len,checkres;
	struct sockaddr_in server_address,client_address;
	char input[MAX],result[MAX];

	server_fd=socket(AF_INET,SOCK_DGRAM,0);
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(8888);
	server_len=sizeof(server_address);

	bind(server_fd,(struct sockaddr *)&server_address,server_len);
	printf("Server Running\n");


	client_len=sizeof(client_address);
	checkres=recvfrom(server_fd,input,MAX,0,(struct sockaddr *)&client_address,&client_len);
	if(checkres!=-1)
	{
		printf("Client Connected\n");
		printf("Server Received : %s\n",input);
		strcpy(result,"Hello from server");
		sendto(server_fd,result,strlen(result)+1,0,(struct sockaddr *)&client_address,client_len);
		strcpy(input,"");
		strcpy(result,"");
	}
	else
	{
		printf("No client : Server Ends\n");
		exit(1);
	}

	while(1)
	{
		recvfrom(server_fd,input,MAX,0,(struct sockaddr *)&client_address,&client_len);
		printf("Server Received Dataword : %s\n",input);

		if(strcmp(input,"end")==0)
		{
			break;
		}
		
		solve(input);

		strcpy(result,res);
		strcpy(res,"");
		printf("Sending codeword %s to the client\n",result);
		sendto(server_fd,result,strlen(result)+1,0,(struct sockaddr *)&client_address,client_len);

	}

	close(server_fd);
	
}
