/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** fetch
*/

#include <curl/curl.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/github.h"
#include "../include/ansi_colors.h"

void free_repo_info(repo_info_t *info)
{
    if (!info)
        return;
    if (info->desc)
        free((char *) info->desc);
    if (info->updated)
        free((char *) info->updated);
    if (info->default_branch)
        free((char *) info->default_branch);
}

void print_repo_info(repo_info_t *info, int commits)
{
    printf("%sRepo:%s%s/%s\n", CYAN, RESET, info->user, info->repo);
    printf("%sURL:%s%s\n", CYAN, RESET, info->url);
    printf(
        "%sDescription:%s%s\n", CYAN, RESET, info->desc ? info->desc : "N/A");
    printf("%sLast updated:%s%s\n", CYAN, RESET,
        info->updated ? info->updated : "unknown");
    printf("%sBranch:%s%s\n", CYAN, RESET,
        info->default_branch ? info->default_branch : "main");
    printf("%sStars:%s%d\n", CYAN, RESET, info->stars);
    printf("%sForks:%s%d\n", CYAN, RESET, info->forks);
    printf("%sIssues:%s%d\n", CYAN, RESET, info->issues);
    printf("%sCommits:%s%d\n", CYAN, RESET, commits);
    printf("---\n");
}

int fetch_commits(
    const char *user, const char *repo, const char *branch, int commit_count)
{
    (void) user;
    (void) repo;
    (void) branch;
    (void) commit_count;
    printf("Fetching commits...\n");
    return 0;
}

static int setup_curl(CURL **curl, response_data_t *chunk, const char *url)
{
    *curl = curl_easy_init();
    if (!*curl) {
        fprintf(stderr, "%sError initializing curl%s\n", RED, RESET);
        return 84;
    }
    if (init_chunk(chunk) == 84) {
        fprintf(stderr, "%sError allocating memory for chunk%s\n", RED, RESET);
        curl_easy_cleanup(*curl);
        return 84;
    }
    curl_easy_setopt(*curl, CURLOPT_URL, url);
    curl_easy_setopt(*curl, CURLOPT_USERAGENT, "hub_stats-app");
    curl_easy_setopt(*curl, CURLOPT_WRITEFUNCTION, handle_response);
    curl_easy_setopt(*curl, CURLOPT_WRITEDATA, (void *) chunk);
    return 0;
}

static json_t *perform_request(CURL *curl, response_data_t *chunk)
{
    CURLcode res = curl_easy_perform(curl);
    json_error_t error;
    json_t *root;

    if (res != CURLE_OK) {
        fprintf(stderr, "%sRequest failed:%s %s\n", RED, RESET,
            curl_easy_strerror(res));
        return NULL;
    }
    root = json_loads(chunk->data, 0, &error);
    if (!root)
        fprintf(
            stderr, "%sFailed to parse JSON:%s %s\n", RED, RESET, error.text);
    return root;
}

static void handle_commits_and_cleanup(fetch_context_t *ctx)
{
    print_repo_info(&ctx->info, ctx->commit_count);
    if (ctx->info.default_branch) {
        fetch_commits(
            ctx->user, ctx->repo, ctx->info.default_branch, ctx->commit_count);
    } else {
        fprintf(stderr,
            "%sWarning:%s default_branch is NULL, skipping commits\n", YELLOW,
            RESET);
    }
    free_repo_info(&ctx->info);
    json_decref(ctx->root);
    free(ctx->chunk.data);
    curl_easy_cleanup(ctx->curl);
}

static int setup_and_fetch_root_ctx(fetch_context_t *ctx)
{
    char url[512];

    snprintf(url, sizeof(url), "https://api.github.com/repos/%s/%s", ctx->user,
        ctx->repo);
    if (setup_curl(&ctx->curl, &ctx->chunk, url) == 84)
        return 84;
    ctx->root = perform_request(ctx->curl, &ctx->chunk);
    if (!ctx->root) {
        curl_easy_cleanup(ctx->curl);
        free(ctx->chunk.data);
        return 84;
    }
    return 0;
}

void fetch_and_display(const char *user, const char *repo, int commit_count)
{
    fetch_context_t ctx = {0};

    ctx.user = user;
    ctx.repo = repo;
    ctx.commit_count = commit_count;
    if (setup_and_fetch_root_ctx(&ctx) == 84)
        return;
    fill_repo_fields(ctx.root, &ctx.info, ctx.commit_count);
    handle_commits_and_cleanup(&ctx);
}
