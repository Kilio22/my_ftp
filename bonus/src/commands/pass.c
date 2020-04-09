/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pass
*/

#include "client.h"

void pass(socket_t *server, char *param)
{
    dprintf(server->fd, "PASS %s\r\n", param);
}