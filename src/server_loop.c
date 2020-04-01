/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server_loop
*/

#include "my_ftp.h"

static void manage_fds(my_ftp_t *my_ftp)
{
    size_t max_idx = my_ftp->current_idx;

    if (my_ftp->main_server->is_triggered == true) {
        manage_server(my_ftp);
    }
    for (size_t i = 0; i < max_idx; i++) {
        if (my_ftp->clients[i] != NULL &&
my_ftp->clients[i]->is_triggered == true) {
            manage_client(my_ftp, my_ftp->clients[i]);
        }
    }
}

int server_loop(my_ftp_t *my_ftp)
{
    while (42) {
        if (poll_fds(my_ftp) == -1)
            return -1;
        manage_fds(my_ftp);
    }
    return 0;
}