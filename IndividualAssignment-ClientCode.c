#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX 1024
#define PORT 42
#define SA struct sockaddr

int main(int argc, int sockfd, char *argv[])
{
	int sockDesc;
	struct sockaddr_in server;
	char *message, server_reply[2000];

	char buff[1024];
	bzero(buff, 1024);
	int n;

	sockDesc = socket(AF_INET, SOCK_STREAM, 0);
	if(sockDesc == -1)
	{
		printf("Could not create a socket");
	}
	else
	{
		printf("Socket successfully created");
	}

	server.sin_addr.s_addr = inet_addr("192.168.56.103");
	server.sin_family = AF_INET;
	server.sin_port = htons( 42 );

	if(connect(sockDesc, (struct sockaddr *)&server, sizeof(server)) <0)
	{
		printf("Connection Error");
		return 1;
	}
	
	printf("Socket connecting to remote server...");
	printf("Socket Connected");
	printf("\nARPA Host Name Server Protocol Client\n");

	do
	{
		bzero(buff, sizeof(buff));
		printf("Enter your request: \n");
		n = 0;
		
		while ((buff[n++] = getchar()) != '\n');
			write(sockfd, buff, sizeof(buff));
			bzero(buff, sizeof(buff));
			read(sockfd,buff,sizeof(buff));
	}
	while (0);

