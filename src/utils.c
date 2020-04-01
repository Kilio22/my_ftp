/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** utils
*/

#include "my_ftp.h"

void remove_client(my_ftp_t *my_ftp, client_t *client)
{
    size_t i = 0;

    for (; i < my_ftp->current_idx; i++) {
        if (my_ftp->clients[i] == client) {
            free(my_ftp->clients[i]);
            my_ftp->clients[i] = NULL;
            break;
        }
    }
    if (i == my_ftp->current_idx)
        return;
    for (; i < my_ftp->current_idx; i++) {
        my_ftp->clients[i] = my_ftp->clients[i + 1];
        my_ftp->clients[i + 1] = NULL;
    }
    my_ftp->current_idx--;
}