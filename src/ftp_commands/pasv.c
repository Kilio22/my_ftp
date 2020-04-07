/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pasv
*/

#include "my_ftp.h"

static void init_data_channel(client_t *client, int server_socket)
{
    char *ip_address = inet_ntoa(client->data_channel.server.sock_in.sin_addr);
    int ip_numbers[4] = {0};
    int port = 0;

    sscanf(ip_address, "%d.%d.%d.%d", &ip_numbers[0], &ip_numbers[1],
&ip_numbers[2], &ip_numbers[3]);
    port = ntohs(client->data_channel.server.sock_in.sin_port);
    dprintf(client->socket.fd, PASSIVE_227, ip_numbers[0],
ip_numbers[1], ip_numbers[2], ip_numbers[3], port / 256, port % 256);
    client->data_channel.status = PASSIVE;
    client->data_channel.server.fd = server_socket;
}

void pasv(my_ftp_t *my_ftp __attribute__((unused)), client_t *client,
char **params __attribute__((unused)))
{
    int server_socket = 0;
    socklen_t size = sizeof(struct sockaddr_in);

    if (is_connected(client) == false)
        return;
    close_data_channel(client);
    server_socket = create_server(0);
    if (server_socket == -1) {
        write(client->socket.fd, CANNOT_OPEN_DATA_CHAN,
strlen(CANNOT_OPEN_DATA_CHAN));
        return;
    }
    getsockname(server_socket,
(struct sockaddr *)&client->data_channel.server.sock_in, &size);
    init_data_channel(client, server_socket);
    return;
}