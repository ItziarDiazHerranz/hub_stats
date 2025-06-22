/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** github
*/

#ifndef INCLUDED_GITHUB_H
    #define INCLUDED_GITHUB_H

    #include <curl/curl.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "commits.h"
    #include <jansson.h>

typedef CURL curl_handle_t;

typedef struct repo_info_s {
    const char *desc;
    int stars;
    int forks;
    int issues;
    const char *updated;
    int commits;
    char user[256];
    char repo[256];
    char url[1024];
} repo_info_t;

void parse_and_display_json(const char *json_data, int commit_count);
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);
int init_chunk(response_data_t *chunk);
void get_repo_info(int argc, char **argv, char *user, char *repo);
curl_handle_t *init_curl_session(response_data_t *chunk, const char *url);
void handle_response(
    CURL *curl, response_data_t *chunk, const repo_info_t *info);
void fill_repo_fields(json_t *root, repo_info_t *info, int commit_count);
void free_repo_fields(repo_info_t *info);
void print_repo_info(const repo_info_t *info);
void print_json_parse_error(const char *json_data, json_error_t *error);

#endif
