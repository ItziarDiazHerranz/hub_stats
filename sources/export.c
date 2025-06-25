/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** export
*/

#include <stdio.h>
#include "../include/github.h"

int export_to_json(repo_info_t *info)
{
    FILE *file = fopen("repo_info.json", "w");

    if (!file)
        return 84;
    fprintf(file,
        "{\n  \"description\": \"%s\",\n  \"updated_at\": \"%s\",\n"
        "  \"stars\": %d,\n  \"forks\": %d,\n"
        "  \"issues\": %d,\n  \"commits\": %d\n}\n",
        info->desc, info->updated, info->stars,
        info->forks, info->issues, info->commits);
    fclose(file);
    return 0;
}

int export_to_csv(repo_info_t *info)
{
    FILE *file = fopen("repo_info.csv", "w");

    if (!file)
        return 84;
    fprintf(file,
        "Description,Updated At,Stars,Forks,Issues,Commits\n"
        "\"%s\",\"%s\",%d,%d,%d,%d\n",
        info->desc, info->updated, info->stars,
        info->forks, info->issues, info->commits);
    fclose(file);
    return 0;
}
