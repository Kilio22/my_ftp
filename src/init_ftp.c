/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** init_ftp
*/

#include "my_ftp.h"

int init_ftp(struct my_ftp_s *my_ftp, char *user_port, char *real_path)
{
    struct socket_s *server = NULL;
    char *given_port = strdup(user_port);
    char *save_ptr = given_port;
    in_port_t port = strtol(given_port, &given_port, 10);

    if (*given_port != '\0' || *save_ptr == '\0')
        return -1;
    free(save_ptr);
    my_ftp->clients = malloc(sizeof(struct client_s *) * (FD_SETSIZE + 1));
    memset(my_ftp->clients, 0, sizeof(struct client_s *) * (FD_SETSIZE + 1));
    server = init_server(port);
    if (server == NULL) {
        free(my_ftp->clients);
        return -1;
    }
    my_ftp->main_server = server;
    my_ftp->root_path = real_path;
    FD_ZERO(&my_ftp->r_set);
    FD_SET(server->fd, &my_ftp->r_set);
    return 0;
}