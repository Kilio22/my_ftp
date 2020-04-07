/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** help
*/

#include "my_ftp.h"

static const char *answers[][2] = {
    {"CDUP", "214 - CHANGE TO PARENT DIRECTORY: \
This command is a special case of CWD\r\n"},
    {"CWD", "214 - CHANGE WORKING DIRECTOR: This command allows the user \
to work with a different directory or dataset for file storage \
or retrieval without altering his login or accounting information.\r\n"},
    {"DELE", "214 - This command causes the file specified in the pathname\
 to be deleted at the server site.\r\n"},
    {"HELP", "214 - This command shall cause the server to send helpful \
information regarding its implementation status over the \
control connection to the user.\r\n"},
    {"NOOP", "214 - This command does not affect any parameters or previously \
entered commands. It specifies no action other than that the \
server send an OK reply.\r\n"},
    {"PASS", "214 - The argument field is a Telnet string specifying the \
user's password. This command must be immediately preceded by the \
user name command, and, for some sites, completes the user's \
identification for access control.\r\n"},
    {"PASV", "214 - This command requests the server-DTP to \"listen\" \
on a data port (which is not its default data port) and to wait for a \
connection rather than initiate one upon receipt of a \
transfer command.  The response to this command includes the \
host and port address this server is listening on.\r\n"},
    {"PORT", "214 - The argument is a HOST-PORT specification for the \
data port to be used in data connection. A port command would be: \
PORT h1,h2,h3,h4,p1,p2\r\n"},
    {"PWD", "214 - This command causes the name of the current working \
directory to be returned in the reply.\r\n"},
    {"QUIT", "214 - This command terminates a USER and if file transfer \
is not in progress, the server closes the control connection.\r\n"},
    {"RETR", "214 - This command causes the server-DTP to transfer a \
copy of the file, specified in the pathname, to the server- or user-DTP \
at the other end of the data connection.\r\n"},
    {"STOR", "214 - This command causes the server-DTP to accept the data \
transferred via the data connection and to store the data as \
a file at the server site.\r\n"},
    {"USER", "214 - The argument field is a Telnet string \
identifying the user. The user identification is that which is required by the \
server for access to its file system.  This command will \
normally be the first command transmitted by the user after \
the control connections are made (some servers may require \
this).\r\n"},
    {NULL, NULL}
};

void help(my_ftp_t *my_ftp __attribute__((unused)), client_t *client,
char **params __attribute__((unused)))
{
    if (params[1] == NULL) {
        write(client->socket.fd, CMD_HELP, strlen(CMD_HELP));
        return;
    }
    for (size_t i = 0; answers[i][0] != NULL; i++) {
        if (strcmp(answers[i][0], params[1]) == 0) {
            write(client->socket.fd, answers[i][1], strlen(answers[i][1]));
            return;
        }
    }
    write(client->socket.fd, CMD_HELP, strlen(CMD_HELP));
}