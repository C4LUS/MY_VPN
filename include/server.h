#ifndef SERVER_H
    #define SERVER_H
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <string.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <poll.h>
    #include <sys/wait.h>
    #define ADDR struct sockaddr_in *address

typedef struct {
    int sockfd;
    int port;
    int len;
    int client_fd;
} server_t;

typedef struct {
    int clien_fd;

} clien_t;

typedef struct {
    struct pollfd *pfds;
    nfds_t nfds;
    nfds_t num_open_fds;
    int ready;

} poll_t;
int accept_new_client(server_t *server, poll_t *p, ADDR);
int setup_socket(int sockfd, int *len, int port, ADDR);
void server_loop(server_t *server, poll_t *p, ADDR);
int run_server(server_t *server, poll_t *p, ADDR);
void remove_fd_from_poll(poll_t *p, nfds_t index);
void handle_client_read(poll_t *p, nfds_t i);
server_t *init_server_struct(void);
poll_t *init_poll_struct(void);
int create_socket(void);

#endif  