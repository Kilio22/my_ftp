/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** noop
*/

#include "my_ftp.h"

void noop(my_ftp_t *my_ftp __attribute__((unused)), client_t *client,
char **params __attribute__((unused)))
{
    if (is_connected(client) == false)
        return;
    write(client->socket.fd, CMD_200, strlen(CMD_200));
}