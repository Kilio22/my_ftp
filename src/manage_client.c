/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** manage_client
*/

#include "my_ftp.h"

int manage_client(my_ftp_t *my_ftp, client_t *client)
{
    char *buff = get_client_input(client);

    if (buff == NULL) {
        remove_client(my_ftp, client);
    } else {
        printf("[%s]\n", buff);
    }
    return 0;
}