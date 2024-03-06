#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define MAX 100

void main()
{
	 
    	FILE *fp;
    	char mac[MAX],res[MAX];

	int sockfd,len,result;
	struct sockaddr_un address;
	sockfd=socket(AF_UNIX,SOCK_STREAM,0);
	address.sun_family=AF_UNIX;
	strcpy(address.sun_path,"dserver");
	len=sizeof(address);
	result=connect(sockfd,(struct sockaddr *)&address,len);

	printf("Client Running\n");

    	fp=popen("ip addr show | awk '/ether/ {print $2}'", "r");
    	fgets(mac, MAX, fp);
    	pclose(fp);
	mac[strcspn(mac, "\n")] = 0;

	if(result==-1)
	{
		printf("Client cannot connect to the server\n");
		perror("connect");
		exit(1);
	}
	else
	{
		printf("Client Connected to the server\n");
	}

	printf("Sending MAC Address to the server\n");
	write(sockfd,mac,strlen(mac)+1);
	printf("Waiting for the server\n");
	sleep(2);
	read(sockfd,res,MAX);
	printf("The reverse of the MAC Address is %s\n",res);

	close(sockfd);
}
