#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "script.h"
#include "logger.h"

char* path = ".";
#define STRINGIFY(x) #x

//black magic for the preprocessor to not just spit out main.c:__LINE__
#define TOSTRING(x) STRINGIFY(x)

#define __CUR_LOC (__FILE__ ":" TOSTRING(__LINE__))

int main(int argc, char** argv){
    if (argc == 2){
        path = argv[1];
    }else if (argc > 2){
        log_err("extranious arguments in the builds command", __CUR_LOC);
        exit(1);
    }
    char* fullpath = malloc(strlen(path) + strlen("/build.lua") + 1);
    memset(fullpath,0,strlen(path) + strlen("/build.lua") + 1);
    strcpy(fullpath,path);
    strcat(fullpath,"/build.lua");
    printf("Build.lua Path: \"%s\"\n",fullpath);

    ab_runscript(fullpath);
}