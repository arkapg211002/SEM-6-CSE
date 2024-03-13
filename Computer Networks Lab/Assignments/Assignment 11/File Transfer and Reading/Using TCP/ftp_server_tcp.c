#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Forcefully attaching socket to the port 8888
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Binding the socket to the port 8888
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) 
    {
            perror("accept");
            exit(EXIT_FAILURE);
    }
    
    // Accepting incoming connections
    while(1) 
    {
        // Receiving filename from client
        read(new_socket, buffer, BUFFER_SIZE);
        printf("Server received filename: %s\n", buffer);
        if (strcmp(buffer, "end") == 0) 
        {
            printf("Server received 'end'. Closing connection.\n");
            close(new_socket);
            break;
        }
        
        // Opening and sending file content to client
        FILE *file = fopen(buffer, "r");
        if (file == NULL) 
        {
            strcpy(buffer, "File not found!");
            send(new_socket, buffer, strlen(buffer), 0);
        } 
        else 
        {
            fseek(file, 0, SEEK_END);
            long file_size = ftell(file);
            rewind(file);
            fread(buffer, sizeof(char), file_size, file);
            send(new_socket, buffer, file_size, 0);
            fclose(file);
        }
        printf("Server sent file content.\n");
        //close(new_socket);
    }
    close(server_fd);
    return 0;
}

