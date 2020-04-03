/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** data_channel_utils
*/

#include "my_ftp.h"

void close_data_channel(client_t *client)
{
    if (client->data_channel.status == NONE) {
        return;
    }
    if (client->data_channel.fd != 0) {
        close(client->data_channel.fd);
    }
    if (client->data_channel.status == PASSIVE) {
        if (client->data_channel.server.fd != 0)
            close(client->data_channel.server.fd);
    }
    memset(&client->data_channel, 0, sizeof(data_channel_t));
}

int connect_to_data_channel_active(client_t *client)
{
    int fd = create_socket();

    if (fd == -1)
        return -1;
    if (connect(fd, (struct sockaddr *)&client->data_channel.server.sock_in,
sizeof(struct sockaddr_in)) == -1)
        return -1;
    client->data_channel.fd = fd;
    return 0;
}

int connect_to_data_channel_passive(client_t *client)
{
    client_t *new_client = accept_client(&client->data_channel.server);

    if (new_client == NULL)
        return -1;
    client->data_channel.fd = new_client->socket.fd;
    free(new_client);
    return 0;
}

int connect_to_data_channel(client_t *client)
{
    if (client->data_channel.status == ACTIVE && client->data_channel.fd == 0) {
        return connect_to_data_channel_active(client);
    } else if (client->data_channel.fd == 0 &&
client->data_channel.status == PASSIVE)
        return connect_to_data_channel_passive(client);
    else
        return 0;
}

bool is_data_channel_open(data_channel_t *data_channel, int fd)
{
    if (data_channel->status == NONE) {
        write(fd, CANNOT_OPEN_DATA_CHAN,
strlen(CANNOT_OPEN_DATA_CHAN));
        return false;
    }
    return true;
}