/*
** EPITECH PROJECT, 2021
** myftp
** File description:
** commands3.c
*/

#include <unistd.h>
#include "../include/my.h"

void stor(__attribute__((unused))char **cmd, client_t *client)
{
    if (client->username != NULL && client->is_logged_in == false) {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
        return;
    }
    write(client->fd, "502 Command not implemented.\r\n", 30);
}

void retr(__attribute__((unused))char **cmd, client_t *client)
{
    if (client->username != NULL && client->is_logged_in == false) {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
        return;
    }
    write(client->fd, "502 Command not implemented.\r\n", 30);
}

void actv(__attribute__((unused))char **cmd, client_t *client)
{
    if (client->username != NULL && client->is_logged_in == false) {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
        return;
    }
    write(client->fd, "200 Command okay.\r\n", 19);
}

void pasv(__attribute__((unused))char **cmd, client_t *client)
{
    if (client->username != NULL && client->is_logged_in == false) {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
        return;
    }
    write(client->fd, "227 Entering Passive Mode \
(h1,h2,h3,h4,p1,p2).\r\n", 48);
}