#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

void func(int sockfd)
{
    char buff[256];
    int n;

    while (1)
    {
        bzero(buff, sizeof(buff));
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));

        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
    }
}

int main()
{
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (client_fd == -1)
    {
        printf("error creating server");
        exit(0);
    }
    else
        printf("creation successful\n");

    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;         //domain
    server_address.sin_addr.s_addr = INADDR_ANY; //address
    server_address.sin_port = htons(9001);       //port

    // int connect(int sockfd, const struct sockaddr *addr, socklen_t
    // addrlen);
    // The connect() system call connects the socket referred to by
    // the file descriptor sockfd to the address specified by addr.
    // Server’s address and port is specified in addr.

    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("connection failed");
        exit(0);
    }

    func(client_fd);
    close(client_fd);
}