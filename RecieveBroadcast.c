#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#define PORT 43454

int main()
{
    char buff[256];
    int server_fd, n;

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    struct sockaddr_in server_address;

    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY; //inet_addr("192.168.43.");
    server_address.sin_port = htons(PORT);

    if ((bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }

    int len = sizeof(server_address);

    recvfrom(server_fd, buff, sizeof(buff), 0, (struct sockaddr *)&server_address, &len);
    printf("Message Recieved : %s\n", buff);

    close(server_fd);
}
