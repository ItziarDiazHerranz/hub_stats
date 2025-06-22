/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** commits
*/

#ifndef INCLUDED_COMMITS_H
    #define INCLUDED_COMMITS_H

    #include <stdio.h>

typedef struct response_data_s {
    char *data;
    size_t size;
} response_data_t;

int fetch_commit_count(const char *user, const char *repo);

#endif
