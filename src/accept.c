/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** accept
*/

#include "my_ftp.h"

static void init_client_values(client_t *client)
{
    client->is_triggered = false;
    client->buffer = NULL;
    client->is_connected = false;
    client->password = NULL;
    client->username = NULL;
}

client_t *accept_client(server_t *main_server)
{
    struct sockaddr_in sock_client = {0};
    socklen_t sockaddr_client_size = sizeof(sock_client);
    int client_fd = accept(main_server->fd, (struct sockaddr *)&sock_client,
&sockaddr_client_size);
    client_t *client = malloc(sizeof(client_t));

    if (client_fd == -1) {
        fprintf(stderr, "Accept failed.\n");
        return NULL;
    }
    if (write(client_fd, CMD_200, strlen(CMD_200)) == -1) {
        fprintf(stderr, "Write failed.\n");
        return NULL;
    }
    client->fd = client_fd;
    init_client_values(client);
    return client;
}