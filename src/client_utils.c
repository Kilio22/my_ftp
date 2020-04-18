/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** client_utils
*/

#include "my_ftp.h"

bool is_connected(struct client_s *client)
{
    if (client->is_connected == false) {
        write(client->socket.fd, NOT_LOGGED_530, strlen(NOT_LOGGED_530));
        return false;
    }
    return true;
}

void close_client_data(struct client_s *client)
{
    close_data_channel(client);
    close(client->socket.fd);
    free(client->password);
    free(client->username);
    free(client->cwd);
    free(client->buffer);
}

void remove_client(struct client_s *client)
{
    struct my_ftp_s *my_ftp = get_ftp(NULL);
    ssize_t len = my_tab_len(my_ftp->clients);
    ssize_t i = 0;

    close_client_data(client);
    for (; i < len; i++) {
        if (my_ftp->clients[i] == client) {
            free(my_ftp->clients[i]);
            my_ftp->clients[i] = NULL;
            break;
        }
    }
    for (; i < len; i++) {
        my_ftp->clients[i] = my_ftp->clients[i + 1];
        my_ftp->clients[i + 1] = NULL;
    }
}