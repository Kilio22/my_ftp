/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cdup
*/

#include "my_ftp.h"

void cdup(client_t *client, char **params __attribute__((unused)),
char *root_path)
{
    char *new_path = NULL;

    if (strcmp(root_path, client->cwd) == 0) {
        write(client->socket.fd, ACTION_250, strlen(ACTION_250));
        return;
    }
    new_path = concat_paths(client->cwd, "../", true);
    if (new_path == NULL) {
        write(client->socket.fd, ERROR_500, strlen(ERROR_500));
        return;
    }
    free(client->cwd);
    client->cwd = new_path;
    write(client->socket.fd, ACTION_250, strlen(ACTION_250));
}