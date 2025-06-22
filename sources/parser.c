/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** parser
*/

#include <jansson.h>
#include <string.h>
#include "../include/github.h"

void parse_and_display_json(const char *json_data, int commit_count)
{
    json_error_t error;
    json_t *root = json_loads(json_data, 0, &error);
    repo_info_t info;

    if (!root) {
        print_json_parse_error(json_data, &error);
        return;
    }
    memset(&info, 0, sizeof(repo_info_t));
    fill_repo_fields(root, &info, commit_count);
    print_repo_info(&info);
    free_repo_fields(&info);
    json_decref(root);
}
