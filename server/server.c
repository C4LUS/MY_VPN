#include "../include/server.h"

void remove_fd_from_poll(poll_t *p, nfds_t index)
{
    if (index >= p->num_open_fds)
        return;
    close(p->pfds[index].fd);
    p->pfds[index] = p->pfds[p->num_open_fds - 1];
    p->num_open_fds--;
    p->nfds = p->num_open_fds;
}

int accept_new_client(server_t *server, poll_t *p, ADDR)
{
    int clientfd = accept(server->sockfd, (struct sockaddr *)address, (socklen_t *)&server->len);
    struct pollfd *tmp = NULL;
    if (clientfd < 0) {
        perror("accept");
        return -1;
    }
    tmp = realloc(p->pfds, sizeof(struct pollfd) * (p->num_open_fds + 1));
    if (!tmp) {
        perror("realloc");
        close(clientfd);
        return -1;
    }
    p->pfds = tmp;
    p->pfds[p->num_open_fds].fd = clientfd;
    p->pfds[p->num_open_fds].events = POLLIN;
    p->num_open_fds++;
    p->nfds = p->num_open_fds;
    write(0, "Client successfuly connected.\n", 30);
    return 0;
}

void handle_client_read(poll_t *p, nfds_t i)
{
    char buf[1024];
    int fd = p->pfds[i].fd;
    ssize_t r = recv(fd, buf, sizeof(buf), 0);

    if (r <= 0) {
        remove_fd_from_poll(p, i);
        dprintf(0, "client: %d disconnected.\n", fd);
        return;
    }
}

void server_loop(server_t *server, poll_t *p, ADDR)
{
    char buff[80];
    int n = 0;
    while (true) {
        p->ready = poll(p->pfds, p->nfds, 1000);
        if (p->ready < 0) {
            perror("poll");
            break;
        }
        if (p->ready == 0)
            continue; 
        if (p->pfds[0].revents & POLLIN) {
            accept_new_client(server, p, address);
            continue;
        }
        for (nfds_t i = 1; i < p->num_open_fds; ++i) {
            if (p->pfds[i].revents & POLLIN)
                // handle_client_read(p, i);
                if (func(p->pfds[i].fd, buff, sizeof(buff)) < 0) {
                    dprintf(0, "client: %d disconnected.\n", p->pfds[i].fd);
                    remove_fd_from_poll(p, i);
                }
        }
    }
}

int run_server(server_t *server, poll_t *p, ADDR)
{
    if (listen(server->sockfd, 10) < 0) {
        perror("listen");
        return -1;
    }
    p->pfds = calloc(1, sizeof(struct pollfd));
    if (!p->pfds)
        return -1;

    p->pfds[0].fd = server->sockfd;
    p->pfds[0].events = POLLIN;
    p->num_open_fds = 1;
    p->nfds = 1;

    server_loop(server, p, address);
    return 0;
}
