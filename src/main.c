/*
** EPITECH PROJECT, 2020
** Repo_starter
** File description:
** main
*/

#include "my_ftp.h"

int main(int ac, char **av)
{
    my_ftp_t my_ftp;

    if (ac != 3)
        return 84;
    if (init_ftp(&my_ftp, av) == -1)
        return 84;
    server_loop(&my_ftp);
    return 0;
}