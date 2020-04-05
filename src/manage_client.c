/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** manage_client
*/

#include "my_ftp.h"

static const struct command_s command_array[] = {
    {"PORT", &port, 2},
    {"PASV", &pasv, 1},
    {"RETR", &retr, 2},
    {"PASS", &pass, -1},
    {"USER", &user, 2},
    {"QUIT", &quit, 1},
    {"CWD", &cwd, 2},
    {"CDUP", &cdup, 1},
    {"PWD", &pwd, 1},
    {"DELE", &dele, 2},
    {"STOR", &stor, 2},
    {"HELP", &help, -1},
    {"NOOP", &noop, 1},
    {"LIST", &list, -1},
    {NULL, NULL, 0}
};

static char **parse_client_input(char *buffer)
{
    char **array = NULL;
    char *token = strtok(buffer, " ");
    size_t i = 0;

    while (token != NULL) {
        array = realloc(array, sizeof(char *) * (my_array_len(array) + 2));
        array[i] = strdup(token);
        array[i + 1] = NULL;
        i++;
        token = strtok(NULL, " ");
    }
    return array;
}

static void exec_command(my_ftp_t *my_ftp, client_t *client, char **params)
{
    if (my_array_len(params) < 1) {
        write(client->socket.fd, SYNTAX_ERROR, strlen(SYNTAX_ERROR));
        return;
    }
    for (size_t i = 0; command_array[i].name != NULL; i++) {
        if (strcmp(command_array[i].name, params[0]) == 0 &&
(my_array_len(params) == command_array[i].params_nb ||
command_array[i].params_nb == -1)) {
            return command_array[i].ptr(my_ftp, client, params);
        } else if (strcmp(command_array[i].name, params[0]) == 0) {
            write(client->socket.fd, SYNTAX_ERROR, strlen(SYNTAX_ERROR));
            return;
        }
    }
    write(client->socket.fd, BAD_COMMAND_500, strlen(BAD_COMMAND_500));
}

int manage_client(my_ftp_t *my_ftp, client_t *client)
{
    char *buffer = get_client_input(client);
    char **params = NULL;

    if (buffer == NULL) {
        remove_client(my_ftp, client);
        return 0;
    } else if (strcmp(buffer, "") == 0) {
        free(buffer);
        return 0;
    }
    params = parse_client_input(buffer);
    exec_command(my_ftp, client, params);
    for (size_t i = 0; params[i]; i++) {
        free(params[i]);
    }
    free(params);
    free(buffer);
    return 0;
}