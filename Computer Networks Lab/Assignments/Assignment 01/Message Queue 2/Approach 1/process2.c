#include "header.h"

int compare(const void *a, const void *b)
{
	return strcmp(*(const char **)a, *(const char **)b);
}

void main()
{
	int n=0,i=0,j;
	messageName mname,mnamereturn;
	total tot;

	int msgid;
	char bufname[BUFSIZ],**string;
	long int mp=1;
	key_t key=ftok("memory",67);
	msgid=msgget(key,0666|IPC_CREAT);
	
	if(msgid==-1)
	{
		printf("Cannot connect the message queue\n");
		exit(EXIT_FAILURE);
	}
	
	msgrcv(msgid,(void *)&tot,BUFSIZ,3,0);
	n=tot.tot;

	string=(char **)malloc(n*sizeof(char *));

	for(j=0;j<n;j++)
	{
		if(msgrcv(msgid,(void *)&mname,BUFSIZ,mp,0)==-1)
		{
			printf("Cannot read name %d\n",j+1);
		}

		printf("Received Name %d : %s\n",j+1,mname.data);
		string[j]=(char *)malloc(MAX*sizeof(char));
		strcpy(string[j],mname.data);
	}
	
	//printf("%d %d",n,i);

	for(i=0;i<n;i++)
	{
		printf("%s\n",string[i]);
	}
	
	printf("\n");

	qsort(string,n,sizeof(char *),compare);

	printf("After sorting\n");
	for(i=0;i<n;i++)
	{
		printf("%s\n",string[i]);
	}
	
	printf("\n");
	for(i=0;i<n;i++)
	{
		mnamereturn.mtype1=5;
		strcpy(mnamereturn.data,string[i]);
		if(msgsnd(msgid,(void *)&mnamereturn,MAX,0)==-1)
		{
			printf("Cannot send back data\n");
			exit(1);
		}
		else
		{
			printf("%s sent back\n",string[i]);
		}
	}

	exit(EXIT_SUCCESS);
	
	
}
