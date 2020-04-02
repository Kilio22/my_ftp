/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** accept
*/

#include "my_ftp.h"

client_t *accept_client(socket_t *main_server)
{
    struct sockaddr_in sock_client = {0};
    socklen_t sockaddr_client_size = sizeof(sock_client);
    int client_fd = accept(main_server->fd, (struct sockaddr *)&sock_client,
&sockaddr_client_size);
    client_t *client = malloc(sizeof(client_t));

    memset(client, 0, sizeof(client_t));
    if (client_fd == -1) {
        fprintf(stderr, "Accept failed.\n");
        return NULL;
    }
    if (write(client_fd, SERVICE_220, strlen(SERVICE_220)) == -1) {
        fprintf(stderr, "Write failed.\n");
        return NULL;
    }
    client->socket.fd = client_fd;
    return client;
}