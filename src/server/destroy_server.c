/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** destroy_server
*/

#include "my_ftp.h"

void destroy_server(void)
{
    struct my_ftp_s *my_ftp = get_ftp(NULL);

    for (size_t i = 0; my_ftp->clients[i] != NULL; i++) {
        close_client_data(my_ftp->clients[i]);
        free(my_ftp->clients[i]);
    }
    free(my_ftp->clients);
    close(my_ftp->main_server->fd);
    free(my_ftp->main_server);
    free(my_ftp->root_path);
}