/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server_loop
*/

#include "my_ftp.h"

void manage_other_servers(client_t *client)
{
    client_t *new_client = accept_client(&client->data_channel.server);

    if (new_client == NULL) {
        return;
    }
    client->data_channel.fd = new_client->socket.fd;
    free(new_client);
}

static void manage_fds(my_ftp_t *my_ftp)
{
    size_t max_idx = my_ftp->current_idx;

    if (my_ftp->main_server->is_triggered == true) {
        manage_server(my_ftp);
    }
    for (size_t i = 0; i < max_idx; i++) {
        if (my_ftp->clients[i] != NULL &&
my_ftp->clients[i]->socket.is_triggered == true)
            manage_client(my_ftp, my_ftp->clients[i]);
        else if (my_ftp->clients[i]->data_channel.server.is_triggered == true)
            manage_other_servers(my_ftp->clients[i]);
    }
}

int server_loop(my_ftp_t *my_ftp)
{
    while (42) {
        if (poll_sockets(my_ftp) == -1)
            return -1;
        manage_fds(my_ftp);
    }
    return 0;
}