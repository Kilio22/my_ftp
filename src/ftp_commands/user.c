/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** user
*/

#include "my_ftp.h"

void user(my_ftp_t *my_ftp __attribute__((unused)), client_t *client,
char **params)
{
    if (client->is_connected == true) {
        write(client->socket.fd, WRONG_SEQUENCE, strlen(WRONG_SEQUENCE));
        return;
    }
    if (client->username != NULL) {
        free(client->username);
        client->username = NULL;
    }
    client->username = strdup(params[1]);
    write(client->socket.fd, LOGIN_331, strlen(LOGIN_331));
}