/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** count
*/

#include <curl/curl.h>
#include "../include/commits.h"
#include "../include/github.h"

int count_commits_in_json(json_t *root)
{
    if (!json_is_array(root))
        return 0;
    return json_array_size(root);
}

static CURL *prepare_commit_request(const char *url, response_data_t *chunk)
{
    CURL *curl = curl_easy_init();

    if (!curl)
        return NULL;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "hub_stats/1.0");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) chunk);
    return curl;
}

static json_t *get_commit_json(CURL *curl, response_data_t *chunk)
{
    CURLcode res = curl_easy_perform(curl);
    json_error_t error;
    json_t *root;

    if (res != CURLE_OK)
        return NULL;
    root = json_loads(chunk->data, 0, &error);
    return root;
}

static int clean_and_return(
    response_data_t *chunk, CURL *curl, json_t *root, int count)
{
    if (root)
        json_decref(root);
    if (curl)
        curl_easy_cleanup(curl);
    if (chunk && chunk->data)
        free(chunk->data);
    return count;
}

int fetch_commit_count(const char *user, const char *repo)
{
    char url[1024];
    response_data_t chunk;
    json_t *root = NULL;
    int count = 0;
    CURL *curl;

    snprintf(url, sizeof(url),
        "https://api.github.com/repos/%s/%s/commits?per_page=100", user, repo);
    if (init_chunk(&chunk) != 0)
        return 0;
    curl = prepare_commit_request(url, &chunk);
    if (!curl)
        return clean_and_return(&chunk, NULL, NULL, 0);
    root = get_commit_json(curl, &chunk);
    if (!root)
        return clean_and_return(&chunk, curl, NULL, 0);
    count = count_commits_in_json(root);
    return clean_and_return(&chunk, curl, root, count);
}
