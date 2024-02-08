#include "head.h"

int compare(const void *a, const void *b)
{
	return strcmp(((struct student *)a)->name, ((struct student *)b)->name);
}

void main()
{
	int msgid,n,i;
	struct message msg,msgreturn;
	struct total t;
	struct student *st;

	msgid=msgget((key_t)1234,0666|IPC_CREAT);
	if(msgid==-1)
	{
		printf("Cannot connect to the message queue\n");
		exit(1);
	}

	msgrcv(msgid,(void *)&t,sizeof(int),4,0);
	printf("Received total number : %d\n",t.num);
	n=t.num;

	st=(struct student *)malloc(n*sizeof(struct student));

	for(i=0;i<n;i++)
	{
		msgrcv(msgid,(void *)&msg,sizeof(struct student),2,0);
		printf("Received Name and Roll : %s %d\n",msg.data.name,msg.data.roll);
		
		st[i]=msg.data;
	}
	
	printf("\nThe Array of student data is : \n");
	for(i=0;i<n;i++)
	{
		printf("%s %d\n",st[i].name,st[i].roll);
	}

	qsort(st,n,sizeof(struct student),compare);

	printf("\nAfter sorting according to name \n");
	for(i=0;i<n;i++)
	{
		printf("%s %d\n",st[i].name,st[i].roll);
	}

	for(i=0;i<n;i++)
	{
		msgreturn.msgtype=6;
		msgreturn.data=st[i];
		if(msgsnd(msgid,(void *)&msgreturn,sizeof(struct student),0)==-1)
		{
			printf("Cannot send back data\n");
			exit(1);
		}
		else
		{
			printf("Sent data %i\n",(i+1));
		}
	}

}
