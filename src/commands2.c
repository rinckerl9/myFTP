/*
** EPITECH PROJECT, 2021
** myftp
** File description:
** commands2.c
*/

#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "../include/my.h"

void noop(__attribute__((unused))char **cmd, client_t *client)
{
    if (client->username != NULL && client->is_logged_in == false) {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
        return;
    }
    if (client->is_logged_in == true)
        write(client->fd, "200 Command okay.\r\n", 19);
    else
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
}

void help(__attribute__((unused))char **cmd, client_t *client)
{
    if (client->username != NULL && client->is_logged_in == false) {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
        return;
    }
    if (client->is_logged_in == true) {
        write(client->fd, "214 Help message.\r\n", 19);
        write(client->fd, " USER PASS CWD CDUP QUIT DELE PWD\r\n", 35);
        write(client->fd, " LIST HELP NOOP PASV PORT RETR STOR\r\n", 37);
        write(client->fd, "214 Help OK.\r\n", 14);
    } else {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
    }
}

void list(__attribute__((unused))char **cmd, client_t *client)
{
    DIR *folder = NULL;
    struct dirent *entry = NULL;

    if (no_pass_entered(client) == true) return;
    if (client->is_logged_in == true) {
        folder = opendir(".");
        if (folder != NULL) {
            write(client->fd, "150 File status okay; \
about to open data connection.\r\n", 54);
            while ((entry = readdir(folder)) != NULL) {
                print_file(entry, client);
            }
            write(client->fd, "\r\n", 2);
            write(client->fd, "226 Closing data connection.\r\n", 30);
            closedir(folder);
        } else
            write(client->fd, "550 Permission denied.\r\n", 24);
    } else
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
}

void pwd(__attribute__((unused))char **cmd, client_t *client)
{
    char buf[512];

    if (client->username != NULL && client->is_logged_in == false) {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
        return;
    }
    if (client->is_logged_in == true) {
        if (getcwd(buf, sizeof(buf)) != NULL) {
            write(client->fd, "257 \"", 5);
            write(client->fd, buf, strlen(buf));
            write(client->fd, "\"\r\n", 3);
        } else {
            write(client->fd, "550 Permission denied.\r\n", 24);
        }
    } else {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
    }
}

void dele(char **cmd, client_t *client)
{
    if (client->username != NULL && client->is_logged_in == false) {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
        return;
    }
    if (client->is_logged_in == true) {
        if (remove(cmd[1]) == 0) {
            write(client->fd, "250 Requested file action okay, \
completed.\r\n", 44);
        } else {
            write(client->fd, "550 Permission denied.\r\n", 24);
        }
    } else {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
    }
}