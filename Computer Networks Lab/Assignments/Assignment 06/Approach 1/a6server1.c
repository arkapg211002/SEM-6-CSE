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
#include <sys/wait.h>
#include <signal.h>

#define MAX 100

char r[MAX];

int count(int n)
{
	int c=0;
	if(n==0) return 1;
	while(n>0)
	{
		c+=1;
		n/=10;
	}
	return c;
}

void check(char *input)
{

	int len=strlen(input);
	int i,c=0,s=0,cp=0;
	int getc=0;
	strcpy(r,"YES");
	if(len<7 || len>15)
	{
		strcpy(r,"NO");
		return;
	}
	strcat(input,".");
	//printf("%s\n",input);
	for(i=0;i<=len;i++)
	{
		
		if(input[i]=='.')
		{
			//printf("%d\n",s);
			cp+=1;
			getc=0;
			if(c>3 || c==0 || s>255 || c>count(s))
			{
				strcpy(r,"NO");
				c=0;
				s=0;
				break;
			}
			
			c=0;
			s=0;
			
		}
		if((int)input[i]>=48 && (int)input[i]<=57)
		{
			c+=1;
			s=(s*10)+(input[i]-'0');
		}
	}

	if(cp>4)
	{
		strcpy(r,"NO");
	}

}

void main()
{
    int server_fd, client_fd, server_len, client_len;
    struct sockaddr_in server_address, client_address;
    char input[MAX], result[MAX];
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(8888);
    server_len = sizeof(server_address);
    bind(server_fd, (struct sockaddr *)&server_address, server_len);

    listen(server_fd, 5);
    printf("Server Running\n");
    signal(SIGCHLD,SIG_IGN);

    while(1)
    {
        client_len = sizeof(client_address);
        client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_len);

        printf("\nConnection Accepted\n");
        printf("Host : %s\tPort : %d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

        if(fork() == 0)
        {
            close(server_fd);
            while (1)
            {
                read(client_fd, input, MAX);
                if (strcmp(input, "end") == 0)
                {
                    printf("\nDisconnected\n\n");
                    printf("Host : %s\tPort : %d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
                    close(client_fd);
                    exit(0);
                }
                else
                {
                    printf("\nServer Received the IPv4 Address: %s\n", input);
                    check(input);
                    strcpy(result,r);
                    printf("\nSending back message to the client\n");
                    write(client_fd, result, strlen(result) + 1);
                }
            }
        }
        else
        {
            close(client_fd);
        }
    }

    close(server_fd);
}
