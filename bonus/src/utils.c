/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** utils
*/

#include "client.h"

size_t my_array_len(char **array)
{
    size_t i = 0;

    if (!array)
        return 0;
    for (; array[i]; i++);
    return i;
}

bool should_exit(bool should_change)
{
    static bool should_exit = false;

    if (should_change == true)
        should_exit = !should_exit;
    return should_exit;
}