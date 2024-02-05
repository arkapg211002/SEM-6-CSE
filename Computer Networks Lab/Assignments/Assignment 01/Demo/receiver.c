#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>

#define MAX 512

typedef struct
{
	long int msgtype;
	char data[BUFSIZ];
}msg;

void main()
{
	int running=1;
	msg message;
	int msgid;
	long int msgpriority=0;
	key_t k=ftok("memory",67);
	msgid=msgget(k,0666|IPC_CREAT);
	
	if(msgid==-1)
	{
		printf("Error connecting to the message queue\n");
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		if(msgrcv(msgid,(void *)&message,BUFSIZ,msgpriority,0)==-1)
		{
			printf("Cannot receive message\n");
			exit(1);
		}
		printf("Message received : %s\n",message.data);
		if(strcmp(message.data,"end")==0)
		{
			running=0;
		}
	}

	if(msgctl(msgid,IPC_RMID,0)==-1)
	{
		printf("Error deleting message queue\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
