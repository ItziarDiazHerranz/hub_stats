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
	  sources/utils.c \
	  sources/logic.c \
	  sources/init.c \
	  sources/repo.c \
	  sources/ansi_colors.c \
	  sources/interactive.c \
	  sources/export.c \
	  sources/help.c \
	  sources/fetch.c \
	  sources/error.c \
	  sources/display.c \
	  sources/request.c \
	  sources/count.c \
	  sources/branch.c \

BIN = hub_stats

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(BIN)

re: clean all
