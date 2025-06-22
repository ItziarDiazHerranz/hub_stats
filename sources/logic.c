/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** logic
*/

#include "../include/github.h"
#include "../include/commits.h"

static void display_http_error(long code, const char *url)
{
    if (code == 404)
        fprintf(stderr, "Error 404: Repository not found (%s)\n", url);
    else if (code == 403)
        fprintf(stderr,
            "Error 403: Forbidden API rate limit may be exceeded.\n");
    else
        fprintf(stderr,
            "Unexpected HTTP error %ld returned by GitHub API.\n", code);
}

static void handle_success_response(
    const response_data_t *chunk, const repo_info_t *info)
{
    int commit_count = fetch_commit_count(info->user, info->repo);

    printf("Repository found! Parsing data...\n\n");
    parse_and_display_json(chunk->data, commit_count);
}

void handle_response(
    CURL *curl, response_data_t *chunk, const repo_info_t *info)
{
    CURLcode res = curl_easy_perform(curl);
    long http_code;

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
        return;
    }
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (http_code == 200)
        handle_success_response(chunk, info);
    else
        display_http_error(http_code, info->url);
}
