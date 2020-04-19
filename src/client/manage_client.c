/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** manage_client
*/

#include "my_ftp.h"

void manage_client(struct client_s *client, char *root_path)
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
    if (my_tab_len(params) > 0) {
        exec_command(client, params, root_path);
        for (size_t i = 0; params[i]; i++)
            free(params[i]);
        free(params);
    } else
        unknown_command(client);
    free(buffer);
}