/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pass
*/

#include "my_ftp.h"

int pass(my_ftp_t *my_ftp __attribute__((unused)), client_t *client,
char **params)
{
    if (my_array_len(params) > 2) {
        write(client->socket.fd, SYNTAX_ERROR, strlen(SYNTAX_ERROR));
        return -1;
    }
    if (client->username == NULL) {
        write(client->socket.fd, WRONG_SEQUENCE, strlen(WRONG_SEQUENCE));
        return -1;
    }
    if (client->password != NULL) {
        free(client->password);
        client->password = NULL;
    }
    client->password = strdup(params[1] == NULL ? "" : params[1]);
    if (has_valid_creditentials(client) == true) {
        write(client->socket.fd, LOGIN_230, strlen(LOGIN_230));
        return 0;
    } else {
        write(client->socket.fd, NOT_LOGGED_530, strlen(NOT_LOGGED_530));
        free(client->password);
        client->password = NULL;
        return -1;
    }
}