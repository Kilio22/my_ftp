/*
** EPITECH PROJECT, 2020
** Repo_starter
** File description:
** main
*/

#include <signal.h>
#include "client.h"

static void my_sa_handler(int sig __attribute__((unused)))
{
    should_exit(true);
}

static void enter_logs(socket_t *server)
{
    char *username = NULL;
    char *password = NULL;
    char *ret_code = NULL;

    while (42) {
        username = get_input("Enter username: ");
        user(server, username);
        free(username);
        ret_code = read_fd(server->fd);
        printf(ret_code);
        if (strstr(ret_code, "331") == NULL)
            continue;
        password = get_input("Enter password: ");
        pass(server, password);
        free(password);
        ret_code = read_fd(server->fd);
        printf(ret_code);
        if (strstr(ret_code, "230") == NULL)
            continue;
        break;
    }
}

int main(int ac, char **av)
{
    socket_t *server = NULL;

    if (ac != 2)
        return 84;
    server = connect_to_server(av);
    if (server == NULL)
        return 84;
    signal(SIGINT, &my_sa_handler);
    enter_logs(server);
    client_loop(server);
    close(server->fd);
    free(server);
    return 0;
}