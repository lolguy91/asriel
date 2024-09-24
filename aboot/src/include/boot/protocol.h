#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <stdint.h>
#include <common.h>

// Substructs

typedef struct framebuffer {
    uint32_t phys_addr;
    uint16_t width;
    uint16_t height;
    uint16_t pitch;
    uint8_t  bpp;
    uint8_t  red_bits;
    uint8_t  green_bits;
    uint8_t  blue_bits;
    uint8_t  channel_order;
} __attribute__((packed)) framebuffer_t;

typedef struct memmap_entry {
    uint8_t type;
    uintptr_t start;
    uintptr_t size;
} memmap_entry_t;

struct boot_info {
    const uint16_t memmap_entry_count;
    const uintptr_t memmap;

    const uint16_t driver_ramfs_size;
    const uintptr_t driver_ramfs;

    const uintptr_t rsdt;

    const char boot_tag[4];

    const framebuffer_t fb;
} __attribute__((packed));

#endif // __PROTOCOL_H__