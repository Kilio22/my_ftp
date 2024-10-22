/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** create_socket
*/

#include "my_ftp.h"

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

struct socket_s *init_server(in_port_t port)
{
    int fd = create_server(port);
    struct socket_s *server_socket = malloc(sizeof(struct socket_s));

    if (fd == -1)
        return NULL;
    server_socket->fd = fd;
    return server_socket;
}