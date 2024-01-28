#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<errno.h>

#define MAX 512

typedef struct
{
	long int msgtype;
	char data[BUFSIZ];
}msg;

