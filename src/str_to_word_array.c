/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** str_to_word_array
*/

#include <stdlib.h>
#include "../include/my.h"

int is_a_sep(char c, char *sep)
{
    for (int i = 0; sep && sep[i]; i++) {
        if (sep[i] == c) {
            return (1);
        }
    }
    return (0);
}

int len_word(char const *str, char *sep)
{
    int len = 0;

    for (int i = 0; str && str[i] && !is_a_sep(str[i], sep); i++) {
        len++;
    }
    return (len);
}

int count_words(char const *str, char *sep)
{
    int len = 0;

    for (int i = 0; str && str[i]; i++) {
        if (is_a_sep(str[i], sep)) {
            len++;
        }
    }
    return (len + 1);
}

void fill_word(char **word, char **str, int len)
{
    char *new = *word;
    char *copy = *str;

    for (int i = 0; i < len; i++) {
        new[i] = copy[i];
    }
    new[len] = '\0';
    if (copy[len]) {
        *str = &copy[len + 1];
    }
}

char **str_to_word_array(char const *str, char *sep)
{
    int nb_words = count_words(str, sep);
    int len_words = 0;
    char **word_array = (char **)malloc(sizeof(char *) * (nb_words + 1));

    for (int i = 0; i < nb_words + 1; i++) {
        len_words = len_word(str, sep);
        word_array[i] = (char *)malloc(sizeof(char) * (len_words + 1));
        fill_word(&word_array[i], (char **)&str, len_words);
    }
    word_array[nb_words] = NULL;
    return (word_array);
}