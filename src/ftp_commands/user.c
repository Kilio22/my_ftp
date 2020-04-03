/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** user
*/

#include "my_ftp.h"

int user(my_ftp_t *my_ftp __attribute__((unused)), client_t *client,
char **params)
{
    if (client->username != NULL && client->password != NULL) {
        write(client->socket.fd, WRONG_SEQUENCE, strlen(WRONG_SEQUENCE));
        return -1;
    }
    if (client->username != NULL) {
        free(client->username);
        client->username = NULL;
    }
    client->username = strdup(params[1]);
    write(client->socket.fd, LOGIN_331, strlen(LOGIN_331));
    return 0;
}