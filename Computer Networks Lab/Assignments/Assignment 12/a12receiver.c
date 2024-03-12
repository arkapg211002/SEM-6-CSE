#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main (){
	struct sockaddr_in s, c;
	int r, ack = 0, seed = 10001000, delay;
	int sid = socket (AF_INET, SOCK_STREAM, 0);
	perror ("socket");

	s.sin_family = AF_INET;
	s.sin_port = htons (5555);
	inet_aton ("127.0.0.1", &s.sin_addr);
	bind (sid, (struct sockaddr *) &s, sizeof (s));
	perror ("bind");

	listen (sid, 1);
	perror ("listen");

	int l = sizeof (c);
	int cid = accept (sid, (struct sockaddr *) &c, &l);
	perror ("accept");

	srand (seed);
	while (1)
	{
		read (cid, &r, sizeof (r));
		if (r == ack)
		{
		printf ("\nReceived Sequence No.: %d\n", r);
		ack = (ack + 1) % 2;
		}
		else
		printf ("\nReceived DUPLICATE frame: %d\n", r);
		/* Introducing a random delay (1 - 7 sec.) between receiving a frame and */
		/* sending it's ack to see what happens in the Sender side */
		delay = (rand() % 7) + 1;
		sleep (delay);
		write (cid, &ack, sizeof (ack));
		printf ("\nAcknowledgement %d sent\n", ack);
	}
	return 0;
}
