#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MULTICAST_GROUP "239.0.0.1"
#define PORT 8888
#define MAX_MSG_SIZE 100

int main() {
    int sockfd;
    struct sockaddr_in server_address;
    char input[MAX_MSG_SIZE], res[MAX_MSG_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);
    server_address.sin_port = htons(PORT);

    printf("Client Running\n");

    while (1) {
        printf("[+] Client : ");
        fgets(input, MAX_MSG_SIZE, stdin);

        if (sendto(sockfd, input, strlen(input) + 1, 0, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
            perror("sendto");
            exit(EXIT_FAILURE);
        }

        if (strcmp(input, "end\n") == 0) {
            break;
        }

        if (recvfrom(sockfd, res, MAX_MSG_SIZE, 0, NULL, NULL) < 0) {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }
        printf("[-] Server : %s\n", res);
    }

    close(sockfd);
    return 0;
}

