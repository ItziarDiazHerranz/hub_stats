/*
** EPITECH PROJECT, 2025
** hub_stats
** File description:
** commits
*/

#include "../include/commits.h"
#include "../include/github.h"
#include <curl/curl.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    response_data_t *mem = (response_data_t *)userp;
    char *ptr = realloc(mem->data, mem->size + realsize + 1);

    if (!ptr)
        return 0;
    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->data[mem->size] = 0;
    return realsize;
}
