#include "../include/server.h"

server_t *init_server_struct(void)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL)
        return NULL;
    server->client_fd = 0;
    server->sockfd = 0;
    server->len = 0;
    server->port = 0;
    return server;
}

poll_t *init_poll_struct(void)
{
    poll_t *poll = malloc(sizeof(poll_t));

    if (poll == NULL)
        return NULL;
    
    poll->pfds = memset(poll, 0, sizeof(poll->pfds));
    poll->nfds = 1;
    poll->num_open_fds = 1;
    poll->ready = 0;
    return poll;
}
