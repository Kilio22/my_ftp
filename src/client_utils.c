/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** client_utils
*/

#include "my_ftp.h"

static const char default_user[] = "Anonymous";
static const char default_password[] = "";

bool is_connected(client_t *client)
{
    if (client->is_connected == false) {
        write(client->socket.fd, NOT_LOGGED_530, strlen(NOT_LOGGED_530));
        return false;
    }
    return true;
}

bool has_valid_creditentials(client_t *client, bool should_send_msg)
{
    if (client->password == NULL || client->username == NULL) {
        if (should_send_msg == true)
            write(client->socket.fd, NOT_LOGGED_530, strlen(NOT_LOGGED_530));
        return false;
    }
    if (!strcmp(client->username, default_user) &&
!strcmp(client->password, default_password))
        return true;
    if (should_send_msg == true)
        write(client->socket.fd, NOT_LOGGED_530, strlen(NOT_LOGGED_530));
    return false;
}

void close_client_data(client_t *client)
{
    close_data_channel(client);
    close(client->socket.fd);
    free(client->password);
    free(client->username);
    free(client->cwd);
    free(client->buffer);
}

void remove_client(client_t *client)
{
    my_ftp_t *my_ftp = get_ftp(NULL);
    size_t len = get_clients_nb(my_ftp->clients);
    size_t i = 0;

    close_client_data(client);
    for (; i < len; i++) {
        if (my_ftp->clients[i] == client) {
            free(my_ftp->clients[i]);
            my_ftp->clients[i] = NULL;
            break;
        }
    }
    if (i == len)
        return;
    for (; i < len; i++) {
        my_ftp->clients[i] = my_ftp->clients[i + 1];
        my_ftp->clients[i + 1] = NULL;
    }
}