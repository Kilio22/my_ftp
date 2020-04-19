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

#define READ_SIZE 4096

#define IS_COMMAND strcmp(command_array[i].name, params[0]) == 0 &&\
(my_tab_len(params) >= command_array[i].params_nb ||\
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
    struct socket_s server;
    int fd;
};

struct my_ftp_s
{
    struct client_s **clients;
    struct socket_s *main_server;
    fd_set r_set;
    char *root_path;
};

struct client_s
{
    char *username;
    char *password;
    char *buffer;
    char *cwd;
    struct socket_s socket;
    struct data_channel_s data_channel;
    bool is_connected;
};

struct command_s
{
    char *name;
    void (*ptr)(struct client_s *, char **, char *);
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
extern const char DATA_425[];
extern const char TRANSFER_ABORT[];

// Main functions
int init_ftp(struct my_ftp_s *my_ftp, char *port, char *real_path);
int server_loop(struct my_ftp_s *my_ftp);
int create_socket(void);

// Server
struct socket_s *init_server(in_port_t port);
struct client_s *accept_client(struct socket_s *main_server, char *root_path,
bool should_write);
int manage_main_server(struct my_ftp_s *my_ftp);
void manage_other_servers(struct client_s *client);
int create_server(in_port_t port);
void remove_client(struct client_s *client);
bool is_data_channel_open(struct data_channel_s *data_channel, int fd);
int connect_to_data_channel(struct client_s *client);
void close_data_channel(struct client_s *client);
void destroy_server(void);

// Client
void manage_client(struct client_s *client, char *root_path);
void exec_command(struct client_s *client, char **params, char *root_path);
char *get_client_input(struct client_s *client);
void close_client_data(struct client_s *client);
bool is_connected(struct client_s *client);
char **parse_client_input(char *buffer);
void unknown_command(struct client_s *client);

// utils
ssize_t my_tab_len(void *array);
struct my_ftp_s *get_ftp(struct my_ftp_s *ftp);

// commands
void port(struct client_s *client, char **params, char *root_path);
void retr(struct client_s *client, char **params, char *root_path);
void pasv(struct client_s *client, char **params, char *root_path);
void pass(struct client_s *client, char **params, char *root_path);
void user(struct client_s *client, char **params, char *root_path);
void quit(struct client_s *client, char **params, char *root_path);
void cwd(struct client_s *client, char **params, char *root_path);
void cdup(struct client_s *client, char **params, char *root_path);
void dele(struct client_s *client, char **params, char *root_path);
void pwd(struct client_s *client, char **params, char *root_path);
void stor(struct client_s *client, char **params, char *root_path);
void help(struct client_s *client, char **params, char *root_path);
void noop(struct client_s *client, char **params, char *root_path);
void list(struct client_s *client, char **params, char *root_path);

// directory
bool is_dir(char *path);
char *concat_paths(char *cwd, char *filepath, bool need_slash);
char *concat_strings(char *str1, char *str2);

#endif /* !MY_FTP_H_ */
