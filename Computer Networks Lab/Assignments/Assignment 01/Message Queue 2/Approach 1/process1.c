#include "header.h"

void main()
{
	int n,i;
	messageName mname,mnamesorted;
	messageRoll mroll,mrollsorted;
	total tot1,tot2;

	int msgid;
	char bufname[BUFSIZ];
	int bufroll;
	key_t key=ftok("memory",67);
	msgid=msgget(key,0666|IPC_CREAT);

	if(msgid==-1)
	{
		printf("Cannot create Message Queue\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Enter the number of students : ");
	scanf("%d",&n);

	tot1.ttype=3;
	tot1.tot=n;
	msgsnd(msgid,(void *)&tot1,MAX,0);
	tot2.ttype=4;
	tot2.tot=n;
	msgsnd(msgid,(void *)&tot2,MAX,0);
	printf("Total Number of students sent\n");	

	for(i=0;i<n;i++)
	{
		printf("Enter the name and roll of the student %d : ",i+1);
		scanf("%s %d",bufname,&bufroll);
		getchar();
		
		mname.mtype1=1;
		mroll.mtype2=2;

		strcpy(mname.data,bufname);
		mroll.num=bufroll;

		if(msgsnd(msgid,(void *)&mname,MAX,0)==-1)
		{
			printf("Cannot send the name to message queue\n");
			msgctl(msgid,IPC_RMID,0);
			exit(1);
		}
		else
		{
			printf("Name sent successfully\n");
		}

		if(msgsnd(msgid,(void *)&mroll,BUFSIZ,0)==-1)
		{
			printf("Cannot send the roll to message queue\n");
			msgctl(msgid,IPC_RMID,0);
			exit(1);
		}
		else
		{
			printf("Roll sent successfully\n");
		}

	}
	
	printf("\nSorted names and roll numbers are :\n");
	for(i=0;i<n;i++)
	{
		if(msgrcv(msgid,(void *)&mnamesorted,BUFSIZ,5,0)==-1)
		{
			printf("Cannot read name\n");
			exit(1);
		}
		if(msgrcv(msgid,(void *)&mrollsorted,BUFSIZ,6,0)==-1)
		{
			printf("Cannot read roll\n");
			exit(1);
		}
		printf("%s\t%d\n",mnamesorted.data,mrollsorted.num);
		
	}

	msgctl(msgid,IPC_RMID,0);

	exit(EXIT_SUCCESS);

}
