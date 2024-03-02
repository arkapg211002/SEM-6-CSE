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

char* bitstuffing(char* input)
{
    char* stuffed = (char*)malloc(strlen(input) * 2 + 1); 
    if (stuffed == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    int i = 0;
    int j = 0;
    while (input[i] != '\0') 
    {
        if (input[i] == '0') 
	{
            int count = 1;
            stuffed[j] = input[i];
            j++;
            int k;
            for (k = i + 1; input[k] == '0' && count < 5; k++)
	    {
                stuffed[j] = input[k];
                j++;
                count++;
                if (count == 5) 
		{
                    stuffed[j] = '1';
                    j++;
                }
                i = k;
            }
        }
        else 
	{
            stuffed[j] = input[i];
            j++;
        }
        i++;
    }
    stuffed[j] = '\0';
    return stuffed;
}

void main()
{
	int running=1;
	struct message msg,rmsg;
	int msgid=msgget((key_t)1234,0666|IPC_CREAT);
	char result[MAX];

	while(running)
	{
		msgrcv(msgid,(void *)&msg,sizeof(struct message),1,0);
		if(strcmp(msg.data,"end")==0)
		{
			break;
		}
		strcpy(result,bitstuffing(msg.data));
		printf("Sending back %s to client\n",result);
		strcpy(rmsg.data,result);
		rmsg.type=2;
		msgsnd(msgid,(void *)&rmsg,sizeof(struct message),0);
	}

	msgctl(msgid,IPC_RMID,NULL);
}
