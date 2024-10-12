#include "object_manager.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t object_memory_size = 0;
char* object_memory = NULL;

char* write_ptr = NULL;
char* max_ptr = NULL;
uint16_t cur_obj_id = 0;
uint32_t room = 0;

#define OM_SMALLEST_OBJ_SIZE sizeof(vfs_long_name_t)
#define OM_MAX_TYPE 5

static const uint32_t type2size[] = {
    sizeof(thread_t),
    sizeof(device_t),
    sizeof(vfs_node_t),
    sizeof(vfs_long_name_t),
    sizeof(vfs_child_page_t), 
};

bool object_manager_init() {
    object_memory_size = 0x1000; // starting size is 4kb
    object_memory = (char*)malloc(object_memory_size);
    write_ptr = object_memory;
    max_ptr = object_memory;
    cur_obj_id = 1; //0 is invalid
    room = 0xffffff;

    if(object_memory == NULL) {
        return false;
    }
    memset(object_memory, 0xff, 0x1000);

    return true;
}

uint16_t object_manager_insert(obj_to_insert_t obj) {
    if(room < type2size[obj.type] + sizeof(object_header_t) || object_memory_size < type2size[obj.type] + sizeof(object_header_t)) {
        //TODO: handle not enough room
        return 0xffff;
    }

    // The header starts with the magic pattern on purpuse, the (currently TODO) no room handling will find dead objects
    object_header_t h = {
        .magic_pattern = OM_MAGIC_PATTERN_ALIVE,
        .type = obj.type,
        .id = cur_obj_id
    };
    *((object_header_t*)write_ptr) = h;
    write_ptr += sizeof(object_header_t);

    memcpy(write_ptr, &obj.data, type2size[obj.type]);
    room -= type2size[obj.type] + sizeof(object_header_t);
    write_ptr = object_memory + object_memory_size;

    if (write_ptr > max_ptr) {
        max_ptr = write_ptr;
    }

    return cur_obj_id;
}

char* object_manager_get(uint16_t obj_id) {
    char* read_ptr = object_memory + OM_SMALLEST_OBJ_SIZE * (obj_id - 1);
    if(read_ptr >= max_ptr) {
        return NULL;
    }
    while(read_ptr < max_ptr) {
        object_header_t h = *((object_header_t*)read_ptr);
        if(h.magic_pattern == OM_MAGIC_PATTERN_ALIVE && h.id == obj_id && h.type < OM_MAX_TYPE) {
            return read_ptr;
        }
        read_ptr++;
    }

    return NULL;
}

bool object_manager_remove(uint16_t obj_id) {
    char* obj = object_manager_get(obj_id);
    if(obj == NULL) {
        return false;
    }

    // mark the object as dead, this means insertions can overwrite it, and object_manager_get will ignore it
    ((object_header_t*)obj)->magic_pattern = OM_MAGIC_PATTERN_DEAD;

    // if you delete something before the write pointer, you have to update the write pointer
    // this is so the space left from the deletion can be reused
    if(obj < write_ptr) {
        write_ptr = obj;
    }

    return true;
}