/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** repo
*/

#include "../include/github.h"

void fill_repo_fields(json_t *root, repo_info_t *info, int commit_count)
{
    info->desc =
        strdup(json_string_value(json_object_get(root, "description")));
    info->updated =
        strdup(json_string_value(json_object_get(root, "updated_at")));
    info->stars =
        json_integer_value(json_object_get(root, "stargazers_count"));
    info->forks = json_integer_value(json_object_get(root, "forks_count"));
    info->issues =
        json_integer_value(json_object_get(root, "open_issues_count"));
    info->commits = commit_count;
}

void free_repo_fields(repo_info_t *info)
{
    free((char *) info->desc);
    free((char *) info->updated);
}

void print_repo_info(const repo_info_t *info)
{
    printf("📘 Repo: %s/%s\n", info->user, info->repo);
    printf("🌐 URL: %s\n", info->url);
    printf("📝 Description: %s\n", info->desc ? info->desc : "(none)");
    printf(
        "📅 Last updated: %s\n", info->updated ? info->updated : "(unknown)");
    printf("⭐ Stars: %d\n", info->stars);
    printf("🍴 Forks: %d\n", info->forks);
    printf("🐞 Issues: %d\n", info->issues);
    printf("🕒 Commits: %d\n", info->commits);
}

void print_json_parse_error(const char *json_data, json_error_t *error)
{
    fprintf(stderr, "❌ JSON parse error: %s (line %d, column %d)\n",
        error->text, error->line, error->column);
    fprintf(stderr, "Raw JSON: %s\n", json_data);
}
