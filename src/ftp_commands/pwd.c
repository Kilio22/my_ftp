/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pwd
*/

#include "my_ftp.h"

void pwd(client_t *client,
char **params __attribute__((unused)), char *root_path)
{
    char *to_send = NULL;

    to_send = strdup(&client->cwd[strlen(root_path) - 1]);
    if (strcmp(to_send, "/") != 0) {
        to_send[strlen(to_send) - 1] = '\0';
    }
    dprintf(client->socket.fd, PATHNAME_257, to_send);
    free(to_send);
}