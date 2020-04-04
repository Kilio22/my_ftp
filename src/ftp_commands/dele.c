/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** dele
*/

#include "my_ftp.h"

void dele(my_ftp_t *my_ftp __attribute__((unused)), client_t *client,
char **params)
{
    char *full_path = NULL;

    if (has_valid_creditentials(client, true) == false)
        return;
    if (params[1][0] == '/') {
        full_path = concat_paths(client->cwd, &params[1][1], false);
    } else {
        full_path = concat_paths(client->cwd, params[1], false);
    }
    if (full_path == NULL) {
        write(client->socket.fd, FILE_NOT_FOUND, strlen(FILE_NOT_FOUND));
    }
    if (remove(full_path) == -1) {
        write(client->socket.fd, FILE_NOT_FOUND, strlen(FILE_NOT_FOUND));
    } else {
        write(client->socket.fd, ACTION_250, strlen(ACTION_250));
    }
}