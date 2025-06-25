/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** error
*/

#include <curl/curl.h>
#include <string.h>
#include <unistd.h>
#include "../include/github.h"

void write_error(const char *message)
{
    write(2, message, strlen(message));
}

static int configure_curl_for_head(CURL *curl, const char *url)
{
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "hub_stats");
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    return 0;
}

static int perform_head_request(CURL *curl, long *http_code)
{
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
        return 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, http_code);
    return 1;
}

int repository_exists(const char *user, const char *repo)
{
    CURL *curl = curl_easy_init();
    long http_code = 0;
    char url[1024];
    int success;

    if (!curl)
        return 0;
    snprintf(
        url, sizeof(url), "https://api.github.com/repos/%s/%s", user, repo);
    configure_curl_for_head(curl, url);
    success = perform_head_request(curl, &http_code);
    curl_easy_cleanup(curl);
    return success && http_code == 200;
}
