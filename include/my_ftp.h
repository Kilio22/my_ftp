/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** my_ftp
*/

#ifndef MY_FTP_H_
#define MY_FTP_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdbool.h>

typedef struct server_s server_t;
typedef struct my_ftp_s my_ftp_t;
typedef struct client_s client_t;

#define READ_SIZE 4096

struct client_s
{
    char *username;
    char *password;
    char *buffer;
    int fd;
    bool is_triggered;
    bool is_connected;
};

struct server_s
{
    int fd;
    bool is_triggered;
};

struct my_ftp_s
{
    client_t **clients;
    server_t *main_server;
    size_t current_idx;
    fd_set r_set;
    char *root_path;
};

extern const char SERVICE_READY[];
extern const char DATA_125[];
extern const char DATA_150[];
extern const char CMD_200[];
extern const char CMD_HELP[];
extern const char SERVICE_220[];
extern const char SERVICE_221[];
extern const char DATA_226[];
extern const char PASSIVE_227[];
extern const char LOGIN_230[];
extern const char ACTION_250[];
extern const char PATHNAME_257[];
extern const char LOGIN_331[];
extern const char LOGIN_332[];

server_t *init_server(in_port_t port);
int init_ftp(my_ftp_t *my_ftp, char **av);
int poll_fds(my_ftp_t *my_ftp);
client_t *accept_client(server_t *main_server);
int server_loop(my_ftp_t *my_ftp);
char *get_client_input(client_t *client);
int manage_client(my_ftp_t *my_ftp, client_t *client);
int manage_server(my_ftp_t *my_ftp);
void remove_client(my_ftp_t *my_ftp, client_t *client);

#endif /* !MY_FTP_H_ */
