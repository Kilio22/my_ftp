/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** dele
*/

#include "my_ftp.h"

void dele(struct client_s *client, char **params, char *root_path)
{
    char *full_path = NULL;

    if (params[1][0] == '/') {
        full_path = concat_paths(root_path, &params[1][1], false);
    } else {
        full_path = concat_paths(client->cwd, params[1], false);
    }
    if (full_path == NULL) {
        write(client->socket.fd, ERROR_500, strlen(ERROR_500));
        return;
    }
    if (remove(full_path) == -1)
        write(client->socket.fd, ERROR_500, strlen(ERROR_500));
    else
        write(client->socket.fd, ACTION_250, strlen(ACTION_250));
}