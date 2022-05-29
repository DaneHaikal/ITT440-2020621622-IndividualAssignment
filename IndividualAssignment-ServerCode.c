#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
        int socketDesc, socketnew, s;
        struct socketaddr_in server, client;
        char *message;

        socketDesc = socket(AF_INET, SOCK_STREAM, 0);
        if(socketDesc == -1)
        {
                printf("Socket Could Not Be Created");
        }
        else
        {
                printf("Socket Created Successfully");
        }

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(42);

        if(bind(socketDesc,(struct socketaddr *)&server, sizeof(server)) <0)
        {
                printf("Bind Failed");
        }
        else
        {
                printf("Socket Binded Successfully");
        }

        listen(socketDesc, 3);
        puts("ARPA Host Name Server Protocol Listening...\n");
        puts("ARPA Host Name Protocol Server");

        puts("\nWaiting for Incoming Connection...\n");
        s = sizeof(struct socketaddr_in);
	while((socketnew = accept(socketDesc, (struct socketaddr *)&client, (socklen_t*)&s))
        {
                printf("Connection Accepted");

                message = "\nYoutube Hostname has been resolved. IP address has been sent");
                write(socketnew, message, strlen(message));
        }

        if(socketnew < 0)
        {
                perror("Accept Failed");
                return 1;
        }

        return 0;

        close(socketDesc);
}

