/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** init
*/

#include "../include/commits.h"
#include "../include/github.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int init_chunk(response_data_t *chunk)
{
    chunk->data = malloc(1);
    if (!chunk->data) {
        fprintf(stderr, "❌ Memory allocation failed\n");
        return 0;
    }
    chunk->size = 0;
    return 1;
}

void get_repo_info(int argc, char **argv, char *user, char *repo)
{
    if (argc < 3)
        exit(84);
    strcpy(user, argv[1]);
    strcpy(repo, argv[2]);
}

curl_handle_t *init_curl_session(
    response_data_t *chunk, const char *url)
{
    curl_handle_t *handle;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    handle = curl_easy_init();
    if (!handle) {
        fprintf(stderr, "Curl init failed\n");
        free(chunk->data);
        curl_global_cleanup();
        return NULL;
    }
    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_USERAGENT, "MyGitHubCLI/1.0");
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *) chunk);
    return handle;
}
