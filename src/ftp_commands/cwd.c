/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cwd
*/

#include "my_ftp.h"

static char *handle_path(struct client_s *client,
char *given_path, char *root_path)
{
    char *path = NULL;

    if (given_path[0] == '/')
        path = concat_paths(root_path, &given_path[1], true);
    else
        path = concat_paths(client->cwd, given_path, true);
    if (path == NULL || is_dir(path) == false) {
        write(client->socket.fd, ERROR_500, strlen(ERROR_500));
        return NULL;
    }
    return path;
}

void cwd(struct client_s *client, char **params, char *root_path)
{
    char *new_path = NULL;

    new_path = handle_path(client, params[1], root_path);
    if (new_path == NULL)
        return;
    if (strncmp(root_path, new_path, strlen(root_path)) == 0) {
        free(client->cwd);
        client->cwd = new_path;
    } else {
        client->cwd = strdup(root_path);
    }
    write(client->socket.fd, ACTION_250, strlen(ACTION_250));
}