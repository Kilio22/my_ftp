/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** manage_server
*/

#include "my_ftp.h"

void manage_other_servers(client_t *client)
{
    client_t *new_client = accept_client(&client->data_channel.server,
"", false);

    if (new_client == NULL) {
        return;
    }
    client->data_channel.fd = new_client->socket.fd;
    free(new_client);
}

int manage_main_server(my_ftp_t *my_ftp)
{
    client_t *client = accept_client(my_ftp->main_server,
my_ftp->root_path, true);
    size_t nb_clients = get_clients_nb(my_ftp->clients);

    printf("%ld\n", nb_clients);
    if (client == NULL)
        return -1;
    if (nb_clients < FD_SETSIZE) {
        my_ftp->clients[nb_clients] = client;
    } else {
        close(client->socket.fd);
        free(client->cwd);
        free(client);
    }
    return 0;
}