/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** main
*/

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/commits.h"
#include "../include/github.h"

static void cleanup_and_exit(CURL *curl, response_data_t *chunk, int code)
{
    curl_easy_cleanup(curl);
    free(chunk->data);
    curl_global_cleanup();
    exit(code);
}

static int validate_args(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <user> <repo>\n", argv[0]);
        return 0;
    }
    return 1;
}

static void fill_repo_info(
    repo_info_t *info, const char *user, const char *repo, const char *url)
{
    memset(info, 0, sizeof(repo_info_t));
    strcpy(info->user, user);
    strcpy(info->repo, repo);
    strcpy(info->url, url);
}

static int run_fetch(const char *user, const char *repo)
{
    curl_handle_t *curl;
    response_data_t chunk;
    char url[1024] = {0};
    repo_info_t info;

    if (!init_chunk(&chunk))
        return 84;
    snprintf(
        url, sizeof(url), "https://api.github.com/repos/%s/%s", user, repo);
    printf("🔎 Fetching info for %s/%s...\n", user, repo);
    fill_repo_info(&info, user, repo, url);
    curl = init_curl_session(&chunk, url);
    if (!curl)
        return 84;
    handle_response(curl, &chunk, &info);
    cleanup_and_exit(curl, &chunk, 0);
    return 0;
}

int main(int argc, char **argv)
{
    char user[256] = {0};
    char repo[256] = {0};

    if (!validate_args(argc, argv))
        return 84;
    get_repo_info(argc, argv, user, repo);
    return run_fetch(user, repo);
}
