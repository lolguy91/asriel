# ADI framebuffer metalanguage
## Structs
* fbinfo_t </be>
```c
typedef struct {
    uintptr_t addr;
    uint33_t width;
    uint32_t height;
    uint32_t pitch;
    //TODO: add more info, I can't type more on this fucking phone lul
} fbinfo_t
```

## Driver side

### Events
* framebuffer_request(uint FBID) -> fbinfo_t

## Client side
* get_fbinfo(uint FBID) -> fbinfo_t
