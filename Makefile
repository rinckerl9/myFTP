##
## EPITECH PROJECT, 2021
## myftp
## File description:
## Makefile
##

OBJS	= src/main.o src/init.o src/server.o src/gnl.o src/str_to_word_array.o src/utils.o src/commands.o src/commands2.o src/commands3.o
SOURCE	= src/main.c src/init.c src/server.c src/gnl.c src/str_to_word_array.c src/utils.c src/commands.c src/commands2.c src/commands3.c
HEADER	= include/my.h
OUT	= myftp
CC	= gcc
LFLAGS	 = -Wall -Wextra

all: myftp

myftp: $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c $(HEADER)
	$(CC) -c -o $@ $< $(LFLAGS)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OUT)

re: clean fclean all

run: $(OUT)
	./$(OUT)

debug: $(OUT)
	valgrind ./$(OUT)