#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char filename[BUFFER_SIZE],result[BUFFER_SIZE];
    
    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    while (1) {
        printf("Enter filename (or 'end' to quit): ");
        scanf("%[^\n]", filename);
        getchar();
        
        // Send filename to server
        send(sock, filename, strlen(filename)+1, 0);
        if (strcmp(filename, "end") == 0) {
            printf("Client sent 'end'. Exiting.\n");
            break;
        }
        
        // Receive file content from server
        read(sock, result, BUFFER_SIZE);
        printf("%s\n", result);
        //memset(buffer, 0, BUFFER_SIZE);
    }
    close(sock);
    return 0;
}

