#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>

#define MAX 512

typedef struct
{
	long int ttype;
	int tot;
}total;

typedef struct
{
	long int mtype1;
	char data[BUFSIZ];
}messageName;

typedef struct
{
	long int mtype2;
	int num;
}messageRoll;

