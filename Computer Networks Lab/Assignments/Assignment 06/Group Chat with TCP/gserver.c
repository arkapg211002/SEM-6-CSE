#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#define MAX 100
#define N 10

pthread_t t[N];
int server_fd,server_len;
struct sockaddr_in server_address;
int ac=0;

struct Node
{
	int cfd;
	char ip[MAX];
	int cport;
	struct Node *next;
};
struct Node *head=NULL;

struct Node *createNode(int cfd,char *ip,int cport)
{
	struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
	strcpy(newNode->ip,ip);
	newNode->cfd=cfd;
	newNode->cport=cport;
	newNode->next=NULL;
	return newNode;
}

void insert(struct Node **head,int cfd,char *ip,int cport)
{
	struct Node *newNode=createNode(cfd,ip,cport);
	if(*head==NULL)
	{
		*head=newNode;
		printf("Client fd(%d) : %s : %d added to the list\n",cfd,ip,cport);
		return;
	}

	struct Node *temp=*head;
	while(temp->next != NULL)
		temp=temp->next;
	temp->next=newNode;
	printf("Client fd(%d) : %s : %d added to the list\n",cfd,ip,cport);
}

void deleteNode(struct Node** headRef, int cfd, char *ip, int cport) {
	struct Node* currentNode = *headRef;
	struct Node* prevNode = NULL;

	if(currentNode!=NULL && currentNode->cfd==cfd && currentNode->cport==cport && strcmp(currentNode->ip,ip)==0) 
	{
		*headRef=currentNode->next;  
		free(currentNode);  
		printf("Client fd(%d) : %s : %d removed from the list\n",cfd,ip,cport);
		return;
	}

	while(currentNode!=NULL && currentNode->cport!=cport) 
	{
		prevNode=currentNode;
		currentNode=currentNode->next;
	}

	if(currentNode==NULL) 
	{
		printf("Node with port %d not found in the list\n", cport);
		return;
	}

	prevNode->next=currentNode->next;
	free(currentNode);
	printf("Client fd(%d) : %s : %d removed from the list\n",cfd,ip,cport);
}

void *client(void *args)
{
	int sockfd=server_fd;
	struct sockaddr_in client_address;
	int client_len=sizeof(client_address);
	char cip[MAX],input[MAX];
	int client_port;
	int client_fd=accept(sockfd,(struct sockaddr *)&client_address,&client_len);
	strcpy(cip,inet_ntoa(client_address.sin_addr));
	client_port=ntohs(client_address.sin_port);
	printf("Client fd(%d) : %s : %d joined the chat\n",client_fd,cip,client_port);
	insert(&head,client_fd,cip,client_port);
	ac+=1;
	
	while(1)
	{
		printf("Server Waiting..\n");
		read(client_fd,input,MAX);
		printf("Reeceived from client fd(%d) : %s : %d -> %s\n",client_fd,cip,client_port,input);
		
		struct Node *temphead=head;
		struct Node *tempnode;
		struct sockaddr_in tempclient=client_address;
		
		while(temphead!=NULL)
		{
			tempnode=temphead;
			temphead=temphead->next;
			
			int cfd=tempnode->cfd;
			client_address.sin_addr.s_addr=inet_addr(tempnode->ip);
			client_address.sin_port=htons(tempnode->cport);
			
			if(tempnode->cfd!=client_fd && tempnode->cport!=client_port)
			{
				write(cfd,input,strlen(input)+1);
				printf("Sending message to client fd(%d) : %s : %d\n",cfd,tempnode->ip,tempnode->cport);
			}
				
			client_address=tempclient;
		}	
		
		if(strstr(input,"end")!=NULL)
		{
			printf("Client fd(%d) : %s : %d Disconnected\n",client_fd,cip,client_port);
			close(client_fd);
			deleteNode(&head,client_fd,cip,client_port);
			break;
		}
	}
	
	ac-=1;
	if(ac==0)
	{
		printf("No more clients : Server Ending\n");
		close(server_fd);
		exit(0);
	}
	pthread_exit(NULL);
}

void main()
{
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(8888);
	server_len=sizeof(server_address);

	bind(server_fd,(struct sockaddr *)&server_address,server_len);
	listen(server_fd,5);
	printf("Server Running\n");

	for(int i=0;i<N;i++) pthread_create(&t[i],NULL,(void *)&client,NULL);
	for(int i=0;i<N;i++) pthread_join(t[i],NULL);
}
