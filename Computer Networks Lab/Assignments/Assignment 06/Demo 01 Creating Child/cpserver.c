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
                    printf("\nServer Received : %s\n", input);
                    strcpy(result, "Received Message by Server :)\n");
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
