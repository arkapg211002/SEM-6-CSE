#include "header.h"

void main()
{
	int running=1;
	msg message;
	int msgid;
	long int mp=2;
	int res[BUFSIZ];
	char buf[BUFSIZ],rev[BUFSIZ];
	key_t key=ftok("memory",67);
	msgid=msgget(key,0666|IPC_CREAT);
	
	int num,i,j;

	if(msgid==-1)
	{
		printf("Error connecting to Message Queue\n");
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		if(msgrcv(msgid,(void *)&message,BUFSIZ,mp,0)==-1)
		{
			printf("Cannot receive message 2\n");
			exit(1);
		}

		printf("Message Received : %s\n",message.data);
		if(strcmp(message.data,"end")==0)
		{
			running=0;
			continue;
		}
		
		strcpy(buf,message.data);
		num=atoi(buf);
		
		i=0;
		while(num>0)
		{
			res[i]=num%8;
			num/=8;
			i+=1;
		}
		res[i]='\0';

		for(j=0;j<i;j++)
		{
			rev[j]=res[i-j-1]+'0';
		}
		rev[j]='\0';

		printf("Octal Output of %s is %s\n",buf,rev);
	}

}
