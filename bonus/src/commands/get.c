/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** get
*/

#include "client.h"

static int get_fd(char *filename)
{
    int fd = 0;
    char *ptr = NULL;

    ptr = strrchr(filename, '/');
    if (ptr == NULL) {
        fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    } else {
        fd = open(ptr + 1, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    }
    if (fd == -1) {
        printf("Unable to open new file, printing file on stdout.\n");
        return 1;
    }
    return fd;
}

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
    if (strstr(answer, "226") == NULL && strstr(answer, "250") == NULL)
        return -1;
    printf(answer);
    free(answer);
    return 0;
}

static void write_to_file(socket_t *server, socket_t *data_channel,
char *filename)
{
    char *answer = NULL;
    int fd = get_fd(filename);

    if (check_command_status(server) == -1)
        return;
    answer = read_fd(data_channel->fd);
    if (!answer) {
        if (fd != 1)
            close(fd);
        return;
    }
    write(fd, answer, strlen(answer));
    if (fd != 1)
        close(fd);
    free(answer);
}

void get(socket_t *server, socket_t *data_channel, char **params)
{
    if (params[1] == NULL) {
        printf("You must provide a filepath to use this command.\n");
        return;
    }
    if (check_data_channel(server, data_channel) == false)
        return;
    dprintf(server->fd, "RETR %s\r\n", params[1]);
    write_to_file(server, data_channel, params[1]);
    close(data_channel->fd);
    data_channel->fd = 0;
    memset(&data_channel->sock_in, 0, sizeof(struct sockaddr_in));
}