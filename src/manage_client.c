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

static int exec_command(my_ftp_t *my_ftp, client_t *client, char **params)
{
    if (my_array_len(params) < 1) {
        write(client->socket.fd, SYNTAX_ERROR, strlen(SYNTAX_ERROR));
        return -1;
    }
    for (size_t i = 0; command_array[i].name != NULL; i++) {
        if (strcmp(command_array[i].name, params[0]) == 0 &&
my_array_len(params) == command_array[i].params_nb) {
            return command_array[i].ptr(my_ftp, client, params);
        } else if (strcmp(command_array[i].name, params[0]) == 0) {
            write(client->socket.fd, SYNTAX_ERROR, strlen(SYNTAX_ERROR));
            return -1;
        }
    }
    write(client->socket.fd, BAD_COMMAND_500, strlen(BAD_COMMAND_500));
    return -1;
}

int manage_client(my_ftp_t *my_ftp, client_t *client)
{
    char *buffer = get_client_input(client);
    char **params = NULL;

    if (buffer == NULL) {
        remove_client(my_ftp, client);
        return 0;
    } else if (strcmp(buffer, "") == 0)
        return 0;
    printf("[%s]\n", buffer);
    params = parse_client_input(buffer);
    return exec_command(my_ftp, client, params);
}