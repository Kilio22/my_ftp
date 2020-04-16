/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** retr
*/

#include "my_ftp.h"

static void send_file(client_t *client, int fd)
{
    char buffer[READ_SIZE + 1] = {'\0'};
    ssize_t nread = 0;

    while ((nread = read(fd, buffer, READ_SIZE)) > 0) {
        if (write(client->data_channel.fd, buffer, nread) == -1) {
            write(client->socket.fd, TRANSFER_ABORT, strlen(TRANSFER_ABORT));
            return;
        }
        memset(&buffer, '\0', READ_SIZE);
    }
    write(client->socket.fd, DATA_226, strlen(DATA_226));
}

static void handle_file_sending(client_t *client, int fd)
{
    pid_t pid;

    if (connect_to_data_channel(client) == -1) {
        write(client->socket.fd, DATA_425, strlen(DATA_425));
        return;
    }
    pid = fork();
    if (pid == -1) {
        write(client->socket.fd, DATA_425, strlen(DATA_425));
    } else if (pid == 0) {
        write(client->socket.fd, DATA_150, strlen(DATA_150));
        send_file(client, fd);
        close(fd);
        destroy_server();
        exit(0);
    }
}

static int get_file_fd(client_t *client, char *path, char *root_path)
{
    char *filepath = NULL;
    int fd = 0;

    if (path == NULL) {
        write(client->socket.fd, ERROR_500, strlen(ERROR_500));
        return -1;
    }
    if (path[0] == '/')
        filepath = concat_paths(root_path, &path[1], false);
    else
        filepath = concat_paths(client->cwd, path, false);
    if (filepath == NULL) {
        write(client->socket.fd, ERROR_500, strlen(ERROR_500));
        return -1;
    }
    fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        write(client->socket.fd, ERROR_500, strlen(ERROR_500));
        return -1;
    }
    return fd;
}

void retr(client_t *client, char **params, char *root_path)
{
    int fd = 0;

    if (is_data_channel_open(&client->data_channel, client->socket.fd) == false)
        return;
    fd = get_file_fd(client, params[1], root_path);
    if (fd == -1)
        return;
    handle_file_sending(client, fd);
    close(fd);
    close_data_channel(client);
}