/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** parser
*/

#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/github.h"
#include "../include/ansi_colors.h"

void print_json_parse_error(json_error_t *error)
{
    if (!error)
        return;
    fprintf(stderr, "JSON parsing error at line %d: %s\n", error->line,
        error->text);
}

void free_repo_fields(repo_info_t *info)
{
    if (!info)
        return;
    if (info->name)
        free(info->name);
    if (info->desc)
        free(info->desc);
    if (info->updated)
        free(info->updated);
    if (info->default_branch)
        free(info->default_branch);
}

static void check_json_errors(json_t *root)
{
    json_t *message;

    if (!root || !json_is_object(root)) {
        write_error("Error: Invalid JSON response.\n");
        json_decref(root);
        exit(84);
    }
    message = json_object_get(root, "message");
    if (message && json_is_string(message)
        && strcmp(json_string_value(message), "Not Found") == 0) {
        write_error("Error: No such repository or user.\n");
        json_decref(root);
        exit(84);
    }
}

static const char *get_owner_login(json_t *root)
{
    json_t *owner = json_object_get(root, "owner");
    json_t *login = json_object_get(owner, "login");

    if (!json_is_object(owner))
        return "unknown";
    if (!json_is_string(login))
        return "unknown";
    return json_string_value(login);
}

static void print_repo_fields(json_t *root, const char *user, int commit_count)
{
    const char *name = json_string_value(json_object_get(root, "name"));
    const char *url = json_string_value(json_object_get(root, "html_url"));
    const char *desc = json_string_value(json_object_get(root, "description"));
    const char *update =
        json_string_value(json_object_get(root, "updated_at"));
    json_t *stars = json_object_get(root, "stargazers_count");
    json_t *forks = json_object_get(root, "forks_count");
    json_t *issues = json_object_get(root, "open_issues_count");

    printf(BOLD WHITE "Repo:" RESET "%s/%s\n", user, name);
    printf(BOLD WHITE "URL:" RESET "%s\n", url);
    printf(BOLD WHITE "Description:" RESET "%s\n",
        desc ? desc : "No description.");
    printf(BOLD WHITE "\nLast updated:" RESET "%s\n", update);
    printf(BOLD WHITE "Stars:" RESET " %lld\n", json_integer_value(stars));
    printf(BOLD WHITE "Forks:" RESET " %lld\n", json_integer_value(forks));
    printf(BOLD WHITE "Issues:" RESET " %lld\n", json_integer_value(issues));
    printf(BOLD WHITE "Commits:" RESET " %d\n", commit_count);
}

void parse_and_display_json(const char *json_data, int commit_count)
{
    json_error_t error;
    json_t *root = json_loads(json_data, 0, &error);
    const char *user;

    check_json_errors(root);
    user = get_owner_login(root);
    print_repo_fields(root, user, commit_count);
    json_decref(root);
}
