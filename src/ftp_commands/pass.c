/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pass
*/

#include "my_ftp.h"

void pass(my_ftp_t *my_ftp __attribute__((unused)), client_t *client,
char **params)
{
    if (my_array_len(params) > 2) {
        write(client->socket.fd, SYNTAX_ERROR, strlen(SYNTAX_ERROR));
        return;
    }
    if (client->username == NULL) {
        write(client->socket.fd, WRONG_SEQUENCE, strlen(WRONG_SEQUENCE));
        return;
    }
    if (client->password != NULL) {
        free(client->password);
        client->password = NULL;
    }
    client->password = strdup(params[1] == NULL ? "" : params[1]);
    if (has_valid_creditentials(client, true) == true) {
        write(client->socket.fd, LOGIN_230, strlen(LOGIN_230));
        return;
    } else {
        free(client->password);
        client->password = NULL;
    }
}