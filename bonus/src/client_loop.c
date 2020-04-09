/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** client_loop
*/

#include "client.h"

static const struct command_s commands[] = {
    {"cd", &cd},
    {"pwd", &pwd},
    {"passive", &passive},
    {"ls", &ls},
    {"get", &get},
    {"put", &put},
    {NULL, NULL}
};

void exec_command(socket_t *server, socket_t *data_channel, char **params)
{
    if (my_array_len(params) < 1) {
        printf("Unknown command\n");
        return;
    }
    for (size_t i = 0; commands[i].name != NULL; i++) {
        if (strcmp(params[0], commands[i].name) == 0) {
            return commands[i].ptr(server, data_channel, params);
        }
    }
    printf("Unknown command\n");
}

void client_loop(socket_t *server)
{
    socket_t *data_channel = malloc(sizeof(socket_t));
    char *input = NULL;
    char **params = NULL;

    memset(data_channel, 0, sizeof(socket_t));
    while (should_exit(false) == false) {
        input = get_input("$> ");
        if (!input)
            return;
        params = parse_input(input);
        if (!params)
            continue;
        exec_command(server, data_channel, params);
        for (size_t i = 0; params[i]; i++)
            free(params[i]);
        free(params);
        free(input);
    }
    free(data_channel);
}