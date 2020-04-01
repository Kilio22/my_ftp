/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** poll_fds
*/

#include "my_ftp.h"

static void is_triggered(int fd, client_t **clients, size_t max_val)
{
    for (size_t i = 0; i < max_val; i++) {
        if (clients[i]->fd == fd) {
            clients[i]->is_triggered = true;
            break;
        }
    }
}

static void reset_set(my_ftp_t *my_ftp)
{
    FD_ZERO(&my_ftp->r_set);
    FD_SET(my_ftp->main_server->fd, &my_ftp->r_set);
    my_ftp->main_server->is_triggered = false;
    for (size_t i = 0; i < my_ftp->current_idx; i++) {
        FD_SET(my_ftp->clients[i]->fd, &my_ftp->r_set);
        my_ftp->clients[i]->is_triggered = false;
    }
}

int poll_fds(my_ftp_t *my_ftp)
{
    reset_set(my_ftp);
    if (select(FD_SETSIZE, &my_ftp->r_set, NULL, NULL, NULL) <= 0) {
        fprintf(stderr, "Select failed.\n");
        return -1;
    }
    if (FD_ISSET(my_ftp->main_server->fd, &my_ftp->r_set)) {
        my_ftp->main_server->is_triggered = true;
    }
    for (int fd = 0; fd < FD_SETSIZE; fd++) {
        if (FD_ISSET(fd, &my_ftp->r_set)) {
            is_triggered(fd, my_ftp->clients, my_ftp->current_idx);
        }
    }
    return 0;
}