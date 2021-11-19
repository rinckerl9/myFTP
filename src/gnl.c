/*
** EPITECH PROJECT, 2021
** myteams_server
** File description:
** get_next_line.c
*/

#include <unistd.h>
#include <stdlib.h>
#include "../include/my.h"

char *get_line(int *size_read, char *line)
{
    int i = 0;
    char *new_line = NULL;

    if ((*size_read == 0 && line == NULL) || line == NULL)
        return (NULL);
    while (line != NULL && line[i] != '\n' && line[i] != '\0')
        i++;
    new_line = malloc(sizeof(char) * (i + 1));
    if (new_line == NULL)
        return (NULL);
    for (int j = 0; j < i + 1; j++)
        new_line[j] = '\0';
    for (int i = 0; line != NULL && line[i] != '\n'
        && line[i] != '\0'; i++) {
        new_line[i] = line[i];
    }
    free(line);
    return (new_line);
}

char *get_buff_after_line(int *size_read, char *buffer)
{
    int i = 0;
    int j = 0;
    char *new_buffer = malloc(sizeof(char) * (READ_SIZE + 1));

    if (new_buffer == NULL)
        return (NULL);
    while (buffer[i] != '\0' && buffer[i] != '\n')
        i++;
    for (int i = 0; i < READ_SIZE + 1; i++)
        new_buffer[i] = '\0';
    while (i + 1 < READ_SIZE) {
        new_buffer[j] = buffer[i + 1];
        i++;
        j++;
    }
    new_buffer[READ_SIZE] = '\0';
    if (*size_read == 0)
        return (NULL);
    free(buffer);
    return (new_buffer);
}

char *my_next_strcat(char *buffer, char *line)
{
    int size_line = 0;
    char *next_line = NULL;

    if (line == NULL && buffer[0] == '\0')
        return (NULL);
    while (line != NULL && line[size_line] != '\0')
        size_line++;
    next_line = malloc(sizeof(char) * (size_line + READ_SIZE + 1));
    if (next_line == NULL)
        return (NULL);
    for (int i = 0; i < size_line + READ_SIZE + 1; i++)
        next_line[i] = '\0';
    for (int i = 0; line != NULL && line[i] != '\0'; i++)
        next_line[i] = line[i];
    for (int j = 0; j < READ_SIZE; j++)
        next_line[size_line + j] = buffer[j];
    next_line[size_line + READ_SIZE] = '\0';
    return (next_line);
}

char *reach_end_of_line(int fd, int *size_read, char *buff, char *line)
{
    register int i = 0;

    while (*size_read > 0 && buff[i] != '\n') {
        if (i == READ_SIZE - 1) {
            line = my_next_strcat(buff, line);
            *size_read = read(fd, buff, READ_SIZE);
            if (*size_read == -1)
                return (NULL);
            buff[*size_read] = '\0';
            i = 0;
        } else
            i++;
    }
    if (*size_read != 0)
        line = my_next_strcat(buff, line);
    return (line);
}

char *get_next_line(int fd)
{
    int size_read = 1;
    char *line = NULL;
    static char *buffer;

    if (READ_SIZE <= 0 || fd == -1) {
        return (NULL);
    }
    if (buffer == NULL) {
        buffer = malloc(sizeof(char) * READ_SIZE + 1);
        if (buffer == NULL)
            return (NULL);
        for (int i = 0; i < READ_SIZE + 1; i++)
            buffer[i] = '\0';
    }
    line = reach_end_of_line(fd, &size_read, buffer, line);
    if (line == NULL)
        return (NULL);
    buffer = get_buff_after_line(&size_read, buffer);
    line = get_line(&size_read, line);
    return (line);
}