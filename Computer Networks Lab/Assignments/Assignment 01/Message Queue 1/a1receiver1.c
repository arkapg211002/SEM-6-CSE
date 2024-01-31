#include "header.h"

char* bin(unsigned n)
{
    char* binaryString = (char*)malloc(33); // 32 bits + 1 for null terminator
    unsigned i;
    for (i = 1 << 31; i > 0; i = i / 2)
        strcat(binaryString, (n & i) ? "1" : "0");

    return binaryString;
}

void main()
{
    int running = 1;
    msg message;
    int msgid,num;
    long int mp = 1;
    char buf[BUFSIZ], *rev;
    key_t key = ftok("memory", 67);
    msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1)
    {
        printf("Error connecting to Message Queue\n");
        exit(EXIT_FAILURE);
    }

    while (running)
    {
        if (msgrcv(msgid, (void *)&message, BUFSIZ, mp, 0) == -1)
        {
            printf("Cannot receive message 1\n");
            exit(1);
        }

        printf("Message Received : %s\n", message.data);
        if (strcmp(message.data, "end") == 0)
        {
            running = 0;
            continue;
        }

        strcpy(buf, message.data);
        num = atoi(buf);
	rev=bin(num);
        printf("Binary Output of %s is %s\n", buf, rev);
    }
    exit(EXIT_SUCCESS);
}
