#include <stdio.h>

#include <stdlib.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <string.h>

#include <unistd.h>



void func(int sockfd)

{

    char buff[256];



    while (1)

    {

        bzero(buff, sizeof(buff));

        read(sockfd, buff, sizeof(buff));

        printf("From client: %sTo client : ",buff);





        int ch[1024];

        for(int i=0;i<1024;i++){

           ch[i]=0;

        }

        

        for(int i=0;buff[i]!='\0' && buff[i]!='\n' && i<256;i++){

           ch[buff[i]-'a']++;

        }

        int maxi=0,res=0;

        

        for(int i=0;i<1024;i++){

           if(ch[i]>maxi){

             maxi=ch[i];

             res=i;

           }

        }

        printf("%d",res);

        bzero(buff, sizeof(buff));

        buff[0]='a'+res;

        

        printf("%s", buff);

        write(sockfd, buff, sizeof(buff));

    }

}



int main()

{

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    pid_t pid;

    if (server_fd == -1)

    {

        printf("error creating server");

        exit(0);

    }

    else

        printf("server creation successful\n");



    struct sockaddr_in server_address;



    server_address.sin_family = AF_INET;       

    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    server_address.sin_port = htons(8080);



    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)

    {

        printf("binding failed");

        exit(0);

    }



    if (listen(server_fd, 5) < 0)

    {

        printf("listen failed");

        exit(0);

    }

    

    int client_fd = accept(server_fd, NULL, NULL);

    if (client_fd < 0)

    {

      printf("server acccept failed...\n");

      exit(0);

    }

    else

      func(client_fd);

    

    close(server_fd);

}
