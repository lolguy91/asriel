#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__

#include "stdbool.h"
#include "stdint.h"
#include <stdint.h>

//IMPORTANT: THE FOLLOWING STRUCTS ARE MOCKUPS

typedef struct {
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rsp;
    uint64_t rbp;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rip;
    uint64_t rflags;
    uint64_t cs;
    uint64_t fs;
    uint64_t gs;
    uint64_t ss;
} arch_state_t;

// not official, just made ChatGPT spit smth out while we dont have any specification for this
typedef enum{
    dev_type_null = 0,
    dev_type_block = 1,
    dev_type_char = 2,
    dev_type_fifo = 3,
    dev_type_socket = 4
} dev_type;

//END OF MOCKUPS

#define OM_NULL 0
#define OM_MAGIC_PATTERN_ALIVE 0x55
#define OM_MAGIC_PATTERN_DEAD 0xAA

#define OM_TYPE_THREAD 0
#define OM_TYPE_DEVICE 1
#define OM_TYPE_VFS_NODE 2
#define OM_TYPE_VFS_CHILD_PAGE 3
#define OM_TYPE_VFS_LONG_NAME 4

typedef struct {
    uint8_t magic_pattern;
    uint8_t type;
    uint16_t id;
} object_header_t;

typedef struct{
    char name[128];// name of the thread, aka the command that spawned it
    arch_state_t state; // arch specific, preprocessor macros do the job
    uint8_t state_flags;
    uint16_t argc;
    uintptr_t argv;
    uintptr_t env;

    uint16_t children[64];// OM ids for the children, 0 is null
} thread_t;

typedef struct{
    char name[8];
    dev_type type;
    char data[64];
} device_t;

typedef struct{
    char name[64];
    uint16_t long_name_id; // OM id of the long name, 0 is null
    uint16_t type_permissions; // first nibble is owner perm, second one is goup perm, 3rd one is other perm, 4th one is type
    uint16_t owner_uid;
    uint16_t owner_gid;
    uint64_t size;
    uint16_t children; // OM id of a "child page", 0 is null
} vfs_node_t;

typedef struct{
    uint16_t children[64]; // OM ids of the children, 0 is null
    uint16_t next; // OM id of the next child page, 0 is null
} vfs_child_page_t;

typedef struct{
    char name[64];
    uint16_t next; // OM id of the next long_name, 0 is null
} vfs_long_name_t;

typedef struct{
    uint8_t type;
    union{
        thread_t thread;
        device_t device;
        vfs_node_t vfs_node;
        vfs_child_page_t vfs_child_page;
        vfs_long_name_t vfs_long_name;
    } data;
} obj_to_insert_t;

// fucntions

/*
 * @brief: initializes the object manager
 * @return: true if successful, false if not
*/
bool object_manager_init();
/*
 * @brief: inserts an object into the object manager
 * @param obj: object to insert
 * @return: id of the inserted object
*/
uint16_t object_manager_insert(obj_to_insert_t obj);
/*
 * @brief: removes an object from the object manager
 * @param obj_id: id of the object to remove
 * @return: true if successful, false if not
*/
bool object_manager_remove(uint16_t obj_id);
/*
 * @brief: gets an object from the object manager
 * @param obj_id: id of the object to get
 * @return: the object
*/
char* object_manager_get(uint16_t obj_id);

#endif // __OBJECT_MANAGER_H__