/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** close_client_data
*/

#include "my_ftp.h"

void close_client_data(struct client_s *client)
{
    close_data_channel(client);
    close(client->socket.fd);
    free(client->password);
    free(client->username);
    free(client->cwd);
    free(client->buffer);
}