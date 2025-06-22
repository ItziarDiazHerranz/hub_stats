##
## EPITECH PROJECT, 2025
## hub_stats
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lcurl -ljansson

SRC = sources/main.c \
	  sources/parser.c \
	  sources/commits.c \
	  sources/utils.c \
	  sources/logic.c \
	  sources/init.c \
	  sources/repo.c

BIN = hub_stats

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(BIN)

re: clean all
