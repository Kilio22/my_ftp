/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** parse_client_input
*/

#include "my_ftp.h"

char **parse_client_input(char *buffer)
{
    char **array = NULL;
    char *token = strtok(buffer, " ");
    size_t i = 0;

    while (token != NULL) {
        array = realloc(array, sizeof(char *) * (my_tab_len(array) + 2));
        array[i] = strdup(token);
        array[i + 1] = NULL;
        i++;
        token = strtok(NULL, " ");
    }
    return array;
}