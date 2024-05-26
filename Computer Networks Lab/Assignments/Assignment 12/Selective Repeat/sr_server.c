#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

void func(int connfd) 
{
    char buff[80];
    int f, c, win, ack, k;
    win = 8;
    read(connfd, buff, sizeof(buff));
    if (strcmp("end", buff) == 0) {
        printf("Exit\n");
    }
    f = atoi(buff);
    f = atoi(buff);
    for (k = 0; k < f; k++)
        printf("\n%d ", k);
    c = rand() % (win - 1);
    c = rand() % (win - 1);
    for (k = 0; k < win; k++) {
        if (k != c) {
            sleep(1);
            printf("\nRecieved Frame: %d\n ", k);
        }
    }
    sleep(c);
    printf("\nFrame %d not received\nWaiting for Frame %d\n", c, c);
    ack = c;
    snprintf(buff, sizeof(buff), "%d", ack);
    write(connfd, buff, sizeof(buff));
    read(connfd, buff, sizeof(buff));
    if (strcmp("end", buff) == 0) {
        printf("Exit\n");
    }
    f = atoi(buff);
    // for(k = f-1 ; k < win ; k++ )
    //{
    sleep(1);
    printf("\nRecieved Frame %d\n", (f - 1));
    //}
    printf("\n");
    strcpy(buff, "end");
    write(connfd, buff, sizeof(buff));
}

int main() {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        exit(0);
    }
    printf("Socket successfully created\n");
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(8080); 
    if ((bind(sockfd, (struct sockaddr * ) & servaddr, sizeof(servaddr))) != 0)
    { 
        printf("socket bind failed\n");
        exit(0);
    }
    printf("Socket successfully binded\n");
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed\n");
        exit(0);
    }
    printf("Server listening\n");
    len = sizeof(cli);
    connfd = accept(sockfd, (struct sockaddr * ) & cli, & len);
    if (connfd < 0) {
        printf("Server accept failed\n");
        exit(0);
    }
    printf("Server accept the client\n");
    func(connfd);
    close(sockfd);
}
