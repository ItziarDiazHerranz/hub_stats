/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** utils
*/

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/commits.h"
#include "../include/github.h"

void cleanup_and_exit(CURL *curl, response_data_t *chunk, int code)
{
    if (curl)
        curl_easy_cleanup(curl);
    if (chunk && chunk->data)
        free(chunk->data);
    curl_global_cleanup();
    exit(code);
}

curl_handle_t *init_curl_handle(response_data_t *chunk, const char *url)
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
