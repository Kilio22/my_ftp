/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** is_data_channel_open
*/

#include "my_ftp.h"

bool is_data_channel_open(struct data_channel_s *data_channel, int fd)
{
    if (data_channel->status == NONE) {
        write(fd, DATA_425, strlen(DATA_425));
        return false;
    }
    return true;
}