#include "./include/server.h"

int func(int connfd, char *buff, size_t buff_size)
{
    // Nettoie le buffer
    bzero(buff, buff_size);

    // Lecture depuis le client
    ssize_t r = read(connfd, buff, buff_size - 1);
    if (r <= 0) {
        // r == 0  → déconnexion propre
        // r < 0   → erreur
        printf("Error on read.\n");
        return -1;
    }

    // On s'assure que buff soit une string
    buff[r] = '\0';
    printf("From client (%d): %s\n", connfd, buff);

    // ------------------------------
    //   RÉPONSE AU CLIENT (écho)
    // ------------------------------
    if (write(connfd, buff, r) <= 0)
        return -1;

    return 0;
}

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