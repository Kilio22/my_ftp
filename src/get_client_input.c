/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** get_client_input
*/

#include "my_ftp.h"

static size_t my_strlen(char *str)
{
    if (str == NULL)
        return 0;
    return strlen(str);
}

static void concat_buffer(client_t *client, char *buff, ssize_t nread)
{
    char *tmp = realloc(client->buffer,
my_strlen(client->buffer) + nread + 1);

    if (client->buffer == NULL) {
        memset(tmp, '\0', my_strlen(client->buffer) + nread + 1);
    }
    strcat(tmp, buff);
    client->buffer = tmp;
}

char *get_client_input(client_t *client)
{
    char buff[READ_SIZE + 1] = {0};
    char *tmp = NULL;
    ssize_t nread = 0;

    nread = read(client->socket.fd, buff, READ_SIZE);
    if (nread <= 0) {
        tmp = client->buffer;
        client->buffer = NULL;
        return tmp;
    }
    concat_buffer(client, buff, nread);
    tmp = strstr(client->buffer, "\n");
    if (tmp == NULL)
        return strdup("");
    *tmp = '\0';
    tmp = strchr(client->buffer, '\r');
    if (tmp != NULL)
        *tmp = '\0';
    tmp = client->buffer;
    client->buffer = NULL;
    return tmp;
}