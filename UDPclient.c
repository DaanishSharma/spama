#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

int main()
{
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_address;

    if (client_fd == -1)
    {
        printf("socket creation error");
        exit(0);
    }
    else
        printf("socket creation success");

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    char buff[256];
    int n;
    int len = sizeof(server_address);

    while (1)
    {
        bzero(buff, sizeof(buff));
        printf("Enter message :");
        while ((buff[n++] = getchar()) != '\n')
            ;
        sendto(client_fd, buff, sizeof(buff), 0, (struct sockaddr *)&server_address, len);

        bzero(buff, sizeof(buff));
        recvfrom(client_fd, buff, sizeof(buff), 0, (struct sockaddr *)&server_address, &len);
        printf("From server: %s", buff);
    }

    close(client_fd);
}