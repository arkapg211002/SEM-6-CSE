#include "head.h"

void main()
{
	int msgid,n,i;
	struct message msg1,msg2,rmsg1,rmsg2;
	struct total t1,t2;

	msgid=msgget((key_t)1234,0666|IPC_CREAT);
	if(msgid == -1)
	{
		printf("Cannot Create message queue\n");
		exit(1);
	}

	printf("Enter the number of students : ");
	scanf("%d",&n);

	t1.type=3;
	t1.num=n;
	if(msgsnd(msgid,(void *)&t1,sizeof(int),0)==-1)
	{
		printf("Cannot send the total number1 \n");
		perror("msgsnd");
		exit(1);
	}

	t2.type=4;
	t2.num=n;
	if(msgsnd(msgid,(void *)&t2,sizeof(int),0)==-1)
	{
		printf("Cannot send the total number2 \n");
		perror("msgsnd");
		exit(1);
	}

	for(i=0;i<n;i++)
	{
		printf("Enter the name of the student %d : ",(i+1));
		scanf("%s",msg1.data.name);
		printf("Enter the roll number of the student %d : ",(i+1));
		scanf("%d",&msg1.data.roll);
		
		strcpy(msg2.data.name,msg1.data.name);
		msg2.data.roll=msg1.data.roll;

		msg1.msgtype=1;
		if(msgsnd(msgid,(void *)&msg1,sizeof(struct student),0)==-1)
		{
			printf("Cannot send student data to p2\n");
			perror("msgid");
			exit(1);
		}
		else
		{
			printf("Sent data to p2\n");
		}

		msg2.msgtype=2;
		if(msgsnd(msgid,(void *)&msg2,sizeof(struct student),0)==-1)
		{
			printf("Cannot send student data to p3\n");
			perror("msgid");
			exit(1);
		}
		else
		{
			printf("Sent data to p3\n");
		}
	}

	printf("\nReceiving back sorted data\n\n");

	printf("Sorted data according to roll number\n");
	for(i=0;i<n;i++)
	{
		msgrcv(msgid,(void *)&rmsg1,sizeof(struct student),5,0);
		printf("%s %d\n",rmsg1.data.name,rmsg1.data.roll);
	}

	printf("\nSorted data sccording to name\n");
	for(i=0;i<n;i++)
	{
		msgrcv(msgid,(void *)&rmsg2,sizeof(struct student),6,0);
		printf("%s %d\n",rmsg2.data.name,rmsg2.data.roll);
	}

	printf("\n");

	msgctl(msgid,IPC_RMID,NULL);
	
}
