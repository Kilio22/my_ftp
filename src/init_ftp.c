/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** init_ftp
*/

#include "my_ftp.h"

int init_ftp(my_ftp_t *my_ftp, char **av)
{
    socket_t *server = NULL;
    char *given_port = strdup(av[1]);
    in_port_t port = strtol(given_port, &given_port, 10);

    if (*given_port != '\0')
        return -1;
    my_ftp->clients = malloc(sizeof(client_t *) * (FD_SETSIZE + 1));
    if (my_ftp->clients == NULL)
        return -1;
    memset(my_ftp->clients, 0, sizeof(client_t *) * (FD_SETSIZE + 1));
    my_ftp->current_idx = 0;
    server = init_server(port);
    if (server == NULL) {
        free(my_ftp->clients);
        return -1;
    }
    my_ftp->main_server = server;
    my_ftp->root_path = strdup(av[2]);
    FD_ZERO(&my_ftp->r_set);
    FD_SET(server->fd, &my_ftp->r_set);
    return 0;
}