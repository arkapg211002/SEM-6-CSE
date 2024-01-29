#include "header.h"

int compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

void main()
{
	int n=0,i=0,j;
	messageRoll mroll,mrollreturn;
	total tot;

	int msgid;
	char bufname[BUFSIZ];
	int *rolln;
	long int mp=2;
	key_t key=ftok("memory",67);
	msgid=msgget(key,0666|IPC_CREAT);
	
	if(msgid==-1)
	{
		printf("Cannot connect the message queue\n");
		exit(EXIT_FAILURE);
	}
	
	msgrcv(msgid,(void *)&tot,BUFSIZ,4,0);
	n=tot.tot;

	rolln=(int *)malloc(n*sizeof(int));

	for(j=0;j<n;j++)
	{
		if(msgrcv(msgid,(void *)&mroll,BUFSIZ,mp,0)==-1)
		{
			printf("Cannot read roll %d\n",j+1);
		}

		printf("Received Roll %d : %d\n",j+1,mroll.num);
		rolln[j]=mroll.num;
	}
	
	//printf("%d %d",n,i);

	for(i=0;i<n;i++)
	{
		printf("%d\n",rolln[i]);
	}
	
	printf("\n");

	qsort(rolln,n,sizeof(int), compare);

	printf("After sorting\n");
	for(i=0;i<n;i++)
	{
		printf("%d\n",rolln[i]);
	}

	printf("\n");
	for(i=0;i<n;i++)
	{
		mrollreturn.mtype2=6;
		mrollreturn.num=rolln[i];
		if(msgsnd(msgid,(void *)&mrollreturn,MAX,0)==-1)
		{
			printf("Cannot send back roll\n");
			exit(1);
		}
		else
		{
			printf("%d sent back\n",rolln[i]);
		}
	}

	exit(EXIT_SUCCESS);
	
	
}
