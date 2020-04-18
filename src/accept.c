/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** accept
*/

#include "my_ftp.h"

struct client_s *accept_client(struct socket_s *main_server, char *root_path,
bool should_write)
{
    struct sockaddr_in sock_client = {0};
    socklen_t sockaddr_client_size = sizeof(sock_client);
    int client_fd = accept(main_server->fd, (struct sockaddr *)&sock_client,
&sockaddr_client_size);
    struct client_s *client = malloc(sizeof(struct client_s));

    memset(client, 0, sizeof(struct client_s));
    if (client_fd == -1) {
        fprintf(stderr, "Accept failed.\n");
        return NULL;
    }
    if (should_write == true
&& write(client_fd, SERVICE_220, strlen(SERVICE_220)) == -1) {
        fprintf(stderr, "Write failed.\n");
        return NULL;
    }
    client->socket.fd = client_fd;
    client->cwd = strdup(root_path);
    return client;
}