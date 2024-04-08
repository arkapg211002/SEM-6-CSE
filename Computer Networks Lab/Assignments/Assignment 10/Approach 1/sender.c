#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define BROADCAST_PORT 4444

char* getBroadcastAddress(int ss){
	struct ifreq *ifr,*inf;
	struct ifconf ifcnf;
	char buf[4096];
	char* braddr=(char*)malloc(sizeof(char)*32);
	strcpy(braddr,"braddr");
	int i=0,flag=0;
	size_t len;
	ifcnf.ifc_len=sizeof(buf);
	ifcnf.ifc_buf=buf;
	ioctl(ss,SIOCGIFCONF,&ifcnf);
	ifr=ifcnf.ifc_req;
	while(flag==0){
		inf=&ifr[i++];
		if(!strcasecmp(inf->ifr_name,"lo"))
			continue;
		if(ioctl(ss,SIOCGIFBRDADDR,inf)>=0){
			strcpy(braddr,inet_ntoa(((struct sockaddr_in*)&inf->ifr_broadaddr)->sin_addr));
			flag++;
		}
	}
	if(!strcasecmp(braddr,"0.0.0.0") || !strcasecmp(braddr,"braddr")){
		strcpy(braddr,"NA");
	}
	return braddr;
}

int main(int argc,char* argv[]){
	struct sockaddr_in saddr;
	char data[1024];
	char BROADCAST_ADDR[32];
	int broadcast=1;
	int ss=socket(AF_INET,SOCK_DGRAM,0);
	setsockopt(ss,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(broadcast));
	saddr.sin_family=AF_INET;
	strcpy(BROADCAST_ADDR,getBroadcastAddress(ss));
	printf("Broadcast Address: %s\n",BROADCAST_ADDR);
	if(!strcasecmp(BROADCAST_ADDR,"NA")){
		saddr.sin_addr.s_addr=htonl(INADDR_BROADCAST);	
	}
	else{
		inet_aton(BROADCAST_ADDR,&(saddr.sin_addr));
	}
	saddr.sin_port=htons(BROADCAST_PORT);
	while(1){
		printf("\nEnter message to be broadcasted: ");
		fgets(data,sizeof(data),stdin);
		data[strlen(data)-1]='\0';
		sendto(ss,data,strlen(data)+1,0,(struct sockaddr*)&saddr,sizeof(saddr));
		if(!strcasecmp(data,"exit"))
			break;
		printf("\nMessage Broadcasted!\n");
	}
	close(ss);
	return 0;
}
