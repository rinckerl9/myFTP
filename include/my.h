/*
** EPITECH PROJECT, 2021
** myftp
** File description:
** my.h
*/

#ifndef MY_H_
#define MY_H_

#include <dirent.h>
#include <stddef.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <sys/socket.h>

typedef struct s_client {
    int fd;
    struct sockaddr_in caddr;
    char *username;
    char *password;
    bool is_logged_in;
} client_t;

typedef struct s_server {
    int sock_fd;
    struct sockaddr_in saddr;
} server_t;

typedef struct s_commands {
    char *cmd;
    void (*func_ptr)(char **, client_t *);
} commands_t;

// utils.c
bool check_bad_input(char **cmd, client_t *client);
bool no_pass_entered(client_t *client);
void print_file(struct dirent *entry, client_t *client);
void free_array(char **array);

// str_to_word_array.c
int is_a_sep(char c, char *sep);
int len_word(char const *str, char *sep);
int count_words(char const *str, char *sep);
void fill_word(char **word, char **str, int len);
char **str_to_word_array(char const *str, char *sep);

// server.c
void handle_requests_from_client(client_t *client, server_t *server);
int handle_client(int fd_client, struct sockaddr_in cadrr, server_t *server);
int run_server(server_t *server);

// init.c
server_t *binding_and_listening(char const *path, server_t *new);
server_t *init_server_addr(int port, char const *path, server_t *new);
server_t *init_server(int port, char const *path);

// main.c
int main(int argc, char **argv);

#endif /* MY_H_ */

#ifndef GNL_H_
#define GNL_H_
#define READ_SIZE 100

// gnl.c
char *get_line(int *size_read, char *line);
char *get_buff_after_line(int *size_read, char *buffer);
char *my_next_strcat(char *buffer, char *line);
char *reach_end_of_line(int fd, int *size_read, char *buff, char *line);
char *get_next_line(int fd);

#endif /* GNL_H_ */

#ifndef CMD_H_
#define CMD_H_

// commands.c
void user(char **cmd, client_t *client);
void pass(char **cmd, client_t *client);
void cwd(char **cmd, client_t *client);
void cdup(char **cmd, client_t *client);
void quit(char **cmd, client_t *client);
void dele(char **cmd, client_t *client);
void pwd(char **cmd, client_t *client);
void pasv(char **cmd, client_t *client);
void actv(char **cmd, client_t *client);
void help(char **cmd, client_t *client);
void noop(char **cmd, client_t *client);
void retr(char **cmd, client_t *client);
void stor(char **cmd, client_t *client);
void list(char **cmd, client_t *client);

static const commands_t commands[] = {
    {"USER", &user},
    {"PASS", &pass},
    {"CWD", &cwd},
    {"CDUP", &cdup},
    {"QUIT", &quit},
    {"DELE", &dele},
    {"PWD", &pwd},
    {"LIST", &list},
    {"HELP", &help},
    {"NOOP", &noop},
    {"PASV", &pasv},
    {"PORT", &actv},
    {"RETR", &retr},
    {"STOR", &stor},
};

#endif /* CMD_H_ */