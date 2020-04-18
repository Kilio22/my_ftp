/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** user
*/

#include "my_ftp.h"

void user(struct client_s *client,
char **params, char *root_path __attribute__((unused)))
{
    if (client->is_connected == true) {
        write(client->socket.fd, WRONG_SEQUENCE, strlen(WRONG_SEQUENCE));
        return;
    }
    if (client->username != NULL) {
        free(client->username);
        client->username = NULL;
    }
    if (params[1] == NULL) {
        write(client->socket.fd, NOT_LOGGED_530, strlen(NOT_LOGGED_530));
        return;
    }
    client->username = strdup(params[1]);
    write(client->socket.fd, LOGIN_331, strlen(LOGIN_331));
}