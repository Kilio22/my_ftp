/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cwd
*/

#include "my_ftp.h"

static char *handle_absolute_path(client_t *client, char *given_path)
{
    struct stat st = {0};
    char *new_path = NULL;

    if (stat(given_path, &st) == -1 || S_ISDIR(st.st_mode) == false) {
        write(client->socket.fd, FILE_NOT_FOUND, strlen(FILE_NOT_FOUND));
        return NULL;
    }
    new_path = strdup(given_path);
    if (new_path[strlen(new_path) - 1] != '/') {
        new_path = realloc(new_path, strlen(new_path) + 2);
        new_path[strlen(new_path) + 1] = '\0';
        new_path[strlen(new_path)] = '/';
    }
    return new_path;
}

static char *handle_relative_path(client_t *client, char *given_path)
{
    struct stat st = {0};
    char *path = NULL;

    path = concat_paths(client->cwd, given_path, true);
    if (path == NULL || stat(path, &st) == -1 || S_ISDIR(st.st_mode) == false) {
        write(client->socket.fd, FILE_NOT_FOUND, strlen(FILE_NOT_FOUND));
        return NULL;
    }
    return path;
}

void cwd(my_ftp_t *my_ftp, client_t *client, char **params)
{
    char *new_path = NULL;

    if (has_valid_creditentials(client, true) == false)
        return;
    if (params[1][0] == '/') {
        new_path = handle_absolute_path(client, params[1]);
    } else {
        new_path = handle_relative_path(client, params[1]);
    }
    if (new_path == NULL)
        return;
    if (strncmp(my_ftp->root_path, new_path, strlen(my_ftp->root_path)) != 0) {
        write(client->socket.fd, FILE_NOT_FOUND, strlen(FILE_NOT_FOUND));
        return;
    }
    free(client->cwd);
    client->cwd = new_path;
    write(client->socket.fd, ACTION_250, strlen(ACTION_250));
}