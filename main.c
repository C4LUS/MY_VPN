#include "./include/server.h"

int main(int ac, char **av)
{
    (void)ac;

    server_t *server = init_server_struct();
    poll_t *poll_s = init_poll_struct();
    struct sockaddr_in address;

    server->sockfd = create_socket();
    setup_socket(server->sockfd, &server->len, atoi(av[1]), &address);
    run_server(server, poll_s, &address);
    return 0;
}