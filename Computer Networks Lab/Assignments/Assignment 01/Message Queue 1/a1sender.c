#include "header.h"

void main()
{
	int running=1;
	msg msg1,msg2,msg3;
	int msgid;
	char buf[BUFSIZ];
	key_t key=ftok("memory",67);
	msgid=msgget(key,0666|IPC_CREAT);
	
	if(msgid==-1)
	{
		printf("Cannot create Message Queue\n");
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		printf("Enter the number : ");
		scanf("%[^\n]",buf);
		getchar();
		
		msg1.msgtype=1;
		msg2.msgtype=2;
		msg3.msgtype=3;

		strcpy(msg1.data,buf);
		strcpy(msg2.data,buf);
		strcpy(msg3.data,buf);

		if(msgsnd(msgid,(void *)&msg1,MAX,0)==-1)
		{
			printf("Cannot send message to receiver 1\n");
			exit(1);
		}

		if(msgsnd(msgid,(void *)&msg2,MAX,0)==-1)
		{
			printf("Cannot send message to receiver 2\n");
			exit(1);
		}

		if(msgsnd(msgid,(void *)&msg3,MAX,0)==-1)
		{
			printf("Cannot send message to receiver 3\n");
			exit(1);
		}

		if(strcmp(buf,"end")==0)
		{
			running=0;
		}
	}
	exit(EXIT_SUCCESS);
}
