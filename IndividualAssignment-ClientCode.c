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
		printf("Socket successfully created\n");
	}

	server.sin_addr.s_addr = inet_addr("192.168.56.103");
	server.sin_family = AF_INET;
	server.sin_port = htons( 42 );

	if(connect(sockDesc, (struct sockaddr *)&server, sizeof(server)) <0)
	{
		printf("Connection Error");
		return 1;
	}

	puts("Socket connecting to remote server...");

	puts("Socket Connected");

	puts("\nARPA Host Name Server Protocol Client\n");

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

	if(recv(sockDesc, server_reply, 2000, 0) <0)
	{
		puts("recv failed");
	}

	puts("\nReply Received\n");

	puts(server_reply);

	char *hostname = "www.facebook.com";
	char ipaddr[100];
	struct hostent *host;
	struct in_addr  **addr_list;
	int i;

	if((host = gethostbyname(hostname)) == NULL)
	{
		herror("gethostbyname");
		return 1;
	}
	puts("Hostname: www.facebook.com");

	addr_list = (struct in_addr **) host->h_addr_list;

	for(i = 0; addr_list[i] != NULL; i++)
	{
		strcpy(ipaddr, inet_ntoa(*addr_list[i]));
	}

	printf("IP ADDRESS: %s \n",ipaddr);
	return 0;

	close(sockfd);
}
