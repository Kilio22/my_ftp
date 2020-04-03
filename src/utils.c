/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** utils
*/

#include "my_ftp.h"

static const char default_user[] = "Anonymous";
static const char default_password[] = "";

bool has_valid_creditentials(client_t *client)
{
    if (client->password == NULL || client->username == NULL) {
        return false;
    }
    if (!strcmp(client->username, default_user) &&
!strcmp(client->password, default_password))
        return true;
    return false;
}

ssize_t my_array_len(char **array)
{
    ssize_t i = 0;

    if (array == NULL)
        return 0;
    for (; array[i]; i++);
    return i;
}

void remove_client(my_ftp_t *my_ftp, client_t *client)
{
    size_t i = 0;

    for (; i < my_ftp->current_idx; i++) {
        if (my_ftp->clients[i] == client) {
            free(my_ftp->clients[i]);
            my_ftp->clients[i] = NULL;
            break;
        }
    }
    if (i == my_ftp->current_idx)
        return;
    for (; i < my_ftp->current_idx; i++) {
        my_ftp->clients[i] = my_ftp->clients[i + 1];
        my_ftp->clients[i + 1] = NULL;
    }
    my_ftp->current_idx--;
}