#include "../include/server.h"

int create_socket(void) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("Error while creating socket.\n");
        close(sockfd);
        return -1;
    }
    return sockfd;
}

int setup_socket(int sockfd, int *len, int port, ADDR)
{
    *len = sizeof((*address));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    address->sin_family = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr*)address, (socklen_t)*len) < 0) {
        perror("Error while bind.\n");
        close(sockfd);
        return -1;
    }
    return 0;
}