
/*
** EPITECH PROJECT, 2021
** myftp
** File description:
** init.c
*/

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/my.h"

server_t *binding_and_listening(char const *path, server_t *new)
{
    if (chdir(path) == -1) {
        free(new);
        return (write(2, "Path doesn't exists\n", 21), NULL);
    }
    if (bind(new->sock_fd,
        (struct sockaddr *)&new->saddr, sizeof(struct sockaddr)) == -1) {
        free(new);
        return (write(2, "Can't bind to this port\n", 25), NULL);
    }
    if (listen(new->sock_fd, 10) == -1) {
        free(new);
        return (write(2, "Listen failed\n", 15), NULL);
    }
    return (new);
}

server_t *init_server_addr(int port, char const *path, server_t *new)
{
    memset(&new->saddr, 0, sizeof(new->saddr));
    new->saddr.sin_family = AF_INET;
    new->saddr.sin_port = htons(port);
    new->saddr.sin_addr.s_addr = INADDR_ANY;
    return (binding_and_listening(path, new));
}

server_t *init_server(int port, char const *path)
{
    server_t *new = NULL;

    if (port < 1 || port > 65535)
        return (write(2, "Port must be between 1 and 65535\n", 34), NULL);
    new = (server_t *)malloc(sizeof(server_t));
    if (new == NULL)
        return (write(2, "Malloc failed\n", 15), NULL);
    new->sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (new->sock_fd == -1) {
        free(new);
        return (write(2, "Socket creation failed\n", 24), NULL);
    }
    if (setsockopt(new->sock_fd, SOL_SOCKET, SO_REUSEADDR,
        &(int){1}, sizeof(int)) == -1) {
        free(new);
        return (write(2, "Setsockopt failed\n", 19), NULL);
    }
    return (init_server_addr(port, path, new));
}