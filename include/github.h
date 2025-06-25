/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** github
*/

#ifndef INCLUDED_GITHUB_H
    #define INCLUDED_GITHUB_H

    #include <curl/curl.h>
    #include <jansson.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "commits.h"

typedef CURL curl_handle_t;
typedef struct repo_info_s {
    char *name;
    char user[256];
    char repo[256];
    char url[1024];
    char *desc;
    char *updated;
    char *default_branch;
    int stars;
    int forks;
    int issues;
    int commits;
} repo_info_t;

typedef struct fetch_context_s {
    const char *user;
    const char *repo;
    CURL *curl;
    response_data_t chunk;
    json_t *root;
    repo_info_t info;
    int commit_count;
} fetch_context_t;


void parse_and_display_json(const char *json_data, int commit_count);
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);
int init_chunk(response_data_t *chunk);
void get_repo_info(int argc, char **argv, char *user, char *repo);
curl_handle_t *init_curl_session(response_data_t *chunk, const char *url);
size_t handle_response(void *contents, size_t size, size_t nmemb, void *userp);
void fill_repo_fields(json_t *root, repo_info_t *info, int commit_count);
void free_repo_fields(repo_info_t *info);
void free_repo_info(repo_info_t *info);
void print_repo_info(repo_info_t *info, int commits);
void print_json_parse_error(json_error_t *error);
void print_help(void);
void print_label(const char *label);
char *build_repo_path(void);
int export_to_json(repo_info_t *info);
int export_to_csv(repo_info_t *info);
void fetch_and_display(const char *user, const char *repo, int commit_count);
int is_interactive(int argc);
int interactive_mode(char *user, char *repo, int max_len);
void print_repo_info(repo_info_t *info, int commits);
curl_handle_t *init_curl_handle(response_data_t *chunk, const char *url);
int repository_exists(const char *user, const char *repo);
void write_error(const char *msg);

#endif
