/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cd
*/

#include "client.h"

void cd(socket_t *server, socket_t *data_channel __attribute__((unused)),
char **params)
{
    char *answer = NULL;

    if (params[1] == NULL) {
        dprintf(server->fd, "CWD /\r\n");
    } else {
        dprintf(server->fd, "CWD %s\r\n", params[1]);
    }
    answer = read_fd(server->fd);
    if (answer)
        printf(answer);
    free(answer);
}
