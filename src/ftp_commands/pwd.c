/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pwd
*/

#include "my_ftp.h"

void pwd(my_ftp_t *my_ftp, client_t *client,
char **params __attribute__((unused)))
{
    char *to_send = NULL;

    if (is_connected(client) == false)
        return;
    to_send = strdup(&client->cwd[strlen(my_ftp->root_path) - 1]);
    to_send = realloc(to_send, strlen(to_send) + 3);
    if (strcmp(to_send, "/") == 0) {
        to_send[strlen(to_send) + 2] = '\0';
        to_send[strlen(to_send) + 1] = '\n';
        to_send[strlen(to_send)] = '\r';
    } else {
        to_send[strlen(to_send) + 1] = '\0';
        to_send[strlen(to_send) - 1] = '\r';
        to_send[strlen(to_send)] = '\n';
    }
    write(client->socket.fd, to_send, strlen(to_send));
    free(to_send);
}