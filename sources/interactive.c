/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** interactive
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int is_interactive(int argc)
{
    return argc == 1 && isatty(STDIN_FILENO);
}

char *prompt_input(const char *message)
{
    char *buffer = malloc(256);
    size_t len;

    if (!buffer)
        return NULL;
    printf("%s", message);
    if (!fgets(buffer, 256, stdin)) {
        free(buffer);
        return NULL;
    }
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
    return buffer;
}

static char *allocate_repo_path(const char *user, const char *repo)
{
    char *full;
    size_t len = strlen(user) + strlen(repo) + 2;

    full = malloc(len);
    if (!full)
        return NULL;
    snprintf(full, len, "%s/%s", user, repo);
    return full;
}

char *build_repo_path(void)
{
    char *user = prompt_input("Enter GitHub username: ");
    char *repo = NULL;
    char *full = NULL;

    if (!user)
        return NULL;
    repo = prompt_input("Enter repository name: ");
    if (!repo) {
        free(user);
        return NULL;
    }
    full = allocate_repo_path(user, repo);
    free(user);
    free(repo);
    return full;
}

int interactive_mode(char *user, char *repo, int max_len)
{
    char *input = build_repo_path();
    char *sep = NULL;

    if (!input)
        return 84;
    sep = strchr(input, '/');
    if (!sep) {
        fprintf(stderr, "Invalid format. Use user/repo\n");
        free(input);
        return 84;
    }
    *sep = '\0';
    strncpy(user, input, max_len);
    strncpy(repo, sep + 1, max_len);
    free(input);
    return 0;
}
