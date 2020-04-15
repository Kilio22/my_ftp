/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** manage_client
*/

#include "my_ftp.h"

static const struct command_s command_array[] = {
    {"PORT", &port, 2, true},
    {"PASV", &pasv, 1, true},
    {"RETR", &retr, 1, true},
    {"PASS", &pass, 1, false},
    {"USER", &user, 1, false},
    {"QUIT", &quit, 1, false},
    {"CWD", &cwd, 2, true},
    {"CDUP", &cdup, 1, true},
    {"PWD", &pwd, 1, true},
    {"DELE", &dele, 2, true},
    {"STOR", &stor, 1, true},
    {"HELP", &help, 1, true},
    {"NOOP", &noop, 1, true},
    {"LIST", &list, 1, true},
    {NULL, NULL, 0, false}
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

static void is_connected_checker(client_t *client)
{
    if (client->is_connected == false) {
        write(client->socket.fd, NOT_LOGGED_530, strlen(NOT_LOGGED_530));
    } else {
        write(client->socket.fd, BAD_COMMAND_500, strlen(BAD_COMMAND_500));
    }
}

static void exec_command(client_t *client, char **params, char *root_path)
{
    for (size_t i = 0; command_array[i].name != NULL; i++) {
        if (IS_COMMAND) {
            return command_array[i].ptr(client, params, root_path);
        }
        if (strcmp(command_array[i].name, params[0]) == 0 &&
command_array[i].to_be_connected == true && client->is_connected == false) {
            write(client->socket.fd, NOT_LOGGED_530, strlen(NOT_LOGGED_530));
            return;
        }
        if (strcmp(command_array[i].name, params[0]) == 0
&& my_array_len(params) < command_array[i].params_nb) {
            write(client->socket.fd, ERROR_500, strlen(ERROR_500));
            return;
        }
    }
    is_connected_checker(client);
}

void manage_client(client_t *client, char *root_path)
{
    char *buffer = get_client_input(client);
    char **params = NULL;

    if (buffer == NULL) {
        remove_client(client);
        return;
    }
    if (strcmp(buffer, "") == 0) {
        free(buffer);
        return;
    }
    params = parse_client_input(buffer);
    if (my_array_len(params) > 0) {
        exec_command(client, params, root_path);
        for (size_t i = 0; params[i]; i++)
            free(params[i]);
        free(params);
    } else
        is_connected_checker(client);
    free(buffer);
}