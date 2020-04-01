/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** const_values
*/

const char SERVICE_READY[] = "120 Service ready in nnn minutes.\r\n";
const char DATA_125[] = "125 Data connection already open; \
transfer starting.\r\n";
const char DATA_150[] = "150 File status okay; about to open \
data connection.\r\n";
const char CMD_200[] = "200 Command okay.\r\n";
const char CMD_HELP[] = "214 Help message. On how to use the server or the \
meaning of a particular non-standard command. \
This reply is useful only to the human user.\r\n";
const char SERVICE_220[] = "220 Service ready for new user.\r\n";
const char SERVICE_221[] = "221 Service closing control connection.\
Logged out if appropriate.\r\n";
const char DATA_226[] = "226 Closing data connection. Requested file action \
successful (for example, file transfer or file abort).\r\n";
const char PASSIVE_227[] = "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\r\n";
const char LOGIN_230[] = "230 User logged in, proceed.\r\n";
const char ACTION_250[] = "250 Requested file action okay, completed.\r\n";
const char PATHNAME_257[] = "257 \"PATHNAME\" created.\r\n";
const char LOGIN_331[] = "331 User name okay, need password.\r\n";
const char LOGIN_332[] = "332 Need account for login.\r\n";