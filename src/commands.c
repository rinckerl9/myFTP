/*
** EPITECH PROJECT, 2021
** myftp
** File description:
** commands.c
*/

#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "../include/my.h"

void quit(__attribute__((unused))char **cmd, client_t *client)
{
    write(client->fd, "221 Goodbye.\r\n", 14);
    usleep(1);
    close(client->fd);
}

void cdup(__attribute__((unused))char **cmd, client_t *client)
{
    if (client->username != NULL && client->is_logged_in == false) {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
        return;
    }
    if (client->is_logged_in == true) {
        if (chdir("../") != -1) {
            write(client->fd, "250 Directory successfully changed.\r\n", 37);
        } else {
            write(client->fd, "550 Failed to change directory.\r\n", 33);
        }
    } else {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
    }
}

void cwd(char **cmd, client_t *client)
{
    if (client->username != NULL && client->is_logged_in == false) {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
        return;
    }
    if (client->is_logged_in == true) {
        if (chdir(cmd[1]) != -1) {
            write(client->fd, "250 Directory successfully changed.\r\n", 37);
        } else {
            write(client->fd, "550 Failed to change directory.\r\n", 33);
        }
    } else {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
    }
}

void pass(__attribute__((unused))char **cmd, client_t *client)
{
    if (client->is_logged_in == true) {
        write(client->fd, "230 Already logged in.\r\n", 24);
        return;
    }
    if (client->username != NULL) {
        if (strncasecmp(client->username, "Anonymous",
            strlen("Anonymous")) == 0) {
            write(client->fd, "230 Login successful.\r\n", 23);
            client->is_logged_in = true;
        } else {
            write(client->fd, "530 Login incorrect.\r\n", 22);
            client->username = NULL;
        }
    } else {
        write(client->fd, "503 Login with USER first.\r\n", 28);
    }
}

void user(char **cmd, client_t *client)
{
    if (client->is_logged_in == true) {
        write(client->fd, "530 Can't change from guest user.\r\n", 35);
        return;
    }
    if (cmd[1] != NULL) {
        write(client->fd, "331 Please specify the password.\r\n", 34);
        client->username = strdup(cmd[1]);
    } else {
        write(client->fd, "530 Permission denied.\r\n", 24);
    }
}