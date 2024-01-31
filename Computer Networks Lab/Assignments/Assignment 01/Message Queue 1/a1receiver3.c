#include "header.h"

void main()
{
	int running=1;
	msg message;
	int msgid;
	long int mp=3;
	char res[BUFSIZ];
	char buf[BUFSIZ],rev[BUFSIZ];
	key_t key=ftok("memory",67);
	msgid=msgget(key,0666|IPC_CREAT);
	
	int num,i,j,remainder=0;

	if(msgid==-1)
	{
		printf("Error connecting to Message Queue\n");
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		if(msgrcv(msgid,(void *)&message,BUFSIZ,mp,0)==-1)
		{
			printf("Cannot receive message 1\n");
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
/*		
		i=0;
		while(num>0)
		{
			remainder=num%16;
			if(remainder<10) 
				res[i]=remainder+'0';
			else
				res[i]=(remainder-10)+'A';
			num/=16;
			i+=1;
		}
		res[i]='\0';

		for(j=0;j<i;j++)
		{
			rev[j]=res[i-j-1];
		}
		rev[j]='\0';
*/

/*

To get the string form of octal form

char ch[32];
sprintf(ch,"%032o",num);

To get the string form of hex form

sprintf(ch,"%032x",num);
 
*/
		printf("Hex Output of %s is %032x\n",buf,num);
	}

}
