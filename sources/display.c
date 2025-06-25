/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** display
*/

#include "../include/ansi_colors.h"
#include <curl/curl.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_commit_message(json_t *commit_obj)
{
    json_t *commit = json_object_get(commit_obj, "commit");
    json_t *message = json_object_get(commit, "message");
    const char *msg = json_string_value(message);

    if (!json_is_object(commit))
        return;
    if (!json_is_string(message))
        return;
    printf("- %s\n", msg);
}

static void iterate_and_print_commits(json_t *root)
{
    size_t array_size;
    size_t i;
    json_t *commit_obj;

    array_size = json_array_size(root);
    printf(BOLD WHITE "Commits: %zu\n" RESET, array_size);
    for (i = 0; i < array_size; ++i) {
        commit_obj = json_array_get(root, i);
        if (json_is_object(commit_obj))
            print_commit_message(commit_obj);
    }
}

void display_commits_from_json(const char *json_text)
{
    json_error_t error;
    json_t *root = json_loads(json_text, 0, &error);

    if (!root) {
        fprintf(stderr, RED "Error parsing JSON: %s\n" RESET, error.text);
        return;
    }
    if (!json_is_array(root)) {
        fprintf(stderr, RED "Invalid JSON format: expected array\n" RESET);
        json_decref(root);
        return;
    }
    iterate_and_print_commits(root);
    json_decref(root);
}
