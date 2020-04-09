/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** passive
*/

#include "client.h"

static void go_in_passive_mode(socket_t *data_channel, int infos[6])
{
    char ip_addr[14] = {'\0'};

    sprintf(ip_addr, "%d.%d.%d.%d", infos[0], infos[1], infos[2], infos[3]);
    if (inet_aton(ip_addr,
(struct in_addr *)&data_channel->sock_in.sin_addr) == 0) {
        printf("Invalid address\n");
        return;
    }
    data_channel->sock_in.sin_family = AF_INET;
    data_channel->sock_in.sin_port = htons((infos[4] * 256) + infos[5]);
    data_channel->fd = create_socket();
    if (data_channel->fd == -1) {
        data_channel->fd = 0;
        memset(&data_channel->sock_in, 0, sizeof(struct sockaddr_in));
        return;
    }
    if (connect(data_channel->fd, (struct sockaddr *)&data_channel->sock_in,
sizeof(struct sockaddr_in)) == -1) {
        data_channel->fd = 0;
        memset(&data_channel->sock_in, 0, sizeof(struct sockaddr_in));
        return;
    }
    printf("Passive mode activated!\n");
}

void passive(socket_t *server, socket_t *data_channel,
char **params __attribute__((unused)))
{
    int infos[6] = {0};
    char *answer = NULL;
    char *ptr = NULL;

    dprintf(server->fd, "PASV\r\n");
    answer = read_fd(server->fd);
    if (!answer)
        return;
    printf(answer);
    if (strstr(answer, "227") == NULL)
        return;
    ptr = strchr(answer, ')');
    *ptr = '\0';
    ptr = strchr(answer, '(');
    ptr++;
    if (data_channel->fd != 0)
        close(data_channel->fd);
    sscanf(ptr, "%d,%d,%d,%d,%d,%d", &infos[0], &infos[1],
&infos[2], &infos[3], &infos[4], &infos[5]);
    go_in_passive_mode(data_channel, infos);
}