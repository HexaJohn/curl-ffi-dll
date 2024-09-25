// CurlConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "pch.h"

#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include <string>
#include "console.h"
#include "dll7.h"

CONSOLE::CONSOLE() {}

struct ExpandedPolicy CONSOLE::create_policy(
    char* key,
    char* x_amz_credential,
    char* x_amz_algorithm,
    char* x_amz_date,
    char* encoded,
    char* x_amz_signature,
    char* x_amz_security_token,
    char* x_amz_storage_class)
{
    struct ExpandedPolicy policy;
    policy.key = key;
    policy.x_amz_credential = x_amz_credential;
    policy.x_amz_algorithm = x_amz_algorithm;
    policy.x_amz_date = x_amz_date;
    policy.encoded = encoded;
    policy.x_amz_signature = x_amz_signature;
    policy.x_amz_security_token = x_amz_security_token;
    policy.x_amz_storage_class = x_amz_storage_class;

    return policy;
}

static std::string readBuffer;

static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

static size_t read_callback(char* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t retcode;
    unsigned long nread;
    retcode = fread(ptr, size, nmemb, stream);

    if (retcode > 0) {
        nread = (unsigned long)retcode;
        fprintf(stderr, "Read %lu bytes\n", nread);
    }

    return retcode;
}

void add_mime_part(curl_mime* mime, const char* name, const char* data) {
    curl_mimepart* part = curl_mime_addpart(mime);
    curl_mime_name(part, name);
    curl_mime_data(part, data, CURL_ZERO_TERMINATED);
}

int CONSOLE::run_segment(
    char* key,
    char* x_amz_credential,
    char* x_amz_algorithm,
    char* x_amz_date,
    char* encoded,
    char* x_amz_signature,
    char* x_amz_security_token,
    char* x_amz_storage_class,
    char* bucket_key,
    char* file_path)
{
    std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();

    struct ExpandedPolicy policy = create_policy(
    key,
    x_amz_credential,
    x_amz_algorithm,
    x_amz_date,
    encoded,
    x_amz_signature,
    x_amz_security_token,
    x_amz_storage_class);
    
    printf("starting curl test");
    // Curl vars
    CURL* curl;
    CURLcode res;
    curl_mime* mime;
    curl_mimepart* part;
    curl_slist *headers = {};
    errno_t error_code;

    // File vars
    FILE *fs;
    struct stat file_info;
    _off_t file_size;

    // Vars for testing
    // TODO: Make these args for actual use
    const char* file_name = file_path;
    char url[] = "sanitized.s3-us-east-2.amazonaws.com";
    char request_url[256];
    std::snprintf(request_url, 256, "sanitized.s3-us-east-2.amazonaws.com/%s", bucket_key);

    // url = "https://sanitized.s3-us-east-2.amazonaws.com";
    // Confirm the url isn't malformed
    printf(request_url);

    // Open the file
    error_code = fopen_s(&fs, file_name, "r");
    if (error_code != 0) {
        printf("error opening file");
        // TODO: Handle errors
    }

    // init curl
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        // Initialize the MIME structure
        mime = curl_mime_init(curl);

        // Add all necessary fields using a helper function
        add_mime_part(mime, "key", policy.key);
        add_mime_part(mime, "x-amz-credential", policy.x_amz_credential);
        add_mime_part(mime, "x-amz-algorithm", policy.x_amz_algorithm);
        add_mime_part(mime, "x-amz-date", policy.x_amz_date);
        add_mime_part(mime, "policy", policy.encoded);
        add_mime_part(mime, "x-amz-signature", policy.x_amz_signature);
        add_mime_part(mime, "x-amz-security-token", policy.x_amz_security_token);
        add_mime_part(mime, "x-amz-storage-class", policy.x_amz_storage_class);

        // Add file part
        part = curl_mime_addpart(mime);
        curl_mime_name(part, "file");
        curl_mime_filedata(part, file_name);

        // Set curl options
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check response
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed (%d): %s\n", res, curl_easy_strerror(res));
            return 0;
        }

        // Clean up
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        curl_mime_free(mime);  // Clean up mime object to prevent memory leak
    }

    
    _fcloseall(); /* close the local file(s) */
    curl_global_cleanup();

    const char* str = readBuffer.c_str();

    std::chrono::steady_clock::time_point finish = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds diff = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
    int ms = diff.count();

    return ms;
    //return output;
}