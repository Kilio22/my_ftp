/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** list
*/

#include "my_ftp.h"

static void send_list(client_t *client, char *path)
{
    FILE *file = NULL;
    char buffer[READ_SIZE + 1] = {'\0'};
    char *command = NULL;

    command = concat_strings("/bin/ls -l ", path);
    file = popen(command, "r");
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

static char *get_path(client_t *client, char *path)
{
    char *filepath = NULL;

    if (path[0] == '/') {
        filepath = concat_paths(client->cwd, &path[1], false);
    } else {
        filepath = concat_paths(client->cwd, path, false);
    }
    if (filepath == NULL) {
        write(client->socket.fd, FILE_NOT_FOUND, strlen(FILE_NOT_FOUND));
        return NULL;
    }
    return filepath;
}

static void handle_child(client_t *client, char *param)
{
    char *path = NULL;

    if (param == NULL) {
        path = strdup(client->cwd);
    } else {
        path = get_path(client, param);
    }
    if (path == NULL)
        return;
    write(client->socket.fd, DATA_150, strlen(DATA_150));
    if (connect_to_data_channel(client) == -1) {
        write(client->socket.fd, CANNOT_OPEN_DATA_CHAN,
strlen(CANNOT_OPEN_DATA_CHAN));
        return;
    }
    send_list(client, path);
    free(path);
    close_data_channel(client);
    exit(0);
}

void list(my_ftp_t *my_ftp __attribute__((unused)), client_t *client,
char **params)
{
    pid_t pid = 0;

    if (my_array_len(params) > 2) {
        write(client->socket.fd, SYNTAX_ERROR, strlen(SYNTAX_ERROR));
        return;
    }
    if (is_connected(client) == false)
        return;
    if (is_data_channel_open(&client->data_channel, client->socket.fd) == false)
        return;
    pid = fork();
    if (pid == -1) {
        write(client->socket.fd,
CANNOT_OPEN_DATA_CHAN, strlen(CANNOT_OPEN_DATA_CHAN));
        return;
    } else if (pid == 0)
        handle_child(client, params[1]);
    close_data_channel(client);
}