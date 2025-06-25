/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** branch
*/

#include <curl/curl.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/commits.h"
#include "../include/github.h"

static char *parse_branch_from_json(const char *json_data)
{
    json_error_t error;
    json_t *root;
    json_t *branch;
    const char *branch_name;
    char *result;

    root = json_loads(json_data, 0, &error);
    branch = json_object_get(root, "default_branch");
    branch_name = json_string_value(branch);
    if (!root || !json_is_object(root)) {
        json_decref(root);
        return NULL;
    }
    result = branch_name ? strdup(branch_name) : NULL;
    json_decref(root);
    return result;
}

static int is_response_valid(CURL *curl, response_data_t *chunk)
{
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK || chunk->size == 0) {
        free(chunk->data);
        curl_easy_cleanup(curl);
        return 0;
    }
    return 1;
}

static CURL *init_curl_for_branch(const char *url, response_data_t *chunk)
{
    CURL *curl = curl_easy_init();

    if (!curl)
        return NULL;
    chunk->data = malloc(1);
    chunk->size = 0;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT,
        "hub_stats_app (https://github.com/ItziarDiazHerranz/hub_stats)");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, chunk);
    return curl;
}

char *get_default_branch(const char *user, const char *repo)
{
    char url[1024];
    response_data_t chunk;
    CURL *curl;
    char *result;

    snprintf(url, sizeof(url),
        "https://api.github.com/repos/%s/%s", user, repo);
    curl = init_curl_for_branch(url, &chunk);
    if (!curl || !is_response_valid(curl, &chunk))
        return NULL;
    result = parse_branch_from_json(chunk.data);
    free(chunk.data);
    curl_easy_cleanup(curl);
    return result;
}
