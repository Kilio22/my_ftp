/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** port
*/

#include "my_ftp.h"

static size_t count_char(char *str, char c)
{
    size_t occur = 0;

    for (size_t i = 0; str[i]; i++) {
        if (str[i] == c)
            occur++;
    }
    return occur;
}

static void init_data_channel(struct client_s *client, int infos[6])
{
    char ip_address[16] = {0};

    sprintf(ip_address, "%d.%d.%d.%d", infos[0], infos[1], infos[2], infos[3]);
    if (inet_aton(ip_address,
&client->data_channel.server.sock_in.sin_addr) == 0) {
        write(client->socket.fd, SYNTAX_ERROR, strlen(SYNTAX_ERROR));
        return;
    }
    client->data_channel.server.sock_in.sin_family = AF_INET;
    client->data_channel.server.sock_in.sin_port =
htons((infos[4] * 256) + infos[5]);
    dprintf(client->socket.fd, CMD_200, "PORT");
    client->data_channel.status = ACTIVE;
}

void port(struct client_s *client,
char **params, char *root_path __attribute__((unused)))
{
    int infos[6] = {-1};

    close_data_channel(client);
    if (count_char(params[1], ',') != 5) {
        write(client->socket.fd, SYNTAX_ERROR, strlen(SYNTAX_ERROR));
        return;
    }
    if (sscanf(params[1], "%d,%d,%d,%d,%d,%d", &infos[0], &infos[1], &infos[2],
&infos[3], &infos[4], &infos[5]) == EOF) {
        write(client->socket.fd, SYNTAX_ERROR, strlen(SYNTAX_ERROR));
        return;
    }
    for (size_t i = 0; i < 6; i++) {
        if (infos[i] == -1) {
            write(client->socket.fd, SYNTAX_ERROR, strlen(SYNTAX_ERROR));
            return;
        }
    }
    return init_data_channel(client, infos);
}