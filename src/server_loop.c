/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server_loop
*/

#include <signal.h>
#include "my_ftp.h"

static void my_sa_handler(int sig)
{
    my_ftp_t *my_ftp = NULL;

    if (sig != SIGINT)
        return;
    my_ftp = get_ftp(NULL);
    for (size_t i = 0; i < my_ftp->current_idx; i++) {
        close(my_ftp->clients[i]->socket.fd);
        free(my_ftp->clients[i]->password);
        free(my_ftp->clients[i]->username);
        free(my_ftp->clients[i]);
    }
    free(my_ftp->clients);
    close(my_ftp->main_server->fd);
    free(my_ftp->main_server);
    free(my_ftp->root_path);
    exit(0);
}

static void manage_clients(my_ftp_t *my_ftp, int fd)
{
    for (size_t i = 0; i < my_ftp->current_idx; i++) {
        if (my_ftp->clients[i] != NULL && my_ftp->clients[i]->socket.fd == fd)
            manage_client(my_ftp, my_ftp->clients[i]);
        else if (my_ftp->clients[i]->data_channel.server.fd == fd)
            manage_other_servers(my_ftp->clients[i]);
    }
}

static void reset_set(my_ftp_t *my_ftp)
{
    FD_ZERO(&my_ftp->r_set);
    FD_SET(my_ftp->main_server->fd, &my_ftp->r_set);
    for (size_t i = 0; i < my_ftp->current_idx; i++) {
        FD_SET(my_ftp->clients[i]->socket.fd, &my_ftp->r_set);
        if (my_ftp->clients[i]->data_channel.status == PASSIVE &&
my_ftp->clients[i]->data_channel.server.fd != 0 &&
my_ftp->clients[i]->data_channel.fd == 0) {
            FD_SET(my_ftp->clients[i]->data_channel.server.fd, &my_ftp->r_set);
        }
    }
}

static int manage_sockets(my_ftp_t *my_ftp)
{
    reset_set(my_ftp);
    if (select(FD_SETSIZE, &my_ftp->r_set, NULL, NULL, NULL) <= 0) {
        fprintf(stderr, "Select failed.\n");
        return -1;
    }
    if (FD_ISSET(my_ftp->main_server->fd, &my_ftp->r_set))
        manage_main_server(my_ftp);
    for (int fd = 0; fd < FD_SETSIZE; fd++) {
        if (FD_ISSET(fd, &my_ftp->r_set))
            manage_clients(my_ftp, fd);
    }
    return 0;
}

int server_loop(my_ftp_t *my_ftp)
{
    signal(SIGINT, &my_sa_handler);
    while (42) {
        if (manage_sockets(my_ftp) == -1)
            return -1;
    }
    return 0;
}