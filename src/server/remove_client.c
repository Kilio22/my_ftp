/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** remove_client
*/

#include "my_ftp.h"

void remove_client(struct client_s *client)
{
    struct my_ftp_s *my_ftp = get_ftp(NULL);
    ssize_t len = my_tab_len(my_ftp->clients);
    ssize_t i = 0;

    close_client_data(client);
    for (; i < len; i++) {
        if (my_ftp->clients[i] == client) {
            free(my_ftp->clients[i]);
            my_ftp->clients[i] = NULL;
            break;
        }
    }
    for (; i < len; i++) {
        my_ftp->clients[i] = my_ftp->clients[i + 1];
        my_ftp->clients[i + 1] = NULL;
    }
}