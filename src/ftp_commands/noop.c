/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** noop
*/

#include "my_ftp.h"

void noop(client_t *client,
char **params __attribute__((unused)), char *root_path __attribute__((unused)))
{
    dprintf(client->socket.fd, CMD_200, "NOOP");
}