#include "../include/server.h"

void func_client(int sockfd)
{
    char buff[80];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main(int ac, char **av) {
    int sockfd = create_socket();
    struct sockaddr_in server_address;
    // struct sockaddr_in client_address;

    bzero(&server_address, sizeof(server_address));
    setup_client_socket(atoi(av[2]), &server_address, av[1]);

    if (connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) != 0) {
        perror("Connection to the server failed.\n");
        return 84;
    } else
        printf("Connected to the server.\n");
    func_client(sockfd);
    close(sockfd);
}