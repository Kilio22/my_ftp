/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** ls
*/

#include "client.h"

static int check_command_status(socket_t *server)
{
    char *answer = read_fd(server->fd);

    if (!answer)
        return -1;
    printf(answer);
    if (strstr(answer, "150") == NULL && strstr(answer, "125") == NULL)
        return -1;
    free(answer);
    answer = read_fd(server->fd);
    if (!answer)
        return -1;
    printf(answer);
    if (strstr(answer, "226") == NULL && strstr(answer, "250") == NULL)
        return -1;
    free(answer);
    return 0;
}

static void get_infos(socket_t *server, socket_t *data_channel)
{
    char *answer = NULL;

    if (check_command_status(server) == -1)
        return;
    answer = read_fd(data_channel->fd);
    if (!answer)
        return;
    printf(answer);
    free(answer);
}

void ls(socket_t *server, socket_t *data_channel, char **params)
{
    if (check_data_channel(server, data_channel) == false)
        return;
    if (params[1] == NULL)
        dprintf(server->fd, "LIST\r\n");
    else
        dprintf(server->fd, "LIST %s\r\n", params[1]);
    get_infos(server, data_channel);
    close(data_channel->fd);
    data_channel->fd = 0;
    memset(&data_channel->sock_in, 0, sizeof(struct sockaddr_in));
}
