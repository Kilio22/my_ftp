/*
** EPITECH PROJECT, 2020
** Repo_starter
** File description:
** main
*/

#include "my_ftp.h"

static const int FTP_FAILURE = 84;
static const int FTP_SUCCESS = 0;

static char *get_root_directory(char *path)
{
    char *result = NULL;
    size_t len = 0;

    result = realpath(path, NULL);
    if (result == NULL) {
        free(path);
        return NULL;
    }
    free(path);
    len = strlen(result);
    if (result[len - 1] != '/') {
        result = realloc(result, sizeof(char) * (len + 2));
        result[len] = '/';
        result[len + 1] = '\0';
    }
    return result;
}

int main(int ac, char **av)
{
    struct my_ftp_s my_ftp = {0};
    char *real_path = NULL;

    if (ac != 3 || strcmp(av[2], "") == 0)
        return FTP_FAILURE;
    real_path = get_root_directory(strdup(av[2]));
    if (is_dir(real_path) == false)
        return FTP_FAILURE;
    if (init_ftp(&my_ftp, av[1], real_path) == -1)
        return FTP_FAILURE;
    get_ftp(&my_ftp);
    if (server_loop(&my_ftp) == -1)
        return FTP_FAILURE;
    return FTP_SUCCESS;
}