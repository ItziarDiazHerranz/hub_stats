/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** ansi_colors
*/

#include <unistd.h>
#include <stdio.h>
#include "../include/github.h"

void print_colored_info(const char *label, const char *value)
{
    printf("\033[1;34m%s:\033[0m %s\n", label, value);
}

void print_colored_int(const char *label, int value)
{
    printf("\033[1;34m%s:\033[0m %d\n", label, value);
}

void print_repo_info_colored(repo_info_t *info)
{
    print_colored_info("Description", info->desc);
    print_colored_info("Last updated", info->updated);
    print_colored_int("Stars", info->stars);
    print_colored_int("Forks", info->forks);
    print_colored_int("Issues", info->issues);
    print_colored_int("Commits", info->commits);
}
