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

static void close_client_data(client_t *client)
{
    if (client->data_channel.status != NONE) {
        if (client->data_channel.fd != 0)
            close(client->data_channel.fd);
        if (client->data_channel.status == PASSIVE &&
client->data_channel.server.fd != 0) {
            close(client->data_channel.server.fd);
        }
    }
    close(client->socket.fd);
    free(client->password);
    free(client->username);
    free(client->cwd);
}

void remove_client(my_ftp_t *my_ftp, client_t *client)
{
    size_t i = 0;

    close_client_data(client);
    for (; i < my_ftp->current_idx; i++) {
        if (my_ftp->clients[i] == client) {
            free(my_ftp->clients[i]);
            my_ftp->clients[i] = NULL;
            break;
        }
    }
    if (i == my_ftp->current_idx)
        return;
    for (; i < my_ftp->current_idx; i++) {
        my_ftp->clients[i] = my_ftp->clients[i + 1];
        my_ftp->clients[i + 1] = NULL;
    }
    my_ftp->current_idx--;
}