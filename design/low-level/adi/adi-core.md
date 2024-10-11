# ADI Core 
This document details the core API and ABI of the ADI protocol.
## Function loading
All drivers get a pointer to the Core Function Region(CFR) as a global variable called `core`.
all functions are in `core`(e.g. "core->alloc(...)")
## Management API
* log
* error
* register_device
* unregister_device
## Memory API
* alloc
* free
* realloc