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
#define MAX_CLIENTS 10

int main() {
    int server_fd;
    struct sockaddr_in server_address, client_address;
    struct ip_mreq multicast_req;
    char input[MAX_MSG_SIZE];

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    inet_pton(AF_INET, MULTICAST_GROUP, &multicast_req.imr_multiaddr);
    multicast_req.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(server_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicast_req, sizeof(multicast_req)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    printf("Server Running\n");

    struct sockaddr_in client_addresses[MAX_CLIENTS];
    int num_clients = 0;

    while (1) {
        struct sockaddr_in sender_address;
        socklen_t addr_len = sizeof(sender_address);

        if (recvfrom(server_fd, input, MAX_MSG_SIZE, 0, (struct sockaddr *)&sender_address, &addr_len) < 0) {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }

        printf("[-] Message from client: %s\n", input);

        // Store sender's address if it's not already in the list
        int i, sender_exists = 0;
        for (i = 0; i < num_clients; i++) {
            if (memcmp(&client_addresses[i], &sender_address, sizeof(sender_address)) == 0) {
                sender_exists = 1;
                break;
            }
        }
        if (!sender_exists) {
            memcpy(&client_addresses[num_clients], &sender_address, sizeof(sender_address));
            num_clients++;
        }

        // Forward the received message to all clients except the sender
        for (i = 0; i < num_clients; i++) {
            if (memcmp(&client_addresses[i], &sender_address, sizeof(sender_address)) != 0) {
                if (sendto(server_fd, input, strlen(input) + 1, 0, (struct sockaddr *)&client_addresses[i], addr_len) < 0) {
                    perror("sendto");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    close(server_fd);
    return 0;
}

