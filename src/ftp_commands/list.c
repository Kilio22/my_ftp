/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** list
*/

#include "my_ftp.h"

static void send_list(struct client_s *client, char *path)
{
    FILE *file = NULL;
    char buffer[READ_SIZE + 1] = {'\0'};
    char *command = NULL;

    command = concat_strings("/bin/ls -l ", path);
    file = popen(command, "r");
    free(command);
    if (file == NULL) {
        write(client->socket.fd, TRANSFER_ABORT, strlen(TRANSFER_ABORT));
        return;
    }
    while (fgets(buffer, READ_SIZE, file) != NULL) {
        write(client->data_channel.fd, buffer, strlen(buffer));
        memset(buffer, '\0', READ_SIZE);
    }
    write(client->socket.fd, DATA_226, strlen(DATA_226));
    fclose(file);
}

static char *get_path(struct client_s *client, char *path, char *root_path)
{
    char *filepath = NULL;

    if (path == NULL)
        return strdup(client->cwd);
    if (path[0] == '/') {
        filepath = concat_paths(root_path, &path[1], false);
    } else {
        filepath = concat_paths(client->cwd, path, false);
    }
    if (filepath == NULL) {
        write(client->socket.fd, ERROR_500, strlen(ERROR_500));
        return NULL;
    }
    return filepath;
}

static void handle_ls(struct client_s *client, char *path)
{
    pid_t pid = 0;

    if (connect_to_data_channel(client) == -1) {
        write(client->socket.fd, DATA_425, strlen(DATA_425));
        free(path);
        return;
    }
    pid = fork();
    if (pid == -1) {
        write(client->socket.fd, DATA_425, strlen(DATA_425));
    } else if (pid == 0) {
        write(client->socket.fd, DATA_150, strlen(DATA_150));
        send_list(client, path);
        free(path);
        destroy_server();
        exit(0);
    }
}

void list(struct client_s *client, char **params, char *root_path)
{
    char *path = NULL;

    if (is_data_channel_open(&client->data_channel, client->socket.fd) == false)
        return;
    path = get_path(client, params[1], root_path);
    if (path == NULL)
        return;
    handle_ls(client, path);
    close_data_channel(client);
}