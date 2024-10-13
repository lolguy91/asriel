#include <stdint.h>
#include <stdio.h>
#include "object_manager.h"

int main(int argc, char *argv[]) {
    if(!om_init()){
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
    uint16_t id = om_insert(obj);

    printf("Inserted object at id %d\n", id);

    char* objdat = om_get(id);

    printf("Got object at %p\n", objdat);

    object_header_t* h = (object_header_t*)objdat;
    printf("Magic: 0x%4x\n", h->magic_pattern);
    printf("Type:  0x%4x\n", h->type);
    printf("ID:    0x%4x\n", h->id);

    dev = (device_t){
        .name = "test2",
        .type = 0,
    };
    obj = (obj_to_insert_t){
        .type = 0,
        .data.device = dev
    };
    id = om_insert(obj);

    printf("Inserted object at id %d\n", id);

    objdat = om_get(id);

    printf("Got object at %p\n", objdat);

    h = (object_header_t*)objdat;
    printf("Magic: 0x%4x\n", h->magic_pattern);
    printf("Type:  0x%4x\n", h->type);
    printf("ID:    0x%4x\n", h->id);

    dev = (device_t){
        .name = "test2",
        .type = 0,
    };
    obj = (obj_to_insert_t){
        .type = 0,
        .data.device = dev
    };
    id = om_insert(obj);

    printf("Inserted object at id %d\n", id);

    objdat = om_get(id);

    printf("Got object at %p\n", objdat);

    h = (object_header_t*)objdat;
    printf("Magic: 0x%4x\n", h->magic_pattern);
    printf("Type:  0x%4x\n", h->type);
    printf("ID:    0x%4x\n", h->id);

    dev = (device_t){
        .name = "test2",
        .type = 0,
    };
    obj = (obj_to_insert_t){
        .type = 0,
        .data.device = dev
    };
    id = om_insert(obj);

    printf("Inserted object at id %d\n", id);

    objdat = om_get(id);

    printf("Got object at %p\n", objdat);

    h = (object_header_t*)objdat;
    printf("Magic: 0x%4x\n", h->magic_pattern);
    printf("Type:  0x%4x\n", h->type);
    printf("ID:    0x%4x\n", h->id);

    dev = (device_t){
        .name = "test2",
        .type = 0,
    };
    obj = (obj_to_insert_t){
        .type = 0,
        .data.device = dev
    };
    id = om_insert(obj);

    printf("Inserted object at id %d\n", id);

    objdat = om_get(id);

    printf("Got object at %p\n", objdat);

    h = (object_header_t*)objdat;
    printf("Magic: 0x%4x\n", h->magic_pattern);
    printf("Type:  0x%4x\n", h->type);
    printf("ID:    0x%4x\n", h->id);

    dev = (device_t){
        .name = "test2",
        .type = 0,
    };
    obj = (obj_to_insert_t){
        .type = 0,
        .data.device = dev
    };
    id = om_insert(obj);

    printf("Inserted object at id %d\n", id);

    objdat = om_get(id);

    printf("Got object at %p\n", objdat);

    h = (object_header_t*)objdat;
    printf("Magic: 0x%4x\n", h->magic_pattern);
    printf("Type:  0x%4x\n", h->type);
    printf("ID:    0x%4x\n", h->id);

    om_remove(id);

    dev = (device_t){
        .name = "test2",
        .type = 0,
    };
    obj = (obj_to_insert_t){
        .type = 0,
        .data.device = dev
    };
    id = om_insert(obj);

    printf("Inserted object at id %d\n", id);

    objdat = om_get(id);

    printf("Got object at %p\n", objdat);

    h = (object_header_t*)objdat;
    printf("Magic: 0x%4x\n", h->magic_pattern);
    printf("Type:  0x%4x\n", h->type);
    printf("ID:    0x%4x\n", h->id);

    dev = (device_t){
        .name = "test2",
        .type = 0,
    };
    obj = (obj_to_insert_t){
        .type = 0,
        .data.device = dev
    };
    id = om_insert(obj);

    printf("Inserted object at id %d\n", id);

    objdat = om_get(id);

    printf("Got object at %p\n", objdat);

    h = (object_header_t*)objdat;
    printf("Magic: 0x%4x\n", h->magic_pattern);
    printf("Type:  0x%4x\n", h->type);
    printf("ID:    0x%4x\n", h->id);

        dev = (device_t){
        .name = "test2",
        .type = 0,
    };
    obj = (obj_to_insert_t){
        .type = 0,
        .data.device = dev
    };
    id = om_insert(obj);

    printf("Inserted object at id %d\n", id);

    objdat = om_get(id);

    printf("Got object at %p\n", objdat);

    h = (object_header_t*)objdat;
    printf("Magic: 0x%4x\n", h->magic_pattern);
    printf("Type:  0x%4x\n", h->type);
    printf("ID:    0x%4x\n", h->id);

    dev = (device_t){
        .name = "test2",
        .type = 0,
    };
    obj = (obj_to_insert_t){
        .type = 0,
        .data.device = dev
    };
    id = om_insert(obj);

    printf("Inserted object at id %d\n", id);

    objdat = om_get(id);

    printf("Got object at %p\n", objdat);

    h = (object_header_t*)objdat;
    printf("Magic: 0x%4x\n", h->magic_pattern);
    printf("Type:  0x%4x\n", h->type);
    printf("ID:    0x%4x\n", h->id);

    return 0;
}