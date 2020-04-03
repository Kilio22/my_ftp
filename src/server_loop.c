/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server_loop
*/

#include <signal.h>
#include "my_ftp.h"

void my_sa_handler(int sig)
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

void manage_other_servers(client_t *client)
{
    client_t *new_client = accept_client(&client->data_channel.server, "");

    if (new_client == NULL) {
        return;
    }
    client->data_channel.fd = new_client->socket.fd;
    free(new_client);
}

static void manage_fds(my_ftp_t *my_ftp)
{
    size_t max_idx = my_ftp->current_idx;

    if (my_ftp->main_server->is_triggered == true) {
        manage_server(my_ftp);
    }
    for (size_t i = 0; i < max_idx; i++) {
        if (my_ftp->clients[i] != NULL &&
my_ftp->clients[i]->socket.is_triggered == true)
            manage_client(my_ftp, my_ftp->clients[i]);
        else if (my_ftp->clients[i]->data_channel.server.is_triggered == true)
            manage_other_servers(my_ftp->clients[i]);
    }
}

int server_loop(my_ftp_t *my_ftp)
{
    signal(SIGINT, &my_sa_handler);
    while (42) {
        if (poll_sockets(my_ftp) == -1)
            return -1;
        manage_fds(my_ftp);
    }
    return 0;
}