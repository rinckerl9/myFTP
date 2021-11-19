/*
** EPITECH PROJECT, 2021
** myftp
** File description:
** server.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "../include/my.h"

void exec_command(char **cmd, client_t *client,
    __attribute__((unused))server_t *server)
{
    bool is_done = false;

    if (cmd == NULL || check_bad_input(cmd, client) == true)
        return;
    for (unsigned int i = 0; i < 14; i++) {
        if (strncasecmp(cmd[0], commands[i].cmd,
            strlen(commands[i].cmd)) == 0) {
            (*commands[i].func_ptr)(cmd, client);
            is_done = true;
        }
    }
    if (is_done == false && client->is_logged_in == true)
        write(client->fd, "500 Unknown command.\r\n", 22);
    else if (is_done == false && client->is_logged_in == false)
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
    else
        free_array(cmd);
}

void handle_requests_from_client(client_t *client, server_t *server)
{
    char *input = NULL;

    write(client->fd, "220 Service ready for new user.\r\n", 33);
    while (1) {
        input = get_next_line(client->fd);
        if (input != NULL) {
            exec_command(str_to_word_array(input, " \t\r\n"), client, server);
            free(input);
        }
    }
}

int handle_client(int fd_client, struct sockaddr_in cadrr, server_t *server)
{
    pid_t pid = 0;
    client_t *client = (client_t *)malloc(sizeof(client_t));

    if (client == NULL)
        return (write(2, "Malloc failed, closing connection\n", 35), -1);
    memset(client, 0, sizeof(client_t));
    client->fd = fd_client;
    client->caddr = cadrr;
    client->username = NULL;
    client->password = NULL;
    client->is_logged_in = false;
    if ((pid = fork()) == 0) {
        handle_requests_from_client(client, server);
        exit(0);
    }
    if (pid == -1)
        return (write(2, "Fork failed, closing connection\n", 33), -1);
    free(client);
    return (0);
}

int run_server(server_t *server)
{
    int fd_client = 0;
    struct sockaddr_in cadrr = {};
    socklen_t addr_len = sizeof(cadrr);

    while (1) {
        fd_client = accept(server->sock_fd,
            (struct sockaddr *)&cadrr, &addr_len);
        if (fd_client != -1) {
            if (handle_client(fd_client, cadrr, server) == -1) {
                close(fd_client);
                break;
            } else {
                close(fd_client);
            }
        }
    }
    close(server->sock_fd);
    return (0);
}