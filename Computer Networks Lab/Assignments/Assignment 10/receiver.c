#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define BROADCAST_PORT 4444

int main(int argc,char* argv[]){
	struct sockaddr_in caddr;
	char data[1024];
	char BROADCAST_ADDR[32];
	int cs=socket(AF_INET,SOCK_DGRAM,0);
	int reuse=1;
	setsockopt(cs,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	caddr.sin_family=AF_INET;
	caddr.sin_addr.s_addr=htonl(INADDR_ANY);
	caddr.sin_port=htons(BROADCAST_PORT);
	bind(cs,(struct sockaddr*)&caddr,sizeof(caddr));
	printf("Receiver %s\n",argv[1]);
	while(1){
		recvfrom(cs,data,sizeof(data),0,NULL,0);
		printf("\nBroadcasted Message: %s\n",data);
		if(!strcasecmp(data,"quit"))
			break;
	}
	close(cs);
	return 0;
}
