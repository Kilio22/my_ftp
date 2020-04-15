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

typedef struct socket_s socket_t;
typedef struct my_ftp_s my_ftp_t;
typedef struct client_s client_t;
typedef struct data_channel_s data_channel_t;

#define READ_SIZE 4096
#define IS_COMMAND strcmp(command_array[i].name, params[0]) == 0 &&\
(my_array_len(params) >= command_array[i].params_nb ||\
command_array[i].params_nb == -1) && (command_array[i].to_be_connected == false\
|| (command_array[i].to_be_connected == true && client->is_connected == true))

enum data_channel_status_e
{
    NONE,
    ACTIVE,
    PASSIVE
};

struct socket_s
{
    struct sockaddr_in sock_in;
    int fd;
};

struct data_channel_s
{
    enum data_channel_status_e status;
    socket_t server;
    int fd;
};

struct my_ftp_s
{
    client_t **clients;
    socket_t *main_server;
    fd_set r_set;
    char *root_path;
};

struct client_s
{
    char *username;
    char *password;
    char *buffer;
    char *cwd;
    socket_t socket;
    data_channel_t data_channel;
    bool is_connected;
};

struct command_s
{
    char *name;
    void (*ptr)(client_t *, char **, char *);
    ssize_t params_nb;
    bool to_be_connected;
};

extern const char DATA_150[];
extern const char CMD_200[];
extern const char SERVICE_220[];
extern const char SERVICE_221[];
extern const char DATA_226[];
extern const char PASSIVE_227[];
extern const char LOGIN_230[];
extern const char ACTION_250[];
extern const char PATHNAME_257[];
extern const char LOGIN_331[];
extern const char NOT_LOGGED_530[];
extern const char BAD_COMMAND_500[];
extern const char WRONG_SEQUENCE[];
extern const char SYNTAX_ERROR[];
extern const char ERROR_500[];
extern const char CANNOT_OPEN_DATA_CHAN[];
extern const char TRANSFER_ABORT[];

socket_t *init_server(in_port_t port);
int init_ftp(my_ftp_t *my_ftp, char *port, char *real_path);
client_t *accept_client(socket_t *main_server, char *root_path,
bool should_write);
int server_loop(my_ftp_t *my_ftp);
char *get_client_input(client_t *client);
void manage_client(client_t *client, char *root_path);
int manage_main_server(my_ftp_t *my_ftp);
void manage_other_servers(client_t *client);
int create_socket(void);
int create_server(in_port_t port);

// utils
void remove_client(client_t *client);
void close_client_data(client_t *client);
ssize_t my_array_len(char **array);
bool is_data_channel_open(data_channel_t *data_channel, int fd);
int connect_to_data_channel(client_t *client);
void close_data_channel(client_t *client);
bool has_valid_creditentials(client_t *client, bool should_send_msg);
my_ftp_t *get_ftp(my_ftp_t *ftp);
char *concat_paths(char *cwd, char *filepath, bool need_slash);
char *concat_strings(char *str1, char *str2);
bool is_connected(client_t *client);
size_t get_clients_nb(client_t **clients);

// commands
void port(client_t *client, char **params, char *root_path);
void retr(client_t *client, char **params, char *root_path);
void pasv(client_t *client, char **params, char *root_path);
void pass(client_t *client, char **params, char *root_path);
void user(client_t *client, char **params, char *root_path);
void quit(client_t *client, char **params, char *root_path);
void cwd(client_t *client, char **params, char *root_path);
void cdup(client_t *client, char **params, char *root_path);
void dele(client_t *client, char **params, char *root_path);
void pwd(client_t *client, char **params, char *root_path);
void stor(client_t *client, char **params, char *root_path);
void help(client_t *client, char **params, char *root_path);
void noop(client_t *client, char **params, char *root_path);
void list(client_t *client, char **params, char *root_path);

// directory
bool is_dir(char *path);

#endif /* !MY_FTP_H_ */
