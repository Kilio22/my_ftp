/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** exec_command
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

void exec_command(struct client_s *client, char **params, char *root_path)
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
&& my_tab_len(params) < command_array[i].params_nb) {
            write(client->socket.fd, ERROR_500, strlen(ERROR_500));
            return;
        }
    }
    unknown_command(client);
}