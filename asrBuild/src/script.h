#ifndef __SCRIPT_H__
#define __SCRIPT_H__
#include <stdbool.h>
#include <stdint.h>

// config struct
typedef struct config {
    char *compiler_path;
    char *src_dir;
    char **include_dirs;
    char **lib_dirs;
    char *linker_path;
    char **linker_flags;
    char **compiler_flags;
} config_t;

bool ab_runscript(const char* path,int argc,char** argv);

#endif // __SCRIPT_H__