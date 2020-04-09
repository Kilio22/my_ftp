/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** user
*/

#include "client.h"

void user(socket_t *server, char *param)
{
    dprintf(server->fd, "USER %s\r\n", param);
}