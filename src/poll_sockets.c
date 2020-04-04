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
        if (clients[i]->socket.fd == fd) {
            clients[i]->socket.is_triggered = true;
            break;
        }
        if (clients[i]->data_channel.status == PASSIVE &&
clients[i]->data_channel.server.fd != 0 &&
clients[i]->data_channel.server.fd == fd) {
            clients[i]->data_channel.server.is_triggered = true;
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
        FD_SET(my_ftp->clients[i]->socket.fd, &my_ftp->r_set);
        if (my_ftp->clients[i]->data_channel.server.fd != 0 &&
my_ftp->clients[i]->data_channel.fd == 0 &&
my_ftp->clients[i]->data_channel.status == PASSIVE) {
            FD_SET(my_ftp->clients[i]->data_channel.server.fd, &my_ftp->r_set);
        }
        my_ftp->clients[i]->socket.is_triggered = false;
        my_ftp->clients[i]->data_channel.server.is_triggered = false;
    }
}

int poll_sockets(my_ftp_t *my_ftp)
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