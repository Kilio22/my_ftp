/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** client_is_connected
*/

#include "my_ftp.h"

bool is_connected(struct client_s *client)
{
    if (client->is_connected == false) {
        write(client->socket.fd, NOT_LOGGED_530, strlen(NOT_LOGGED_530));
        return false;
    }
    return true;
}