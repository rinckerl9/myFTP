/*
** EPITECH PROJECT, 2021
** myftp
** File description:
** utils.c
*/

#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include "../include/my.h"

bool check_bad_input(char **cmd, client_t *client)
{
    unsigned int tmp = 0;

    for (unsigned int i = 0; cmd && cmd[i]; i++) {
        for (unsigned int j = 0; cmd[i][j] != '\0'; j++) {
            if (cmd[i][j] == ' ' || cmd[i][j] == '\t'
                || cmd[i][j] == '\r' || cmd[i][j] == '\n')
                tmp = tmp + 1;
        }
    }
    if (tmp == strlen(cmd[0])) {
        if (no_pass_entered(client) == true) {
            return (true);
        } else {
            write(client->fd, "500 Unknown command.\r\n", 22);
            return (true);
        }
    }
    return (false);
}

bool no_pass_entered(client_t *client)
{
    if (client->username == NULL && client->is_logged_in == false) {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
        return (true);
    }
    if (client->username != NULL && client->is_logged_in == false) {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
        return (true);
    }
    return (false);
}

void print_file(struct dirent *entry, client_t *client)
{
    if (entry->d_name[0] != '.') {
        write(client->fd, entry->d_name, strlen(entry->d_name));
        write(client->fd, " ", 1);
    }
}

void free_array(char **array)
{
    for (unsigned int i = 0; array && array[i]; i++)
        free(array[i]);
    free(array);
}