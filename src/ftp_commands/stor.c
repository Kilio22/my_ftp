/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** stor
*/

#include "my_ftp.h"

static void get_file(struct client_s *client, int fd)
{
    ssize_t nread = 0;
    char buffer[READ_SIZE + 1] = {'\0'};

    while ((nread = read(client->data_channel.fd, buffer, READ_SIZE)) > 0) {
        write(fd, buffer, nread);
        memset(buffer, '\0', READ_SIZE);
    }
    write(client->socket.fd, DATA_226, strlen(DATA_226));
}

static void handle_file_fetching(struct client_s *client, int fd)
{
    pid_t pid = 0;

    if (connect_to_data_channel(client) == -1) {
        write(client->socket.fd, DATA_425, strlen(DATA_425));
        exit(0);
    }
    pid = fork();
    if (pid == -1) {
        write(client->socket.fd, DATA_425, strlen(DATA_425));
    } else if (pid == 0) {
        write(client->socket.fd, DATA_150, strlen(DATA_150));
        get_file(client, fd);
        close(fd);
        destroy_server();
        exit(0);
    }
}

static char *get_filepath(struct client_s *client, char *path, char *root_path)
{
    char *filepath = NULL;

    if (path[0] == '/') {
        filepath = concat_strings(root_path, &path[1]);
    } else {
        filepath = path;
        while (strncmp(filepath, "./", 2) == 0) {
            filepath = filepath + 2;
        }
        filepath = concat_strings(client->cwd, filepath);
    }
    return filepath;
}

static int get_file_fd(struct client_s *client, char *path, char *root_path)
{
    char *filepath = NULL;
    int fd = 0;

    if (path == NULL) {
        write(client->socket.fd, ERROR_500, strlen(ERROR_500));
        return -1;
    }
    filepath = get_filepath(client, path, root_path);
    fd = open(filepath, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd == -1) {
        write(client->socket.fd, ERROR_500, strlen(ERROR_500));
        return -1;
    }
    free(filepath);
    return fd;
}

void stor(struct client_s *client, char **params, char *root_path)
{
    int fd = 0;

    if (is_data_channel_open(&client->data_channel, client->socket.fd) == false)
        return;
    fd = get_file_fd(client, params[1], root_path);
    if (fd == -1)
        return;
    handle_file_fetching(client, fd);
    close(fd);
    close_data_channel(client);
}