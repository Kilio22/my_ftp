/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** input
*/

#include "client.h"

char *get_input(char *str)
{
    char *buffer = NULL;
    size_t len = 0;

    printf(str);
    fflush(stdout);
    if (getline(&buffer, &len, stdin) < 0) {
        return NULL;
    }
    buffer[strlen(buffer) - 1] = '\0';
    return buffer;
}

char **parse_input(char *input)
{
    char **array = NULL;
    char *token = strtok(input, " ");
    size_t idx = 0;

    if (!token)
        return array;
    while (token != NULL) {
        array = realloc(array, sizeof(char *) * (my_array_len(array) + 2));
        array[idx++] = strdup(token);
        array[idx] = NULL;
        token = strtok(NULL, " ");
    }
    return array;
}