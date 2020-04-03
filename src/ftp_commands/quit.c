/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** quit
*/

#include "my_ftp.h"

void quit(my_ftp_t *my_ftp, client_t *client,
char **params __attribute__((unused)))
{
    write(client->socket.fd, SERVICE_221, strlen(SERVICE_221));
    remove_client(my_ftp, client);
}