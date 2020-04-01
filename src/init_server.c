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

int create_server(in_port_t port)
{
    int fd = create_socket();
    struct sockaddr_in sock_in = {0};

    if (fd == -1) {
        return -1;
    }
    sock_in.sin_family = AF_INET;
    sock_in.sin_port = htons(port);
    sock_in.sin_addr.s_addr = INADDR_ANY;
    if (bind(fd, (struct sockaddr *)&sock_in, sizeof(sock_in)) == -1) {
        fprintf(stderr, "Bind failed.\n");
        close(fd);
        return -1;
    }
    if (listen(fd, SOMAXCONN) == -1) {
        fprintf(stderr, "Listen failed\n");
        close(fd);
        return -1;
    }
    return fd;
}

server_t *init_server(in_port_t port)
{
    int fd = create_server(port);
    server_t *server_fd = malloc(sizeof(server_t));

    if (fd == -1)
        return NULL;
    server_fd->fd = fd;
    server_fd->is_triggered = false;
    return server_fd;
}