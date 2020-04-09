/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** client
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdbool.h>

#define READ_SIZE 4096

typedef struct socket_s socket_t;

struct socket_s
{
    struct sockaddr_in sock_in;
    int fd;
};

struct command_s
{
    char *name;
    void (*ptr)(socket_t *, socket_t *, char **);
};

socket_t *connect_to_server(char **av);
char *get_input(char *str);
char **parse_input(char *input);
void client_loop(socket_t *server);

size_t my_array_len(char **array);
int create_socket(void);
bool should_exit(bool should_change);

void cd(socket_t *server, socket_t *data_channel, char **params);
void pwd(socket_t *server, socket_t *data_channel, char **params);
void passive(socket_t *server, socket_t *data_channel, char **params);
void ls(socket_t *server, socket_t *data_channel, char **params);
void get(socket_t *server, socket_t *data_channel, char **params);
void put(socket_t *server, socket_t *data_channel, char **params);

char *read_fd(int fd);
bool check_data_channel(socket_t *server, socket_t *data_channel);
void user(socket_t *server, char *param);
void pass(socket_t *server, char *param);

#endif /* !CLIENT_H_ */
