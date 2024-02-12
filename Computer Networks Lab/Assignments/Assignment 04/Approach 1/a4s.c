#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include <sys/un.h>

typedef struct DataPacket {
    char message[100];
    char divisor[20];
} DataPacket;

void main() {
    remove("mySock");
    
    int serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un serverAddress, clientAddress;
    serverAddress.sun_family = AF_UNIX;
    strcpy(serverAddress.sun_path, "mySock");
    bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 5);

    int clientSocket, clientAddressLen;
    clientAddressLen = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);

    while(1) {
        DataPacket packet;
        read(clientSocket, (void *)&packet, sizeof(packet));
        printf("Received message from client\n");

        if(strcmp(packet.message, "EXIT") == 0 || strcmp(packet.message, "exit") == 0)
            break;

        int divisorLength = strlen(packet.divisor);
        int msgCursor = divisorLength;

        char tempDivisor[20] = "";
        strncat(tempDivisor, packet.message, divisorLength);

        while(msgCursor <= strlen(packet.message)) {
            char remainder[20] = "";
            
            for(int i = 0; i < divisorLength; i++) {
                if(tempDivisor[i] == packet.divisor[i])
                    remainder[i] = '0';
                else
                    remainder[i] = '1';
            }

            int startPos;
            for(startPos = 0; startPos < divisorLength; startPos++) {
                if(remainder[startPos] == '1')
                    break;
            }

            int tempStart = 0;
            while(startPos < divisorLength) {
                tempDivisor[tempStart++] = remainder[startPos++];
            }

            while(tempStart < divisorLength) {
                tempDivisor[tempStart++] = packet.message[msgCursor++];
            }
        }

        int messageIndex = strlen(packet.message) - strlen(tempDivisor);
        int tempIndex = 0;
        for(; messageIndex < strlen(packet.message); messageIndex++, tempIndex++) {
            if(packet.message[messageIndex] == tempDivisor[tempIndex])
                packet.message[messageIndex] = '0';
            else
                packet.message[messageIndex] = '1';
        }

        write(clientSocket, (void *)&packet, sizeof(packet));
        printf("Message sent to client\n\n");

        sleep(1);
    }

    close(clientSocket);
}

