# my_ftp
This program is a FTP (file transfer protocol) server made in C language.  
Supported commands are RFC 959 compliant.

## Supported commands
* PORT
* PASV
* RETR
* PASS
* USER
* QUIT
* CWD
* CDUP
* PWD
* DELE
* STOR
* HELP
* NOOP
* LIST

Read RFC 959 to know the purpose of each command : https://tools.ietf.org/html/rfc959

## How to use it?
Clone the project and run this command to compile the program:
```sh
$> make
```
After that, you can run the server with this command:
```sh
$> ./myftp <SERVER PORT> <SERVER ROOT LOCATION>
```
Exemple:
```sh
$> ./myftp 4242 .
```

The default username is "Anonymous".  
The default password is "".
