#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include <sys/un.h>

typedef struct DataPackage {
    char message[100];
    char polynomial[20];
} DataPackage;

void main(){
    int clientSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un serverAddress;
    serverAddress.sun_family = AF_UNIX;
    strcpy(serverAddress.sun_path, "mySock");
    connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    while(1){
        DataPackage package;

        printf("Enter message to be sent: ");
        scanf("%s", package.message);

        if(strcmp(package.message, "EXIT")==0 || strcmp(package.message, "exit")==0)
            break;

        int power;
        printf("Enter max power of x: ");
        scanf("%d", &power);
        printf("Enter 1/0 (without space) for presence/absence of x^n starting with x^%d, x^%d, ... x^0: ", power, power - 1);
        scanf("%s", package.polynomial);

        char additionalBit = '0';
        for(int i=0; i<power; i++)
            strncat(package.message, &additionalBit, 1);

        write(clientSocket, (void *)&package, sizeof(package));
        sleep(1);
        read(clientSocket, (void *)&package, sizeof(package));
        printf("Received message: %s\n\n", package.message);
    }

    close(clientSocket);
}

