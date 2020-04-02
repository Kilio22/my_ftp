/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** retr
*/

#include "my_ftp.h"

int send_file(client_t *client, int fd)
{
    char buffer[READ_SIZE] = {'\0'};
    int nread = 0;

    write(client->socket.fd, DATA_150, strlen(DATA_150));
    while ((nread = read(fd, buffer, READ_SIZE)) > 0) {
        if (write(client->data_channel.fd, buffer, nread) == -1) {
            write(client->socket.fd, TRANSFER_ABORT, strlen(TRANSFER_ABORT));
            return -1;
        }
        memset(&buffer, '\0', READ_SIZE);
    }
    write(client->socket.fd, DATA_226, strlen(DATA_226));
    return 0;
}

int retr(my_ftp_t *my_ftp __attribute__((unused)), client_t *client,
char **params)
{
    int fd = open(params[1], O_RDONLY);
    pid_t pid;

    if (is_data_channel_open(&client->data_channel, client->socket.fd) == false)
        return -1;
    if (fd == -1) {
        write(client->socket.fd, FILE_NOT_FOUND, strlen(FILE_NOT_FOUND));
        return -1;
    }
    pid = fork();
    if (pid == 0) {
        if (connect_to_data_channel(client) == -1) {
            write(fd, CANNOT_OPEN_DATA_CHAN, strlen(CANNOT_OPEN_DATA_CHAN));
            return -1;
        }
        send_file(client, fd);
        close_data_channel(client);
        exit(0);
    }
    close_data_channel(client);
    return 0;
}