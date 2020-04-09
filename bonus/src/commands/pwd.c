/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pwd
*/

#include "client.h"

void pwd(socket_t *server, socket_t *data_channel __attribute__((unused)),
char **params __attribute__((unused)))
{
    char *answer = NULL;

    dprintf(server->fd, "PWD\r\n");
    answer = read_fd(server->fd);
    if (answer)
        printf(answer);
    free(answer);
}