/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** logic
*/

#include "../include/commits.h"
#include "../include/github.h"

void check_json_errors(const response_data_t *chunk, json_t *root)
{
    if (!chunk || !chunk->data || strlen(chunk->data) == 0) {
        write_error("Error: Empty response from GitHub.\n");
        exit(84);
    }
    if (!root) {
        write_error("Error: Failed to parse JSON.\n");
        exit(84);
    }
}

void handle_success_response(
    const response_data_t *chunk, const repo_info_t *info)
{
    json_error_t error;
    json_t *root = json_loads(chunk->data, 0, &error);
    json_t *message = json_object_get(root, "message");
    int commit_count = fetch_commit_count(info->user, info->repo);
    const char *msg = json_string_value(message);

    check_json_errors(chunk, root);
    if (message && json_is_string(message)) {
        if (strcmp(msg, "Not Found") == 0) {
            json_decref(root);
            write_error("Error: No such repository or user.\n");
            exit(84);
        }
    }
    parse_and_display_json(chunk->data, commit_count);
    json_decref(root);
}

size_t handle_response(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t real_size = size * nmemb;
    response_data_t *mem = (response_data_t *) userp;
    char *ptr;

    ptr = realloc(mem->data, mem->size + real_size + 1);
    if (!ptr)
        return 0;
    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, real_size);
    mem->size += real_size;
    mem->data[mem->size] = 0;
    return real_size;
}
