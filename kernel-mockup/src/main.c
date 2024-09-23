#include <stdio.h>
#include "object_manager.h"

int main(int argc, char *argv[]) {
    if(!object_manager_init()){
        printf("Failed to initialize object manager\n");
        return 1;
    }

    printf("Object manager initialized\n");
    device_t dev = {
        .name = "test",
        .type = 0,
    };
    obj_to_insert_t obj = {
        .type = 0,
        .data.device = dev
    };
    object_manager_insert(obj);

    return 0;
}