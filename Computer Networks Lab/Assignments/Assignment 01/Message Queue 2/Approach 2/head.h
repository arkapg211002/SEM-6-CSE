#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MAX_LENGTH 100

struct total
{
	long int type;
	int num;
};

struct student
{
	char name[MAX_LENGTH];
	int roll;
};

struct message
{
	long int msgtype;
	struct student data;
};
