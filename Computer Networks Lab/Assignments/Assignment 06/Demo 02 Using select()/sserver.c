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

#define MAX 100
#define MAX_CLIENTS 5
#define MAX_MSG_LEN 100

void main() 
{
    int server_fd, client_fds[MAX_CLIENTS] = {0};
    struct sockaddr_in server_address, client_address;
    socklen_t client_len;
    fd_set readfds, testfds;
    char input[MAX_MSG_LEN];
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
                        printf("Server Received : %s\n", input);
                        strcpy(input, "Received from server :)");
                        write(fd, input, strlen(input) + 1);
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
