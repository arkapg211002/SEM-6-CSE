#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<semaphore.h>
#include<pthread.h>

sem_t s;
int seqNo = 0, timedOut = 0;
pthread_t t3;
int count = 0;

void* timer (void *c)
{
	count++;
	printf ("Started Timer %d\n", count);
	sleep (5);
	timedOut = 1;
	sem_post (&s);
	pthread_exit (NULL);
}


void* sender (void *arg){
	int cid = *((int *) arg);
	while (1)
	{
		if (!timedOut)
		{
			printf ("\nSending Sequence number: %d\n", seqNo);
			write (cid, &seqNo, sizeof (seqNo));
			seqNo = (seqNo + 1) % 2;
		}
		else if (timedOut)
		{
			seqNo = (seqNo + 1) % 2;
			printf ("\nAcknowledgement not Received. Timer timed out.\n");
			printf ("Re-Sending Sequence number: %d\n", seqNo);
			write (cid, &seqNo, sizeof (seqNo));
		}
		timedOut = 0;
		pthread_create (&t3, NULL, timer, NULL);
		sem_wait (&s);
		pthread_join (t3, NULL);
	}
	pthread_exit (NULL);
}


void* receiver (void *arg){
	int cid = *((int *) arg);
	int ack;
	while (1){
		read (cid, &ack, sizeof (ack));
		printf ("\nAcknowledgement %d Received\n", ack);
		if (ack == seqNo)
		{
			pthread_cancel (t3);
			timedOut = 0;
			sem_post (&s);
		}
	}
	pthread_exit (NULL);
}


int main (){
	int cid = socket (AF_INET, SOCK_STREAM, 0);
	perror ("socket");

	struct sockaddr_in c;
	c.sin_family = AF_INET;
	c.sin_port = htons (5555);
	inet_aton ("127.0.0.1", &c.sin_addr);
	connect (cid, (struct sockaddr *) &c, sizeof (c));
	perror ("connect");

	sem_init(&s, 0, 1);
	pthread_t t1, t2;
	pthread_create (&t1, NULL, sender, (void *) &cid);
	pthread_create (&t2, NULL, receiver, (void *) &cid);
	pthread_join (t1, NULL);
	pthread_join (t2, NULL);
	sem_destroy(&s);
	return 0;
}



