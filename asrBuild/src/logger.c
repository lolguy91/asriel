#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void get_timestamp(char* buffer, size_t buffer_size) {
    time_t now = time(NULL);
    struct tm* tstruct = localtime(&now);
    strftime(buffer, buffer_size, "[%Y/%m/%d] [%H:%M:%S]", tstruct);
}

void log_info(const char* message,const char* location) {
    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));
    if (message != NULL) {
        printf("\e[1m%s [%s] [INFO] - %s\e[0m\n", timestamp,location,message);
    } else {
        printf("\e[1;31m%s [%s] [ERR=] - logging a nil value or a table is unsupported\n\e[0m",timestamp,location);
    }
}

void log_err(const char* message,const char* location) {
    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));
    if (message != NULL) {
        printf("\e[1;31m%s [%s] [ERR=] - %s\n\e[0m", timestamp,location,message);
    } else {
        printf("\e[1;31m%s [%s] [ERR=] - logging a nil value or a table is unsupported\n\e[0m",timestamp,location);
    }
}