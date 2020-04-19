/*
** EPITECH PROJECT, 2020
** Repo_starter
** File description:
** main
*/

#include "my_ftp.h"

static const int FTP_FAILURE = 84;
static const int FTP_SUCCESS = 0;

int main(int ac, char **av)
{
    struct my_ftp_s my_ftp = {0};
    char *real_path = NULL;

    if (ac != 3 || strcmp(av[2], "") == 0)
        return FTP_FAILURE;
    real_path = concat_paths(av[2], "", true);
    if (is_dir(real_path) == false)
        return FTP_FAILURE;
    if (init_ftp(&my_ftp, av[1], real_path) == -1)
        return FTP_FAILURE;
    get_ftp(&my_ftp);
    if (server_loop(&my_ftp) == -1)
        return FTP_FAILURE;
    return FTP_SUCCESS;
}