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
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_address, client_address;
    char buff[] = "This is a broadcast Message";

    if (server_fd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_BROADCAST;
    server_address.sin_port = htons(PORT);

    int broadcastPermission = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_BROADCAST, (void *)&broadcastPermission, sizeof(broadcastPermission));

    printf("\n Sending Broadcast");
    sendto(server_fd, buff, sizeof(buff), 0, (struct sockaddr *)&server_address, sizeof(server_address));
    printf("\n........sent");

    close(server_fd);
}
