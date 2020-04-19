/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** close_data_channel
*/

#include "my_ftp.h"

void close_data_channel(struct client_s *client)
{
    if (client->data_channel.status != NONE) {
        if (client->data_channel.fd != 0)
            close(client->data_channel.fd);
        if (client->data_channel.status == PASSIVE
&& client->data_channel.server.fd) {
                close(client->data_channel.server.fd);
        }
    }
    memset(&client->data_channel, 0, sizeof(struct data_channel_s));
}