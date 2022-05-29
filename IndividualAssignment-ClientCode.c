#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX 1024
#define PORT 42
#define SA struct socketaddr

int main(int argc, int sockfd, char *argv[])
{
	int socketDesc;
	struct socketaddr_in server;
	char *message, server_reply[2000];

	char buff[1024];
	bzero(buff, 1024);
	int n;

	socketDesc = socket(AF_INET, SOCK_STREAM, 0);
	if(socketDesc == -1)
	{
		printf("Socket Could Not Be Created");
	}
	else
	{
		printf("Socket Created Successfully\n");
	}

	server.sin_addr.s_addr = inet_addr("192.168.56.103");
	server.sin_family = AF_INET;
	server.sin_port = htons( 42 );

	if(connect(socketDesc, (struct socketaddr *)&server, sizeof(server)) <0)
	{
		printf("Connection Error");
		return 1;
	}

	printf("Socket Connecting to Server...");

	printf("Socket Connected");

	printf("\nARPA Host Name Server Protocol Client\n");

	do
	{
		bzero(buff, sizeof(buff));
		printf("Enter Your Request: \n");
		n = 0;

		while ((buff[n++] = getchar()) != '\n');
			write(sockfd, buff, sizeof(buff));
			bzero(buff, sizeof(buff));
			read(sockfd,buff,sizeof(buff));
	}
	while (0);

	if(recv(socketDesc, server_reply, 2000, 0) <0)
	{
		printf("Recv Failed");
	}

	printf("\nReply Received\n");

	printf(server_reply);

	char *hostname = "www.youtube.com";
	char ipaddr[100];
	struct hostent *host;
	struct in_addr  **addr_list;

	if((host = gethostbyname(hostname)) == NULL)
	{
		herror("gethostbyname");
		return 1;
	}
	printf("Hostname: www.youtube.com");

	addr_list = (struct in_addr **) host->h_addr_list;

	for(int i = 0; addr_list[i] != NULL; i++)
	{
		strcpy(ipaddr, inet_ntoa(*addr_list[i]));
	}

	printf("IP ADDRESS: %s \n",ipaddr);
	return 0;

	close(sockfd);
}
