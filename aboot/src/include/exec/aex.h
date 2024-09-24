#ifndef __AEX_H__
#define __AEX_H__

#include <stdint.h>
#include <common.h>

typedef struct aex_segment {
    uint8_t flags;
    uint64_t base;
    uint64_t size;
    union {
        uint32_t offset;
        uint8_t prefill_1;
        uint16_t prefill_2;
        uint32_t prefill_3;
    };
} aex_segment_t;

typedef struct aex_header {
    uint32_t magic;
    uint8_t flags;
    uint64_t entry_point;
    uint32_t crc32;
    uint8_t segments;
    uint16_t size_st;
} aex_header_t;

typedef struct aex_executable {
    aex_header_t header;
    
} aex_executable_t;



#endif // __AEX_H__