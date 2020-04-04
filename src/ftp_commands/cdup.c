/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cdup
*/

#include "my_ftp.h"

void cdup(my_ftp_t *my_ftp, client_t *client,
char **params __attribute__((unused)))
{
    char *new_path = NULL;

    if (client->is_connected == false)
        return;
    new_path = concat_paths(client->cwd, "../", true);
    if (new_path == NULL) {
        write(client->socket.fd, FILE_NOT_FOUND, strlen(FILE_NOT_FOUND));
        return;
    }
    if (strncmp(my_ftp->root_path, new_path, strlen(my_ftp->root_path)) != 0) {
        write(client->socket.fd, FILE_NOT_FOUND, strlen(FILE_NOT_FOUND));
        free(new_path);
        return;
    }
    free(client->cwd);
    client->cwd = new_path;
}