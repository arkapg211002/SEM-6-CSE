#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>

#define TERMINATE "Exit"
#define MAX_MESSAGE_LENGTH 1000

char name[100]; // Assuming maximum name length of 100 characters
volatile bool finished = false;

struct ReadThreadArgs {
    int socketDescriptor;
    struct sockaddr_in groupAddr;
    int port;
};

void *readThread(void *args) {
    struct ReadThreadArgs *threadArgs = (struct ReadThreadArgs *)args;
    int socketDescriptor = threadArgs->socketDescriptor;
    struct sockaddr_in groupAddr = threadArgs->groupAddr;
    int port = threadArgs->port;

    while (!finished) {
        char buffer[MAX_MESSAGE_LENGTH];
        socklen_t addrLength = sizeof(struct sockaddr_in);
        ssize_t recvLen = recvfrom(socketDescriptor, buffer, MAX_MESSAGE_LENGTH, 0,
                                    (struct sockaddr *)&groupAddr, &addrLength);

        if (recvLen < 0) {
            perror("Error receiving message");
            continue;
        }

        buffer[recvLen] = '\0'; // Null-terminate the received message

        // Add your message processing here
    }

    free(threadArgs); // Free memory allocated for thread arguments
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Two arguments required: <multicast-host> <port-number>\n");
    } else {
        struct sockaddr_in groupAddr;
        int port;
        int socketDescriptor;

        inet_pton(AF_INET, argv[1], &groupAddr.sin_addr);
        port = atoi(argv[2]);

        printf("Enter your name: ");
        fgets(name, MAX_MESSAGE_LENGTH, stdin);
        strtok(name, "\n"); // Remove the trailing newline character

        // Your socket creation and configuration here

        printf("Start typing messages...\n");

        while (1) {
            char message[MAX_MESSAGE_LENGTH];
            fgets(message, MAX_MESSAGE_LENGTH, stdin);
            strtok(message, "\n"); // Remove the trailing newline character

            if (strcmp(message, TERMINATE) == 0) {
                finished = true;
                // Your cleanup code here
                break;
            }

            char formattedMessage[MAX_MESSAGE_LENGTH];
            snprintf(formattedMessage, MAX_MESSAGE_LENGTH, "%s: %s", name, message);

            // Your message sending code here
        }
    }

    return 0;
}
