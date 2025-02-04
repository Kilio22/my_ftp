/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** const_values
*/

const char DATA_150[] = "150 File status okay; openning data connection.\r\n";
const char CMD_200[] = "200 %s okay.\r\n";
const char SERVICE_220[] = "220 Service ready for new user.\r\n";
const char SERVICE_221[] = "221 Logged out.\r\n";
const char DATA_226[] = "226 Closing data connection.\r\n";
const char PASSIVE_227[] = "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n";
const char LOGIN_230[] = "230 User logged in, proceed.\r\n";
const char ACTION_250[] = "250 Requested file action okay, completed.\r\n";
const char PATHNAME_257[] = "257 \"%s\"\r\n";
const char LOGIN_331[] = "331 User name okay, need password.\r\n";
const char TRANSFER_ABORT[] = "426 Connection closed; transfer aborted.\r\n";
const char DATA_425[] = "425 Can't open data connection.\r\n";
const char NOT_LOGGED_530[] = "530 Not logged in.\r\n";
const char WRONG_SEQUENCE[] = "503 Bad sequence of commands.\n\r";
const char BAD_COMMAND_500[] = "500 Syntax error, command unrecognized.\r\n";
const char SYNTAX_ERROR[] = "501 Syntax error in parameters or arguments.\r\n";
const char ERROR_500[] = "550 Requested action not taken.\r\n";