/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** utils
*/

#include "my_ftp.h"

ssize_t my_array_len(char **array)
{
    ssize_t i = 0;

    if (array == NULL)
        return 0;
    for (; array[i]; i++);
    return i;
}

size_t get_clients_nb(client_t **clients)
{
    size_t i = 0;

    if (clients == NULL)
        return 0;
    for (; clients[i]; i++);
    return i;
}

my_ftp_t *get_ftp(my_ftp_t *ftp)
{
    static my_ftp_t *store_ftp = NULL;

    if (ftp == NULL)
        return store_ftp;
    store_ftp = ftp;
    return ftp;
}

bool check_params_len(char **params, int fd, int nb_params)
{
    if (my_array_len(params) < nb_params) {
        write(fd, SYNTAX_ERROR, strlen(SYNTAX_ERROR));
        return false;
    }
    return true;
}