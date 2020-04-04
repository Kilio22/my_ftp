/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** help
*/

#include "my_ftp.h"

void help(my_ftp_t *my_ftp __attribute__((unused)), client_t *client,
char **params __attribute__((unused)))
{
    write(client->socket.fd, CMD_HELP, strlen(CMD_HELP));
}