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

my_ftp_t *get_ftp(my_ftp_t *ftp)
{
    static my_ftp_t *store_ftp = NULL;

    if (ftp == NULL)
        return store_ftp;
    store_ftp = ftp;
    return ftp;
}