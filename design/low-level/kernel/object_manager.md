# The Object Manager

types of objects:

1. thread:
```c
typedef struct{
    char name[128];// name of the thread, aka the command that spawned it
    arch_state_t state; // arch specific, preprocessor macros do the job
    uint8_t state_flags;
    uint16_t argc;
    uintptr_t argv;
    uintptr_t env;

    uint16_t children[64];// OM ids for the children, 0 is null
} thread_t;
```

2. device:
```c
typedef struct{
    char name[8];
    dev_type type;
    char data[64];
} device_t;
```


3. vfs_node:
```c
typedef struct{
    char name[64];
    uint16_t long_name_id; // OM id of the long name, 0 is null
    uint16_t type_permissions; // first nibble is owner perm, second one is goup perm, 3rd one is other perm, 4th one is type
    uint16_t owner_uid;
    uint16_t owner_gid;
    uint64_t size;
    uint16_t children; // OM id of a "child page", 0 is null
} vfs_node_t;
```

4. vfs_child_page:
```c
typedef struct{
    uint16_t children[64]; // OM ids of the children, 0 is null
    uint16_t next; // OM id of the next child page, 0 is null
} vfs_child_page_t;
```
5. vfs_long_name:
```c
typedef struct{
    char name[64];
    uint16_t next; // OM id of the next long_name, 0 is null
} vfs_long_name_t;
```