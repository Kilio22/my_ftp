/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** stor
*/

#include "my_ftp.h"

static void get_file(client_t *client, int fd)
{
    ssize_t nread = 0;
    char buffer[READ_SIZE + 1] = {'\0'};

    while ((nread = read(client->data_channel.fd, buffer, READ_SIZE)) > 0) {
        write(fd, buffer, nread);
        memset(buffer, '\0', READ_SIZE);
    }
    write(client->socket.fd, DATA_226, strlen(DATA_226));
}

static void handle_child(client_t *client, int fd)
{
    write(client->socket.fd, DATA_150, strlen(DATA_150));
    if (connect_to_data_channel(client) == -1) {
        write(client->socket.fd,
CANNOT_OPEN_DATA_CHAN, strlen(CANNOT_OPEN_DATA_CHAN));
        exit(0);
    }
    get_file(client, fd);
    close(fd);
    close_data_channel(client);
    exit(0);
}

static char *get_filepath(client_t *client, char *path)
{
    char *filepath = NULL;

    if (path[0] == '/') {
        filepath = concat_strings(client->cwd, &path[1]);
    } else {
        filepath = path;
        while (strncmp(filepath, "./", 2) == 0) {
            filepath = filepath + 2;
        }
        filepath = concat_strings(client->cwd, filepath);
    }
    return filepath;
}

static int get_file_fd(client_t *client, char *path)
{
    char *filepath = NULL;
    int fd = 0;

    filepath = get_filepath(client, path);
    if (filepath == NULL) {
        write(client->socket.fd, FILE_NOT_FOUND, strlen(FILE_NOT_FOUND));
        return -1;
    }
    fd = open(filepath, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd == -1) {
        write(client->socket.fd, FILE_NOT_FOUND, strlen(FILE_NOT_FOUND));
        return -1;
    }
    free(filepath);
    return fd;
}

void stor(my_ftp_t *my_ftp __attribute__((unused)), client_t *client,
char **params)
{
    int fd = 0;
    pid_t pid = 0;

    if (is_connected(client) == false)
        return;
    fd = get_file_fd(client, params[1]);
    if (fd == -1)
        return;
    if (is_data_channel_open(&client->data_channel, client->socket.fd) == false)
        return;
    pid = fork();
    if (pid == -1) {
        write(client->socket.fd,
CANNOT_OPEN_DATA_CHAN, strlen(CANNOT_OPEN_DATA_CHAN));
        return;
    } else if (pid == 0) {
        handle_child(client, fd);
    }
    close(fd);
    close_data_channel(client);
}