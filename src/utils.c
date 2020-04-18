/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** utils
*/

#include "my_ftp.h"

ssize_t my_tab_len(void *array)
{
    char **byte_tab = array;
    size_t i = 0;

    if (array == NULL)
        return 0;
    for (; byte_tab[i]; i++);
    return i;
}

struct my_ftp_s *get_ftp(struct my_ftp_s *ftp)
{
    static struct my_ftp_s *stored_ftp = NULL;

    if (ftp == NULL)
        return stored_ftp;
    stored_ftp = ftp;
    return ftp;
}
