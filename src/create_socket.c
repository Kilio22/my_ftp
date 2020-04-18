/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** create_socket
*/

#include "my_ftp.h"

int create_socket(void)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt_val = 1;

    if (fd == -1) {
        fprintf(stderr, "Socket creation failed.\n");
        return -1;
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(int)) == -1) {
        fprintf(stderr, "Setsockopt failed.\n");
        close(fd);
        return -1;
    }
    return fd;
}