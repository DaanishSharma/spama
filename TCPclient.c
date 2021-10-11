#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

void func(int client_fd)
{
    char buff[256];
    int n;

    while (1)
    {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(client_fd, buff, sizeof(buff));

        bzero(buff, sizeof(buff));
        read(client_fd, buff, sizeof(buff));
        printf("From Server : %s", buff);

        // if ((strncmp(buff, "exit", 4)) == 0)
        // {
        //     printf("Client Exit...\n");
        //     close(client_fd);
        //     break;
        // }
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
        printf("server creation successful");

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