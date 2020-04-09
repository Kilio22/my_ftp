/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** connect_to_server
*/

#include "client.h"

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

int my_connect(socket_t *socket)
{
    char buffer[READ_SIZE + 1] = {'\0'};

    if (connect(socket->fd, (struct sockaddr *)&socket->sock_in,
sizeof(struct sockaddr_in)) == -1) {
        printf("Connect failed.\n");
        return -1;
    }
    if (read(socket->fd, buffer, READ_SIZE) == -1) {
        return -1;
    }
    printf(buffer);
    return 0;
}

socket_t *connect_to_server(char **av)
{
    socket_t *server = NULL;
    char *ptr = av[1];
    in_port_t port = strtol(av[1], &ptr, 10);

    if (*av[1] == '\0' || *ptr != '\0')
        return NULL;
    server = malloc(sizeof(socket_t));
    if (!server)
        return NULL;
    server->sock_in.sin_addr.s_addr = INADDR_ANY;
    server->sock_in.sin_family = AF_INET;
    server->sock_in.sin_port = htons(port);
    server->fd = create_socket();
    if (server->fd == -1)
        return NULL;
    if (my_connect(server) == -1)
        return NULL;
    return server;
}