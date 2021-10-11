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



    server_address.sin_family = AF_INET;         

    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    server_address.sin_port = htons(8080);



    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)

    {

        printf("connection failed");

        exit(0);

    }



    func(client_fd);

    close(client_fd);

}
