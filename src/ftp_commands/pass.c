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
    if (check_params_len(params, client->socket.fd, 2) == false)
        return;
    if (client->username == NULL || client->is_connected == true) {
        write(client->socket.fd, WRONG_SEQUENCE, strlen(WRONG_SEQUENCE));
        return;
    }
    client->password = strdup(params[1] == NULL ? "" : params[1]);
    if (has_valid_creditentials(client, true) == true) {
        write(client->socket.fd, LOGIN_230, strlen(LOGIN_230));
        client->is_connected = true;
        return;
    } else {
        free(client->password);
        client->password = NULL;
    }
}