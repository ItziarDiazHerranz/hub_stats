/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** main
*/

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/github.h"

static int handle_interactive_mode(char *user, char *repo)
{
    int commit_count;

    write(1, "\033[1m\033[32mEntering interactive mode...\033[0m\n", 43);
    interactive_mode(user, repo, 256);
    if (user[0] == '\0' || repo[0] == '\0')
        return 84;
    commit_count = fetch_commit_count(user, repo);
    if (commit_count <= 0) {
        write(2, "\033[31mError: No commits found or request failed.\033[0m\n",
            53);
        return 84;
    }
    fetch_and_display(user, repo, commit_count);
    return 0;
}

static int validate_and_copy_args(
    char *user, char *repo, int argc, char **argv)
{
    if (argc < 3 || argc > 4) {
        write(2, "\033[31mUsage: ./hub_stats <user> <repo> [commits]\033[0m\n",
            52);
        return 84;
    }
    strncpy(user, argv[1], 255);
    strncpy(repo, argv[2], 255);
    user[255] = '\0';
    repo[255] = '\0';
    return 0;
}

static int handle_args(int argc, char **argv)
{
    char user[256] = {0};
    char repo[256] = {0};
    int commit_count;

    if (validate_and_copy_args(user, repo, argc, argv) == 84)
        return 84;
    commit_count =
        (argc == 4) ? atoi(argv[3]) : fetch_commit_count(user, repo);
    if (commit_count <= 0) {
        write(2, "\033[31mError: No commits found or request failed.\033[0m\n",
            53);
        return 84;
    }
    fetch_and_display(user, repo, commit_count);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 1)
        return handle_interactive_mode((char[256]){0}, (char[256]){0});
    return handle_args(argc, argv);
}
