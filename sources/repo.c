/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** repo
*/

#include "../include/github.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <jansson.h>
#include <stdlib.h>

static void fill_user_repo(json_t *root, repo_info_t *info)
{
    json_t *value = json_object_get(root, "full_name");
    char *name_copy = NULL;
    char *user_part = NULL;
    char *repo_part = NULL;

    if (!json_is_string(value))
        return;
    name_copy = strdup(json_string_value(value));
    if (!name_copy)
        return;
    user_part = strtok(name_copy, "/");
    repo_part = strtok(NULL, "/");
    if (user_part)
        strncpy(info->user, user_part, sizeof(info->user) - 1);
    if (repo_part)
        strncpy(info->repo, repo_part, sizeof(info->repo) - 1);
    free(name_copy);
}

static void fill_desc_and_url(json_t *root, repo_info_t *info)
{
    json_t *value = json_object_get(root, "html_url");

    if (json_is_string(value))
        strncpy(info->url, json_string_value(value), sizeof(info->url) - 1);
    else
        snprintf(info->url, sizeof(info->url), "unknown");
    value = json_object_get(root, "description");
    info->desc = json_is_string(value)
        ? strdup(json_string_value(value)) : strdup("No description.");
}

static void fill_update_and_branch(json_t *root, repo_info_t *info)
{
    json_t *value = json_object_get(root, "updated_at");
    char *formatted = NULL;
    const char *iso_date = json_string_value(value);

    if (json_is_string(value)) {
        formatted = malloc(20);
        if (formatted)
            snprintf(formatted, 20, "%.10s %.8s", iso_date, iso_date + 11);
        info->updated = formatted ? formatted : strdup("unknown");
    } else {
        info->updated = strdup("unknown");
    }
    value = json_object_get(root, "default_branch");
    info->default_branch = json_is_string(value)
        ? strdup(json_string_value(value)) : strdup("main");
}

static void fill_stats(json_t *root, repo_info_t *info, int commit_count)
{
    json_t *value;

    value = json_object_get(root, "stargazers_count");
    info->stars = json_is_integer(value) ? json_integer_value(value) : 0;
    value = json_object_get(root, "forks_count");
    info->forks = json_is_integer(value) ? json_integer_value(value) : 0;
    value = json_object_get(root, "open_issues_count");
    info->issues = json_is_integer(value) ? json_integer_value(value) : 0;
    info->commits = commit_count;
}

void fill_repo_fields(json_t *root, repo_info_t *info, int commit_count)
{
    fill_user_repo(root, info);
    fill_desc_and_url(root, info);
    fill_update_and_branch(root, info);
    fill_stats(root, info, commit_count);
}
