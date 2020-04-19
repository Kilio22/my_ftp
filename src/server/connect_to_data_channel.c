/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** connect_to_data_channel
*/

#include "my_ftp.h"

static int connect_to_data_channel_active(struct client_s *client)
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

static int connect_to_data_channel_passive(struct client_s *client)
{
    struct client_s *new_client = accept_client(&client->data_channel.server,
"", false);

    if (new_client == NULL)
        return -1;
    client->data_channel.fd = new_client->socket.fd;
    free(new_client->cwd);
    free(new_client);
    return 0;
}

int connect_to_data_channel(struct client_s *client)
{
    if (client->data_channel.status == ACTIVE && client->data_channel.fd == 0) {
        return connect_to_data_channel_active(client);
    } else if (client->data_channel.fd == 0 &&
client->data_channel.status == PASSIVE)
        return connect_to_data_channel_passive(client);
    else
        return 0;
}