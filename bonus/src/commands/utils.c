/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** utils
*/

#include "client.h"

bool check_data_channel(socket_t *server, socket_t *data_channel)
{
    if (data_channel->fd == 0) {
        passive(server, data_channel, NULL);
        if (data_channel->fd == 0) {
            printf("Cannot get requested informations.\n");
            return false;
        }
    }
    return true;
}

static size_t my_strlen(char *str)
{
    if (!str)
        return 0;
    return strlen(str);
}

char *read_fd(int fd)
{
    char buffer[READ_SIZE + 1] = {'\0'};
    char *readed = NULL;
    ssize_t nread = 0;

    if ((nread = read(fd, buffer, READ_SIZE)) <= 0) {
        return NULL;
    }
    readed = realloc(readed, sizeof(char) * (my_strlen(readed)
+ my_strlen(buffer) + 1));
    strcpy(readed, buffer);
    while (strchr(readed, '\n') == NULL || nread == READ_SIZE) {
        memset(buffer, '\0', READ_SIZE);
        if ((nread = read(fd, buffer, READ_SIZE)) <= 0)
            return readed;
        readed = realloc(readed, sizeof(char) * (my_strlen(readed)
+ my_strlen(buffer) + 1));
        strcat(readed, buffer);
    }
    return readed;
}