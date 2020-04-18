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
    if (sig != SIGINT)
        return;
    destroy_server();
    exit(0);
}

static void manage_clients(struct my_ftp_s *my_ftp, int fd)
{
    for (size_t i = 0; my_ftp->clients[i]; i++) {
        if (my_ftp->clients[i] != NULL && my_ftp->clients[i]->socket.fd == fd)
            return manage_client(my_ftp->clients[i], my_ftp->root_path);
        if (my_ftp->clients[i] != NULL &&
my_ftp->clients[i]->data_channel.server.fd == fd)
            return manage_other_servers(my_ftp->clients[i]);
    }
}

static void reset_set(struct my_ftp_s *my_ftp)
{
    FD_ZERO(&my_ftp->r_set);
    FD_SET(my_ftp->main_server->fd, &my_ftp->r_set);
    for (size_t i = 0; my_ftp->clients[i]; i++) {
        FD_SET(my_ftp->clients[i]->socket.fd, &my_ftp->r_set);
        if (my_ftp->clients[i]->data_channel.status == PASSIVE &&
my_ftp->clients[i]->data_channel.server.fd != 0 &&
my_ftp->clients[i]->data_channel.fd == 0) {
            FD_SET(my_ftp->clients[i]->data_channel.server.fd, &my_ftp->r_set);
        }
    }
}

static int manage_sockets(struct my_ftp_s *my_ftp)
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

int server_loop(struct my_ftp_s *my_ftp)
{
    struct sigaction sig = {0};

    sig.sa_handler = &my_sa_handler;
    sigaction(SIGINT, &sig, NULL);
    while (42) {
        if (manage_sockets(my_ftp) == -1)
            return -1;
    }
    return 0;
}