/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** manage_server
*/

#include "my_ftp.h"

int manage_server(my_ftp_t *my_ftp)
{
    client_t *client = accept_client(my_ftp->main_server);

    if (client == NULL) {
        return -1;
    }
    if (my_ftp->current_idx < FD_SETSIZE) {
        my_ftp->clients[my_ftp->current_idx++] = client;
    } else {
        close(client->fd);
        free(client);
    }
    return 0;
}