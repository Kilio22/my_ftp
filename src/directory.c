/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** directory
*/

#include "my_ftp.h"

bool is_dir(char *path)
{
    struct stat st;

    if (path == NULL)
        return false;
    if (stat(path, &st) == -1)
        return false;
    if (S_ISDIR(st.st_mode) == true)
        return true;
    return false;
}

char *concat_paths(char *cwd, char *filepath, bool need_slash)
{
    char *new_path = malloc(sizeof(char) *
(strlen(cwd) + strlen(filepath) + 1));
    char real_path[PATH_MAX + 1] = {0};
    char *ptr = NULL;

    strcpy(new_path, cwd);
    strcat(new_path, filepath);
    ptr = realpath(new_path, real_path);
    if (ptr == NULL) {
        free(new_path);
        return NULL;
    }
    ptr = strdup(ptr);
    if (ptr[strlen(ptr - 1) != '/'] && need_slash == true) {
        ptr = realloc(ptr, strlen(ptr) + 2);
        ptr[strlen(ptr) + 1] = '\0';
        ptr[strlen(ptr)] = '/';
    }
    free(new_path);
    return ptr;
}