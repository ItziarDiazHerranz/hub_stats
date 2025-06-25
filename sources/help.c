/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** help
*/

#include <string.h>
#include <unistd.h>

int is_help(int argc, char **argv)
{
    return argc > 1 && strcmp(argv[1], "--help") == 0;
}

void print_help(void)
{
    write(1, "Usage:\n", 7);
    write(1, "./github_stats <user>/<repo>\n", 30);
    write(1,
        "If no arguments are given, you will be prompted to enter them.\n",
        63);
    write(1, "Options:\n", 9);
    write(1, "  --help      Show this help message\n", 37);
    write(1, "  --json      Export output to stats.json\n", 42);
    write(1, "  --csv       Export output to stats.csv\n", 41);
}
