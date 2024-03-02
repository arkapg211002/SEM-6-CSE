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

#define MAX 100

struct message
{
	long int type;
	char data[MAX];
};

void main()
{
	int running=1;
	struct message msg,rmsg;
	int msgid=msgget((key_t)1234,0666|IPC_CREAT);
	char buf[MAX];

	while(running)
	{
		printf("Enter the bit stream : ");
		scanf("%[^\n]",buf);
		getchar();
		msg.type=1;
		strcpy(msg.data,buf);
		printf("Sending to the server \n");
		msgsnd(msgid,(void *)&msg,sizeof(struct message),0);
		if(strcmp(buf,"end")==0)
		{
			break;
		}
		msgrcv(msgid,(void *)&rmsg,sizeof(struct message),2,0);
		printf("Received from server : %s\n",rmsg.data);
	}
}
