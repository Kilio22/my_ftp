/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cwd
*/

#include "my_ftp.h"

static char *handle_path(client_t *client, char *given_path)
{
    char *path = NULL;

    path = concat_paths(client->cwd, given_path, true);
    if (path == NULL || is_dir(path) == false) {
        write(client->socket.fd, ERROR_500, strlen(ERROR_500));
        return NULL;
    }
    return path;
}

void cwd(client_t *client, char **params, char *root_path)
{
    char *new_path = NULL;

    if (params[1][0] == '/')
        new_path = handle_path(client, &params[1][1]);
    else
        new_path = handle_path(client, params[1]);
    if (new_path == NULL)
        return;
    if (strncmp(root_path, new_path, strlen(root_path)) == 0) {
        free(client->cwd);
        client->cwd = new_path;
    }
    write(client->socket.fd, ACTION_250, strlen(ACTION_250));
}