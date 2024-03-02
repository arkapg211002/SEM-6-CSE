#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <errno.h>

#define MAX 32

struct message
{
	long int type;
	char data[MAX];
};

void main()
{
	int running=1;
	struct message msg;
	int msgid=msgget((key_t)1234,0666|IPC_CREAT);
	char buf[100];
	while(running)
	{
		printf("enter the roll number : ");
		scanf("%[^\n]",buf);
		getchar();
		if(strlen(buf)>32)
		{
			printf("32 bits allowed only \n");
			printf("enter correctly : ");
			scanf("%[^\n]",buf);
			getchar();
		}

		strcpy(msg.data,buf);
		msg.type=1;
		msgsnd(msgid,(void *)&msg,sizeof(struct message),0);
		if(strcmp(msg.data,"end")==0)
		{
			break;
		}
	}
}
