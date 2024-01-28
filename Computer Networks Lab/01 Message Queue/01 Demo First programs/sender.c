#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/stat.h>
#include<errno.h>

#define MAX 512

typedef struct
{
	long int msgtype;
	char data[BUFSIZ];
}msg;

void main()
{
	int running = 1;
	msg message;
	int msgid;
	char buf[BUFSIZ];
	key_t k=ftok("memory",67);
	msgid=msgget(k,0666|IPC_CREAT);
	
	if(msgid==-1)
	{
		printf("Cannot create message queue\n");
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		printf("Enter some text : ");
		scanf("%[^\n]",buf);
		getchar();
		message.msgtype=1;
		strcpy(message.data,buf);

		if(msgsnd(msgid,(void *)&message,MAX,0)==-1)
		{
			printf("Message cannot be send\n");
			exit(1);
		}
		else
		{
			printf("Message sent successfully\n");
		}

		if(strcmp(buf,"end")==0)
		{
			running=0;
		}
	}
	exit(EXIT_SUCCESS);
}

