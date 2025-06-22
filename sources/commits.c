/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** commits
*/

#include "../include/commits.h"
#include <curl/curl.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t real_size = size * nmemb;
    response_data_t *mem = (response_data_t *) userp;
    char *ptr = realloc(mem->data, mem->size + real_size + 1);

    if (!ptr) {
        fprintf(stderr, "Not enough memory (realloc returned NULL)\n");
        return 0;
    }
    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, real_size);
    mem->size += real_size;
    mem->data[mem->size] = '\0';
    return real_size;
}

void *init_commit_chunk(response_data_t *chunk)
{
    chunk->data = malloc(1);
    if (!chunk->data)
        return NULL;
    chunk->size = 0;
    return chunk->data;
}

static int parse_commit_count(const char *data)
{
    json_error_t error;
    json_t *root = json_loads(data, 0, &error);
    int count = -1;

    if (root && json_is_array(root)) {
        count = json_array_size(root);
        json_decref(root);
    }
    return count;
}

static void setup_curl(CURL *curl, const char *url, response_data_t *chunk)
{
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "MyGitHubCLI/1.0");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) chunk);
}

int fetch_commit_count(const char *user, const char *repo)
{
    char url[1024];
    response_data_t chunk;
    int count = -1;
    CURL *curl;

    snprintf(url, sizeof(url), "https://api.github.com/repos/%s/%s/commits",
        user, repo);
    curl = curl_easy_init();
    if (!curl || !init_commit_chunk(&chunk))
        return -1;
    setup_curl(curl, url, &chunk);
    if (curl_easy_perform(curl) == CURLE_OK)
        count = parse_commit_count(chunk.data);
    curl_easy_cleanup(curl);
    free(chunk.data);
    return count;
}
