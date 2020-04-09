/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** put
*/

#include "client.h"

static int get_fd(char *filepath)
{
    int fd = 0;

    fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        printf("Cannot send given file: couldn't open file.\n");
        return -1;
    }
    return fd;
}

static void send_command(int fd, char *filepath)
{
    char *ptr = strrchr(filepath, '/');

    if (ptr == NULL) {
        dprintf(fd, "STOR %s\r\n", filepath);
    } else {
        dprintf(fd, "STOR %s\r\n", ptr + 1);
    }
}

static int check_command_status(socket_t *server)
{
    char *answer = read_fd(server->fd);

    if (!answer)
        return -1;
    printf(answer);
    if (strstr(answer, "150") == NULL && strstr(answer, "125") == NULL) {
        free(answer);
        return -1;
    }
    free(answer);
    return 0;
}

static void send_file(socket_t *server, socket_t *data_channel, char *filepath)
{
    int fd = get_fd(filepath);
    char *file = NULL;
    char *answer = NULL;

    if (fd == -1)
        return;
    file = read_fd(fd);
    close(fd);
    send_command(server->fd, filepath);
    if (check_command_status(server) == -1)
        return;
    write(data_channel->fd, file, strlen(file));
    close(data_channel->fd);
    data_channel->fd = 0;
    answer = read_fd(server->fd);
    if (answer)
        printf(answer);
    free(answer);
}

void put(socket_t *server, socket_t *data_channel, char **params)
{
    if (params[1] == NULL) {
        printf("You must provide a filepath to use this command.\n");
        return;
    }
    if (check_data_channel(server, data_channel) == false)
        return;
    send_file(server, data_channel, params[1]);
    if (data_channel->fd != 0) {
        close(data_channel->fd);
        data_channel->fd = 0;
    }
    memset(&data_channel->sock_in, 0, sizeof(struct sockaddr_in));
}