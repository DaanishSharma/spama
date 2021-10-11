#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

void func(int server_fd)
{
    char buff[256];
    int n;
    struct sockaddr_in client_address;
    int len = sizeof(client_address);

    while (1)
    {
        bzero(buff, sizeof(buff));
        recvfrom(server_fd, buff, sizeof(buff), 0, (struct sockaddr *)&client_address, &len);
        printf("From client: %sTo server:", buff);

        for (int i = 0, j = strlen(buff) - 1; i < j; i++, j--)
        {
            int temp = buff[i];
            buff[i] = buff[j];
            buff[j] = temp;
        }
        sendto(server_fd, buff, sizeof(buff), 0, (struct sockaddr *)&client_address, len);
    }
}

int main()
{
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_address;

    if (server_fd == -1)
    {
        printf("socket creation error");
        exit(0);
    }
    else
        printf("socket creation success");

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        printf("binding error");
        exit(0);
    }
    else
        printf("binding success");

    func(server_fd);
    close(server_fd);
}