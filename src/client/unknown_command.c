/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** unknown_command
*/

#include "my_ftp.h"

void unknown_command(struct client_s *client)
{
    if (client->is_connected == false) {
        write(client->socket.fd, NOT_LOGGED_530, strlen(NOT_LOGGED_530));
    } else {
        write(client->socket.fd, BAD_COMMAND_500, strlen(BAD_COMMAND_500));
    }
}