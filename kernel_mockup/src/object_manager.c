#include "object_manager.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

uint32_t object_memory_size = 0;
char* object_memory = NULL;

char* write_ptr = NULL;
char* max_ptr = NULL;
uint16_t cur_obj_id = 0;
uint32_t room = 0;

#define OM_SMALLEST_OBJ_SIZE sizeof(vfs_long_name_t)
#define OM_MAX_TYPE 4

static const uint32_t type2size[] = {
    sizeof(thread_t),
    sizeof(device_t),
    sizeof(vfs_node_t),
    sizeof(vfs_long_name_t),
    sizeof(vfs_child_page_t), 
};

bool om_init() {
    object_memory_size = 0x1000; // starting size is 4kb
    object_memory = (char*)malloc(object_memory_size);
    write_ptr = object_memory;
    max_ptr = object_memory;
    cur_obj_id = 1; //0 is invalid
    room = object_memory_size;

    if(object_memory == NULL) {
        return false;
    }
    memset(object_memory, 0xff, 0x1000);

    return true;
}

uint16_t om_insert(obj_to_insert_t obj) {
    recheck:
    if(room < type2size[obj.type] + sizeof(object_header_t)) {
        if((write_ptr - object_memory) + type2size[obj.type] + sizeof(object_header_t) >= object_memory_size){
            object_memory_size += 0x1000;
            object_memory = (char*)realloc(object_memory, object_memory_size);
        }
        while(write_ptr <= object_memory + object_memory_size) {
            object_header_t* h = (object_header_t*)write_ptr;
            if(write_ptr > max_ptr) {
                room = object_memory_size - (write_ptr - object_memory);
                goto recheck;
            }
            if(h->magic_pattern == OM_MAGIC_PATTERN_DEAD) {
                room = type2size[h->type] + sizeof(object_header_t);
                goto recheck;
            }
            write_ptr++;
        }

        return 0xffff;
    }

    // The header starts with the magic pattern on purpuse, the no room handling will find dead objects
    object_header_t h = {
        .magic_pattern = OM_MAGIC_PATTERN_ALIVE,
        .type = obj.type,
        .id = cur_obj_id
    };
    ((object_header_t*)write_ptr)[0] = h;
    room -= sizeof(object_header_t);
    write_ptr += sizeof(object_header_t);

    memcpy(write_ptr, &obj.data, type2size[obj.type]);
    room -= type2size[obj.type];
    write_ptr += type2size[obj.type];

    if (write_ptr > max_ptr) {
        max_ptr = write_ptr;
    }

    cur_obj_id++;
    return cur_obj_id - 1;
}

char* om_get(uint16_t obj_id) {
    char* read_ptr = object_memory + (OM_SMALLEST_OBJ_SIZE * (obj_id - 1));
    
    printf("Read ptr: %p\n", read_ptr);
    printf("Max ptr: %p\n", max_ptr);

    if(read_ptr >= max_ptr) {
        return (char*)0xdeadbeef;
    }
    while(read_ptr <= max_ptr) {
        object_header_t* h = (object_header_t*)read_ptr;
        if(h->magic_pattern == OM_MAGIC_PATTERN_ALIVE && h->id == obj_id && h->type < OM_MAX_TYPE) {
            return read_ptr;
        }
        read_ptr++;
    }

    return (char*)0xdeadb00b;
}

bool om_remove(uint16_t obj_id) {
    char* obj = om_get(obj_id);
    if(obj == NULL) {
        return false;
    }

    //mark the object as dead, this means insertions can overwrite it, and object_manager_get will ignore it
    ((object_header_t*)obj)->magic_pattern = OM_MAGIC_PATTERN_DEAD;

    //this is so the space left from the deletion can be reused
    write_ptr = obj;

    return true;
}