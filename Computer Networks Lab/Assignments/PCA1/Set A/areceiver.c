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
	int running=1,i,len=0;
	struct message msg;
	int msgid=msgget((key_t)1234,0666|IPC_CREAT);
	char buf[100];

	while(running)
	{
		msgrcv(msgid,(void *)&msg,sizeof(struct message),1,0);
		strcpy(buf,msg.data);
		printf("Received : %s\n",buf);
		if(strcmp(buf,"end")==0)
		{
			break;
		}
		printf("The roll in reverse order \n");
		len=strlen(buf);
		for(i=len-1;i>=0;i--)
		{
			printf("%c",buf[i]);
		}
		printf("\n");
	}
	msgctl(msgid,IPC_RMID,NULL);
}
