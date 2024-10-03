#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logger.h"
#include "util.h"

#include "script.h"

char* path = ".";

int main(int argc, char** argv){
    if (argc >= 2){
        path = argv[1];
    }

    if(chdir(path) != 0){
        log_err("Failed to change directory to the project path",__CUR_LOC);
        exit(EXIT_FAILURE);
    }

    //check if build.lua exists
    if (access("build.lua", F_OK) == 0) {
        ab_runscript("build.lua",argc,argv);
    }

    return 0;
}