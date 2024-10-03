#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "util.h"
#include "logger.h"
#include "src_discovery.h"

/*
 * @brief Checks if `a` ends with `b`
 * @param `a` The string being checked
 * @param `b` The string that must be at the end of `a`
 * @return `1` if the end of `a` is the same as the end of `b`, `0` otherwise
*/
bool cmp_end(const char *a, const char *b) {
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);

    if (len_b > len_a) {
        return 0;
    }

    return strcmp(a + len_a - len_b, b) == 0;
}

/*
 * @brief Concatenates `path` and `filename`
 * @param `path` The path to concatenate
 * @param `filename` The filename to concatenate
 * @return The concatenated path
*/
char *concat_path(const char *path, const char *filename) {
    size_t len_path = strlen(path);
    size_t len_filename = strlen(filename);

    bool is_trailing_slash = path[len_path - 1] == '/';

    char *full_path = (char *)malloc(len_path + len_filename + 1 + is_trailing_slash);
    if (!full_path) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (is_trailing_slash) {
        sprintf(full_path, "%s%s", path, filename);
    } else {
        sprintf(full_path, "%s/%s", path, filename);
    }

    return full_path;
}

/*
 * @brief Gets all files in `src_dirs` with extension `src_extension`
 * @param `src_dirs` The directories to search in
 * @param `src_extension` The extension of the files to search for
 * @return An array of strings containing the paths of the files
*/
char** get_files(char** src_dirs,char* src_extension){
    int num_files = 0;
    int capacity = 10;
    char** files = malloc(capacity * sizeof(char*));
    memset(files, 0, capacity * sizeof(char*));

    if(strchr(src_extension,'.') == NULL){
        char* tmp = malloc(strlen(src_extension) + 2);
        strcpy(tmp,".");
        strcat(tmp,src_extension);
        free(src_extension);
        src_extension = tmp;
    }

    for(int i = 0; src_dirs[i] != NULL; i++){
        DIR* dir = opendir(src_dirs[i]);
        if (dir == NULL) {
            log_err("Failed to open directory", src_dirs[i]);
            continue;
        }

        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                char* full_path = concat_path(src_dirs[i], entry->d_name);
                if (cmp_end(full_path, src_extension)) {
                    if (num_files == capacity) {
                        capacity *= 2;
                        files = realloc(files, capacity * sizeof(char*));
                    }
                    files[num_files] = full_path;
                    num_files++;
                }
            }
        }

        closedir(dir);
    }

    return files;
}
