# the SOUL bootup process
1. the kernel gains execution
2. the kernel initializes the HAL
3. the kernel initializes the object manager
4. the kernel loads all drivers and firmware from the driver ramfs making copies of them
5. the kernel initializes all drivers
6. the kernel frees all initalizing memory including the originals of the drivers 
7. the kernel initializes the scheduler
8. the kernel sets up the asr32 startup code
9. the kernel starts the scheduler
10. asr32 starts all startup processes from the registery