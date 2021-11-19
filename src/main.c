/*
** EPITECH PROJECT, 2021
** myftp
** File description:
** main.c
*/

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/my.h"

int main(int argc, char **argv)
{
    unsigned int retv = 0;
    server_t *server = NULL;

    if (argc == 2 && strncmp(argv[1], "-h", 2) == 0) {
        return (write(1, "USAGE: ./myftp port path\n\
\tport\tis the port number on which the server socket listens\n\
\tpath\tis the path to the home directory for the Anonymous user\n", 149), 0);
    } else if (argc == 3) {
        if ((server = init_server(atoi(argv[1]), argv[2])) == NULL) {
            retv = 84;
        }
        if (retv != 84) {
            retv = run_server(server);
            free(server);
        }
    } else {
        retv = 84;
    }
    return (retv);
}