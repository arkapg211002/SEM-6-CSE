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
#include <sys/time.h>
#include <sys/ioctl.h>

#define MAX_CLIENTS 5
#define MAX_MSG_LEN 100

char r[MAX_MSG_LEN];

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
    int server_fd, client_fds[MAX_CLIENTS] = {0};
    struct sockaddr_in server_address, client_address;
    socklen_t client_len;
    fd_set readfds, testfds;
    char input[MAX_MSG_LEN],res[MAX_MSG_LEN];
    int result, fd, nread, client_count = 0;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(8888);
    bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address));

    listen(server_fd, 5);
    printf("Server Running\n");

    FD_ZERO(&readfds);
    FD_SET(server_fd, &readfds);

    while(1) 
    {
        testfds = readfds;
        printf("Server Waiting..\n");
        result = select(FD_SETSIZE, &testfds, NULL, NULL, NULL);
        if(result < 0) 
	{
            perror("select");
            exit(EXIT_FAILURE);
        }

        for(fd = 0; fd < FD_SETSIZE; fd++) 
	{
            if(FD_ISSET(fd, &testfds)) 
	    {    
                if(fd == server_fd) 
	        {
                    client_len = sizeof(client_address);
                    client_fds[client_count] = accept(server_fd, (struct sockaddr *)&client_address, &client_len);
                    if(client_fds[client_count] < 0) 
		    {
                        perror("accept");
                        continue;
                    }
                    FD_SET(client_fds[client_count], &readfds);
                    printf("Adding Client on fd %d\n", client_fds[client_count]);
                    client_count++;
                } 
		else 
		{
                    ioctl(fd, FIONREAD, &nread);
                    if(nread == 0) 
		    {
                        close(fd);
                        FD_CLR(fd, &readfds);
                        printf("Removing Client on fd %d\n", fd);
                    } 
		    else 
		    {
                        read(fd, input, MAX_MSG_LEN);
                        printf("Serving Client on fd %d\n", fd);
                        printf("Server Received IPv4 Address: %s\n", input);
                        check(input);
                        strcpy(res,r);
                        printf("Sending result to the client on fd %d\n", fd);
                        write(fd, res, strlen(res) + 1);
                        if(strcmp(input, "end") == 0) 
			{
                            close(fd);
                            FD_CLR(fd, &readfds);
                            printf("Removing Client on fd %d\n", fd);
                        }
                    }
                }
            }
        }
    }
}
