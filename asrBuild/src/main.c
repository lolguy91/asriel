#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "script.h"

char* path = ".";

int main(int argc, char** argv){
    if (argc >= 2){
        path = argv[1];
    }
    char* fullpath = malloc(strlen(path) + strlen("/build.lua") + 1);
    memset(fullpath,0,strlen(path) + strlen("/build.lua") + 1);
    strcpy(fullpath,path);
    strcat(fullpath,"/build.lua");
    printf("Build.lua Path: \"%s\"\n",fullpath);

    ab_runscript(fullpath,argc,argv);
}