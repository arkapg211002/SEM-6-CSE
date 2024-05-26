#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

void func(int sockfd, int nf, int ws) 
{
    char buff[80];
    int ack, i = 0, k, f;
    snprintf(buff, sizeof(buff), "%d", i);
    write(sockfd, buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    ack = atoi(buff);
    printf("Frames Sending : ");
    for (k = 0; k < 8; k++) {
        printf("%d ", k);
    }
    printf("\nFrame %d not sent properly. \n", ack);
    printf("Resending Frame : ");
    // for(k = ack ; k < 8 ; k++ )
    printf("%d ", ack);
    printf("\n");
    snprintf(buff, sizeof(buff), "%d", ack + 1);
    write(sockfd, buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    if (strcmp("end", buff) == 0) {
        printf("All frames sent successfully\n");
        printf("Exit\n");
    }
}

int main() {
    int sockfd, connfd, f, w;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        exit(0);
    } else
        printf("Socket successfully created\n");
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(8080);
    if (connect(sockfd, (struct sockaddr * ) & servaddr, sizeof(servaddr)) != 0) {
        printf("Connection with the reciever failed\n");
        exit(0);
    } else
        printf("Connected to the reciever\n");
    f = 0;
    func(sockfd, f, 1);
    close(sockfd);
}
